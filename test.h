/****************************************************************************
** $Id$
**
** This file is part of QTRunner.
**
** Copyright (C) Alex Skoruppa 2010
** All rights reserved.
**
** Base class for classes that represent a unit test.
** The NullTest class will be returned by the factory e.g. if something goes
** wrong during the construction of an object whose class is derived from Test.
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
#ifndef TEST_H
#define TEST_H

#include <QString>
#include "testtypes.h"

class QXmlStreamWriter;

enum TestRunState
{
    TRS_PAUSED,
    TRS_RUNNING,
    TRS_SUCCESS,
    TRS_FAILURE,
};

class Test
{
public:
    Test(QString name, QString filePathTest, QString filePathOutput);
    virtual ~Test() {};

    static QString testType2String(TestType type);
    static TestType string2TestType(QString type);

    virtual TestType getTestType() = 0;
    virtual bool execute();    

    virtual QString getName();
    virtual QString getTestFileName();
    virtual QString getTestOutputFileName();

    virtual void save(QXmlStreamWriter* xml);

    void setState(TestRunState state) { m_state=state; }
    TestRunState getState() { return m_state; }

private:        
    QString getLogFileName();
    bool checkLogFileIfTestWasSuccessfulAfterExecution();

    QString m_name;
    QString m_executable;
    QString m_ouputfile;

    TestRunState m_state;
};

class NullTest : public Test
{
public:
    NullTest(QString name, QString filePathTest, QString filePathOutput) : Test("", "", ""){}
    virtual ~NullTest(){}    
    virtual TestType getTestType() { return TT_NULLTEST; }
    virtual bool testExecutedWithSuccess() { return false; }
};

#endif // TEST_H
