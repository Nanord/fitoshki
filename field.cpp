#include "field.h"
#include <ctime>

field::field(QWidget *parent) : QMainWindow(parent)
{

}

void field::generation() {
    srand( time( 0 ) );                 // автоматическая рандомизация
    quantity = 0;
    do {
        quantity++;
        for(register int j = 0; j < 4; j++) {
            for(register int i = 0; i < 4; i++) {
                if(i == 3) {
                    unsigned __int8 number = 1 + rand() % 4;
                    while(number == _field[j][0] || number == _field[j][1] || number == _field[j][2]) number = 1 + rand() % 4;
                    _field[j][i] = number;
                }
                else if (i == 2) {
                    unsigned __int8 number = 1 + rand() % 4;
                    while(number == _field[j][0] || number == _field[j][1])  number = 1 + rand() % 4;
                    _field[j][i] = number;
                }
                else if(i == 1) {
                    unsigned __int8 number = 1 + rand() % 4;
                    while(number == _field[j][0]) number = 1 + rand() % 4;
                    _field[j][i] = number;
                }
                else _field[j][i] = 1 + rand() % 4;
            }
        }

        // от 2 до 4 знаков
        // первый два знака, вертикальный и горизонтальный
        if(!_zn_vertical.empty() || !_zn_horizontal.empty()) {
            _zn_vertical.clear();
            _zn_horizontal.clear();
        }
        pair<unsigned __int8, unsigned __int8> p ((rand() % 3), (rand() % 4));
        if((rand() % 2) == 0 ) _zn_vertical.insert( pair< pair<unsigned __int8, unsigned __int8 >, unsigned __int8> ( p, LESS ) );
        else _zn_vertical.insert( pair< pair<unsigned __int8, unsigned __int8 >, unsigned __int8> ( p, MORE ) );
        pair<unsigned __int8, unsigned __int8> p1 ((rand() % 4), (rand() % 3));
        if((rand() % 2) == 0 ) _zn_horizontal.insert( pair< pair<unsigned __int8, unsigned __int8 >, unsigned __int8> ( p1, LESS ) );
        else _zn_horizontal.insert( pair< pair<unsigned __int8, unsigned __int8 >, unsigned __int8> ( p1, MORE ) );

        // вторый 50/50
        if((rand() % 3) == 0) {
            p.first = rand() % 3;
            p.second = rand() % 4;
            if((rand() % 2) == 0 ) _zn_vertical.insert( pair< pair<unsigned __int8, unsigned __int8 >, unsigned __int8> ( p, LESS ) );
            else _zn_vertical.insert( pair< pair<unsigned __int8, unsigned __int8 >, unsigned __int8> ( p, MORE ) );
        }
        int r = rand() % 3;
        if(r == 0 || r == 1) {
            p1.first = rand() % 4;
            p1.second = rand() % 3;
            if((rand() % 2) == 0 ) _zn_horizontal.insert( pair< pair<unsigned __int8, unsigned __int8 >, unsigned __int8> ( p1, LESS ) );
            else _zn_horizontal.insert( pair< pair<unsigned __int8, unsigned __int8 >, unsigned __int8> ( p1, MORE ) );
        }

    } while(!check_number() || !check_znaki());
}

bool field::check_number() { //ПРОВЕРКА ПОЛЯ
    for(int j = 0; j < 4; j++) {
        for(int i = 0; i < 4; i++) {
            for(int k = 0; k < 4; k++) {
                if(i == k) continue;
                //qDebug() << _field[j][i] << _field[j][k];
                if(_field[j][i] == _field[j][k] || _field[i][j] == _field[k][j]) return false;
            }
        }
    }
    return true;
}


bool field::check_znaki() { //ПРОВЕРКА ЦИФР
    map< pair<unsigned __int8, unsigned __int8>, unsigned __int8>::iterator  it;

    // для горизонтального map
    it = _zn_horizontal.begin();
    while(it != _zn_horizontal.end() ) {
        if(it->second == MORE) {                                        // для знака больше
            if(_field[it->first.first][it->first.second] > _field[it->first.first][(it->first.second + 1)] ) ;
            else return false;
            /*  сравнивает число со всей строкой, не то!!
             * for(int i = it->first.second; i < 4; i++) {
                if(i == it->first.second && i != 3) i++;
                if(_field[it->first.first][it->first.second] > _field[it->first.first][i] ) status = true;
                else return false;
            }
            */
        }
        else {                                                          //  для знака меньше
            if(_field[it->first.first][it->first.second] < _field[it->first.first][(it->first.second + 1)] ) ;
            else return false;
            /* такая же херня как и сверху!
             *
            for(int i = it->first.second; i < 4; i++) {
                if(i == it->first.second && i != 3) i++;
                if(_field[it->first.first][it->first.second] < _field[it->first.first][i] ) status = true;
                else return false;
            }
            */
        }
        it++;
    }

    // для вертикального map
    it = _zn_vertical.begin();
    while(it != _zn_vertical.end() ) {
        if(it->second == MORE) {                                        // для знака больше
            if(_field[it->first.first][it->first.second] > _field[(it->first.first + 1)][it->first.second] ) ;
            else return false;
        }
        else {                                                          //  для знака меньше
            if(_field[it->first.first][it->first.second] < _field[(it->first.first + 1)][it->first.second] ) ;
            else return false;
        }
        it++;
    }
    return true;
}


unsigned __int8 field::get_arr(int x, int y) {
    return _field[x][y];
}

void field::set_arr(int x, int y, int number) {
    if(x > 3 || y > 3 || x < 0 || y < 0 || number > 4 || number < 0) return;
    _field[x][y] = number;
}

unsigned __int8 field::search_znak_vertical(unsigned __int8 x, unsigned __int8 y) {
    pair<unsigned __int8, unsigned __int8> search(x, y);
    map< pair<unsigned __int8, unsigned __int8>, unsigned __int8>::iterator  it;
    it = _zn_vertical.find(search);
    if (it != _zn_vertical.end()) {
        return _zn_vertical.find(search)->second;
    }
    else return UNKNOWN;
}

unsigned __int8 field::search_znak_horizontal(unsigned __int8 x, unsigned __int8 y) {
    pair<unsigned __int8, unsigned __int8> search(x, y);
    map< pair<unsigned __int8, unsigned __int8>, unsigned __int8>::iterator  it;
    it = _zn_horizontal.find(search);
    if (it != _zn_horizontal.end()) {
        return _zn_horizontal.find(search)->second;
    }
    else return UNKNOWN;
}


void field::print() {
    qDebug() << "C " << quantity << " раза";
    for(int j = 0; j < 4; j++) {
        qDebug() << _field[j][0] << _field[j][1] << _field[j][2] << _field[j][3];
    }

    map< pair<unsigned __int8, unsigned __int8>, unsigned __int8>::iterator  it;
    it = _zn_horizontal.begin();
    while(it != _zn_horizontal.end() ) {
        if(it->second == MORE)
            qDebug() << "Horizontal " << it->first.first << it->first.second << "MORE";
        else
            qDebug() << "Horizontal " << it->first.first << it->first.second << "LESS";
        it++;
    }

    it = _zn_vertical.begin();
    while(it != _zn_vertical.end() ) {
        if(it->second == MORE)
            qDebug() << "Vertical " << it->first.first << it->first.second << "MORE";
        else
            qDebug() << "Vertical " << it->first.first << it->first.second << "LESS";
        it++;
    }
}
