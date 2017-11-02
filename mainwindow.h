#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "field.h"
#include "winorlose.h"

#include <QMainWindow>
#include <QLabel>
#include <QLineEdit>
#include <QIntValidator>
#include <QPushButton>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    field f;
    QLineEdit* qle[4][4];
    QLabel* label_horizontal[4][3];
    QLabel* label_vertical[3][4];
    const int _size = 4;
    void drawField();
    void clearAll();

private slots:
    void slot_generationsField();
    void slot_play();
};

#endif // MAINWINDOW_H
