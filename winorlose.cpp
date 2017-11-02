#include "winorlose.h"
#include "ui_winorlose.h"

WinOrLose::WinOrLose(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::WinOrLose)
{
    ui->setupUi(this);

    setWindowTitle("Ваш результат");
}

WinOrLose::~WinOrLose()
{
    delete ui;
}

void WinOrLose::win() {
    QPixmap win ("image/win.png");
    ui->label_2->setPixmap(win);
    ui->label->setText("Победа!");
}

void WinOrLose::lose() {
    QPixmap lose ("image/lose.png");
    ui->label_2->setPixmap(lose);
    ui->label->setText("Не правильно!");
}

void WinOrLose::on_buttonBox_accepted()
{
    accept();
}

void WinOrLose::on_buttonBox_rejected()
{
    reject();
}
