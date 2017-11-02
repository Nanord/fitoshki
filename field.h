#ifndef FIELD_H
#define FIELD_H

#include <QMainWindow>
#include <QDebug>
#include <map>
#include <utility>

using namespace std;

enum {LESS, MORE, UNKNOWN};

class field : public QMainWindow
{
    Q_OBJECT

private:
    // 2-5 открыто
    unsigned __int8 _field[4][4];
    map< pair<unsigned __int8, unsigned __int8>, unsigned __int8> _zn_vertical;
    map< pair<unsigned __int8, unsigned __int8>, unsigned __int8> _zn_horizontal;
    unsigned quantity;
public:
    explicit field(QWidget *parent = 0);
    void generation();
    bool check_znaki();
    bool check_number();
    unsigned __int8 get_arr(int, int);
    void set_arr(int x, int y, int number);
    unsigned __int8 search_znak_vertical(unsigned __int8, unsigned __int8);
    unsigned __int8 search_znak_horizontal(unsigned __int8, unsigned __int8);
    void print();


signals:

public slots:
};

#endif // FIELD_H
