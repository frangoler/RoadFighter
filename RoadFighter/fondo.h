#ifndef FONDO_H
#define FONDO_H

#include <QPainter>
#include "dibujable.h"

class Fondo
{
public:
    Fondo();
    void dibujar(QPainter *p);
    void actualizarFondo(int velocidad);
private:
    int pos_x;
    int pos_y;
    QList<QRect> linea;
    QList<QRect> Arbolito;
};

#endif // FONDO_H
