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
#include "addtestdialog.h"
#include "ui_addtestdialog.h"

#include <QFileDialog>

AddTestDialog::AddTestDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::AddTestDialog)
{
    ui->setupUi(this);
    ui->radioButtonGoogle->setChecked(true);

    connect(ui->pushButtonSelectTest, SIGNAL(clicked()), this, SLOT(selectTestExecutable()));   
}

AddTestDialog::~AddTestDialog()
{
    delete ui;
}

void AddTestDialog::changeEvent(QEvent *e)
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

void AddTestDialog::selectTestExecutable()
{
    QString fileName = QFileDialog::getOpenFileName(this, tr("Select a test"),
                                                    "",
                                                    tr("Executables (*.exe)"));
    ui->lineEditTest->setText(fileName);
}

QString AddTestDialog::getTestName()
{
    return ui->lineEditTest->text();
}

TestType AddTestDialog::getTestType()
{
    if(ui->radioButtonQt->isChecked())
        return TT_QTESTLIB;
    return TT_GOOGLETEST;
}
