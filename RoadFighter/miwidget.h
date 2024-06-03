#ifndef MIWIDGET_H
#define MIWIDGET_H

#include <QWidget>
#include <QTimer>
#include <QKeyEvent>
#include <QMouseEvent>
#include "game.h"
#include "QLabel"


class MiWidget : public QWidget
{
    Q_OBJECT

public:
    MiWidget(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;
    void keyReleaseEvent(QKeyEvent *event) override;
    void configurarGrafica();
    void IniciarJuego();

private:
    QLabel* Nasta;
    QLabel* Puntuacion;
    QTimer timer;
    QTimer timer_spawn;
    QTimer timer_keys;
    Game *game;
    QMap<int,bool> keys;
    float velocidad=0;
    int time_refresco=20;
    int incremento=0;
    int score=0;
private slots:
    void timerOutEvent();
    void spawnEnemiesEvent();
    void ConsumoNafta();
    void actualizarPuntaje();


};

#endif // MIWIDGET_H
