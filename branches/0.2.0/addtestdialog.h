/****************************************************************************
** $Id$
**
** This file is part of QTRunner.
**
** Copyright (C) Alex Skoruppa 2010
** All rights reserved.
**
** A dialog for adding a test executable to the test suite.
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
#ifndef ADDTESTDIALOG_H
#define ADDTESTDIALOG_H

#include <QDialog>
#include "testtypes.h"

namespace Ui {
    class AddTestDialog;
}

class AddTestDialog : public QDialog {
    Q_OBJECT
public:
    AddTestDialog(QWidget *parent = 0);
    ~AddTestDialog();

    QString getTestName();
    TestType getTestType();

public slots:
    void selectTestExecutable();

protected:
    void changeEvent(QEvent *e);

private:
    Ui::AddTestDialog *ui;
};

#endif // ADDTESTDIALOG_H
