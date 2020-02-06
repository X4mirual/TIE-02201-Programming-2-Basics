/* Game15 (or puzzle 15) : Template code
 *
 * Class: Board
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

#include "board.hh"
#include <iostream>
#include <iomanip>
#include <vector>
#include <random>



const int EMPTY = 16;
const unsigned int PRINT_WIDTH = 5;

void Board::print()
{
    for(unsigned int x = 0; x < SIZE; ++x)
    {
        std::cout << std::string(PRINT_WIDTH * SIZE + 1, '-') << std::endl;
        for(unsigned int y = 0; y < SIZE; ++y)
        {
            std::cout << "|" << std::setw(PRINT_WIDTH - 1);
            if(grid_.at(x).at(y) != EMPTY)
            {
                std::cout << grid_.at(x).at(y);
            }
            else
            {
                std::cout << ".";
            }
        }
        std::cout << "|" << std::endl;
    }
    std::cout << std::string(PRINT_WIDTH * SIZE + 1, '-') << std::endl;
}

void Board::make(std::string syotetty) {
    std::vector<std::vector<unsigned int>> numbers
        {{0,0,0,0}, {0,0,0,0}, {0,0,0,0}, {0,0,0,0}};
    int i = 0;
    while (i < 16) {
        numbers.at(i/4).at(i-(i/4)*i) = (unsigned int)syotetty.at(i);
        ++i;
    }

    grid_ = numbers;
}

std::vector<std::vector<unsigned int>> Board::get_grid() {
    return grid_;
}

// syötetään vektori (pituus 16),
//joka sisältää (unsigned int numbersit, int seedin)

void Board::my_shuffle(int seed_num) {
    std::vector<unsigned int> numbers
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    std::default_random_engine randomEng(seed_num);
    std::uniform_int_distribution<int> distr(0, numbers.size() - 1);
    for(unsigned int i = 0; i < numbers.size(); ++i)
    {
        unsigned int random_index = distr(randomEng); //5
        unsigned int temp = numbers.at(i); //1
        numbers.at(i) = numbers.at(random_index);
        numbers.at(random_index) = temp;
    }
    std::vector<std::vector<unsigned int>> numbers2D;
    for (unsigned int i = 0; i < numbers.size(); i++) {
        int row = i / 4;
        int col = i % 4;
        numbers2D[row][col] = numbers[i];
    }
    grid_ = numbers2D;
}

