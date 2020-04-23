#include "mainwindow.hh"
#include "ui_mainwindow.h"
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    timer = new QTimer;
    timer->setInterval(1000);
    connect(timer, SIGNAL(timeout()), this, SLOT(on_timeChange()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_startButton_clicked()
{
    if(not timer->isActive()) {
        timer->start();
    }
}

void MainWindow::on_stopButton_clicked()
{
    if(timer->isActive()) {
        timer->stop();
    }
}

void MainWindow::on_timeChange()
{
    ++seconds_;
    updateDisplay();
}

void MainWindow::on_resetButton_clicked()
{
    on_stopButton_clicked();
    seconds_ = 0;
    updateDisplay();
}

void MainWindow::updateDisplay()
{
    ui->lcdNumberSec->display(seconds_%60);
    ui->lcdNumberMin->display(seconds_/60);
}













