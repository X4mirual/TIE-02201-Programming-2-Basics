/* Game15 (or puzzle 15) : Template code
 *
 * Class: Board
 *
 * Program author ( Fill with your own info )
 * Name: Teemu Teekkari
 * Student number: 123456
 * UserID: teekkart ( Necessary due to gitlab folder naming. )
 * E-Mail: teemu.teekkari@tuni.fi
 *
 * Notes:
 *
 * */

#include "board.hh"
#include <iostream>
#include <iomanip>

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

void Board::my_shuffle(std::vector<unsigned int> &numbers, int seed)
{
    std::default_random_engine randomEng(seed);
    std::uniform_int_distribution<int> distr(0, numbers.size() - 1);
    for(unsigned int i = 0; i < numbers.size(); ++i)
    {
        unsigned int random_index = distr(randomEng);
        unsigned int temp = numbers.at(i);
        numbers.at(i) = numbers.at(random_index);
        numbers.at(random_index) = temp;
    }
}

