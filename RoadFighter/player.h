#ifndef PLAYER_H
#define PLAYER_H
#include <QPainter>
#include "dibujable.h"

class Player : Dibujable
{
public:
    Player(int pos_x, int pos_y );
    void dibujar(QPainter *p);
    void actualizarPosicion(float dx);
    void reductNasta();

    //Getters
    int getPosX();
    int getPosY();
    int getNasta(){return this->NivelNasta;};

    //Setters
    bool getExplota(){return this->explota;};
    void setExplota(){explota = true;};
    void setNasta(int dN);

private:
     float pos_x;
     float pos_y;
     int b;
     int h;
     int NivelNasta;
     bool explota = false;
};

#endif // PLAYER_H
