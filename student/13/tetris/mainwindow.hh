/* Class: Mainwindow
 * ----------
 * TIE-02201/TIE-02207 SPRING 2020
 * ----------
 * Tetris game.
 * Game instructions in instructions.txt.
 *
 * Controls:
 * Space: drop new tetromino
 * A: move latest tetromino to the left
 * S: move latest tetromino downwards
 * D: move latest tetromino to the right
 * N: start new game
 *
 * Author of code made onto template:
 * Name: Lauri Hiltunen
 * Student number: 274422
 * UserID: hiltunen
 * E-Mail: lauri.hiltunen@tuni.fi
 *
 * */

#ifndef MAINWINDOW_HH
#define MAINWINDOW_HH

#include <QMainWindow>
#include <QPushButton>
#include <QGraphicsScene>
#include <QGraphicsItem>
#include <QGraphicsRectItem>
#include <random>
#include <QTimer>
#include <QKeyEvent>

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
    /**
     * @brief on_dropTetrominoButton_clicked
     * Free new tetromino to fall down
     */
    void on_dropTetrominoButton_clicked();

    /**
     * @brief moveTetrominoDown
     * Parameterless slot required by timer
     */
    void moveTetrominoDown();

    /**
     * @brief onTimeChange
     * Advance time played and display it
     */
    void onTimeChange();

    /**
     * @brief on_newGameButton_clicked
     * Start new game
     */
    void on_newGameButton_clicked();

private:
    Ui::MainWindow* ui;
    QGraphicsScene* scene_;
    QTimer* timer;
    int timerInterval_ = 1000;
    std::vector<QColor> colours_ = {Qt::cyan, Qt::blue, Qt::magenta,
                            Qt::yellow, Qt::green, Qt::darkMagenta, Qt::red};
    int seconds_played_ = 0;

    //Constants describing scene coordinates
    const int BORDER_UP = 0;
    const int BORDER_DOWN = 480;
    const int BORDER_LEFT = 0;
    const int BORDER_RIGHT = 240;

    //Size of a tetromino component
    const int SQUARE_SIDE = 20;
    //Number of horizontal cells (places for tetromino components)
    const int COLUMNS = BORDER_RIGHT / SQUARE_SIDE;
    //Number of vertical cells (places for tetromino components)
    const int ROWS = BORDER_DOWN / SQUARE_SIDE;

    //Different tetrominos are configured (1: square, 0: no square)
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

    //For randomly selecting the next dropping tetromino
    std::default_random_engine randomEng;
    std::uniform_int_distribution<int> distr;

    /**
     * @brief tetMovementGameWalls
     * @param square
     * @param xModifier
     * @param yModifier
     * Check for game area boundaries and prohibit movement if trying to move
     * outside of game area
     */
    void tetMovementGameWalls(QGraphicsRectItem* square, int& xModifier,
                                                            int& yModifier);

    /**
     * @brief tetMovementOtherTetrominoes
     * @param square
     * @param otherSquare
     * @param xModifier
     * @param yModifier
     * Check for other tetrominoes in direction of movement and prohibit
     * movement onto other tetrominoes
     */
    void tetMovementOtherTetrominoes(QGraphicsRectItem* square,
               QGraphicsRectItem* otherSquare, int& xModifier, int& yModifier);

    /**
     * @brief moveTetromino
     * @param xModifier
     * @param yModifier
     * Move newest tetromino in direction of coordinate modifiers if possible
     */
    void moveTetromino(int xModifier, int yModifier);

    /**
     * @brief checkAndSetGameOver
     * @param square
     * If square of tetromino is high enough when timer stops, end game
     */
    void checkAndSetGameOver(QGraphicsRectItem* square);

    /**
     * @brief displayPlayedTime
     */
    void displayPlayedTime();

    /**
     * @brief updateDifficulty
     * Make timer faster (tetrominos fall faster and game time count faster)
     * every 30 sec
     */
    void updateDifficulty();

};

#endif // MAINWINDOW_HH
