#ifndef GAME_H
#define GAME_H
#include "obstaculo.h"
#include <random>
#include <QRandomGenerator>
#include <QtMath>
#include <QTimer>
#include "dibujable.h"
#include "player.h"
#include "fondo.h"
#include <time.h>
using namespace std;
class Game: public Dibujable
{
public:
    Game();
    void GenerarObstaculosRandom();
    void dibujar(QPainter *p) override;
    void ActualizarLista(int velocidad);
    void AgregarObjeto(Obstaculo *obj);
    void posPlayer(float dx);
    bool chequearColisiones();
    bool chequearExplosion();
    void MovLateral();
    void nasta();
    int getNasta();
    bool getChoco(){return this->choco;};
    bool getChoqueLateral(){return this->choqueLateral;};
    void setChoco(bool new_choco){choco=new_choco;};

    virtual ~Game();

private:
    QList<Obstaculo *> obstaculos;
    Borde * raid;
    Player *jugador;
    Fondo *fondito;
    bool choco=false;
    int * random;
    bool choqueLateral;
    int incrementoPuntaje;
    int contadorChoque = 0;

};

#endif // GAME_H
