/****************************************************************************
** $Id$
**
** This file is part of QTRunner.
**
** Copyright (C) Alex Skoruppa 2010
** All rights reserved.
**
** Base class for classes that represent a unit test.
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
#include "test.h"
#include <QtXml/QXmlStreamWriter>
#include <QFile>

Test::Test(QString name, QString filePathTest, QString filePathOutput)
:   m_name(name),
    m_executable(filePathTest),
    m_ouputfile(filePathOutput),
    m_state(TRS_PAUSED)
{    
}

void Test::save(QXmlStreamWriter* xml)
{
    xml->writeStartElement("Test");
    xml->writeTextElement("", "Type", testType2String(getTestType()));
    xml->writeTextElement("", "Name", getName());
    xml->writeTextElement("", "Executable", getTestFileName());
    xml->writeTextElement("", "Outputfile", getTestOutputFileName());
    xml->writeEndElement(); // Test
}

QString Test::testType2String(TestType type)
{
    switch(type)
    {
    case TT_GOOGLETEST:
        return "GoogleTest";
    case TT_QTESTLIB:
        return "QTestLib";
    default:
       return "NULL";
    }
}

TestType Test::string2TestType(QString type)
{
    if(type=="GoogleTest")
      return TT_GOOGLETEST;
    else if(type=="QTestLib")
      return TT_QTESTLIB;
    return TT_NULLTEST;
}


bool Test::execute()
{
    QString syscall=QString("%1 > %2").arg(getTestFileName())
                                      .arg(getLogFileName());

    qDebug(QString("Executing test with command: %1").arg(syscall).toStdString().c_str());
    qDebug(QString("TestType is set to %1. Starting test...").arg(testType2String(getTestType())).toStdString().c_str());

    setState(TRS_RUNNING);
    system( syscall.toStdString().c_str() );

    qDebug("...finished test execution.\n");

    bool success=checkLogFileIfTestWasSuccessfulAfterExecution();
    success ? setState(TRS_SUCCESS) : setState(TRS_FAILURE);

    return success;
}

QString Test::getLogFileName()
{
    return getTestFileName().left(getTestFileName().toUpper().lastIndexOf(".EXE"))+".log";
}

bool Test::checkLogFileIfTestWasSuccessfulAfterExecution()
{
    QFile file(getLogFileName());
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return false;

    QString document;
    while (!file.atEnd())
    {
        QByteArray line = file.readLine();
        document+=QString(file.readLine());
    }
    if(document.contains("FAIL") || document.contains("failure"))
        return false;
    return true;
}

QString Test::getName()
{
    return m_name;
}

QString Test::getTestFileName()
{
    return m_executable.replace("/","\\");
}

QString Test::getTestOutputFileName()
{
    return getTestFileName().left(getTestFileName().toUpper().lastIndexOf(".EXE"))+".log";
}
