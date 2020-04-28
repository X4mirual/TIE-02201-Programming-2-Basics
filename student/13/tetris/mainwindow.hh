#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <QPushButton>
#include <QGraphicsScene>
#include <QGraphicsItem> //itemAt
#include <QGraphicsRectItem>
#include <random>
#include <QDebug>
#include <QTimer>
#include <vector> //rbegin, rend
#include <QRect> // moveTo
#include <QKeyEvent> //read keystrockes

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void keyPressEvent(QKeyEvent* event) override;

private slots:
    void on_dropTetrominoButton_clicked();
    void moveTetrominoDown();
    void moveTetromino(int x_modifier, int y_modifier);
    void mirrorTetromino();

    void on_newGameButton_clicked();

private:
    Ui::MainWindow* ui;
    QGraphicsScene* scene_;
    QTimer* timer;
    std::vector<QColor> colours_ = {Qt::cyan, Qt::blue, Qt::magenta,
                                    Qt::yellow, Qt::green, Qt::darkMagenta, Qt::red};

    // Constants describing scene coordinates
    // Copied from moving circle example and modified a bit
    const int BORDER_UP = 0;
    const int BORDER_DOWN = 480; // 260; (in moving circle)
    const int BORDER_LEFT = 0;
    const int BORDER_RIGHT = 240; // 680; (in moving circle)

    // Size of a tetromino component
    const int SQUARE_SIDE = 20;
    // Number of horizontal cells (places for tetromino components)
    const int COLUMNS = BORDER_RIGHT / SQUARE_SIDE;
    // Number of vertical cells (places for tetromino components)
    const int ROWS = BORDER_DOWN / SQUARE_SIDE;

    // Constants for different tetrominos and the number of them
    enum Tetromino_kind {HORIZONTAL,
                         LEFT_CORNER,
                         RIGHT_CORNER,
                         SQUARE,
                         STEP_UP_RIGHT,
                         PYRAMID,
                         STEP_UP_LEFT,
                         NUMBER_OF_TETROMINOS};
    // From the enum values above, only the last one is needed in this template.
    // Recall from enum type that the value of the first enumerated value is 0,
    // the second is 1, and so on.
    // Therefore the value of the last one is 7 at the moment.
    // Remove those tetromino kinds above that you do not implement,
    // whereupon the value of NUMBER_OF_TETROMINOS changes, too.
    // You can also remove all the other values, if you do not need them,
    // but most probably you need a constant value for NUMBER_OF_TETROMINOS.

    // VAI TETROMINOT NÄIN?
    std::vector<std::vector<int>> tetrominos_ = {
                                    {1,1,1,1,
                                    0,0,0,0},
                                    {1,0,0,0,
                                    1,1,1,0},
                                    {0,0,1,0,
                                    1,1,1,0},
                                    {0,1,1,0,
                                    0,1,1,0},
                                    {0,1,1,0,
                                    1,1,0,0},
                                    {0,1,0,0,
                                    1,1,1,0},
                                    {1,1,0,0,
                                    0,1,1,0}
                                   };

    std::vector<std::vector<QGraphicsRectItem*>> tetrominoes_;


    // For randomly selecting the next dropping tetromino
    std::default_random_engine randomEng;
    std::uniform_int_distribution<int> distr;

    // More constants, attibutes, and methods

    void endGame();

};

#endif // MAINWINDOW_HH
