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

//laita esittelyt ja varsinaiset .cpp:ssä olevat määrittelyt samaan järjestykseen

class Board
{
public:
    //kommentti
    void make_board_to_order(std::string);

    // Prints the game grid
    void print();

    //kommentti
    void move_tiles(std::string komento);

    // Shuffles the numbers vector by using seed as a seed value
    void my_shuffle(int seed_num); // siirrä privateksi, jos ehtii

    //komentti
    std::vector<std::vector<unsigned int>>
    make_1D_to_2D_vector(std::vector<unsigned int> numbers);


private:

    // Game grid for the 15 puzzle | vektori grid_, jolle tallennetaan luvut
    std::vector<std::vector<unsigned int>> grid_;

};

#endif // BOARD_HH
