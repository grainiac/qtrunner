/****************************************************************************
** $Id$
**
** This file is part of QTRunner.
**
** Copyright (C) Alex Skoruppa 2010
** All rights reserved.
**
** Unit Test for the Tests.
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
#include "../../test.h"
#include "../../googletest.h"
#include "../../qtestlibtest.h"

class TestTheTests : public QObject
{
    Q_OBJECT
private slots:
    void initTestCase();
    void cleanupTestCase();

    void testTheNullTest();
    void testTheGoogleTest();
    void testTheQTestLibTest();

private:
};

void TestTheTests::initTestCase()
{
}

void TestTheTests::cleanupTestCase()
{    
}

void TestTheTests::testTheNullTest()
{
    Test* null=new NullTest("","","");
    QVERIFY(null !=0);
    QVERIFY(null->getTestType() == TT_NULLTEST);
}

void TestTheTests::testTheGoogleTest()
{
    Test* null=new GoogleTest("Google", "c:\\test\\lala.exe", "");
    QVERIFY(null !=0);
    QVERIFY(null->getTestType() == TT_GOOGLETEST);
}

void TestTheTests::testTheQTestLibTest()
{
    Test* null=new QTestLibTest("QTestLib","c:\\qefqef.exe", "test.xml");
    QVERIFY(null !=0);
    QVERIFY(null->getTestType() == TT_QTESTLIB);
}

QTEST_MAIN(TestTheTests)
#include "TestTheTests.moc"

