#include "changeaccountwindow.h"
#include "ui_changeaccountwindow.h"
#include <QDebug>

ChangeAccountWindow::ChangeAccountWindow(QWidget *parent, SessionData *session) :
    QWidget(parent),
    ui(new Ui::ChangeAccountWindow)
{
    ui->setupUi(this);

    this->session = session;

    session->resetTimer();

    updateUI();

    connect(ui->buttonGroup, SIGNAL(buttonClicked(QAbstractButton *)),
            this, SLOT(accountButtonClicked(QAbstractButton *)));
}

ChangeAccountWindow::~ChangeAccountWindow()
{
    delete ui;

    session->resetTimer();
}

void ChangeAccountWindow::updateUI()
{
    //see if previous can be shown
    if(listIndex == 0)
    {
        ui->buttonPrevious->setFlat(true);
        ui->buttonPrevious->setDisabled(true);
    }
    else
    {
        ui->buttonPrevious->setFlat(false);
        ui->buttonPrevious->setDisabled(false);
    }

    //see if next can be shown
    if(session->additionalAccountNames.count() - listIndex <= 5)
    {
        ui->buttonNext->setFlat(true);
        ui->buttonNext->setDisabled(true);
    }
    else
    {
        ui->buttonNext->setFlat(false);
        ui->buttonNext->setDisabled(false);
    }

    QList<QPushButton *> accountButtons = ui->buttonWrapper->findChildren<QPushButton *>();

    QListIterator<QString> additionalAccountNames(session->additionalAccountNames);
    additionalAccountNames.toFront();

    //reel iterator to index
    for (int i = 0; i < listIndex; ++i) {
        additionalAccountNames.next();
    }

    qDebug() << Q_FUNC_INFO << "accountNames list size: " << session->additionalAccountNames.count() <<
                "| listIndex: " << listIndex;
    //prints the list
    for (int i = 0; i < 5; ++i) {

        //index would traverse outside of list
        if(i + listIndex >= session->additionalAccountNames.count())
        {
            qDebug() << Q_FUNC_INFO << "Index outside of list, outputting a blank";
            accountButtons[i]->setText("");
            accountButtons[i]->setFlat(true);
            accountButtons[i]->setDisabled(true);
        }
        else
        {
            qDebug() << Q_FUNC_INFO << "Index inside of list, outputting accountNames[" << i + listIndex;
            accountButtons[i]->setText(additionalAccountNames.next());
            accountButtons[i]->setFlat(false);
            accountButtons[i]->setDisabled(false);
        }
    }

    //other ui elements
    if(session->language == "fi")
    {
        ui->buttonLogout->setText("Kirjaudu ulos");

        ui->labelInfo->setText("Valitse tili:");
        ui->buttonNext->setText("Seuraavat");
        ui->buttonPrevious->setText("Edelliset");
    }
    if(session->language == "en")
    {
        ui->buttonLogout->setText("Log out");

        ui->labelInfo->setText("Choose Account:");
        ui->buttonNext->setText("Next");
        ui->buttonPrevious->setText("Previous");
    }
}

void ChangeAccountWindow::accountButtonClicked(QAbstractButton * button)
{
    qDebug() << Q_FUNC_INFO << "slot activated";
    QList<QAbstractButton *> accountButtons = ui->buttonWrapper->findChildren<QAbstractButton *>();

    //find out which button was pressed (position in the list/layout)
    int nthButton = 0;
    for (int i = 0; i < 5; ++i) {
        if(accountButtons[i]->text() == button->text())
        {
            qDebug() << Q_FUNC_INFO << "button[" << i << "] was the sender";
            qDebug() << Q_FUNC_INFO << "accountButtons[i]->text():" << accountButtons[i]->text() <<
                        "\n\tbutton->text(): " << button->text();
            nthButton = i;
            break;
        }
    }

    int accountID = session->additionalAccountIDs[listIndex + nthButton];

    qDebug() << Q_FUNC_INFO << "Attempting to change to accountID:" << accountID;

    //check if same account as current one didn't get selected
    if(accountID != session->accountID) {
        emit changeToAccount(accountID);
    }
    else
    {
        delete this;
    }
}


void ChangeAccountWindow::on_buttonPrevious_clicked()
{
    listIndex -= 5;
    updateUI();

    session->resetTimer();
}


void ChangeAccountWindow::on_buttonNext_clicked()
{
    listIndex += 5;
    updateUI();

    session->resetTimer();
}


void ChangeAccountWindow::on_buttonLogout_clicked()
{
    emit session->sendLogout(this);
}

