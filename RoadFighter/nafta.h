#ifndef NAFTA_H
#define NAFTA_H

#include "dibujable.h"
#include "player.h"

class Nafta: public Dibujable
{
public:
    Nafta(int pos_x, int pos_y);
    bool colisionNafta(Player *jugador);
    void dibujar(QPainter *p) override;
    void mov_spawn(int dy);
    //Getters
    int getPosX(){return this->pos_x; };
    int  getPosY(){return this->pos_y; };
    int getNafta(){return this->NivelNafta; };
    //Setters
    int setNafta();

    //Destructor
    virtual ~Nafta();

protected:
    int pos_x;
    int pos_y;
    int vel_vertical;
    int NivelNafta;
};

#endif // NAFTA_H
