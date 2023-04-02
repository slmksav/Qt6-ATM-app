#ifndef CHANGEACCOUNTWINDOW_H
#define CHANGEACCOUNTWINDOW_H

#include <QDialog>

namespace Ui {
class ChangeAccountWindow;
}

class ChangeAccountWindow : public QDialog
{
    Q_OBJECT

public:
    explicit ChangeAccountWindow(QWidget *parent = nullptr);
    ~ChangeAccountWindow();

private:
    Ui::ChangeAccountWindow *ui;
};

#endif // CHANGEACCOUNTWINDOW_H
