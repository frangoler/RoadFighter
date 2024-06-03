#include "fondo.h"

Fondo::Fondo(){      //Crea una lista de lineas y una de arboles según la cantidad que entren en pantalla
    for(int i = -10; i<=510; i = i + 30){
        linea.append(QRect(245,i,5,15));
    }
    for(int i = -10; i<=510; i = i + 80){
        Arbolito.append(QRect(25,i,46,20));
    }
}

void Fondo::dibujar(QPainter *p){
    p->setBrush(QBrush(Qt::black)); //dibuja la ruta
    p->drawRect(125,0,375-125,500);
    p->setBrush(QBrush(Qt::darkGreen)); //dibuja el césped
    p->drawRect(0,0,125,500);
    p->drawRect(375,0,125,500);
    for(int i= 0; i < linea.length(); ++i){ //dibuja las líneas amarillas
        p->setBrush(QBrush(Qt::yellow));
        p->drawRect(linea[i]);
    }
    for(int i= 0; i < Arbolito.length(); ++i){  //dibuja los arbolitos
        QPixmap pixmap(":/new/prefix1/Imagenes/Arbolito.png");
        p->drawPixmap(Arbolito[i],pixmap);
    }
}

void Fondo::actualizarFondo(int velocidad){ //Actualiza el fondo según la velocidad
                                            //es decir, hace que las líneas y los arbolitos se muevan
    for(int i= 0; i < linea.length(); ++i){
        if(linea[i].y()>=510){
            linea.removeAt(i);  //borra las lineas por debajo de Y = 510
            linea.append(QRect(245,-10,5,15));
        }
        linea[i].moveBottom(linea[i].y()+5+velocidad);
    }
    for(int i= 0; i < Arbolito.length(); ++i){
       if(Arbolito[i].y()>=510){
            Arbolito.removeAt(i);   //borra los arbolitos por debajo de Y = 510
            Arbolito.append(QRect(25,-10,46,20));
       }
       Arbolito[i].moveBottom(Arbolito[i].y()+15+velocidad);
    }
}
