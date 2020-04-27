#include "mainwindow.hh"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // We need a graphics scene in which to draw rectangles.
    scene_ = new QGraphicsScene(this);

    // The graphicsView object is placed on the window
    // at the following coordinates, but if you want
    // different placement, you can change their values.
    int left_margin = 100; // x coordinate
    int top_margin = 150; // y coordinate

    // The width of the graphicsView is BORDER_RIGHT added by 2,
    // since the borders take one pixel on each side
    // (1 on the left, and 1 on the right).
    // Similarly, the height of the graphicsView is BORDER_DOWN added by 2.
    ui->graphicsView->setGeometry(left_margin, top_margin,
                                  BORDER_RIGHT + 2, BORDER_DOWN + 2);
    ui->graphicsView->setScene(scene_);

    // The width of the scene_ is BORDER_RIGHT decreased by 1 and
    // the height of it is BORDER_DOWN decreased by 1, because
    // each square of a tetromino is considered to be inside the sceneRect,
    // if its upper left corner is inside the sceneRect.
    scene_->setSceneRect(0, 0, BORDER_RIGHT - 1, BORDER_DOWN - 1);

    // Setting random engine ready for the first real call.
    int seed = time(0); // You can change seed value for testing purposes
    randomEng.seed(seed);
    distr = std::uniform_int_distribution<int>(0, NUMBER_OF_TETROMINOS - 1);
    distr(randomEng); // Wiping out the first random number (which is almost always 0)
    // After the above settings, you can use randomEng to draw the next falling
    // tetromino by calling: distr(randomEng) in a suitable method.

    // Add more initial settings and connect calls, when needed.

    timer = new QTimer;
    timer->setInterval(1000);
    connect(timer, SIGNAL(timeout()), this, SLOT(moveTetrominoDown()));

}

MainWindow::~MainWindow() {
    delete ui;
}


void MainWindow::on_dropTetromino_clicked() {
    std::vector<QGraphicsRectItem*> thisTetromino;

    QBrush redBrush(Qt::red);
    QPen blackPen(Qt::black);

    int i = 0;
    int num;
    while(i < 8) {
        num = tetrominos_.at(1).at(i); //... .at(3). ... choose which type of tetromino
        qDebug() << i << num;
        if(num == 1) {
            thisTetromino.push_back( scene_->addRect((BORDER_RIGHT/2 - SQUARE_SIDE*2) + (i%4)*SQUARE_SIDE ,
                            (i/4)*SQUARE_SIDE, SQUARE_SIDE, SQUARE_SIDE, blackPen, redBrush) );
        }
        ++i;
    }
    tetrominoes_.push_back(thisTetromino);
    timer->start();
}

void MainWindow::moveTetrominoDown() {
    std::vector<QGraphicsRectItem*> tetromino = tetrominoes_.at(0);//tetrominoes_.end() - 1);

    //Move each square down until it reaches border
    for(auto square : tetromino) {
        if(scene_->sceneRect().contains(square->x(), square->y() + 2*SQUARE_SIDE)) {
            square->moveBy(0, SQUARE_SIDE);
        }
        // if _tetromino_ (not each square) can't move down anymore
        else {
            timer->stop();
            return;
        }
    }
}


























