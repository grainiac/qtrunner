/****************************************************************************
** $Id$
**
** This file is part of QTRunner.
**
** Copyright (C) Alex Skoruppa 2010
** All rights reserved.
**
** A suite represents a collection of executable unit-tests.
**
** QTRunner is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** QTRunner is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with QTRunner.  If not, see <http://www.gnu.org/licenses/>.
**
****************************************************************************/
#include "testsuite.h"
#include "test.h"
#include "testfactory.h"

#include <QtXmlPatterns/QXmlQuery>
#include <QtXmlPatterns/QXmlResultItems>

TestSuite::TestSuite(TestFactory const * testFactory)
:   m_testFactory(testFactory),
    m_suiteChanged(false),
    m_suiteFileName("")
{
}

TestSuite::~TestSuite()
{
    removeAllTests();
}

TestFactory const * const TestSuite::getFactory()
{
    return m_testFactory;
}

QString TestSuite::getSuiteFileName()
{
    return m_suiteFileName;
}

void TestSuite::addTest(Test* test)
{
    if(test->getTestType()!=TT_NULLTEST)
    {
        m_tests.push_back(test);
        m_suiteChanged=true;
    }
}

Test* TestSuite::updateTest(Test* test, TestType newType)
{
    Test* newTest=const_cast<TestFactory*>(m_testFactory)->transformTest(test, newType);
    int index=m_tests.indexOf(test);
    m_tests.removeAt(index);
    m_tests.insert(index, newTest);
    delete test;
    m_suiteChanged=true;
    return newTest;
}

void TestSuite::removeTest(Test* test)
{
    int index=m_tests.indexOf(test);
    m_tests.removeAt(index);
    delete test;
    m_suiteChanged=true;
}

void TestSuite::removeTest(int index)
{
    for(int i=0; i<testCount(); i++)
    {
        if(i==index)
        {
            Test* t=m_tests.at(i);
            m_tests.removeAt(i);
            delete t;
            m_suiteChanged=true;
            return;
        }
    }
}

void TestSuite::removeAllTests()
{
    m_tests.clear();
    m_suiteChanged=false;
    m_suiteFileName="";
}

int TestSuite::testCount() const
{
    return m_tests.count();
}

Test* TestSuite::getTest(int index) const
{
    if(index>=0 && index<testCount())
    {
        if(!m_tests.at(index))
            return new NullTest("","",""); // retun NullTest if Test was deleted externally
        else
            return m_tests.at(index);
    }
    return new NullTest("","","");
}

void TestSuite::saveSuite(QString fileName)
{
    QFile file(fileName);
    file.open(QIODevice::WriteOnly);
    QDataStream out(&file);
    QString document=getSuiteXmlDocument();
    out.writeRawData(document.toStdString().c_str(), document.length());
    m_suiteChanged=false;
    m_suiteFileName=fileName;
}

QString TestSuite::getSuiteXmlDocument()
{
    QString document;
    QXmlStreamWriter xml(&document);
    xml.setAutoFormatting(true);
    xml.writeStartDocument();
    xml.writeStartElement("Suite");

        xml.writeStartElement("Common");
        xml.writeEndElement(); // Common

        xml.writeStartElement("Tests");
            addTestsToDocument(&xml);
        xml.writeEndElement(); // Tests

    xml.writeEndElement(); // Suite
    xml.writeEndDocument();
    return document;
}

void TestSuite::addTestsToDocument(QXmlStreamWriter* xml)
{
    for(int i=0; i<m_tests.count(); i++)
        m_tests.at(i)->save(xml);
}

void TestSuite::loadSuite(QString fileName)
{
    m_tests.clear();    

    QStringList types=extractAllTextElementsFromNodeExpressionInDocument(fileName,
                                                                         "/Suite/Tests/Test/Type/child::text()");
    QStringList names=extractAllTextElementsFromNodeExpressionInDocument(fileName,
                                                                         "/Suite/Tests/Test/Name/child::text()");
    QStringList exes=extractAllTextElementsFromNodeExpressionInDocument(fileName,
                                                                         "/Suite/Tests/Test/Executable/child::text()");
    QStringList xmls=extractAllTextElementsFromNodeExpressionInDocument(fileName,
                                                                         "/Suite/Tests/Test/Outputfile/child::text()");

    for(int i=0; i<types.count(); i++)
    {
        Test* t=const_cast<TestFactory*>(m_testFactory)->
                buildTest(Test::string2TestType(types.at(i)), names.at(i), exes.at(i), xmls.at(i));
        addTest(t);
    }
    m_suiteChanged=false;
    m_suiteFileName=fileName;
}

QStringList TestSuite::extractAllTextElementsFromNodeExpressionInDocument(QString fileName, QString searchExpression)
{
    QFile file(fileName);
    file.open(QIODevice::ReadOnly | QIODevice::Text);
    QXmlResultItems xmlItems;
    doXmlQueryOnFile(&file, searchExpression, &xmlItems);
    QStringList results=extractAllTextElementsFromXmlNode(&xmlItems);
    file.close();
    return results;
}

void TestSuite::doXmlQueryOnFile(QFile* fh, QString searchExpression, QXmlResultItems* xmlResultItems)
{
    QXmlQuery query;
    query.setFocus(fh);
    query.setQuery(searchExpression);
    query.evaluateTo(xmlResultItems);
}

QStringList TestSuite::extractAllTextElementsFromXmlNode(QXmlResultItems const * items)
{
    QStringList resultsAsString;
    extractTextElementFromXmlNode(items, &resultsAsString);
    return resultsAsString;
}

void TestSuite::extractTextElementFromXmlNode(QXmlResultItems const * items, QStringList const * extractHere)
{
    QXmlResultItems* xi=const_cast<QXmlResultItems*>(items);
    QXmlItem xmlItem(xi->next());
    while (!xmlItem.isNull())
    {
        if(xmlItem.isNode())
        {
            QXmlNodeModelIndex idx=xmlItem.toNodeModelIndex();
            const QAbstractXmlNodeModel* model=idx.model();
            const_cast<QStringList*>(extractHere)->push_back(model->stringValue(idx));
        }
        xmlItem = xi->next();
    }
}

bool TestSuite::hasChanged()
{
    return m_suiteChanged;
}

void TestSuite::resetSuiteTest()
{
    for(int i=0; i<m_tests.count(); i++)
    {
        m_tests.at(i)->setState(TRS_PAUSED);
        QFile file(m_tests.at(i)->getTestOutputFileName());
        if(file.exists())
            QFile::remove(m_tests.at(i)->getTestOutputFileName());
    }
}
