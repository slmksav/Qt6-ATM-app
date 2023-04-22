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
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DLLPinCode
{
public:
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
    QLabel *labelFreezed1;
    QLabel *labelFreezed2;
    QWidget *widget;
    QLabel *labelLangInfo_5;
    QLabel *labelLangInfo_4;
    QButtonGroup *buttonGroup;

    void setupUi(QWidget *DLLPinCode)
    {
        if (DLLPinCode->objectName().isEmpty())
            DLLPinCode->setObjectName("DLLPinCode");
        DLLPinCode->resize(800, 480);
        DLLPinCode->setMinimumSize(QSize(800, 480));
        DLLPinCode->setMaximumSize(QSize(800, 480));
        DLLPinCode->setStyleSheet(QString::fromUtf8(""));
        button4 = new QPushButton(DLLPinCode);
        buttonGroup = new QButtonGroup(DLLPinCode);
        buttonGroup->setObjectName("buttonGroup");
        buttonGroup->addButton(button4);
        button4->setObjectName("button4");
        button4->setGeometry(QRect(20, 180, 91, 81));
        button4->setStyleSheet(QString::fromUtf8("QWidget {\n"
"    background-image: url(:/exeimgs/yellowyellow.jpg);\n"
"    background-repeat: no-repeat;\n"
"    background-position: center;\n"
"}"));
        ButtonClear = new QPushButton(DLLPinCode);
        ButtonClear->setObjectName("ButtonClear");
        ButtonClear->setGeometry(QRect(330, 150, 130, 50));
        ButtonClear->setStyleSheet(QString::fromUtf8("QWidget {\n"
"    background-image: url(:/exeimgs/button130x50.jpg);\n"
"    background-repeat: no-repeat;\n"
"    background-position: center;\n"
"}"));
        button2 = new QPushButton(DLLPinCode);
        buttonGroup->addButton(button2);
        button2->setObjectName("button2");
        button2->setGeometry(QRect(120, 90, 91, 81));
        button2->setTabletTracking(false);
        button2->setAutoFillBackground(false);
        button2->setStyleSheet(QString::fromUtf8("QWidget {\n"
"    background-image: url(:/exeimgs/yellowyellow.jpg);\n"
"    background-repeat: no-repeat;\n"
"    background-position: center;\n"
"}"));
        label_3 = new QLabel(DLLPinCode);
        label_3->setObjectName("label_3");
        label_3->setGeometry(QRect(330, 350, 221, 41));
        QFont font;
        font.setFamilies({QString::fromUtf8("Verdana Pro Semibold")});
        font.setPointSize(11);
        label_3->setFont(font);
        label_3->setStyleSheet(QString::fromUtf8("QLabel#label_3l {\n"
"    background-color: none;\n"
"    border: none;\n"
"    color: none;\n"
"    font-size: none;\n"
"    /* any other styles you want to remove */\n"
"    stylesheet: \"\";\n"
"}"));
        label_3->setTextFormat(Qt::AutoText);
        button1 = new QPushButton(DLLPinCode);
        buttonGroup->addButton(button1);
        button1->setObjectName("button1");
        button1->setGeometry(QRect(20, 90, 91, 81));
        button1->setAcceptDrops(false);
        button1->setStyleSheet(QString::fromUtf8("QWidget {\n"
"    background-image: url(:/exeimgs/yellowyellow.jpg);\n"
"    background-repeat: no-repeat;\n"
"    background-position: center;\n"
"}"));
        buttonEnter = new QPushButton(DLLPinCode);
        buttonEnter->setObjectName("buttonEnter");
        buttonEnter->setGeometry(QRect(330, 210, 130, 140));
        buttonEnter->setStyleSheet(QString::fromUtf8("QPushButton {\n"
"    background-image: url(:/exeimgs/button130x140.jpg);\n"
"    background-repeat: no-repeat;\n"
"    background-position: center;\n"
"}"));
        labelInterrupt = new QLabel(DLLPinCode);
        labelInterrupt->setObjectName("labelInterrupt");
        labelInterrupt->setGeometry(QRect(220, 200, 431, 51));
        QFont font1;
        font1.setFamilies({QString::fromUtf8("Verdana Pro Cond Light")});
        font1.setPointSize(16);
        font1.setBold(true);
        labelInterrupt->setFont(font1);
        button9 = new QPushButton(DLLPinCode);
        buttonGroup->addButton(button9);
        button9->setObjectName("button9");
        button9->setGeometry(QRect(220, 270, 91, 81));
        button9->setStyleSheet(QString::fromUtf8("QWidget {\n"
"    background-image: url(:/exeimgs/yellowyellow.jpg);\n"
"    background-repeat: no-repeat;\n"
"    background-position: center;\n"
"}"));
        button9->setAutoDefault(true);
        button9->setFlat(false);
        lineEdit = new QLineEdit(DLLPinCode);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(50, 30, 241, 51));
        QFont font2;
        font2.setPointSize(16);
        font2.setBold(true);
        lineEdit->setFont(font2);
        lineEdit->setStyleSheet(QString::fromUtf8("\n"
"background-color: rgb(254, 195, 50);"));
        lineEdit->setFrame(true);
        lineEdit->setAlignment(Qt::AlignCenter);
        button5 = new QPushButton(DLLPinCode);
        buttonGroup->addButton(button5);
        button5->setObjectName("button5");
        button5->setGeometry(QRect(120, 180, 91, 81));
        button5->setStyleSheet(QString::fromUtf8("QWidget {\n"
"    background-image: url(:/exeimgs/yellowyellow.jpg);\n"
"    background-repeat: no-repeat;\n"
"    background-position: center;\n"
"}"));
        button8 = new QPushButton(DLLPinCode);
        buttonGroup->addButton(button8);
        button8->setObjectName("button8");
        button8->setGeometry(QRect(120, 270, 91, 81));
        button8->setStyleSheet(QString::fromUtf8("QWidget {\n"
"    background-image: url(:/exeimgs/yellowyellow.jpg);\n"
"    background-repeat: no-repeat;\n"
"    background-position: center;\n"
"}"));
        labelAttempts = new QLabel(DLLPinCode);
        labelAttempts->setObjectName("labelAttempts");
        labelAttempts->setGeometry(QRect(540, 90, 211, 41));
        labelAttempts->setFont(font);
        label = new QLabel(DLLPinCode);
        label->setObjectName("label");
        label->setGeometry(QRect(310, 30, 500, 41));
        label->setMaximumSize(QSize(500, 41));
        QFont font3;
        font3.setFamilies({QString::fromUtf8("Verdana Pro")});
        font3.setPointSize(11);
        font3.setBold(true);
        font3.setKerning(false);
        font3.setStyleStrategy(QFont::NoAntialias);
        label->setFont(font3);
        label->setStyleSheet(QString::fromUtf8("QLabel {\n"
"    background-color: transparent;\n"
"}"));
        label->setFrameShape(QFrame::NoFrame);
        label->setFrameShadow(QFrame::Plain);
        label->setLineWidth(0);
        button7 = new QPushButton(DLLPinCode);
        buttonGroup->addButton(button7);
        button7->setObjectName("button7");
        button7->setGeometry(QRect(20, 270, 91, 81));
        button7->setStyleSheet(QString::fromUtf8("QWidget {\n"
"    background-image: url(:/exeimgs/yellowyellow.jpg);\n"
"    background-repeat: no-repeat;\n"
"    background-position: center;\n"
"}"));
        ButtonStop = new QPushButton(DLLPinCode);
        ButtonStop->setObjectName("ButtonStop");
        ButtonStop->setGeometry(QRect(330, 90, 130, 50));
        ButtonStop->setStyleSheet(QString::fromUtf8("QWidget {\n"
"    background-image: url(:/exeimgs/button130x50.jpg);\n"
"    background-repeat: no-repeat;\n"
"    background-position: center;\n"
"}"));
        button3 = new QPushButton(DLLPinCode);
        buttonGroup->addButton(button3);
        button3->setObjectName("button3");
        button3->setGeometry(QRect(220, 90, 91, 81));
        QFont font4;
        font4.setPointSize(9);
        button3->setFont(font4);
        button3->setStyleSheet(QString::fromUtf8("QWidget {\n"
"    background-image: url(:/exeimgs/yellowyellow.jpg);\n"
"    background-repeat: no-repeat;\n"
"    background-position: center;\n"
"}"));
        button0 = new QPushButton(DLLPinCode);
        button0->setObjectName("button0");
        button0->setGeometry(QRect(120, 360, 91, 71));
        button0->setStyleSheet(QString::fromUtf8("QWidget {\n"
"    background-image: url(:/exeimgs/yellowyellow.jpg);\n"
"    background-repeat: no-repeat;\n"
"    background-position: center;\n"
"}"));
        button6 = new QPushButton(DLLPinCode);
        buttonGroup->addButton(button6);
        button6->setObjectName("button6");
        button6->setGeometry(QRect(220, 180, 91, 81));
        button6->setStyleSheet(QString::fromUtf8("QWidget {\n"
"    background-image: url(:/exeimgs/yellowyellow.jpg);\n"
"    background-repeat: no-repeat;\n"
"    background-position: center;\n"
"}"));
        labelFreezed1 = new QLabel(DLLPinCode);
        labelFreezed1->setObjectName("labelFreezed1");
        labelFreezed1->setGeometry(QRect(50, 250, 691, 41));
        QFont font5;
        font5.setFamilies({QString::fromUtf8("Verdana")});
        font5.setPointSize(11);
        font5.setBold(true);
        labelFreezed1->setFont(font5);
        labelFreezed2 = new QLabel(DLLPinCode);
        labelFreezed2->setObjectName("labelFreezed2");
        labelFreezed2->setGeometry(QRect(100, 280, 581, 41));
        QFont font6;
        font6.setFamilies({QString::fromUtf8("Verdana")});
        font6.setPointSize(10);
        font6.setBold(true);
        labelFreezed2->setFont(font6);
        labelFreezed2->setStyleSheet(QString::fromUtf8(""));
        widget = new QWidget(DLLPinCode);
        widget->setObjectName("widget");
        widget->setGeometry(QRect(0, 0, 801, 481));
        widget->setLayoutDirection(Qt::RightToLeft);
        widget->setStyleSheet(QString::fromUtf8("QWidget {\n"
"    background-image: url(:/exeimgs/blueblue.jpg);\n"
"    background-repeat: no-repeat;\n"
"    background-position: center;\n"
"}"));
        labelLangInfo_5 = new QLabel(DLLPinCode);
        labelLangInfo_5->setObjectName("labelLangInfo_5");
        labelLangInfo_5->setGeometry(QRect(10, 440, 291, 31));
        QFont font7;
        font7.setFamilies({QString::fromUtf8("Verdana")});
        font7.setPointSize(8);
        font7.setBold(false);
        labelLangInfo_5->setFont(font7);
        labelLangInfo_4 = new QLabel(DLLPinCode);
        labelLangInfo_4->setObjectName("labelLangInfo_4");
        labelLangInfo_4->setGeometry(QRect(10, 420, 291, 31));
        labelLangInfo_4->setFont(font7);
        widget->raise();
        button4->raise();
        ButtonClear->raise();
        button2->raise();
        label_3->raise();
        button1->raise();
        buttonEnter->raise();
        labelInterrupt->raise();
        button9->raise();
        lineEdit->raise();
        button5->raise();
        button8->raise();
        labelAttempts->raise();
        label->raise();
        button7->raise();
        ButtonStop->raise();
        button3->raise();
        button0->raise();
        button6->raise();
        labelFreezed1->raise();
        labelFreezed2->raise();
        labelLangInfo_5->raise();
        labelLangInfo_4->raise();

        retranslateUi(DLLPinCode);

        button9->setDefault(false);


        QMetaObject::connectSlotsByName(DLLPinCode);
    } // setupUi

    void retranslateUi(QWidget *DLLPinCode)
    {
        DLLPinCode->setWindowTitle(QCoreApplication::translate("DLLPinCode", "Dialog", nullptr));
        button4->setText(QCoreApplication::translate("DLLPinCode", "4", nullptr));
        ButtonClear->setText(QCoreApplication::translate("DLLPinCode", "CLEAR", nullptr));
        button2->setText(QCoreApplication::translate("DLLPinCode", "2", nullptr));
        label_3->setText(QCoreApplication::translate("DLLPinCode", "<html><head/><body><p><span style=\" font-size:10pt;\">Hit &quot;ENTER&quot; when done</span></p></body></html>", nullptr));
        button1->setText(QCoreApplication::translate("DLLPinCode", "1", nullptr));
        buttonEnter->setText(QCoreApplication::translate("DLLPinCode", "ENTER", nullptr));
        labelInterrupt->setText(QCoreApplication::translate("DLLPinCode", "Login interrupted, cancelling...", nullptr));
        button9->setText(QCoreApplication::translate("DLLPinCode", "9", nullptr));
        button5->setText(QCoreApplication::translate("DLLPinCode", "5", nullptr));
        button8->setText(QCoreApplication::translate("DLLPinCode", "8", nullptr));
        labelAttempts->setText(QCoreApplication::translate("DLLPinCode", "attempt(s) left!", nullptr));
        label->setText(QCoreApplication::translate("DLLPinCode", "N\303\244pp\303\244ile nelinumeroinen tunnusluku", nullptr));
        button7->setText(QCoreApplication::translate("DLLPinCode", "7", nullptr));
        ButtonStop->setText(QCoreApplication::translate("DLLPinCode", "STOP", nullptr));
        button3->setText(QCoreApplication::translate("DLLPinCode", "3", nullptr));
        button0->setText(QCoreApplication::translate("DLLPinCode", "0", nullptr));
        button6->setText(QCoreApplication::translate("DLLPinCode", "6", nullptr));
        labelFreezed1->setText(QCoreApplication::translate("DLLPinCode", "The account has been frozen due to excessive amount of attempts", nullptr));
        labelFreezed2->setText(QCoreApplication::translate("DLLPinCode", "<html><head/><body><p><span style=\" font-weight:700;\">Ota yhteys asiakaspalvelumme numeroon: +358 10 1234567</span></p></body></html>", nullptr));
        labelLangInfo_5->setText(QCoreApplication::translate("DLLPinCode", "banksimul18@gmail.com", nullptr));
        labelLangInfo_4->setText(QCoreApplication::translate("DLLPinCode", "+358 10 1234567", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DLLPinCode: public Ui_DLLPinCode {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DLLPINCODE_H
