#ifndef WINORLOSE_H
#define WINORLOSE_H

#include <QDialog>

namespace Ui {
class WinOrLose;
}

class WinOrLose : public QDialog
{
    Q_OBJECT

public:
    explicit WinOrLose(QWidget *parent = 0);
    ~WinOrLose();
    void win();
    void lose();

private slots:
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::WinOrLose *ui;

};

#endif // WINORLOSE_H
