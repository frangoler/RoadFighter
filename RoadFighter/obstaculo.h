#ifndef OBSTACULO_H
#define OBSTACULO_H

#include "dibujable.h"
#include "player.h"

//En esta clase implementamos todas las
//clase de obstaculo

//Principal de obstaculos
class Obstaculo:  public Dibujable
{
public:
    Obstaculo(int pos_x, int pos_y);
    virtual  bool colision(Player *jugador)=0;
    virtual void dibujar(QPainter *p)=0;
    virtual void mov_spawn(int dy);
    virtual void mov_lateral(int incremento)=0;

    //Getters
    virtual bool getesNasta(){return false;};
    virtual bool getesMancha(){return false;};
    bool getLadoChoque(){return this->ladoChoque;};
    int getPosX(){return this->pos_x; };
    int  getPosY(){return this->pos_y; };

    virtual ~Obstaculo();


protected:
    int pos_x;
    int pos_y;
    int base;
    int altura;
    int vel_vertical;
    bool ladoChoque;
};


//Auto con movimiento
class Movil : public Obstaculo
{
public:
    Movil(int pos_x, int pos_y);
    bool colision(Player *jugador) override;
    void dibujar(QPainter *p) override;
    void mov_lateral(int incremento) override;

};


//Borde Ruta
class Borde: public Obstaculo
{
public:
    Borde();
    void dibujar(QPainter *p) override;
    bool colision(Player *jugador) override;
    void mov_lateral(int incremento) override;
};


//Fijos general

class Fijo: public Obstaculo{
public:
    Fijo(int pos_x, int pos_y);
};

class Nafta: public Fijo
{
public:
    Nafta(int pos_x, int pos_y);
    bool colision(Player *jugador) override;
    void dibujar(QPainter *p) override;
    void mov_lateral(int incremento) override;

    //Getters
    int getNafta(){return this->NivelNafta; };
    bool getesNasta(){return this->esNasta; };

protected:
    int NivelNafta;
    bool cambiarColor = false;
    bool esNasta = true;
};

//Mancha
class Mancha:public Fijo
{
public:
    Mancha(int pos_x, int pos_y);
    void dibujar(QPainter *p) override;
    void mov_lateral(int incremento) override;
    bool colision(Player *jugador) override;
    void mov_spawn(int dy) override;

    //Getters
    bool getesMancha(){return this->esMancha;};

protected:
    bool esMancha = true;
};



//Auto Fijo
class AutoRojo: public Fijo
{
public:
    AutoRojo(int pos_x, int pos_y);
    void dibujar(QPainter *p) override;
    bool colision(Player *jugador) override;
    void mov_lateral(int incremento) override;
};


#endif // OBSTACULO_H
