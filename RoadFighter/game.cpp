#include "game.h"
#include <typeinfo>
Game::Game(){   //Creamos el jugador, los bordes de la ruta, el fondo y
                //los autos que aparecen al inicio
    jugador=new Player(235,300);
    raid= new Borde();
    fondito = new Fondo();
    obstaculos.append(new AutoRojo(150,100));
    obstaculos.append(new AutoRojo(150,200));
    obstaculos.append(new AutoRojo(150,300));
    obstaculos.append(new AutoRojo(320,100));
    obstaculos.append(new AutoRojo(320,200));
    obstaculos.append(new AutoRojo(320,300));
}
void Game::dibujar(QPainter *p){
    fondito->dibujar(p);    //dibujo el fondo
    //Chequeo de lista obstaculos
    if (obstaculos.length()>0){
        for (int i= 0; i < obstaculos.length(); ++i) {
            obstaculos[i]->dibujar(p); //Los dibuja todos ya que se deberian dibujar hasta q se termine la animacion
        }
   }
   //Dibujo borde
   raid->dibujar(p);
   //Dibujo Player
   jugador->dibujar(p);
   //Dibujo el logo
   QPixmap pixmap(":/new/prefix1/Imagenes/HASBULLA GROUP.png");
   p->drawPixmap(400,350,80,80,pixmap);
}

void Game::nasta(){
    jugador->reductNasta(); //reduce la nafta del jugador según el timer de Game
}

int Game::getNasta(){
    return jugador->getNasta(); //devuelve el nivel de nafta del jugador
}

void Game::GenerarObstaculosRandom(){

    static random_device rd{};
    static seed_seq seeder {rd(), rd(), rd(), rd(), 0xDEAD'FACE};
    static mt19937 rand_eng {seeder};
    static uniform_int_distribution<int> UnifDistPos(150, 350); //toma un número random con distribución uniforme entre 150 y 350
    static uniform_int_distribution<int> UnifDistTipo(0,130);   //toma un número random con distribución uniforme entre 0 y 130

    if(obstaculos.length()<5){ //Chequeo que la cantidad de obstáculos en pantalla sea entre 0 y 5
        if(UnifDistTipo(rand_eng)>15 && UnifDistTipo(rand_eng)<70){ //si el número random de UnifDistTipo está entre 15 y 70
            int number = UnifDistPos(rand_eng);
            obstaculos.append(new AutoRojo(number,-50));    //genera un auto fijo
        }
        else if(UnifDistTipo(rand_eng)<15){ //entre 0 y 15
            int number = UnifDistPos(rand_eng);
            obstaculos.append(new Nafta(number, -50)); //genera un boost de nafta
        }
        else if(UnifDistTipo(rand_eng)>70 && UnifDistTipo(rand_eng)<100){ //entre 70 y 100
            int number = UnifDistPos(rand_eng);
            obstaculos.append(new Mancha(number, -50)); //genera una mancha
        }
        else{                                  //entre 100 y 30
            int number = UnifDistPos(rand_eng);
            obstaculos.append(new Movil(number,-50)); //genera un auto móvil
        }
    }

}


void Game::ActualizarLista(int velocidad){              //se encarga de mover los obstáculos y el fondo según la velocidad del jugador
    if (obstaculos.length()>0){                         //y si el obstáculo pasa Y=510 se borra
        for (int i= 0; i < obstaculos.length(); ++i) {
            obstaculos[i]->mov_spawn(velocidad);
            if(obstaculos[i]->getPosY()>=510){
                delete obstaculos[i];
                obstaculos.erase(obstaculos.begin()+i);
            }
        }
        if (velocidad>2){
            fondito->actualizarFondo(velocidad);
        }
   }
}

void Game::AgregarObjeto(Obstaculo * obj){      //agrega un obstáculo a la list obstaculos
    obstaculos.append(obj);
}

void Game::posPlayer(float dx){   //actualiza la posición en x del jugador
    jugador->actualizarPosicion(dx);
}

bool Game::chequearColisiones(){
    bool a=false;   //booleano para identificar si existe colisión
    if(obstaculos.length()>0){
        for (int i= 0; i < obstaculos.length(); ++i) {
             if((obstaculos[i]->colision(jugador)) && (choco==false))  {
                choco=true;     //booleano para identificar si existe animación de choque o no
                contadorChoque +=1;     //contador de choques con autos
                if (obstaculos[i]->getesMancha()){  //si el obstáculo es una mancha
                    if(contadorChoque > 0){
                        contadorChoque -=1;         //no cuenta como choque con auto
                    }
                }
                if (obstaculos[i]->getesNasta()){   //si el obstáculo es el boost de nafta
                    choco = false;                  //no existe animación de choque
                    if (contadorChoque > 0){
                        contadorChoque -=1;         //ni cuenta como choque con auto
                    }
                }
                choqueLateral = obstaculos[i]->getLadoChoque();     //busca de que lado fue el choque
                return true;
             }
        }
    }
    return a;
}

bool Game::chequearExplosion(){
    bool b = false;     //booleando para verificar si hay explosión

    if(raid->colision(jugador) || jugador->getExplota() || contadorChoque >=7){ //veo si hay colisión con el borde,
            jugador->setExplota();                                              //si el jugador está en condició de explotar
            b = true;                                                           //y si el contador de choques llegó a 7
        }
    return b;
}

void Game::MovLateral(){    //controla el movimiento lateral de los autos móviles
    static random_device rd{};
    static seed_seq seeder {rd(), rd(), rd(), rd(), 0xDEAD'FACE};
    static mt19937 rand_eng {seeder};
    static uniform_int_distribution<int> UnifDistTipo(0,1); //tomo de forma random 0 o 1
    if(UnifDistTipo(rand_eng)==1){  //si es un uno se va a mover
        for (int i= 0; i < obstaculos.length(); ++i) {
            if(obstaculos[i]->getPosX()<=375-25-10){
                if(obstaculos[i]->getPosX()>=125+10){
                    static random_device rd{};
                    static seed_seq seeder {rd(), rd(), rd(), rd(), 0xDEAD'FACE};
                    static mt19937 rand_eng {seeder};
                    static uniform_int_distribution<int> UnifDistPos(-20, 20);  //tomo un entero random entre -20 y 20
                    obstaculos[i]->mov_lateral(UnifDistPos(rand_eng)); //muevo el auto amarillo según el número anterior
                    //obstaculos[i]->mov_lateral(20);
                }
            }
        }
    }
}

//Destructor Game
Game::~Game(){

}
