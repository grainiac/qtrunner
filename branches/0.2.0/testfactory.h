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
#ifndef TESTFACTORY_H
#define TESTFACTORY_H

#include "testtypes.h"
#include <QString>

class Test;

class TestFactory
{
public:
    TestFactory();
    ~TestFactory();

    Test* buildTest(TestType typeValue, QString name, QString filePathTest, QString filePathOutput);
    Test* transformTest(Test* sourceTest, TestType targetType);
};

#endif // TESTFACTORY_H
