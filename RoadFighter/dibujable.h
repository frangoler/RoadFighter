#ifndef DIBUJABLE_H
#define DIBUJABLE_H
#include <QPainter>


class Dibujable
{
public:
    virtual void dibujar(QPainter * p) = 0; //Funcion virtual para todas las demas clases
};

#endif // DIBUJABLE_H

