#include "miwidget.h"
#include <QProcess>
#include <QString>


MiWidget::MiWidget(QWidget *parent):QWidget(parent){
    //Cambio el foco al widget
    this->setFocusPolicy(Qt::StrongFocus);      //configura que widget reciba los eventos de teclas
    //Timer spawneo de obstaculos de 500 milisegundos
    timer_spawn.setInterval(500);
    connect(&timer_spawn, &QTimer::timeout, this, &MiWidget::spawnEnemiesEvent);    //Conecto el timer_spawn a las funciones:
    connect(&timer_spawn, &QTimer::timeout, this, &MiWidget::ConsumoNafta);         //spawnEnemiesEvent, ConsumoNafta y
    connect(&timer_spawn, &QTimer::timeout, this, &MiWidget::actualizarPuntaje);    //actualizarpuntaje
    //Timer de keys de 20 milisegundos
    timer_keys.setInterval(20);
    connect(&timer_keys, &QTimer::timeout, this, &MiWidget::timerOutEvent);     //Conecto el timer de refresco de keys para
    timer_keys.start();                                                         //la función timerOutEvent
    //Timer Refresco
    timer.setInterval(time_refresco);
    connect(&timer,SIGNAL(timeout()),this,SLOT(update()));

    //Creo el game que se encarga de crear todo
    game= new Game();
    configurarGrafica();
    IniciarJuego();
}


//Paint Event
void MiWidget::paintEvent(QPaintEvent *event){
    QPainter  p(this);
    p.setViewport(0,0,width(),height());    //fija la dependencia de tamaño de widget con mainwindow
    p.setWindow(0,0,500,500);               //define el tamaño inicial de mainwindow
    game->dibujar(&p);                      //dibuja todo el game
    if(game->chequearExplosion()){  //chequea el estado de explosión del auto
        game->dibujar(&p);          //redibuja para que se vea la explosión
        timer.stop();               //para el juego
        timer_spawn.stop();
    }

    if(game->chequearColisiones()){     //chequeo la colisión
        if((game->getChoco())==false){  //para ver si es con un auto nafta
            score=score+1000;           //y que sume 1000 al score
        }
    }
    if(game->getChoco()){                   //si el booleano choco es true
        if(incremento<15 ){                 //significa que chocó con algo que no es un auto nafta
            timer_keys.stop();              //entonces se ejecuta el desplazamiento de animación de choque
            timer_spawn.stop();
            if (game->getChoqueLateral()){
                game->posPlayer(-3.5);
            }
            else{
                game->posPlayer(3.5);
            }
            velocidad=0;
            incremento=incremento+1;
        }
        else{
            game->setChoco(false);
            incremento=0;
            timer_keys.start();
            timer_spawn.start();
        }
    }

    Nasta->setText("Nafta: \n" + QString::number(game->getNasta()));    //se actualiza la etiqueta nafta
    Puntuacion->setText("Score: \n" + QString::number(score));          //se actualiza la etiqueta puntuación
}
//Configuracion Grafica
void MiWidget::configurarGrafica(){     //se configuran las etiquetas nafta y puntuación
    Nasta= new QLabel (this);
    Nasta->setFont(QFont("Arial", 12));
    Nasta->setAlignment(Qt::AlignCenter);
    Nasta->move(380,10);

    Puntuacion=new QLabel (this);
    Puntuacion->setFont(QFont("Arial", 12));
    Puntuacion->setAlignment(Qt::AlignCenter);
    Puntuacion->move(380,60);

}
void MiWidget::IniciarJuego(){  //inicia los timers
    timer_spawn.start();
    timer.start();
}

//Consumo de Nafta
void MiWidget::ConsumoNafta(){  //se llama la función que reduce el nivel de nafta
   game->nasta();
}


void MiWidget::timerOutEvent(){ //chequea si hay teclas apretadas
    if(keys[Qt::Key_A])
    {
        if (velocidad<15){              //si se aprieta la A aumenta la velocidad hasta que sea de 15
            velocidad=velocidad+0.25;
        }
        game->ActualizarLista(velocidad);
    }

    if(keys[Qt::Key_A]==false)
    {
        if (velocidad>-2){
            velocidad=velocidad-0.25;   //si se suelta la A, se reduce la velocidad
        }
        game->ActualizarLista(velocidad);   //y se llama a la función que controla la lista de obstáculos
    }
    if(keys[Qt::Key_Tab]){
        delete game;
        game=new Game();    //Reinicio el Juego con la tecla Tab
        score=0;
        IniciarJuego();
    }
    if(keys[Qt::Key_Left])  //con la izquierda y la derecha se mueve el jugador
    {
        game->posPlayer(-5);
    }
    if(keys[Qt::Key_Right])
    {
        game->posPlayer(5);
    }

}

void MiWidget::keyReleaseEvent(QKeyEvent *event){
    keys[event->key()] = false;
    QWidget::keyReleaseEvent(event);
}

void MiWidget::keyPressEvent(QKeyEvent *event){
    keys[event->key()] = true;
    QWidget::keyPressEvent(event);
}

//Spawn de obstáculos
void MiWidget::spawnEnemiesEvent(){
    game->GenerarObstaculosRandom();
    game->MovLateral();
}
//Puntaje
void MiWidget::actualizarPuntaje(){
    score=score+10;
}




