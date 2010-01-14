/****************************************************************************
** $Id$
**
** This file is part of QTRunner.
**
** Copyright (C) Alex Skoruppa 2010
** All rights reserved.
**
** Main application window of QTRunner.
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
#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QtCore>
#include <QCloseEvent>
#include <QMessageBox>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QFileDialog>
#include "addtestdialog.h"
#include "testtypeselectiondialog.h"
#include "testsuite.h"
#include "testfactory.h"
#include "test.h"
#include "version.h"
#include <windows.h>

MainWindow::MainWindow(TestSuite *testSuite, QWidget *parent)
:   QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_testSuite(testSuite),    
    m_iconPaused(0),
    m_iconRunnning(0),
    m_iconSuccess(0),
    m_iconFailure(0)
{
    ui->setupUi(this);

    ui->tableWidget->setColumnCount(3);
    ui->tableWidget->setCornerButtonEnabled(false);
    ui->tableWidget->setShowGrid(false);
    ui->tableWidget->setHorizontalHeaderItem(0, new QTableWidgetItem(tr("S")));
    ui->tableWidget->setHorizontalHeaderItem(1, new QTableWidgetItem(tr("T")));
    ui->tableWidget->setHorizontalHeaderItem(2, new QTableWidgetItem(tr("Name")));

    ui->tableWidget->setColumnWidth(0,24);
    ui->tableWidget->setColumnWidth(1,24);
    ui->tableWidget->setColumnWidth(2,235);

    updateInformativeTable();

    this->setWindowTitle("QTRunner - <untitled>");

    // Files menu
    connect(ui->actionNew, SIGNAL(triggered()), this, SLOT(actionNewProject()));
    connect(ui->actionOpen_project, SIGNAL(triggered()), this, SLOT(actionOpenProject()));
    connect(ui->actionSave_project, SIGNAL(triggered()), this, SLOT(actionSave()));
    connect(ui->actionSave_project_as, SIGNAL(triggered()), this, SLOT(actionSaveAs()));

    // Help menu
    connect(ui->pushButtonRunTestSuite, SIGNAL(clicked()), this, SLOT(runSuite()));
    connect(ui->actionAbout_QTRunner, SIGNAL(triggered()), this, SLOT(actionShowAbout()));    

    // Buttons in main widget
    connect(ui->pushButtonAddTest, SIGNAL(clicked()), this, SLOT(actionAddTest()));
    connect(ui->pushButtonRemoveTest, SIGNAL(clicked()), this, SLOT(actionRemoveTest()));
    connect(ui->pushButtonConfigureTest, SIGNAL(clicked()), this, SLOT(actionConfigureTest()));
    connect(ui->pushButtonResetResults, SIGNAL(clicked()), this, SLOT(actionResetResults()));

    // Events
    connect(ui->tableWidget, SIGNAL(cellClicked(int,int)), this, SLOT(tableItemSelected(int,int)));
    connect(ui->tableWidget, SIGNAL(cellDoubleClicked(int,int)), this, SLOT(tableItemSelected(int,int)));    
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(m_testSuite->hasChanged())
    {
        askUserIfProjectResetIsAllowed()
        ?   event->accept()
        :   event->ignore();
    }
    else
    {
        event->accept();
    }
}

void MainWindow::changeEvent(QEvent *e)
{
    QMainWindow::changeEvent(e);
    switch (e->type()) {
    case QEvent::LanguageChange:
        ui->retranslateUi(this);
        break;
    default:
        break;
    }
}

void MainWindow::actionAddTest()
{
    AddTestDialog dlg(this);
    dlg.setModal(true);
    if(dlg.exec()==QDialog::Accepted)
    {
        QString name=QFileInfo(dlg.getTestName()).fileName();
        name=name.left(name.toUpper().lastIndexOf(".EXE"));

        Test* t = const_cast<TestFactory*>(testFactory())->buildTest(dlg.getTestType(),
                                           name,
                                           dlg.getTestName(),
                                           "");
        m_testSuite->addTest(t);

        updateUserInterface();
    }
}

void MainWindow::updateUserInterface()
{
    updateWindowTitle();
    updateInformativeTable();
    updateTestList();
    ui->textEdit->setText("");
}

void MainWindow::updateWindowTitle()
{    
    if(m_testSuite->getSuiteFileName()=="")
    {
        if(m_testSuite->hasChanged())
            this->setWindowTitle(QString("QTRunner - untitled*"));
        else
            this->setWindowTitle(QString("QTRunner - untitled"));
    }
    else
    {
        QFileInfo fi(m_testSuite->getSuiteFileName());
        if(m_testSuite->hasChanged())
            this->setWindowTitle(QString("QTRunner - %1*").arg(fi.fileName()));
        else
            this->setWindowTitle(QString("QTRunner - %1").arg(fi.fileName()));
    }
}

void MainWindow::updateInformativeTable()
{
    updateProgressLabels(0,0);
    ui->labelOKCount->setNum(0);
    ui->labelNOKCount->setNum(0);    
}
void MainWindow::updateTestList()
{
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(m_testSuite->testCount());

    for(int i=0; i<m_testSuite->testCount();i++)
    {
        Test* test=m_testSuite->getTest(i);
        setStateIconInTableRow(test, i);
        setTypeIconInTableRow(test, i);
        setTestNameInTableRow(test, i);
    }
}

void MainWindow::setStateIconInTableRow(Test* test, int row)
{
    if(test->getState()==TRS_PAUSED)
        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(QIcon(QPixmap(":/images/images/state_paused.png")),""));
    if(test->getState()==TRS_RUNNING)
        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(QIcon(QPixmap(":/images/images/state_running.png")),""));
    if(test->getState()==TRS_SUCCESS)
        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(QIcon(QPixmap(":/images/images/state_success.png")),""));
    if(test->getState()==TRS_FAILURE)
        ui->tableWidget->setItem(row, 0, new QTableWidgetItem(QIcon(QPixmap(":/images/images/state_failed.png")),""));
}

void MainWindow::setTypeIconInTableRow(Test* test, int row)
{
    test->getTestType()==TT_GOOGLETEST
    ?   ui->tableWidget->setItem(row, 1, new QTableWidgetItem(QIcon(QPixmap(":/images/images/google-logo.png")),""))
    :   ui->tableWidget->setItem(row, 1, new QTableWidgetItem(QIcon(QPixmap(":/images/images/qt_green34.png")),""));
}

void MainWindow::setTestNameInTableRow(Test* test, int row)
{
    ui->tableWidget->setItem(row, 2, new QTableWidgetItem(test->getName()));
}

void MainWindow::updateProgressLabels(int actualTestIndex, int errors)
{
    ui->labelTestExecutableCounter->setText(QString("%1 of %2").arg(actualTestIndex).arg(m_testSuite->testCount()));
    ui->labelOKCount->setText(QString("%1").arg(actualTestIndex-errors));
    ui->labelNOKCount->setText(QString("%1").arg(errors));


    QString styleSheetForErrors=QString("QProgressBar{border: 2px solid grey; border-radius: 5px;}")+
                                QString("QProgressBar::chunk{  background-color: #FF0000; width: 20px;}");

    QString styleSheetForSuccess=QString("QProgressBar{border: 2px solid grey; border-radius: 5px;}")+
                                 QString("QProgressBar::chunk{  background-color: #00FF00; width: 20px;}");

    (errors > 0)
    ?    ui->progressBar->setStyleSheet(styleSheetForErrors)
    :    ui->progressBar->setStyleSheet(styleSheetForSuccess);

    ui->progressBar->setRange(0,m_testSuite->testCount());
    ui->progressBar->setValue(actualTestIndex);
}

void MainWindow::runSuite()
{
    int errors=0;

    for(int i=0; i<m_testSuite->testCount();i++)
    {        
        Test* test=m_testSuite->getTest(i);

        test->setState(TRS_RUNNING);
        updateTestList(); // The test should now be marked as running in the table

        if(!test->execute())
            errors++;

        updateTestList(); // The test should now be marked either as succesful or failed
        updateProgressLabels(i+1, errors);
    }
}

void MainWindow::actionRemoveTest()
{
    QList<QTableWidgetSelectionRange> ranges=ui->tableWidget->selectedRanges();
    if(ranges.count())
        m_testSuite->removeTest(ranges.at(0).topRow());
    updateUserInterface();
}

void MainWindow::actionConfigureTest()
{    
    TestTypeSelectionDialog dlg(this, TestTypeSelectionDialog::TT_GOOGLETEST);
    dlg.setModal(true);
    if(dlg.exec()==QDialog::Accepted)
    {
    }
}

void MainWindow::actionResetResults()
{
    m_testSuite->resetSuiteTest();
    updateUserInterface();
}

void MainWindow::actionNewProject()
{
    resetProject();
}

void MainWindow::actionSave()
{
    if(m_testSuite->getSuiteFileName()=="")
    {
        actionSaveAs();
    }
    else
    {
        m_testSuite->saveSuite(m_testSuite->getSuiteFileName());
        updateUserInterface();
    }
}

void MainWindow::actionSaveAs()
{
    QString fileName=QFileDialog::getSaveFileName(this,
                                                  tr("Save project as"),
                                                  "",
                                                  tr("QTRunner Files")+" (*.qtr)");
    m_testSuite->saveSuite(fileName);
    updateUserInterface();
}

void MainWindow::actionOpenProject()
{
    if( canWeResetTheProject() )
    {
        QString fileName=QFileDialog::getOpenFileName(this,
                                                      tr("Open project"),
                                                      "",
                                                      tr("QTRunner Files")+" (*.qtr)");
        if(fileName.length()>0)
        {
            resetProjectAndUpateUserInterface();
            m_testSuite->loadSuite(fileName);
            updateUserInterface();
            QFileInfo fi(fileName);
        }
    }
}

void MainWindow::resetProject()
{
    if( canWeResetTheProject() )
        resetProjectAndUpateUserInterface();
}

bool MainWindow::canWeResetTheProject()
{
    if(!m_testSuite->hasChanged() ||
       (m_testSuite->hasChanged() && askUserIfProjectResetIsAllowed()) )
        return true;
    return false;
}

bool MainWindow::askUserIfProjectResetIsAllowed()
{
    QMessageBox mb(QMessageBox::Warning,
                   tr("Warning"),
                   tr("Project has been modified, if you continue without saving all changes will be lost! Continue?"),
                   QMessageBox::Yes | QMessageBox::Cancel);
    if(mb.exec()==QMessageBox::Yes)
        return true;
    return false;
}

void MainWindow::resetProjectAndUpateUserInterface()
{
    m_testSuite->removeAllTests();
    updateUserInterface();
}

TestFactory const * const MainWindow::testFactory()
{
    return m_testSuite->getFactory();
}

void MainWindow::tableItemSelected(int iRow, int iCol)
{
    Test* t=m_testSuite->getTest(iRow);
    QString fileName=t->getTestOutputFileName();
    loadLogFileInTextEdit(fileName);
}

void MainWindow::loadLogFileInTextEdit(QString fileName)
{
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        ui->textEdit->setText("ERROR: Can't open the log file! Maybe you need to run the test first?");
        return;
    }

    QString document;
    while (!file.atEnd())
    {
        QByteArray line = file.readLine();
        document+=QString(file.readLine());
    }
    ui->textEdit->setText(document);
}

void MainWindow::actionShowAbout()
{
    QString html=QString("<html><body><table table style=""text-align: left; width: 100%;"" border=""0""> <tbody>")+
                 QString("<tr><td style=""vertical-align: top;"" colspan=""1"" rowspan=""9""><img src="":/images/images/QTRunner64.png"">")+
                 QString("<td colspan=""1"" rowspan=""1""><h1>QTRunner</h1></td></tr>")+
                 QString("<tr><td colspan=""1""></td></tr>")+
                 QString("<tr><td colspan=""1"">Version ")+QString(VERSION_STRING)+QString("</td></tr>")+
                 QString("<tr><td colspan=""1""></td></tr>")+
                 QString("<tr><td colspan=""1"">Copyright © 2010 Alex Skoruppa. All rights reserved.</td></tr>")+
                 QString("<tr><td colspan=""1""></td></tr>")+
                 QString("<tr><td colspan=""1"">QTRunner project @code.google:</td></tr>")+
                 QString("<tr><td colspan=""1""></td></tr>")+
                 QString("<tr><td colspan=""1"">The program is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.</td></tr>")+
                 QString("</tbody></table></body></html>");

    QMessageBox msgBox(this);
    msgBox.setStyleSheet("QMessageBox{background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 gray, stop: 0.6 white)}");
    msgBox.addButton(QMessageBox::Ok);
    msgBox.setText(html);
    msgBox.exec();
}
