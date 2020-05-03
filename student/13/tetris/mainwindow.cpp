/*Is this the right place for this?
 *
 * Tetrominos can be moved sideways after their automatic movement downwards has been stopped.
 * It is allowed to this way leave a tetromino "hanging in the air" (by calling a new tetromino to be dropped while previous is not
 * down yet) as it is the players own choice to perform badly.
 *
 * If tetromino stops so that there is no space for new tetromino (tetromino stops so that there is one row free space left),
 * then game has ended.
 * Moving tetromino sideways after it has stopped moving vertically automatically does not count into game time
*/


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
    distr(randomEng); // Wiping out the first random number

    timer = new QTimer;
    timer->setInterval(timerInterval_);
    connect(timer, SIGNAL(timeout()), this, SLOT(moveTetrominoDown()));
    connect(timer, SIGNAL(timeout()), this, SLOT(onTimeChange()));
    ui->displayPlayedTime->setPalette(Qt::red);
    ui->displayPlayedTime->display("0:00");
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::keyPressEvent(QKeyEvent* event) {
    if(event->key() == Qt::Key_N) {
        on_newGameButton_clicked();
    }
    else if(ui->gameStatus->text() == "Game over!") {
        return;
    }
    else if(event->key() == Qt::Key_Space) {
        //Running timer means a tetromino is already falling
        if(not timer->isActive()) {
            on_dropTetrominoButton_clicked();
        }
    }
    else if(event->key() == Qt::Key_A) {
        moveTetromino(-1,0);
    }
    else if(event->key() == Qt::Key_S) {
        moveTetromino(0,1);
    }
    else if(event->key() == Qt::Key_D) {
        moveTetromino(1,0);
    }
}

void MainWindow::on_dropTetrominoButton_clicked() {
    std::vector<QGraphicsRectItem*> thisTetromino;

    int tetrominoType = distr(randomEng);
    QPen blackPen(Qt::black);
    QBrush Brush(colours_.at(tetrominoType));

    unsigned int i = 0;
    QGraphicsRectItem* oneRect;
    while(i < tetrominoBlueprint_.at(tetrominoType).size()) {
        int num = tetrominoBlueprint_.at(tetrominoType).at(i);
        if(num == 1) {
            //Each square is created at (x,y) = (0,0) so that later the square
            //"knows" its coordinates right
            oneRect = scene_->addRect(0, 0, SQUARE_SIDE, SQUARE_SIDE, blackPen,
                                      Brush);
            oneRect->moveBy((BORDER_RIGHT/2 - SQUARE_SIDE*2) +
                            (i%4)*SQUARE_SIDE, (i/4)*SQUARE_SIDE);
            thisTetromino.push_back(oneRect);
        }
        ++i;
    }
    tetrominoes_.push_back(thisTetromino);
    ui->gameStatus->setText("Playing!");
    ui->newGameButton->setEnabled(true);
    timer->start();
    ui->dropTetrominoButton->setEnabled(false);
}

//Timer requires parameterless slot
void MainWindow::moveTetrominoDown() {
    moveTetromino(0,1);
}

void MainWindow::onTimeChange() {
    ++seconds_played_;
    displayPlayedTime();
    updateDifficulty();
}

void MainWindow::on_newGameButton_clicked() {
    for(auto tetromino : tetrominoes_) {
        for(QGraphicsRectItem *square : tetromino) {
            scene_->removeItem(square);
            delete square;
        }
    }
    tetrominoes_ = {{}};
    ui->newGameButton->setEnabled(false);
    ui->dropTetrominoButton->setEnabled(true);
    ui->gameStatus->setText("Welcome! Press 'Next Tetromino' to play!");
    timer->stop();
    seconds_played_ = 0;
    timerInterval_ = 1000;
    timer->setInterval(timerInterval_);
    displayPlayedTime();
}

void MainWindow::tetMovementGameWalls(QGraphicsRectItem* square,
                                      int& xModifier, int& yModifier) {

    if(not scene_->sceneRect().contains(square->x() + xModifier*SQUARE_SIDE,
                                    square->y() + yModifier*SQUARE_SIDE)) {

        //If tetromino is moving down and hits bottom floor
        if(xModifier == 0) {
            timer->stop();
            ui->dropTetrominoButton->setEnabled(true);
        }
        //When tetromino is trying to move outside of game area, remove
        //possibility for movement
        xModifier = 0;
        yModifier = 0;
    }
}

void MainWindow::tetMovementOtherTetrominoes(QGraphicsRectItem* square,
            QGraphicsRectItem* otherSquare, int& xModifier, int& yModifier) {
    //Tetromino will not move onto still tetromino on the right or
    //left of it (with same y-coordinate, thus make xModifier zero)
    if(square->x() + xModifier*SQUARE_SIDE == otherSquare->x() && square->y()
                                                        == otherSquare->y()) {
        xModifier = 0;
    }

    //If there is a still square directly under moving square
    if(square->x() == otherSquare->x() && square->y() + SQUARE_SIDE ==
                                                        otherSquare->y()) {
        //Stop movement downwards
        timer->stop();
        ui->dropTetrominoButton->setEnabled(true);

        //There is a square directly under moving square so remove vertical
        //movement
        yModifier = 0;
    }
}

void MainWindow::moveTetromino(int xModifier = 0, int yModifier = 1) {
    //Tetromino to be moved is last tetromino added to vector of tetrominoes
    std::vector<QGraphicsRectItem*> tetromino =
            tetrominoes_.at(tetrominoes_.size() - 1);

    for(auto square : tetromino) {
        //If tetromino tries to move outside of game area
        tetMovementGameWalls(square, xModifier, yModifier);

        //Last tetromino (the one moving) not taken into loop
        for(auto tetVecItr = tetrominoes_.begin(); tetVecItr !=
                                        tetrominoes_.end() -1; ++tetVecItr) {
            for(auto otherSquare : (*tetVecItr)) {
                tetMovementOtherTetrominoes(square, otherSquare, xModifier,
                                                                yModifier);
            }
        }
    }

    for(auto square : tetromino) {
        //Move each square of moving tetromino
        square->moveBy(xModifier*SQUARE_SIDE, yModifier*SQUARE_SIDE);

        //Check if square so high game is over
        checkAndSetGameOver(square);
    }
}

void MainWindow::checkAndSetGameOver(QGraphicsRectItem* square) {
    //If square not moving downwards and vertical free space at top is one
    //square (most tetrominoes require two squares space)
    if(not timer->isActive() && square->y() == SQUARE_SIDE) {
        ui->gameStatus->setText("Game over!");
        ui->dropTetrominoButton->setEnabled(false);
    }
}

void MainWindow::displayPlayedTime() {
    std::string text = std::to_string(seconds_played_/60) + ":";
    //Time is 1:02, not 1:2
    if(seconds_played_%60 < 10) {
        text += "0";
    }
    text += std::to_string(seconds_played_%60);
    ui->displayPlayedTime->display(QString::fromStdString(text));
}

void MainWindow::updateDifficulty() {
    if(seconds_played_ % 30 == 0 && timerInterval_ >= 200) {
        timerInterval_ -= 100;
        timer->setInterval(timerInterval_);
    }
}


