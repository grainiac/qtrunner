/********************************************************************************
** Form generated from reading UI file 'addtestdialog.ui'
**
** Created: Thu 14. Jan 23:11:19 2010
**      by: Qt User Interface Compiler version 4.6.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDTESTDIALOG_H
#define UI_ADDTESTDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_AddTestDialog
{
public:
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout_2;
    QLabel *labelTestExe;
    QHBoxLayout *horizontalLayout_2;
    QLineEdit *lineEditTest;
    QPushButton *pushButtonSelectTest;
    QSpacerItem *verticalSpacer;
    QVBoxLayout *verticalLayout;
    QLabel *labelTestType;
    QHBoxLayout *horizontalLayout;
    QRadioButton *radioButtonGoogle;
    QRadioButton *radioButtonQt;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *verticalSpacer_2;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *AddTestDialog)
    {
        if (AddTestDialog->objectName().isEmpty())
            AddTestDialog->setObjectName(QString::fromUtf8("AddTestDialog"));
        AddTestDialog->resize(400, 195);
        AddTestDialog->setMinimumSize(QSize(400, 195));
        AddTestDialog->setMaximumSize(QSize(400, 195));
        gridLayout = new QGridLayout(AddTestDialog);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        labelTestExe = new QLabel(AddTestDialog);
        labelTestExe->setObjectName(QString::fromUtf8("labelTestExe"));

        verticalLayout_2->addWidget(labelTestExe);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        lineEditTest = new QLineEdit(AddTestDialog);
        lineEditTest->setObjectName(QString::fromUtf8("lineEditTest"));

        horizontalLayout_2->addWidget(lineEditTest);

        pushButtonSelectTest = new QPushButton(AddTestDialog);
        pushButtonSelectTest->setObjectName(QString::fromUtf8("pushButtonSelectTest"));
        pushButtonSelectTest->setMinimumSize(QSize(22, 22));
        pushButtonSelectTest->setMaximumSize(QSize(22, 22));

        horizontalLayout_2->addWidget(pushButtonSelectTest);


        verticalLayout_2->addLayout(horizontalLayout_2);


        verticalLayout_3->addLayout(verticalLayout_2);

        verticalSpacer = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout_3->addItem(verticalSpacer);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        labelTestType = new QLabel(AddTestDialog);
        labelTestType->setObjectName(QString::fromUtf8("labelTestType"));

        verticalLayout->addWidget(labelTestType);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        radioButtonGoogle = new QRadioButton(AddTestDialog);
        radioButtonGoogle->setObjectName(QString::fromUtf8("radioButtonGoogle"));

        horizontalLayout->addWidget(radioButtonGoogle);

        radioButtonQt = new QRadioButton(AddTestDialog);
        radioButtonQt->setObjectName(QString::fromUtf8("radioButtonQt"));

        horizontalLayout->addWidget(radioButtonQt);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);


        verticalLayout->addLayout(horizontalLayout);

        verticalSpacer_2 = new QSpacerItem(20, 20, QSizePolicy::Minimum, QSizePolicy::Fixed);

        verticalLayout->addItem(verticalSpacer_2);

        buttonBox = new QDialogButtonBox(AddTestDialog);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        verticalLayout_3->addLayout(verticalLayout);


        gridLayout->addLayout(verticalLayout_3, 0, 0, 1, 1);


        retranslateUi(AddTestDialog);
        QObject::connect(buttonBox, SIGNAL(rejected()), AddTestDialog, SLOT(reject()));
        QObject::connect(buttonBox, SIGNAL(accepted()), AddTestDialog, SLOT(accept()));

        QMetaObject::connectSlotsByName(AddTestDialog);
    } // setupUi

    void retranslateUi(QDialog *AddTestDialog)
    {
        AddTestDialog->setWindowTitle(QApplication::translate("AddTestDialog", "Add test...", 0, QApplication::UnicodeUTF8));
        labelTestExe->setText(QApplication::translate("AddTestDialog", "Test executable:", 0, QApplication::UnicodeUTF8));
        pushButtonSelectTest->setText(QApplication::translate("AddTestDialog", "...", 0, QApplication::UnicodeUTF8));
        labelTestType->setText(QApplication::translate("AddTestDialog", "Unit test type:", 0, QApplication::UnicodeUTF8));
        radioButtonGoogle->setText(QApplication::translate("AddTestDialog", "GoogleTest", 0, QApplication::UnicodeUTF8));
        radioButtonQt->setText(QApplication::translate("AddTestDialog", "QTestLib", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class AddTestDialog: public Ui_AddTestDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDTESTDIALOG_H
