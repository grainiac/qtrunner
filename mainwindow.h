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

namespace Ui {
    class MainWindow;
}

class Test;
class TestSuite;
class TestFactory;

class MainWindow : public QMainWindow {
    Q_OBJECT
public:
    MainWindow(TestSuite* testSuite,               
               QWidget *parent = 0);
    ~MainWindow();

public slots:
    void actionNewProject();
    void actionOpenProject();
    void actionSave();
    void actionSaveAs();
    void actionShowAbout();
    void actionAddTest();
    void actionRemoveTest();
    void actionConfigureTest();
    void actionResetResults();

    void runSuite();

protected:
    void changeEvent(QEvent *e);
    void closeEvent(QCloseEvent *event);

private slots:
    void tableItemSelected(int iRow, int iCol);

private:
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
    void loadLogFileInTextEdit(QString fileName);

    TestFactory const * const testFactory();

    Ui::MainWindow *ui;
    TestSuite* m_testSuite;

    QIcon* m_iconPaused;
    QIcon* m_iconRunnning;
    QIcon* m_iconSuccess;
    QIcon* m_iconFailure;
};

#endif // MAINWINDOW_H
