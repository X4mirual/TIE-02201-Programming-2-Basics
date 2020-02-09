/* Game15 (or puzzle 15) : Template code
 *
 * Class: Board
 *  Describes a two-dimensional grid for puzzle 15 with necessary functions.
 *
 * Program author
 * Name: Lauri Hiltunen
 * Student number: 274422
 * UserID: hiltunen
 * E-Mail: lauri.hiltunen@tuni.fi
 *
 * Notes:
 *
 * */

#ifndef BOARD_HH
#define BOARD_HH
#include <vector>
#include <iostream>

const int SIZE = 4;

struct Command_to_move {
    std::string direction;
    int tile;
};

//laita esittelyt ja varsinaiset .cpp:ssä olevat määrittelyt samaan järjestykseen

class Board
{
public:
    // For creating and initializing the grid, you have at least two choices:
    // 1. Implement a constructor that fills the game grid with empties or such
    // and two initialize methods
    // 2. Implement two constructors, one for each initialization way

    void make_board_to_order(std::string);

    std::vector<std::vector<unsigned int>> get_grid();

    // Prints the game grid
    void print();

    void move_tiles(std::string komento);

    // Shuffles the numbers vector by using seed as a seed value
    void my_shuffle(int seed_num); // siirrä privateksi, jos ehtii

    std::vector<std::vector<unsigned int>>
    make_1D_to_2D_vector(std::vector<unsigned int> numbers);

    // Game grid for the 15 puzzle | vektori grid_, jolle tallennetaan luvut
    std::vector<std::vector<unsigned int>> grid_;

private:


    // More attributes/methods
};

#endif // BOARD_HH
