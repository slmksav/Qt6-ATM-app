#ifndef SPINNER_H
#define SPINNER_H

#include <QDialog>
#include <QMovie>
#include <QLabel>
#include <QVBoxLayout>
namespace Ui {
class Spinner;
}

class Spinner : public QDialog
{
    Q_OBJECT

public:
    explicit Spinner(QWidget *parent = nullptr);
    ~Spinner();

private:
    Ui::Spinner *ui;
};

#endif // SPINNER_H
