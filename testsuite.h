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
#ifndef TESTSUITE_H
#define TESTSUITE_H

#include <QtCore>

class Test;
class TestFactory;
class QXmlResultItems;

class TestSuite
{
public:
    TestSuite(TestFactory const * const testFactory);
    ~TestSuite();

    TestFactory const * const getFactory();

    void addTest(Test* test);
    void removeTest(Test* test);
    void removeTest(int index);
    void removeAllTests();

    int testCount() const;
    Test* getTest(int index) const;

    void saveSuite(QString fileName);
    void loadSuite(QString fileName);
    void resetSuiteTest();

    bool hasChanged();
    QString getSuiteFileName();

private:
    QString getSuiteXmlDocument();
    void addTestsToDocument(QXmlStreamWriter* xml);    
    QStringList extractAllTextElementsFromNodeExpressionInDocument(QString fileName, QString searchExpression);
    void doXmlQueryOnFile(QFile* fh, QString searchExpression, QXmlResultItems* xmlResultItems);
    QStringList extractAllTextElementsFromXmlNode(QXmlResultItems const * items);
    void extractTextElementFromXmlNode(QXmlResultItems const * items, QStringList const * extractHere);

    TestFactory const * const m_testFactory;
    QList<Test*> m_tests;
    bool m_suiteChanged;
    QString m_suiteFileName;
};

#endif // TESTSUITE_H
