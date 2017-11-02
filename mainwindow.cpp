#include "mainwindow.h"
#include "ui_mainwindow.h"

#define MAGIC_CONST 48


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("Фитошки");

    // иконки
    QPixmap img_generation("image/generation.png");
    QIcon ButtonIcon_generation(img_generation);

    QPushButton* button_generate = new QPushButton(this);
    button_generate->setGeometry(30, 220, 36, 30);
    button_generate->setIcon(ButtonIcon_generation);
    button_generate->setIconSize(img_generation.rect().size());

    QPixmap img_play("image/play.png");
    QIcon ButtonIcon_play(img_play);

    QPushButton* button_play = new QPushButton(this);
    button_play->setGeometry(140, 220, 30, 30);
    button_play->setIcon(ButtonIcon_play);
    button_play->setIconSize(img_play.rect().size());

    int x, y;
    y = 30;
    for(int j = 0; j < _size; j++) {
        x = 20;
        for(int i = 0; i < _size; i++) {
            qle[j][i] = new QLineEdit(this);
            qle[j][i]->setValidator(new QIntValidator(1, 4));
            qle[j][i]->setGeometry(x, y, 24, 24);
            if(i != (_size - 1)) {
                label_horizontal[j][i] = new QLabel(this);
                label_horizontal[j][i]->setGeometry(x + 26, y, 22, 22);
            }
            if(j != (_size - 1)) {
                label_vertical[j][i] = new QLabel(this);
                label_vertical[j][i]->setGeometry(x + 2, y + 24, 22, 22);
            }
            x+= MAGIC_CONST;
        }
        y += MAGIC_CONST;
    }

    connect(button_generate, SIGNAL(clicked(bool)), this, SLOT(slot_generationsField()) );
    connect(button_play, SIGNAL(clicked(bool)), this, SLOT(slot_play()) );

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::slot_generationsField() {
    f.generation();
    f.print();
    clearAll();
    drawField();
}

void MainWindow::slot_play() {
    field play;
    for(int j = 0; j < _size; j++) {
        for(int i = 0; i < _size; i++) {
            play.set_arr(i,j,qle[j][i]->text().toInt());
        }
    }

    WinOrLose wol(this);
    if(play.check_number() && play.check_znaki()) {
        wol.win();
    }
    else {

        wol.lose();
    }
    wol.exec();
}

void MainWindow::drawField() { // РИСУЕТ ПОЛЕ

    QPixmap image_vertical_more("image/img_vertical_more.png");
    QPixmap image_vertical_less("image/img_vertical_less.png");
    QPixmap image_horizontal_more("image/img_horizontal_more.png");
    QPixmap image_horizontal_less("image/img_horizontal_less.png");

    int x, y;
    y = 30;
    for(int j = 0; j < _size; j++) {
        int r = rand() % 4;
        x = 20;
        for(int i = 0; i < _size; i++) {
            if(i == r)  qle[j][i]->setText(QString::number(f.get_arr(j, r)));

            if(i != (_size - 1)) {
                if(f.search_znak_horizontal(j,i) == MORE) {
                    label_horizontal[j][i]->setPixmap(image_horizontal_more);
                }
                else if(f.search_znak_horizontal(j,i) == LESS) {
                    label_horizontal[j][i]->setPixmap(image_horizontal_less);
                }
            }

            if(j != (_size - 1)) {
                if(f.search_znak_vertical(j,i) == MORE) {
                    label_vertical[j][i]->setPixmap(image_vertical_more);
                }
                else if(f.search_znak_vertical(j,i) == LESS) {
                    label_vertical[j][i]->setPixmap(image_vertical_less);
                }
            }

            x+= MAGIC_CONST;
        }
        y += MAGIC_CONST;
    }
}

void MainWindow::clearAll() {
    for(int j = 0; j < _size; j++) {
        for(int i = 0; i < _size; i++) {
            qle[j][i]->clear();
            if(i != (_size - 1)) label_horizontal[j][i]->clear();
            if(j != (_size - 1)) label_vertical[j][i]->clear();
        }
    }
}
