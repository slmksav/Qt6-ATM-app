#include "transactionswindow.h"
#include "ui_transactionswindow.h"

TransactionsWindow::TransactionsWindow(QWidget *parent, SessionData *session) :
    QWidget(parent),
    ui(new Ui::TransactionsWindow)
{
    ui->setupUi(this);

    this->session = session;

    session->resetTimer();

    updateUI();
}

TransactionsWindow::~TransactionsWindow()
{
    delete ui;

    session->resetTimer();
}

void TransactionsWindow::updateUI()
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
    if(session->transactionIDs.count() - listIndex <= 5)
    {
        ui->buttonNext->setFlat(true);
        ui->buttonNext->setDisabled(true);
    }
    else
    {
        ui->buttonNext->setFlat(false);
        ui->buttonNext->setDisabled(false);
    }

    QList<QLabel *> transactionLabels = ui->layoutWrapper->findChildren<QLabel *>();

    QListIterator<QString> transactionDates(session->transactionDates);
    transactionDates.toBack();
    QListIterator<double> transactionAmounts(session->transactionAmounts);
    transactionAmounts.toBack();

    //reel iterator to index
    for (int i = 0; i < listIndex; ++i) {
        transactionDates.previous();
        transactionAmounts.previous();
    }

    qDebug() << Q_FUNC_INFO << "transactionDates list size: " << session->transactionDates.count() <<
                "| listIndex: " << listIndex;
    //prints the list
    for (int i = 0; i < 5; ++i) {

        //index would traverse outside of list
        if(i + listIndex >= session->transactionDates.count())
        {
            qDebug() << Q_FUNC_INFO << "Index outside of list, outputting a blank";
            transactionLabels[i]->setText(" ");
        }
        else
        {
            QString transactionDateStr = transactionDates.previous();
            QDateTime transactionDate = QDateTime::fromString(transactionDateStr, Qt::ISODate);
            transactionDate = transactionDate.toLocalTime().addSecs(3 * 3600);
            QString transactionDateFmt = transactionDate.toString("yyyy-MM-dd hh:mm:ss").replace("T", " ").replace("Z", "");

            qDebug() << Q_FUNC_INFO << "Index inside of list, outputting transaction[" << i + listIndex;
            transactionLabels[i]->setText(transactionDateFmt +
                    ": " + QString::number(-1 * transactionAmounts.previous(), 'f', 2));
        }
    }

    //other ui elements
    if(session->language == "fi")
    {
        ui->buttonLogout->setText("Kirjaudu Ulos");
        ui->buttonReturn->setText("Palaa");

        ui->labelInfo->setText("Tilitapahtumat:");
        ui->buttonNext->setText("Seuraavat");
        ui->buttonPrevious->setText("Edelliset");
    }
    if(session->language == "en")
    {
        ui->buttonLogout->setText("Logout");
        ui->buttonReturn->setText("Return");

        ui->labelInfo->setText("Past Transactions:");
        ui->buttonNext->setText("Next");
        ui->buttonPrevious->setText("Previous");
    }
}


void TransactionsWindow::on_buttonLogout_clicked()
{
    emit session->sendLogout(this);
}


void TransactionsWindow::on_buttonReturn_clicked()
{
    delete this;
}


void TransactionsWindow::on_buttonPrevious_clicked()
{
    listIndex -= 5;
    updateUI();

    session->resetTimer();
}


void TransactionsWindow::on_buttonNext_clicked()
{
    listIndex += 5;
    updateUI();

    session->resetTimer();
}

