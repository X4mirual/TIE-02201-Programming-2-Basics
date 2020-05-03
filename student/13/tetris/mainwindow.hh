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
#include <iostream> // toString(seconds_played_/60)

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
    void onTimeChange();
    void on_newGameButton_clicked();

private:
    Ui::MainWindow* ui;
    QGraphicsScene* scene_;
    QTimer* timer;
    std::vector<QColor> colours_ = {Qt::cyan, Qt::blue, Qt::magenta,
                            Qt::yellow, Qt::green, Qt::darkMagenta, Qt::red};
    int seconds_played_ = 0;

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



    // How different tetrominos are configured (1: square, 0: no square)
    std::vector<std::vector<int>> tetrominoBlueprint_ = {
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
    const int NUMBER_OF_TETROMINOS = tetrominoBlueprint_.size();

    //Tetrominoes that are on game area
    std::vector<std::vector<QGraphicsRectItem*>> tetrominoes_;

    // For randomly selecting the next dropping tetromino
    std::default_random_engine randomEng;
    std::uniform_int_distribution<int> distr;

    /**
     * @brief moveTetromino
     * @param xModifier
     * @param yModifier
     * Move newest tetromino in direction of coordinate modifiers
     */
    void tetMovementGameWalls(QGraphicsRectItem* square, int& xModifier, int& yModifier);

    /**
     * @brief moveTetromino
     * @param xModifier
     * @param yModifier
     * Move newest tetromino in direction of coordinate modifiers
     */
    void tetMovementOtherTetrominoes(QGraphicsRectItem* square, QGraphicsRectItem* otherSquare, int& xModifier, int& yModifier);

    /**
     * @brief moveTetromino
     * @param xModifier
     * @param yModifier
     * Move newest tetromino in direction of coordinate modifiers
     */
    void moveTetromino(int xModifier, int yModifier);

    /**
     * @brief print_info
     * @param print_new_line
     * Print short course info, if print_new_line, the also a newline at the end.
     */
    void checkAndSetGameOver(QGraphicsRectItem* square);

    /**
     * @brief print_info
     * @param print_new_line
     * Print short course info, if print_new_line, the also a newline at the end.
     */
    void displayPlayedTime();

    /**
     * @brief print_info
     * @param print_new_line
     * Print short course info, if print_new_line, the also a newline at the end.
     */
    void removeFullRows();

    /**
     * @brief print_info
     * @param print_new_line
     * Print short course info, if print_new_line, the also a newline at the end.
     */
    bool isFullRow(int x, int y);

    /**
     * @brief print_info
     * @param print_new_line
     * Print short course info, if print_new_line, the also a newline at the end.
     */
    void removeRow(int y);

};

#endif // MAINWINDOW_HH
