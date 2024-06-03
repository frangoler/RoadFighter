#include "obstaculo.h"

//Clase Abstracta
Obstaculo::Obstaculo(int pos_x, int pos_y){     //constructor de obstáculo
    this->pos_x = pos_x;
    this->pos_y = pos_y;
}
void Obstaculo::mov_spawn(int dy){  //implemento el movimiento hacia abajo
    pos_y = pos_y + dy;
}


//Enemigo Movil

Movil::Movil(int pos_x, int pos_y): Obstaculo(pos_x, pos_y){        //constructor de auto móvil
    this->pos_x = pos_x;
    this->pos_y = pos_y;
}
bool Movil::colision(Player *jugador){  //chequeo los bordes del jugador y el obstáculo móvil
    if((jugador->getPosX()<=(this->getPosX()+27) && (jugador->getPosX()+27)>=this->getPosX()) &&
        (jugador->getPosY()<=(this->getPosY()+38) && (jugador->getPosY()+38)>=this->getPosY())){
            if(jugador->getPosX()<=(this->getPosX())){  //fijo de qué lado choca
                ladoChoque = true;
            }
            else{
                ladoChoque = false;
           }
            this->mov_spawn(-50);   //mueve al auto 50 píxeles arriba
            return true;
    }
    return false;
}
void Movil::dibujar(QPainter *p){   //dibujo el móvil
    QPixmap pixmap(":/new/prefix1/Imagenes/AutoMovil.png");
    p->drawPixmap(this->pos_x,this->pos_y,25,40,pixmap);
}
void Movil::mov_lateral(int incremento){ //implemento el movimiento lateral del obstáculo móvil
    if(this->pos_y>100){
        pos_x=pos_x+incremento;
    }
}

//Borde Ruta

Borde::Borde(): Obstaculo(pos_x, pos_y){    //constructor de borde

}
void Borde::dibujar(QPainter *p){       //dibujo los bordes de la ruta
    QPixmap pixmap(":/new/prefix1/Imagenes/Borde.png");
    p->drawPixmap(115,0,10,500,pixmap);
    p->drawPixmap(375,0,10,500,pixmap);

}
bool Borde::colision(Player *jugador){  //implemento la colisión con el borde
    if(jugador->getPosX()>=375-25){
        return true;
    }
    else if(jugador->getPosX()<=125){
       return true;
    }
    return false;
}
void Borde::mov_lateral(int incremento){    //implemento el movimiento lateral del borde (no tiene)

}

//Enemigos Fijo

Fijo::Fijo(int pos_x, int pos_y): Obstaculo(pos_x, pos_y){  //constructor de obstáculo fijo
    this->pos_x = pos_x;
    this->pos_y = pos_y;
}

//AutoFijo

AutoRojo::AutoRojo(int pos_x, int pos_y):Fijo(pos_x,pos_y){ //constructor del auto fijo
    this->pos_x = pos_x;
    this->pos_y = pos_y;
}
bool AutoRojo::colision(Player *jugador){   //implemento la colisión del auto fijo
    if((jugador->getPosX()<=(this->getPosX()+27) && (jugador->getPosX()+27)>=this->getPosX()) &&
        (jugador->getPosY()<=(this->getPosY()+38) && (jugador->getPosY()+38)>=this->getPosY())){
            if(jugador->getPosX()<=(this->getPosX())){  //veo de que lado fue el choque
                ladoChoque = true;
            }
            else{
                ladoChoque = false;
            }
            this->mov_spawn(-50);   //mueve al auto 50 píxeles arriba
            return true;
    }
    return false;
}
void AutoRojo::mov_lateral(int incremento){ //implemento el movimiento lateral del auto fijo (no tiene)

}
void AutoRojo::dibujar(QPainter *p){    //dibujo el auto fijo
    QPixmap pixmap(":/new/prefix1/Imagenes/AutoFijo.png");
    p->drawPixmap(this->pos_x,this->pos_y,25,40,pixmap);
}

//Boost de Nafta

Nafta::Nafta(int pos_x, int pos_y):Fijo(pos_x, pos_y){  //constructor del boost de nafta
    this->pos_x = pos_x;
    this->pos_y = pos_y;
}

bool Nafta::colision(Player *jugador){  //implemento la colisión con el boost de nafta
    if((jugador->getPosX()<=(this->getPosX()+27) &&
         (jugador->getPosX()+27)>=this->getPosX()) &&
        (jugador->getPosY()<=(this->getPosY()+38) &&
         (jugador->getPosY()+38)>=this->getPosY())){
            jugador->setNasta(250); //aumento el nivel de nafta del jugador
            this->mov_spawn(-520);  //llevo el boost de nafta a una zona de delete
            return true;
    }
    return false;
}
void Nafta::mov_lateral(int incremento){    //implemento el movimiento lateral del boost (no tiene)

}
void Nafta::dibujar(QPainter *p){   //dibujo el boost de nafta
        QPixmap pixmap(":/new/prefix1/Imagenes/AutoNafta.png");
        p->drawPixmap(this->pos_x,this->pos_y,25,40,pixmap);
}

//Mancha

Mancha::Mancha(int pos_x, int pos_y):Fijo(pos_x, pos_y){    //constructor de la mancha
    this->pos_x = pos_x;
    this->pos_y = pos_y;
}

void Mancha::dibujar(QPainter *p){  //dibujo la mancha
    QPixmap pixmap(":/new/prefix1/Imagenes/Mancha.png");
    p->drawPixmap(this->pos_x,this->pos_y,25,25,pixmap);
}

void Mancha::mov_lateral(int incremento){   //implemento el movimiento lateral de la mancha (no tiene)

}

bool Mancha::colision(Player *jugador){ //implemento la colisión con la mancha
    if((jugador->getPosX()<=(this->getPosX()+10) && (jugador->getPosX()+10)>=this->getPosX()) &&
        (jugador->getPosY()<=(this->getPosY()+15) && (jugador->getPosY()+15)>=this->getPosY())){
        if(jugador->getPosX()<=(this->getPosX())){  //me fijo el lado del choque
                ladoChoque = false; //es al revés del de los autos para que el jugador
        }                           //en vez de rebotar, se deslize
        if(jugador->getPosX()>=(this->getPosX())){
                ladoChoque = true;
        }
        return true;
    }
    return false;
}

void Mancha::mov_spawn(int dy){ //redefino el movimiento hacia abajo para la mancha
    if (dy>0){                  //para que si el jugador está frenado, no se mueva hacia arriba
        pos_y = pos_y + dy;     //como el resto de obstáculos
    }

}

//Destructor Obstáculo

Obstaculo::~Obstaculo(){

}
