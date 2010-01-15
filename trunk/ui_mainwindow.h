/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Fri 15. Jan 00:04:47 2010
**      by: Qt User Interface Compiler version 4.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFormLayout>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QProgressBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSplitter>
#include <QtGui/QTableWidget>
#include <QtGui/QTextEdit>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionNew;
    QAction *actionOpen_project;
    QAction *actionSave_project;
    QAction *actionSave_project_as;
    QAction *actionQuit;
    QAction *actionAbout_QTRunner;
    QAction *actionCheck_for_updates;
    QAction *actionUsed_Qt_version;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_2;
    QPushButton *pushButtonRunTestSuite;
    QFormLayout *formLayout;
    QLabel *labelTests;
    QLabel *labelTestExecutableCounter;
    QLabel *labelOk;
    QLabel *labelOKCount;
    QLabel *labelNOK;
    QLabel *labelNOKCount;
    QProgressBar *progressBar;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout;
    QSplitter *splitter;
    QTableWidget *tableWidget;
    QTextEdit *textEdit;
    QVBoxLayout *verticalLayout;
    QPushButton *pushButtonAddTest;
    QPushButton *pushButtonRemoveTest;
    QSpacerItem *verticalSpacer_2;
    QPushButton *pushButtonConfigureTest;
    QPushButton *pushButtonResetResults;
    QMenuBar *menuBar;
    QMenu *menuFiles;
    QMenu *menuHelp;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(402, 527);
        MainWindow->setWindowTitle(QString::fromUtf8("QTRunner"));
        actionNew = new QAction(MainWindow);
        actionNew->setObjectName(QString::fromUtf8("actionNew"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/images/filenew.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionNew->setIcon(icon);
        actionOpen_project = new QAction(MainWindow);
        actionOpen_project->setObjectName(QString::fromUtf8("actionOpen_project"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/images/fileopen.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionOpen_project->setIcon(icon1);
        actionSave_project = new QAction(MainWindow);
        actionSave_project->setObjectName(QString::fromUtf8("actionSave_project"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/images/images/filesave.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave_project->setIcon(icon2);
        actionSave_project_as = new QAction(MainWindow);
        actionSave_project_as->setObjectName(QString::fromUtf8("actionSave_project_as"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/images/images/filesaveas.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionSave_project_as->setIcon(icon3);
        actionQuit = new QAction(MainWindow);
        actionQuit->setObjectName(QString::fromUtf8("actionQuit"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/images/images/exit.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionQuit->setIcon(icon4);
        actionQuit->setShortcutContext(Qt::ApplicationShortcut);
        actionAbout_QTRunner = new QAction(MainWindow);
        actionAbout_QTRunner->setObjectName(QString::fromUtf8("actionAbout_QTRunner"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/images/images/QTRunner.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionAbout_QTRunner->setIcon(icon5);
        actionCheck_for_updates = new QAction(MainWindow);
        actionCheck_for_updates->setObjectName(QString::fromUtf8("actionCheck_for_updates"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/images/images/globe.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionCheck_for_updates->setIcon(icon6);
        actionUsed_Qt_version = new QAction(MainWindow);
        actionUsed_Qt_version->setObjectName(QString::fromUtf8("actionUsed_Qt_version"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/images/images/qt.png"), QSize(), QIcon::Normal, QIcon::Off);
        actionUsed_Qt_version->setIcon(icon7);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        pushButtonRunTestSuite = new QPushButton(centralWidget);
        pushButtonRunTestSuite->setObjectName(QString::fromUtf8("pushButtonRunTestSuite"));

        verticalLayout_2->addWidget(pushButtonRunTestSuite);

        formLayout = new QFormLayout();
        formLayout->setSpacing(6);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        formLayout->setFieldGrowthPolicy(QFormLayout::AllNonFixedFieldsGrow);
        labelTests = new QLabel(centralWidget);
        labelTests->setObjectName(QString::fromUtf8("labelTests"));

        formLayout->setWidget(0, QFormLayout::LabelRole, labelTests);

        labelTestExecutableCounter = new QLabel(centralWidget);
        labelTestExecutableCounter->setObjectName(QString::fromUtf8("labelTestExecutableCounter"));
        labelTestExecutableCounter->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout->setWidget(0, QFormLayout::FieldRole, labelTestExecutableCounter);

        labelOk = new QLabel(centralWidget);
        labelOk->setObjectName(QString::fromUtf8("labelOk"));

        formLayout->setWidget(1, QFormLayout::LabelRole, labelOk);

        labelOKCount = new QLabel(centralWidget);
        labelOKCount->setObjectName(QString::fromUtf8("labelOKCount"));
        labelOKCount->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout->setWidget(1, QFormLayout::FieldRole, labelOKCount);

        labelNOK = new QLabel(centralWidget);
        labelNOK->setObjectName(QString::fromUtf8("labelNOK"));

        formLayout->setWidget(2, QFormLayout::LabelRole, labelNOK);

        labelNOKCount = new QLabel(centralWidget);
        labelNOKCount->setObjectName(QString::fromUtf8("labelNOKCount"));
        labelNOKCount->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        formLayout->setWidget(2, QFormLayout::FieldRole, labelNOKCount);


        verticalLayout_2->addLayout(formLayout);

        progressBar = new QProgressBar(centralWidget);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setValue(0);
        progressBar->setTextVisible(false);
        progressBar->setFormat(QString::fromUtf8(""));

        verticalLayout_2->addWidget(progressBar);

        verticalSpacer = new QSpacerItem(20, 15, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_2->addItem(verticalSpacer);


        gridLayout->addLayout(verticalLayout_2, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        splitter = new QSplitter(centralWidget);
        splitter->setObjectName(QString::fromUtf8("splitter"));
        splitter->setOrientation(Qt::Vertical);
        tableWidget = new QTableWidget(splitter);
        tableWidget->setObjectName(QString::fromUtf8("tableWidget"));
        tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        tableWidget->setSelectionMode(QAbstractItemView::SingleSelection);
        tableWidget->setSelectionBehavior(QAbstractItemView::SelectRows);
        tableWidget->setShowGrid(false);
        splitter->addWidget(tableWidget);
        tableWidget->horizontalHeader()->setVisible(false);
        tableWidget->horizontalHeader()->setCascadingSectionResizes(false);
        tableWidget->horizontalHeader()->setHighlightSections(false);
        textEdit = new QTextEdit(splitter);
        textEdit->setObjectName(QString::fromUtf8("textEdit"));
        textEdit->setReadOnly(true);
        splitter->addWidget(textEdit);

        horizontalLayout->addWidget(splitter);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        pushButtonAddTest = new QPushButton(centralWidget);
        pushButtonAddTest->setObjectName(QString::fromUtf8("pushButtonAddTest"));
        pushButtonAddTest->setMinimumSize(QSize(128, 28));
        pushButtonAddTest->setMaximumSize(QSize(120, 28));

        verticalLayout->addWidget(pushButtonAddTest);

        pushButtonRemoveTest = new QPushButton(centralWidget);
        pushButtonRemoveTest->setObjectName(QString::fromUtf8("pushButtonRemoveTest"));
        pushButtonRemoveTest->setMinimumSize(QSize(128, 28));
        pushButtonRemoveTest->setMaximumSize(QSize(120, 28));

        verticalLayout->addWidget(pushButtonRemoveTest);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);

        pushButtonConfigureTest = new QPushButton(centralWidget);
        pushButtonConfigureTest->setObjectName(QString::fromUtf8("pushButtonConfigureTest"));
        pushButtonConfigureTest->setMinimumSize(QSize(128, 28));
        pushButtonConfigureTest->setMaximumSize(QSize(120, 28));

        verticalLayout->addWidget(pushButtonConfigureTest);

        pushButtonResetResults = new QPushButton(centralWidget);
        pushButtonResetResults->setObjectName(QString::fromUtf8("pushButtonResetResults"));
        pushButtonResetResults->setMinimumSize(QSize(128, 28));
        pushButtonResetResults->setMaximumSize(QSize(120, 28));

        verticalLayout->addWidget(pushButtonResetResults);


        horizontalLayout->addLayout(verticalLayout);


        gridLayout->addLayout(horizontalLayout, 1, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 402, 21));
        menuFiles = new QMenu(menuBar);
        menuFiles->setObjectName(QString::fromUtf8("menuFiles"));
        menuHelp = new QMenu(menuBar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        MainWindow->setMenuBar(menuBar);

        menuBar->addAction(menuFiles->menuAction());
        menuBar->addAction(menuHelp->menuAction());
        menuFiles->addAction(actionNew);
        menuFiles->addAction(actionOpen_project);
        menuFiles->addSeparator();
        menuFiles->addAction(actionSave_project);
        menuFiles->addAction(actionSave_project_as);
        menuFiles->addSeparator();
        menuFiles->addAction(actionQuit);
        menuHelp->addAction(actionAbout_QTRunner);
        menuHelp->addSeparator();
        menuHelp->addAction(actionCheck_for_updates);

        retranslateUi(MainWindow);
        QObject::connect(actionQuit, SIGNAL(triggered()), MainWindow, SLOT(close()));

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        actionNew->setText(QApplication::translate("MainWindow", "New project", 0, QApplication::UnicodeUTF8));
        actionOpen_project->setText(QApplication::translate("MainWindow", "Open project...", 0, QApplication::UnicodeUTF8));
        actionSave_project->setText(QApplication::translate("MainWindow", "Save project", 0, QApplication::UnicodeUTF8));
        actionSave_project_as->setText(QApplication::translate("MainWindow", "Save project as...", 0, QApplication::UnicodeUTF8));
        actionQuit->setText(QApplication::translate("MainWindow", "Quit", 0, QApplication::UnicodeUTF8));
        actionQuit->setShortcut(QApplication::translate("MainWindow", "Alt+F4", 0, QApplication::UnicodeUTF8));
        actionAbout_QTRunner->setText(QApplication::translate("MainWindow", "About QTRunner...", 0, QApplication::UnicodeUTF8));
        actionCheck_for_updates->setText(QApplication::translate("MainWindow", "Check for updates...", 0, QApplication::UnicodeUTF8));
        actionUsed_Qt_version->setText(QApplication::translate("MainWindow", "Used Qt version...", 0, QApplication::UnicodeUTF8));
        pushButtonRunTestSuite->setText(QApplication::translate("MainWindow", "Run test suite!", 0, QApplication::UnicodeUTF8));
        labelTests->setText(QApplication::translate("MainWindow", "Tests executed:", 0, QApplication::UnicodeUTF8));
        labelTestExecutableCounter->setText(QApplication::translate("MainWindow", "2 of 10", 0, QApplication::UnicodeUTF8));
        labelOk->setText(QApplication::translate("MainWindow", "Tests without error:", 0, QApplication::UnicodeUTF8));
        labelOKCount->setText(QApplication::translate("MainWindow", "2", 0, QApplication::UnicodeUTF8));
        labelNOK->setText(QApplication::translate("MainWindow", "Tests with Error:", 0, QApplication::UnicodeUTF8));
        labelNOKCount->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        pushButtonAddTest->setText(QApplication::translate("MainWindow", "Add test...", 0, QApplication::UnicodeUTF8));
        pushButtonRemoveTest->setText(QApplication::translate("MainWindow", "Remove test", 0, QApplication::UnicodeUTF8));
        pushButtonConfigureTest->setText(QApplication::translate("MainWindow", "Configure...", 0, QApplication::UnicodeUTF8));
        pushButtonResetResults->setText(QApplication::translate("MainWindow", "Reset results", 0, QApplication::UnicodeUTF8));
        menuFiles->setTitle(QApplication::translate("MainWindow", "Files", 0, QApplication::UnicodeUTF8));
        menuHelp->setTitle(QApplication::translate("MainWindow", "Help", 0, QApplication::UnicodeUTF8));
        Q_UNUSED(MainWindow);
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
