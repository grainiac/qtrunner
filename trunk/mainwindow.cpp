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
#include "updatedialog.h"

#include <QtCore>
#include <QCloseEvent>
#include <QMessageBox>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QFileDialog>
#include <QNetworkRequest>
#include <QNetworkReply>
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
    _testSuite(testSuite),
    _check4Updates(true),
    _iconPaused(0),
    _iconRunnning(0),
    _iconSuccess(0),
    _iconFailure(0),
    _recentFilesMenu(0)
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

    // Recent files menu
    createRecentFilesMenu();

    // Files menu
    connect(ui->actionNew, SIGNAL(triggered()), this, SLOT(actionNewProject()));
    connect(ui->actionOpen_project, SIGNAL(triggered()), this, SLOT(actionOpenProject()));
    connect(ui->actionSave_project, SIGNAL(triggered()), this, SLOT(actionSave()));
    connect(ui->actionSave_project_as, SIGNAL(triggered()), this, SLOT(actionSaveAs()));

    // Help menu    
    connect(ui->actionAbout_QTRunner, SIGNAL(triggered()), this, SLOT(actionShowAbout()));
    connect(ui->actionCheck_for_updates, SIGNAL(triggered()), this, SLOT(actionCheck4Updates()));

    // Buttons in main widget
    connect(ui->pushButtonRunTestSuite, SIGNAL(clicked()), this, SLOT(runSuite()));
    connect(ui->pushButtonRunSingleTest, SIGNAL(clicked()), this, SLOT(runSingleTest()));
    connect(ui->pushButtonAddTest, SIGNAL(clicked()), this, SLOT(actionAddTest()));
    connect(ui->pushButtonRemoveTest, SIGNAL(clicked()), this, SLOT(actionRemoveTest()));
    connect(ui->pushButtonUp, SIGNAL(clicked()), this, SLOT(actionMoveUp()));
    connect(ui->pushButtonDown, SIGNAL(clicked()), this, SLOT(actionMoveDown()));
    connect(ui->pushButtonConfigureTest, SIGNAL(clicked()), this, SLOT(actionConfigureTest()));
    connect(ui->pushButtonResetResults, SIGNAL(clicked()), this, SLOT(actionResetResults()));

    // Events
    connect(ui->tableWidget, SIGNAL(cellClicked(int,int)), this, SLOT(tableItemSelected(int,int)));
    connect(ui->tableWidget, SIGNAL(cellDoubleClicked(int,int)), this, SLOT(tableItemSelected(int,int)));

    readSettings();

    m_apNetAccessMan=std::auto_ptr<QNetworkAccessManager>(new QNetworkAccessManager());
    connect(m_apNetAccessMan.get(), SIGNAL(finished(QNetworkReply*)), this, SLOT(check4Updates(QNetworkReply*)));
    if(_check4Updates)
        m_apNetAccessMan->get(QNetworkRequest(m_updateURL));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::closeEvent(QCloseEvent *event)
{
    if(_testSuite->hasChanged())
    {
        askUserIfProjectResetIsAllowed()
        ?   event->accept()
        :   event->ignore();
    }
    else
    {
        writeSettings();
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

void MainWindow::openRecentFile()
{
    QAction *action = qobject_cast<QAction *>(sender());
    if (action)
        openProjectFromRecentFiles(action->data().toString());
}

void MainWindow::createRecentFilesMenu()
{
    _recentFilesMenu=new QMenu(this);
    for (int i = 0; i < MaxRecentFiles; ++i)
    {
        _recentFileActs[i] = new QAction(this);
        _recentFileActs[i]->setVisible(false);
        _recentFilesMenu->addAction(_recentFileActs[i]);
        connect(_recentFileActs[i], SIGNAL(triggered()), this, SLOT(openRecentFile()));
    }
    ui->actionRecent_projects->setMenu(_recentFilesMenu);
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
        _testSuite->addTest(t);

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
    if(_testSuite->getSuiteFileName()=="")
    {
        if(_testSuite->hasChanged())
            this->setWindowTitle(QString("QTRunner - untitled*"));
        else
            this->setWindowTitle(QString("QTRunner - untitled"));
    }
    else
    {
        QFileInfo fi(_testSuite->getSuiteFileName());
        if(_testSuite->hasChanged())
            this->setWindowTitle(QString("QTRunner - %1*").arg(fi.fileName()));
        else
            this->setWindowTitle(QString("QTRunner - %1").arg(fi.fileName()));
    }
}

void MainWindow::updateInformativeTable()
{
    updateAllProgressControls(0,0);
}

void MainWindow::updateTestList()
{
    ui->tableWidget->clearContents();
    ui->tableWidget->setRowCount(_testSuite->testCount());

    for(int i=0; i<_testSuite->testCount();i++)
    {
        Test* test=_testSuite->getTest(i);
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

void MainWindow::updateAllProgressControls(int actualTestIndex, int errors)
{
    setPogressBar(actualTestIndex, _testSuite->testCount(), errors);
    setTestCounter(actualTestIndex, _testSuite->testCount());
    setOKCounter(actualTestIndex-errors);
    setNOKCounter(errors);    
}

void MainWindow::setPogressBar(int actualCount, int totalCount, bool error)
{
    QString styleSheetForErrors=QString("QProgressBar{border: 2px solid grey; border-radius: 5px;}")+
                                QString("QProgressBar::chunk{  background-color: #FF0000; width: 20px;}");

    QString styleSheetForSuccess=QString("QProgressBar{border: 2px solid grey; border-radius: 5px;}")+
                                 QString("QProgressBar::chunk{  background-color: #00FF00; width: 20px;}");

    error
    ?    ui->progressBar->setStyleSheet(styleSheetForErrors)
    :    ui->progressBar->setStyleSheet(styleSheetForSuccess);

    ui->progressBar->setRange(0, totalCount);
    ui->progressBar->setValue(actualCount);
}

void MainWindow::setTestCounter(int actualCount, int totalCount)
{
    ui->labelTestExecutableCounter->setText(QString("%1 of %2").arg(actualCount).arg(totalCount));
}

void MainWindow::setOKCounter(int count)
{
    ui->labelOKCount->setNum(count);
}

void MainWindow::setNOKCounter(int count)
{
    ui->labelNOKCount->setNum(count);
}

void MainWindow::runSuite()
{
    int errors=0;

    for(int i=0; i<_testSuite->testCount();i++)
    {        
        Test* test=_testSuite->getTest(i);

        test->setState(TRS_RUNNING);
        updateTestList(); // The test should now be marked as running in the table

        if(!test->execute())
            errors++;

        updateTestList(); // The test should now be marked either as succesful or failed
        updateAllProgressControls(i+1, errors);
    }
}

void MainWindow::runSingleTest()
{
    QList<QTableWidgetSelectionRange> ranges=ui->tableWidget->selectedRanges();
    if(ranges.count())
    {
        int testIndex=ranges.at(0).topRow();
        Test* test=_testSuite->getTest(testIndex);

        test->setState(TRS_RUNNING);
        updateTestList(); // The test should now be marked as running in the table
        bool success=test->execute();
        updateTestList(); // The test should now be marked either as succesful or failed

        setPogressBar(1, 1, !success);
        setTestCounter(1,1);
        setOKCounter(success);
        setNOKCounter(!success);

        ui->tableWidget->selectRow(testIndex);
        tableItemSelected(testIndex, 0); // select the test item after testrun again
    }
}

void MainWindow::actionRemoveTest()
{
    QList<QTableWidgetSelectionRange> ranges=ui->tableWidget->selectedRanges();
    if(ranges.count())
        _testSuite->removeTest(ranges.at(0).topRow());
    updateUserInterface();
}

void MainWindow::actionMoveUp()
{
    QList<QTableWidgetSelectionRange> ranges=ui->tableWidget->selectedRanges();
    if(ranges.count())
    {
        int index=ranges.at(0).topRow();
        if(index>0)
        {
            _testSuite->swapTests(index, index-1);
            updateUserInterface();
            ui->tableWidget->selectRow(index-1);
        }
    }
}

void MainWindow::actionMoveDown()
{
    QList<QTableWidgetSelectionRange> ranges=ui->tableWidget->selectedRanges();
    if(ranges.count())
    {
        int index=ranges.at(0).topRow();
        if(index<_testSuite->testCount()-1)
        {
            _testSuite->swapTests(index, index+1);
            updateUserInterface();
            ui->tableWidget->selectRow(index+1);
        }
    }
}

void MainWindow::actionConfigureTest()
{    
    QList<QTableWidgetSelectionRange> ranges=ui->tableWidget->selectedRanges();
    if(ranges.count())
    {
        Test* t=_testSuite->getTest(ranges.at(0).topRow());

        TestTypeSelectionDialog dlg(this, t->getTestType());
        dlg.setModal(true);
        if(dlg.exec()==QDialog::Accepted)
        {
            if(t->getTestType()!=dlg.getTestType())
            {
                _testSuite->updateTest(t, dlg.getTestType());
                updateUserInterface();
            }
        }
    }
}

void MainWindow::actionResetResults()
{
    _testSuite->resetSuiteTest();
    updateUserInterface();
}

void MainWindow::actionNewProject()
{
    resetProject();
}

void MainWindow::actionSave()
{
    if(_testSuite->getSuiteFileName()=="")
    {
        actionSaveAs();
    }
    else
    {
        _testSuite->saveSuite(_testSuite->getSuiteFileName());
        setCurrentFile(_testSuite->getSuiteFileName());
        updateUserInterface();
    }
}

void MainWindow::actionSaveAs()
{
    QString fileName=QFileDialog::getSaveFileName(this,
                                                  tr("Save project as"),
                                                  "",
                                                  tr("QTRunner Files")+" (*.qtr)");
    _testSuite->saveSuite(fileName);
    setCurrentFile(fileName);
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
            _testSuite->loadSuite(fileName);
            setCurrentFile(fileName);
            updateUserInterface();
        }
    }
}

void MainWindow::openProjectFromRecentFiles(const QString& fileName)
{
    if( canWeResetTheProject() )
    {
        resetProjectAndUpateUserInterface();
        _testSuite->loadSuite(fileName);
        setCurrentFile(fileName);
        updateUserInterface();
    }
}

void MainWindow::resetProject()
{
    if( canWeResetTheProject() )
        resetProjectAndUpateUserInterface();
}

bool MainWindow::canWeResetTheProject()
{
    if(!_testSuite->hasChanged() ||
       (_testSuite->hasChanged() && askUserIfProjectResetIsAllowed()) )
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
    _testSuite->removeAllTests();
    updateUserInterface();
}

TestFactory const * const MainWindow::testFactory()
{
    return _testSuite->getFactory();
}

void MainWindow::tableItemSelected(int iRow, int iCol)
{
    Test* t=_testSuite->getTest(iRow);
    QString fileName=t->getTestOutputFileName();
    loadLogFileInTextEdit(fileName);
}

void MainWindow::loadLogFileInTextEdit(const QString& fileName)
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
                 QString("<tr><td style=""vertical-align: top;"" colspan=""1"" rowspan=""11""><img src="":/images/images/QTRunner64.png"">")+
                 QString("<td colspan=""1"" rowspan=""1""><h1>QTRunner</h1></td></tr>")+
                 QString("<tr><td colspan=""1""></td></tr>")+
                 QString("<tr><td colspan=""1"">Version ")+QString(VERSION_STRING)+QString("</td></tr>")+
                 QString("<tr><td colspan=""1""></td></tr>")+
                 QString("<tr><td colspan=""1"">Copyright © 2010 Alex Skoruppa. All rights reserved.</td></tr>")+
                 QString("<tr><td colspan=""1""></td></tr>")+
                 QString("<tr><td colspan=""1"">QTRunner project @code.google:</td></tr>")+
                 QString("<tr><td colspan=""1""></td></tr>")+
                 QString("<tr><td colspan=""1""><a href=\"http://code.google.com/p/qtrunner/\">http://code.google.com/p/qtrunner/</td></tr>")+
                 QString("<tr><td colspan=""1""></td></tr>")+
                 QString("<tr><td colspan=""1"">The program is provided AS IS with NO WARRANTY OF ANY KIND, INCLUDING THE WARRANTY OF DESIGN, MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE.</td></tr>")+
                 QString("</tbody></table></body></html>");

    QMessageBox msgBox(this);
    msgBox.setStyleSheet("QMessageBox{background: qlineargradient(x1:0, y1:0, x2:0, y2:1, stop:0 gray, stop: 0.6 white)}");
    msgBox.addButton(QMessageBox::Ok);
    msgBox.setText(html);
    msgBox.exec();
}

void MainWindow::actionCheck4Updates()
{
    m_apNetAccessMan->get(QNetworkRequest(m_updateURL));
}

void MainWindow::check4Updates(QNetworkReply* reply)
{
    if ( reply->error() != QNetworkReply::NoError )
    {
        qDebug() << "Request failed, " << reply->errorString();
        return;
    }

    qDebug() << "Request succeeded";
    processCheck4UpdateResults( reply );
}

void MainWindow::processCheck4UpdateResults( QIODevice *source )
{
    QString strVersion;
    QString strDownload;
    QXmlStreamReader reader( source );
    while(!reader.atEnd())
    {
        QXmlStreamReader::TokenType tokenType = reader.readNext();
        if ( tokenType == QXmlStreamReader::StartElement )
        {
            if ( reader.name() == QString("Version") )
            {
                tokenType=reader.readNext();
                if(tokenType == QXmlStreamReader::Characters)
                {
                    strVersion=reader.text().toString();
                    qDebug() << strVersion;
                }
            }
            if ( reader.name() == QString("Download") )
            {
                tokenType=reader.readNext();
                if(tokenType == QXmlStreamReader::Characters)
                {
                    strDownload=reader.text().toString();
                    qDebug() << strDownload;
                }
            }
        }
    }

    UpdateDialog dlg(_check4Updates, this);
    if(strVersion==QString(VERSION_STRING))
    {
        QString strText =QString("<html><body><table style=""text-align: left; width: 100%;"" border=""0"" cellspacing=""10""><tbody>")+
                         QString("<tr><td colspan=""2""><b>You have the newest version of QTRunner!</b><(td></tr>")+
                         QString("<tr><td colspan=""2"">Version ")+QString(VERSION_STRING)+QString("</td></tr>")+
                         QString("</tbody></table></body></html>");

        dlg.setLabelText(strText);
    }
    else
    {
        QString strText =QString("<html><body><table style=""text-align: left; width: 100%;"" border=""0"" cellspacing=""10""><tbody>")+
                         QString("<tr><td colspan=""2""><b>There's a new version of QTRunner available!</b><(td></tr>")+
                         QString("<tr><td colspan=""2"">Your version: ")+QString(VERSION_STRING)+QString("</td></tr>")+
                         QString("<tr><td colspan=""2""><b>New version: ")+strVersion+QString("<b></td></tr>")+
                         QString("<tr><td colspan=""2"">You can download the new version by clicking on the link below:</td></tr>")+
                         QString("<tr><td colspan=""2""><a href=""")+strDownload+QString(""">")+strDownload+QString("</a></td></tr>")+
                         QString("</tbody></table></body></html>");

        dlg.setLabelText(strText);
    }
    dlg.exec();
    _check4Updates=dlg.getUpdateBoxState();
}

void MainWindow::setCurrentFile(const QString &fileName)
{
    QSettings settings("ASKsoft", "QTRunner");
    QStringList files = settings.value("recentFileList").toStringList();
    files.removeAll(fileName);
    files.prepend(fileName);
    while (files.size() > MaxRecentFiles)
        files.removeLast();

    settings.setValue("recentFileList", files);

    foreach (QWidget *widget, QApplication::topLevelWidgets())
    {
        MainWindow *mainWin = qobject_cast<MainWindow *>(widget);
        if (mainWin)
            mainWin->updateRecentFileActions();
    }
}

void MainWindow::updateRecentFileActions()
{
    QSettings settings("ASKsoft", "QTRunner");
    QStringList files = settings.value("recentFileList").toStringList();

    int numRecentFiles = qMin(files.size(), (int)MaxRecentFiles);

    for (int i = 0; i < numRecentFiles; ++i)
    {
        QString text = tr("&%1 %2").arg(i + 1).arg(strippedName(files[i]));
        QFile file(files[i]);
        if(file.exists())
        {
            _recentFileActs[i]->setText(text);
            _recentFileActs[i]->setData(files[i]);
            _recentFileActs[i]->setVisible(true);
        }
    }
    for (int j = numRecentFiles; j < MaxRecentFiles; ++j)
        _recentFileActs[j]->setVisible(false);
}

QString MainWindow::strippedName(const QString &fullFileName)
{
    return QFileInfo(fullFileName).fileName();
}

void MainWindow::readSettings()
{
    QSettings settings("ASKsoft", "QTRunner");    
    resize(settings.value("size", QSize(476, 595)).toSize());
    move(settings.value("pos", QPoint(200, 200)).toPoint());

    // URL to Update Server
    _check4Updates=settings.value("check_4_updates", true).toBool();
    m_updateURL=settings.value("update_server", QUrl("http://qtrunner.googlecode.com/files/QTRunnerUpdate.xml")).toUrl();

    updateRecentFileActions();
}

void MainWindow::writeSettings()
{
    QSettings settings("ASKsoft", "QTRunner");
    settings.setValue("pos", pos());
    settings.setValue("size", size());

    // save the update server url
    settings.setValue("check_4_updates", _check4Updates);
}
