#ifndef SPINNER_H
#define SPINNER_H

#include <QWidget>
#include <QMovie>
#include <QLabel>
#include <QVBoxLayout>
namespace Ui {
class Spinner;
}

class Spinner : public QWidget
{
    Q_OBJECT

public:
    explicit Spinner(QWidget *parent = nullptr);
    ~Spinner();

private:
    Ui::Spinner *ui;
};

#endif // SPINNER_H
