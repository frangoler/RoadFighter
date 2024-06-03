#include "player.h"

Player::Player(int pos_x, int pos_y){   //constructor del jugador
    this->pos_x = pos_x;
    this->pos_y = pos_y;
    NivelNasta=500; //defino el nivel de nafta inicial en 500
}

void Player::dibujar(QPainter*p){   //dibujo el jugador
    if (explota==false){    //si no está en condición de explotar, se dibuja normalmente
        QPixmap pixmap(":/new/prefix1/Imagenes/Player.png");
        p->drawPixmap(this->pos_x,this->pos_y,25,40,pixmap);
    }
    if (explota){   //si está en condición de explotar, se dibuja la explosión
        QPixmap explosion(":/new/prefix1/Imagenes/Explosion.png");
        p->drawPixmap(this->pos_x,this->pos_y,40,64,explosion);
    }
}

void Player::actualizarPosicion(float dx){  //implemento el desplazamiento lateral del jugador
    pos_x = pos_x + dx;
}


int Player::getPosX(){  //devuelve la posición en x
    return this->pos_x;
}
int Player::getPosY(){  //devuelve la posición en y
    return this->pos_y;
}
void Player::setNasta(int dN){  //modifica el nivel de nafta
    NivelNasta = NivelNasta + dN;
}

void Player::reductNasta(){ //reduce el nivel de nafta
    NivelNasta = NivelNasta - 1;
    if(NivelNasta <=0){ //si el nivel es 0, el jugador está en condición de explotar
        explota=true;
    }
}
