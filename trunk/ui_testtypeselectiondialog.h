/********************************************************************************
** Form generated from reading UI file 'testtypeselectiondialog.ui'
**
** Created: Thu 14. Jan 21:19:41 2010
**      by: Qt User Interface Compiler version 4.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_TESTTYPESELECTIONDIALOG_H
#define UI_TESTTYPESELECTIONDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QFormLayout>
#include <QtGui/QGridLayout>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QRadioButton>
#include <QtGui/QSpacerItem>

QT_BEGIN_NAMESPACE

class Ui_TestTypeSelectionDialog
{
public:
    QGridLayout *gridLayout;
    QGroupBox *groupBox;
    QFormLayout *formLayout;
    QRadioButton *radioButtonGoogle;
    QRadioButton *radioButtonQt;
    QDialogButtonBox *buttonBox;
    QSpacerItem *horizontalSpacer;

    void setupUi(QDialog *TestTypeSelectionDialog)
    {
        if (TestTypeSelectionDialog->objectName().isEmpty())
            TestTypeSelectionDialog->setObjectName(QString::fromUtf8("TestTypeSelectionDialog"));
        TestTypeSelectionDialog->resize(320, 120);
        TestTypeSelectionDialog->setMinimumSize(QSize(320, 120));
        TestTypeSelectionDialog->setMaximumSize(QSize(320, 120));
        gridLayout = new QGridLayout(TestTypeSelectionDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        groupBox = new QGroupBox(TestTypeSelectionDialog);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        formLayout = new QFormLayout(groupBox);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        radioButtonGoogle = new QRadioButton(groupBox);
        radioButtonGoogle->setObjectName(QString::fromUtf8("radioButtonGoogle"));

        formLayout->setWidget(0, QFormLayout::LabelRole, radioButtonGoogle);

        radioButtonQt = new QRadioButton(groupBox);
        radioButtonQt->setObjectName(QString::fromUtf8("radioButtonQt"));

        formLayout->setWidget(1, QFormLayout::LabelRole, radioButtonQt);


        gridLayout->addWidget(groupBox, 0, 0, 1, 1);

        buttonBox = new QDialogButtonBox(TestTypeSelectionDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setLayoutDirection(Qt::LeftToRight);
        buttonBox->setOrientation(Qt::Vertical);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);
        buttonBox->setCenterButtons(true);

        gridLayout->addWidget(buttonBox, 0, 2, 1, 1);

        horizontalSpacer = new QSpacerItem(15, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 1, 1, 1);


        retranslateUi(TestTypeSelectionDialog);
        QObject::connect(buttonBox, SIGNAL(accepted()), TestTypeSelectionDialog, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), TestTypeSelectionDialog, SLOT(reject()));

        QMetaObject::connectSlotsByName(TestTypeSelectionDialog);
    } // setupUi

    void retranslateUi(QDialog *TestTypeSelectionDialog)
    {
        TestTypeSelectionDialog->setWindowTitle(QApplication::translate("TestTypeSelectionDialog", "Dialog", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("TestTypeSelectionDialog", "Type", 0, QApplication::UnicodeUTF8));
        radioButtonGoogle->setText(QApplication::translate("TestTypeSelectionDialog", "GoogleTest", 0, QApplication::UnicodeUTF8));
        radioButtonQt->setText(QApplication::translate("TestTypeSelectionDialog", "QTestLib", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class TestTypeSelectionDialog: public Ui_TestTypeSelectionDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_TESTTYPESELECTIONDIALOG_H
