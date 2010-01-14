/****************************************************************************
** $Id$
**
** This file is part of QTRunner.
**
** Copyright (C) Alex Skoruppa 2010
** All rights reserved.
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
#include <QtGui/QApplication>
#include <memory>
#include "mainwindow.h"
#include "testsuite.h"
#include "testfactory.h"

int main(int argc, char *argv[])
{
    std::auto_ptr<TestFactory> factory=std::auto_ptr<TestFactory>(new TestFactory());
    std::auto_ptr<TestSuite> suite=std::auto_ptr<TestSuite>(new TestSuite(factory.get()));

    QApplication a(argc, argv);
    MainWindow w(suite.get());
    w.show();

    return a.exec();
}
