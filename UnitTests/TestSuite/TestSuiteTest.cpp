/****************************************************************************
** $Id$
**
** This file is part of QTRunner.
**
** Copyright (C) Alex Skoruppa 2010
** All rights reserved.
**
** Unit Test for the TestSuite.
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
#include <QTest>
#include <QObject>
#include "../../testfactory.h"
#include "../../test.h"
#include "../../googletest.h"
#include "../../qtestlibtest.h"
#include "../../testsuite.h"

class TestSuiteTest : public QObject
{
    Q_OBJECT
private slots:
    void initTestCase();
    void cleanupTestCase();
    void testTheNullTest();
//    void testTheGoogleTest();
    void testTheQTestLibTest();
    void transformationTest();
    void suiteIsModified();
    void testPreviouslyInsertedTests();
    void insertItemAndThenDeleteItByIndex();
    void deleteTestSuite();
    void checkIfCreatedTestsWereAlsoDeletedByDestructor();

private:
    TestFactory* m_testFactory;
    TestSuite* m_testSuite;
    QList<Test*> m_tests;
};

void TestSuiteTest::initTestCase()
{
    m_testSuite=new TestSuite(m_testFactory);

    Test* googleTest=m_testFactory->buildTest(TT_GOOGLETEST,"GoogleTest","d:\e.exe","");
    m_testSuite->addTest(googleTest);
    QVERIFY(m_testSuite->testCount() == 1);
}

void TestSuiteTest::cleanupTestCase()
{
    delete m_testFactory;
    //delete m_testSuite; gets deleted in dtor test of TestSuite
}

void TestSuiteTest::suiteIsModified()
{
    QVERIFY(m_testSuite->hasChanged()==true);
}

void TestSuiteTest::testTheNullTest()
{
    Test* nullTest=m_testFactory->buildTest(TT_NULLTEST,"A","","");
    m_testSuite->addTest(nullTest);

    QVERIFY(m_testSuite->testCount() == 1);
}

void TestSuiteTest::testTheQTestLibTest()
{
    Test* qTestLib=m_testFactory->buildTest(TT_QTESTLIB,"QTestLib","f:\et3q.exe","");
    m_testSuite->addTest(qTestLib);

    QVERIFY(m_testSuite->testCount() == 2);

    transformationTest();
}

void TestSuiteTest::transformationTest()
{
    Test* test=m_testSuite->getTest(0);

    if(test->getTestType()== TT_QTESTLIB)
    {
        Test* transformed2GoogleTest=m_testSuite->updateTest(test, TT_GOOGLETEST);
        QVERIFY( transformed2GoogleTest->getTestType() == TT_GOOGLETEST );
    }
    else
    {
        Test* transformed2GoogleTest=m_testSuite->updateTest(test, TT_QTESTLIB);
        QVERIFY( transformed2GoogleTest->getTestType() == TT_QTESTLIB );
    }
}

void TestSuiteTest::testPreviouslyInsertedTests()
{
    Test* t=m_testSuite->getTest(0);
    QVERIFY(t->getTestType() == TT_GOOGLETEST);
    t=m_testSuite->getTest(1);
    QVERIFY(t->getTestType() == TT_QTESTLIB);
    t=m_testSuite->getTest(134); // Invalid index should always return NullTest
    QVERIFY(t->getTestType() == TT_NULLTEST);
    delete t;
    t=m_testSuite->getTest(-234); // Invalid index should always return NullTest
    QVERIFY(t->getTestType() == TT_NULLTEST);
    delete t;
}

void TestSuiteTest::insertItemAndThenDeleteItByIndex()
{    
    Test* googleTest=m_testFactory->buildTest(TT_GOOGLETEST,"GoogleTest","d:\e.exe","");

    int before=m_testSuite->testCount();
    m_testSuite->addTest(googleTest);
    m_testSuite->removeTest(before);
    int after=m_testSuite->testCount();

    QVERIFY(before == after);
}


void TestSuiteTest::TestSuiteTest::deleteTestSuite()
{
    delete m_testSuite;
}

void TestSuiteTest::checkIfCreatedTestsWereAlsoDeletedByDestructor()
{
    QList<Test*>::iterator it=m_tests.begin();
    for(; it!=m_tests.end(); it++)
        QVERIFY(*it==0);
}

QTEST_MAIN(TestSuiteTest)
#include "TestSuiteTest.moc"

