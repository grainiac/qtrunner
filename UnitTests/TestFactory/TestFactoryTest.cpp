/****************************************************************************
** $Id$
**
** This file is part of QTRunner.
**
** Copyright (C) Alex Skoruppa 2010
** All rights reserved.
**
** Unit Test for TestFacory.
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
#include "../../googletest.h"
#include "../../qtestlibtest.h"

class TestFactoryTest : public QObject
{
    Q_OBJECT
private slots:
    void initTestCase();

    void buildTest();

    void cleanupTestCase();

private:
    TestFactory* m_factory;
};

void TestFactoryTest::initTestCase()
{
    m_factory=new TestFactory();
}

void TestFactoryTest::cleanupTestCase()
{
    delete m_factory;
}

void TestFactoryTest::buildTest()
{
    Test* t=m_factory->buildTest(TT_NULLTEST,"","","");
    Test* t2=m_factory->buildTest(TT_NULLTEST,"","","");

    qDebug(QString("%1").arg(t->getTestType()).toStdString().c_str());

    QVERIFY2(t->getTestType() == TT_NULLTEST, "Not a NullTest!");
    delete t;

    t=m_factory->buildTest(TT_GOOGLETEST, "MyFirstGoogleTest", "..\\UnitTests\\depp.exe", "test.xml");
    QVERIFY2(t->getTestType() == TT_GOOGLETEST, "Not a GoogleTest!");
    delete t;

    t=m_factory->buildTest(TT_QTESTLIB, "MyFirstQTestLibTest", "..\\UnitTests\\honz.exe", "test.xml");
    QVERIFY2(t->getTestType() == TT_QTESTLIB, "Not a QTestLibTest!");
    delete t;

    delete t2;
}

QTEST_MAIN(TestFactoryTest)
#include "TestFactoryTest.moc"

