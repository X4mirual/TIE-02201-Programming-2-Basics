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
    timer->setInterval(200); //TODO: make 1000
    connect(timer, SIGNAL(timeout()), this, SLOT(moveTetrominoDown()));

}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent* event) {
    // changing the color of the circle between red and blue
    if(event->key() == Qt::Key_Space) {
        on_dropTetromino_clicked();
    }
    if(event->key() == Qt::Key_D) {
        moveTetromino(1,0);
    }
    if(event->key() == Qt::Key_A) {
        moveTetromino(-1,0);
    }
    if(event->key() == Qt::Key_S) {
        moveTetromino(0,1);
    }
}


void MainWindow::on_dropTetromino_clicked() {
    std::vector<QGraphicsRectItem*> thisTetromino;

    QBrush redBrush(Qt::red);
    QPen blackPen(Qt::black);

    int i = 0;
    QGraphicsRectItem* oneRect;
    int n = 6; //which tetromino type
    int num;
    while(i < tetrominos_.at(n).size()) {
        num = tetrominos_.at(n).at(i); //... .at(3). ... choose which type of tetromino
        qDebug() << i << num;
        if(num == 1) {
            //Jokainen neliö on luotava pisteeseen (x,y) = 0,0 jotta myöhemmin neliöiden ymmärtämä koordinaatisto alkaa tuosta psiteestä
            oneRect = scene_->addRect(0, 0, SQUARE_SIDE, SQUARE_SIDE, blackPen, redBrush);
            oneRect->moveBy((BORDER_RIGHT/2 - SQUARE_SIDE*2) + (i%4)*SQUARE_SIDE, (i/4)*SQUARE_SIDE);
            thisTetromino.push_back(oneRect);
        }
        ++i;
    }
    tetrominoes_.push_back(thisTetromino);
    timer->start();
}

void MainWindow::moveTetrominoDown() {
    moveTetromino(0,1);
}

// Order tetromino to move in direction of coordinate modifiers
void MainWindow::moveTetromino(int x_modifier, int y_modifier) {
    //tetromino to be moved is last tetromino added to vector
    std::vector<QGraphicsRectItem*> tetromino = tetrominoes_.at(tetrominoes_.size() - 1);

    //Each square of tetromino must be within scene after move or no square will not be moved
    for(auto square : tetromino) {
        if(not scene_->sceneRect().contains(square->x() + x_modifier*SQUARE_SIDE, square->y() + y_modifier*SQUARE_SIDE)) {
            return;
        }
        for(auto tetVecItr = tetrominoes_.begin(); tetVecItr != tetrominoes_.end() -1; ++tetVecItr) {
            for(auto stillSquare: (*tetVecItr)) {
                //Timer will not stop if there is a tetromino on the right (with same y-coordinate),
                //but it will not move onto it
                if(square->x() + x_modifier*SQUARE_SIDE == stillSquare->x() && square->y() == stillSquare->y()) {
                    return;
                }
                //Once timer is stopped, last tetromino added to vector will not be moved again
                //If there is a still square under moving square, stop movement downwards
                if(square->x() == stillSquare->x() && square->y() + SQUARE_SIDE == stillSquare->y()) {
                    timer->stop();
                    return;
                }
            }
        }
    }
    for(auto square : tetromino) {
        square->moveBy(x_modifier*SQUARE_SIDE, y_modifier*SQUARE_SIDE);
    }
}























