/********************************************************************************
** Form generated from reading UI file 'dllpincode.ui'
**
** Created by: Qt User Interface Compiler version 6.4.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DLLPINCODE_H
#define UI_DLLPINCODE_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>

QT_BEGIN_NAMESPACE

class Ui_CodeUI
{
public:
    QLabel *cardhexcodeLabel;
    QPushButton *button4;
    QPushButton *ButtonClear;
    QPushButton *button2;
    QLabel *label_3;
    QPushButton *button1;
    QPushButton *buttonEnter;
    QLabel *labelInterrupt;
    QPushButton *button9;
    QLineEdit *lineEdit;
    QPushButton *button5;
    QPushButton *button8;
    QLabel *labelAttempts;
    QLabel *label;
    QPushButton *button7;
    QPushButton *ButtonStop;
    QPushButton *button3;
    QPushButton *button0;
    QPushButton *button6;

    void setupUi(QDialog *CodeUI)
    {
        if (CodeUI->objectName().isEmpty())
            CodeUI->setObjectName("CodeUI");
        CodeUI->resize(693, 644);
        cardhexcodeLabel = new QLabel(CodeUI);
        cardhexcodeLabel->setObjectName("cardhexcodeLabel");
        cardhexcodeLabel->setGeometry(QRect(120, 30, 191, 20));
        button4 = new QPushButton(CodeUI);
        button4->setObjectName("button4");
        button4->setGeometry(QRect(170, 330, 21, 29));
        ButtonClear = new QPushButton(CodeUI);
        ButtonClear->setObjectName("ButtonClear");
        ButtonClear->setGeometry(QRect(260, 330, 61, 29));
        button2 = new QPushButton(CodeUI);
        button2->setObjectName("button2");
        button2->setGeometry(QRect(200, 290, 21, 29));
        label_3 = new QLabel(CodeUI);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(130, 470, 271, 41));
        QFont font;
        font.setPointSize(16);
        label_3->setFont(font);
        button1 = new QPushButton(CodeUI);
        button1->setObjectName("button1");
        button1->setGeometry(QRect(170, 290, 21, 29));
        buttonEnter = new QPushButton(CodeUI);
        buttonEnter->setObjectName("buttonEnter");
        buttonEnter->setGeometry(QRect(260, 370, 61, 29));
        labelInterrupt = new QLabel(CodeUI);
        labelInterrupt->setObjectName("labelInterrupt");
        labelInterrupt->setGeometry(QRect(130, 150, 291, 51));
        labelInterrupt->setFont(font);
        button9 = new QPushButton(CodeUI);
        button9->setObjectName("button9");
        button9->setGeometry(QRect(230, 370, 21, 29));
        lineEdit = new QLineEdit(CodeUI);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(180, 240, 113, 28));
        button5 = new QPushButton(CodeUI);
        button5->setObjectName("button5");
        button5->setGeometry(QRect(200, 330, 21, 29));
        button8 = new QPushButton(CodeUI);
        button8->setObjectName("button8");
        button8->setGeometry(QRect(200, 370, 21, 29));
        labelAttempts = new QLabel(CodeUI);
        labelAttempts->setObjectName("labelAttempts");
        labelAttempts->setGeometry(QRect(130, 520, 211, 41));
        labelAttempts->setFont(font);
        label = new QLabel(CodeUI);
        label->setObjectName("label");
        label->setGeometry(QRect(130, 100, 261, 41));
        label->setFont(font);
        button7 = new QPushButton(CodeUI);
        button7->setObjectName("button7");
        button7->setGeometry(QRect(170, 370, 21, 29));
        ButtonStop = new QPushButton(CodeUI);
        ButtonStop->setObjectName("ButtonStop");
        ButtonStop->setGeometry(QRect(260, 290, 61, 29));
        button3 = new QPushButton(CodeUI);
        button3->setObjectName("button3");
        button3->setGeometry(QRect(230, 290, 21, 29));
        button0 = new QPushButton(CodeUI);
        button0->setObjectName("button0");
        button0->setGeometry(QRect(200, 410, 21, 29));
        button6 = new QPushButton(CodeUI);
        button6->setObjectName("button6");
        button6->setGeometry(QRect(230, 330, 21, 29));

        retranslateUi(CodeUI);

        QMetaObject::connectSlotsByName(CodeUI);
    } // setupUi

    void retranslateUi(QDialog *CodeUI)
    {
        CodeUI->setWindowTitle(QCoreApplication::translate("CodeUI", "Dialog", nullptr));
        cardhexcodeLabel->setText(QCoreApplication::translate("CodeUI", "cardhexcode tulee t\303\244h\303\244", nullptr));
        button4->setText(QCoreApplication::translate("CodeUI", "4", nullptr));
        ButtonClear->setText(QCoreApplication::translate("CodeUI", "CLEAR", nullptr));
        button2->setText(QCoreApplication::translate("CodeUI", "2", nullptr));
        label_3->setText(QCoreApplication::translate("CodeUI", "Lopuksi paina ENTER", nullptr));
        button1->setText(QCoreApplication::translate("CodeUI", "1", nullptr));
        buttonEnter->setText(QCoreApplication::translate("CodeUI", "ENTER", nullptr));
        labelInterrupt->setText(QCoreApplication::translate("CodeUI", "Tapahtuma Keskeytetty", nullptr));
        button9->setText(QCoreApplication::translate("CodeUI", "9", nullptr));
        button5->setText(QCoreApplication::translate("CodeUI", "5", nullptr));
        button8->setText(QCoreApplication::translate("CodeUI", "8", nullptr));
        labelAttempts->setText(QCoreApplication::translate("CodeUI", " yrityst\303\244 j\303\244ljell\303\244", nullptr));
        label->setText(QCoreApplication::translate("CodeUI", "N\303\244pp\303\244ile tunnusluku", nullptr));
        button7->setText(QCoreApplication::translate("CodeUI", "7", nullptr));
        ButtonStop->setText(QCoreApplication::translate("CodeUI", "STOP", nullptr));
        button3->setText(QCoreApplication::translate("CodeUI", "3", nullptr));
        button0->setText(QCoreApplication::translate("CodeUI", "0", nullptr));
        button6->setText(QCoreApplication::translate("CodeUI", "6", nullptr));
    } // retranslateUi

};

namespace Ui {
    class CodeUI: public Ui_CodeUI {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DLLPINCODE_H
