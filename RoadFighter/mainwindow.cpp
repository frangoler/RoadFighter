#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPainter>
#include "game.h"

MainWindow::MainWindow(QWidget *parent) //Se configura el mainwindow
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}



