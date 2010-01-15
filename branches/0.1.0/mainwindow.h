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
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QUrl>
#include <memory>

namespace Ui {
    class MainWindow;
}

class Test;
class TestSuite;
class TestFactory;
class QNetworkAccessManager;
class QNetworkReply;

class MainWindow : public QMainWindow
{
    Q_OBJECT
public:
    MainWindow(TestSuite* testSuite, QWidget *parent = 0);
    ~MainWindow();

public slots:
    void actionNewProject();
    void actionOpenProject();
    void actionSave();
    void actionSaveAs();
    void actionShowAbout();
    void actionCheck4Updates();
    void actionAddTest();
    void actionRemoveTest();
    void actionConfigureTest();
    void actionResetResults();

    void runSuite();

protected:
    void changeEvent(QEvent *e);
    void closeEvent(QCloseEvent *event);

private slots:
    void check4Updates(QNetworkReply* pReply);
    void openRecentFile();
    void tableItemSelected(int iRow, int iCol);

private:
    void openProjectFromRecentFiles(const QString& fileName);
    void createRecentFilesMenu();
    void readSettings();
    void writeSettings();
    void processCheck4UpdateResults( QIODevice *source );
    void updateUserInterface();
    void updateWindowTitle();
    void updateInformativeTable();
    void updateProgressLabels(int actualTestIndex, int errors);
    void updateTestList();
    void setStateIconInTableRow(Test* test, int row);
    void setTypeIconInTableRow(Test* test, int row);
    void setTestNameInTableRow(Test* test, int row);
    void resetProject();
    void resetProjectAndUpateUserInterface();
    bool canWeResetTheProject();
    bool askUserIfProjectResetIsAllowed();
    void loadLogFileInTextEdit(const QString& fileName);
    void setCurrentFile(const QString &fileName);
    void updateRecentFileActions();
    QString strippedName(const QString &fullFileName);

    TestFactory const * const testFactory();
    Ui::MainWindow *ui;
    TestSuite* _testSuite;
    bool _check4Updates;
    QUrl m_updateURL;
    std::auto_ptr<QNetworkAccessManager> m_apNetAccessMan;
    QIcon* _iconPaused;
    QIcon* _iconRunnning;
    QIcon* _iconSuccess;
    QIcon* _iconFailure;
    enum { MaxRecentFiles = 5 };
    QAction* _recentFileActs[MaxRecentFiles];
    QMenu* _recentFilesMenu;
};

#endif // MAINWINDOW_H
