/****************************************************************************
** $Id$
**
** This file is part of QTRunner.
**
** Copyright (C) Alex Skoruppa 2010
** All rights reserved.
**
** This factory builds the Test-Objects for the TestSuite.
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
#include "testfactory.h"
#include "test.h"
#include "googletest.h"
#include "qtestlibtest.h"

TestFactory::TestFactory()
{
}

TestFactory::~TestFactory()
{
}

Test* TestFactory::buildTest(TestType typeValue, QString name, QString filePathTest, QString filePathOutput)
{
    Test* t=0;
    switch(typeValue)
    {
    case TT_NULLTEST:
        t=new NullTest("","","");
        break;
    case TT_GOOGLETEST:
        t=new GoogleTest(name, filePathTest, filePathOutput);
        break;
    case TT_QTESTLIB:
        t=new QTestLibTest(name, filePathTest, filePathOutput);
        break;
    }
    if(!t)
        return new NullTest("","","");
    return t;
}

Test* TestFactory::transformTest(Test* sourceTest, TestType targetType)
{
    return buildTest(targetType, sourceTest->getName(), sourceTest->getTestFileName(), sourceTest->getTestOutputFileName());
}
