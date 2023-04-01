/********************************************************************************
** Form generated from reading UI file 'codeui.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CODEUI_H
#define UI_CODEUI_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_CodeUI
{
public:
    QPushButton *button1;
    QLineEdit *lineEdit;
    QPushButton *button2;
    QPushButton *button3;
    QPushButton *button4;
    QPushButton *button5;
    QPushButton *button6;
    QPushButton *button7;
    QPushButton *button9;
    QPushButton *button8;
    QPushButton *buttonEnter;
    QPushButton *ButtonClear;
    QPushButton *ButtonStop;
    QPushButton *button0;

    void setupUi(QDialog *CodeUI)
    {
        if (CodeUI->objectName().isEmpty())
            CodeUI->setObjectName(QString::fromUtf8("CodeUI"));
        CodeUI->resize(400, 324);
        button1 = new QPushButton(CodeUI);
        button1->setObjectName(QString::fromUtf8("button1"));
        button1->setGeometry(QRect(130, 150, 21, 29));
        lineEdit = new QLineEdit(CodeUI);
        lineEdit->setObjectName(QString::fromUtf8("lineEdit"));
        lineEdit->setGeometry(QRect(140, 100, 113, 28));
        button2 = new QPushButton(CodeUI);
        button2->setObjectName(QString::fromUtf8("button2"));
        button2->setGeometry(QRect(160, 150, 21, 29));
        button3 = new QPushButton(CodeUI);
        button3->setObjectName(QString::fromUtf8("button3"));
        button3->setGeometry(QRect(190, 150, 21, 29));
        button4 = new QPushButton(CodeUI);
        button4->setObjectName(QString::fromUtf8("button4"));
        button4->setGeometry(QRect(130, 190, 21, 29));
        button5 = new QPushButton(CodeUI);
        button5->setObjectName(QString::fromUtf8("button5"));
        button5->setGeometry(QRect(160, 190, 21, 29));
        button6 = new QPushButton(CodeUI);
        button6->setObjectName(QString::fromUtf8("button6"));
        button6->setGeometry(QRect(190, 190, 21, 29));
        button7 = new QPushButton(CodeUI);
        button7->setObjectName(QString::fromUtf8("button7"));
        button7->setGeometry(QRect(130, 230, 21, 29));
        button9 = new QPushButton(CodeUI);
        button9->setObjectName(QString::fromUtf8("button9"));
        button9->setGeometry(QRect(190, 230, 21, 29));
        button8 = new QPushButton(CodeUI);
        button8->setObjectName(QString::fromUtf8("button8"));
        button8->setGeometry(QRect(160, 230, 21, 29));
        buttonEnter = new QPushButton(CodeUI);
        buttonEnter->setObjectName(QString::fromUtf8("buttonEnter"));
        buttonEnter->setGeometry(QRect(220, 230, 61, 29));
        ButtonClear = new QPushButton(CodeUI);
        ButtonClear->setObjectName(QString::fromUtf8("ButtonClear"));
        ButtonClear->setGeometry(QRect(220, 190, 61, 29));
        ButtonStop = new QPushButton(CodeUI);
        ButtonStop->setObjectName(QString::fromUtf8("ButtonStop"));
        ButtonStop->setGeometry(QRect(220, 150, 61, 29));
        button0 = new QPushButton(CodeUI);
        button0->setObjectName(QString::fromUtf8("button0"));
        button0->setGeometry(QRect(160, 270, 21, 29));

        retranslateUi(CodeUI);

        QMetaObject::connectSlotsByName(CodeUI);
    } // setupUi

    void retranslateUi(QDialog *CodeUI)
    {
        CodeUI->setWindowTitle(QCoreApplication::translate("CodeUI", "Dialog", nullptr));
        button1->setText(QCoreApplication::translate("CodeUI", "1", nullptr));
        button2->setText(QCoreApplication::translate("CodeUI", "2", nullptr));
        button3->setText(QCoreApplication::translate("CodeUI", "3", nullptr));
        button4->setText(QCoreApplication::translate("CodeUI", "4", nullptr));
        button5->setText(QCoreApplication::translate("CodeUI", "5", nullptr));
        button6->setText(QCoreApplication::translate("CodeUI", "6", nullptr));
        button7->setText(QCoreApplication::translate("CodeUI", "7", nullptr));
        button9->setText(QCoreApplication::translate("CodeUI", "9", nullptr));
        button8->setText(QCoreApplication::translate("CodeUI", "8", nullptr));
        buttonEnter->setText(QCoreApplication::translate("CodeUI", "ENTER", nullptr));
        ButtonClear->setText(QCoreApplication::translate("CodeUI", "CLEAR", nullptr));
        ButtonStop->setText(QCoreApplication::translate("CodeUI", "STOP", nullptr));
        button0->setText(QCoreApplication::translate("CodeUI", "0", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CodeUI: public Ui_CodeUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CODEUI_H
