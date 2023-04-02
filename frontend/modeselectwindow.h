#ifndef MODESELECTWINDOW_H
#define MODESELECTWINDOW_H

#include <QDialog>

namespace Ui {
class ModeSelectWindow;
}

class ModeSelectWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ModeSelectWindow(QWidget *parent = nullptr);
    ~ModeSelectWindow();

private:
    Ui::ModeSelectWindow *ui;
};

#endif // MODESELECTWINDOW_H
