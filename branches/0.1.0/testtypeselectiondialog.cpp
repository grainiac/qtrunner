/****************************************************************************
** $Id$
**
** This file is part of QTRunner.
**
** Copyright (C) Alex Skoruppa 2010
** All rights reserved.
**
** A dialog for setting the type of a unit test.
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
#include "testtypeselectiondialog.h"
#include "ui_testtypeselectiondialog.h"

TestTypeSelectionDialog::TestTypeSelectionDialog(QWidget *parent, TestType defaultOption)
:   QDialog(parent),
    ui(new Ui::TestTypeSelectionDialog)
{
    ui->setupUi(this);

    if(defaultOption==TT_QTESTLIB)
        ui->radioButtonQt->setChecked(true);
    else
        ui->radioButtonGoogle->setChecked(true);
}

TestTypeSelectionDialog::~TestTypeSelectionDialog()
{
    delete ui;
}

TestType TestTypeSelectionDialog::getTestType()
{
    if(ui->radioButtonGoogle->isChecked())
        return TT_GOOGLETEST;
    return TT_QTESTLIB;
}

void TestTypeSelectionDialog::changeEvent(QEvent *e)
{
    QDialog::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}
