#ifndef PINCODEUI_H
#define PINCODEUI_H

#include <QDialog>

namespace Ui {
class PinCodeUi;
}

class PinCodeUi : public QDialog
{
    Q_OBJECT

public:
    explicit PinCodeUi(QWidget *parent = nullptr);
    ~PinCodeUi();

private:
    Ui::PinCodeUi *ui;
};

#endif // PINCODEUI_H
