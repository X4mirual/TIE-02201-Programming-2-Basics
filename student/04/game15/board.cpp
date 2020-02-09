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
#include <sstream>
#include <algorithm>



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

void Board::make_board_to_order(std::string syotetty) {
    std::vector<unsigned int> numbers;
    std::stringstream iss(syotetty);
    int i;
    while (iss >> i) {
        numbers.push_back(i);
    }
    grid_ = make_1D_to_2D_vector(numbers);
}

std::vector<std::vector<unsigned int>> Board::get_grid() {
    return grid_;
}

std::vector<std::vector<unsigned int>>
Board::make_1D_to_2D_vector(std::vector<unsigned int> numbers) {
    std::vector<std::vector<unsigned int>> numbers2D
    {{0,0,0,0}, {0,0,0,0}, {0,0,0,0}, {0,0,0,0}};
    for (unsigned int i = 0; i < numbers.size(); i++) {
        int row = i / 4;
        int col = i % 4;
        numbers2D.at(row).at(col) = numbers[i];
    }
    return numbers2D;
}


void Board::my_shuffle(int seed_num) {
    std::vector<unsigned int> numbers
        {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
    std::default_random_engine randomEng(seed_num);
    std::uniform_int_distribution<int> distr(0, numbers.size() - 1);
    for(unsigned int i = 0; i < numbers.size(); ++i) {
        unsigned int random_index = distr(randomEng); //5
        unsigned int temp = numbers.at(i); //1
        numbers.at(i) = numbers.at(random_index);
        numbers.at(random_index) = temp;
    }
    grid_ = make_1D_to_2D_vector(numbers);
}

void Board::move_tiles(std::string komento) {
    char direction = komento.at(0);

    int pituus = komento.length()-2;
    int tile = std::stoi(komento.substr(2,pituus));
    std::cout << tile << std::endl;
    int x;
    int y;
    for (int j = 0; j < grid_.size(); j++) {
        for (int i = 0; i < grid_.at(j).size(); i++) {
            if (grid_.at(j).at(i) == tile) {
                x = i;
                y = j;
                break;
            }
        }
    }
    if (direction == 'w') {
        grid_.at(y-1).at(x) = tile;
        grid_.at(y).at(x) = 16;
    }
    if (direction == 'a') {
        grid_.at(y).at(x-1) = tile;
        grid_.at(y).at(x) = 16;
    }
    if (direction == 's') {
        grid_.at(y+1).at(x) = tile;
        grid_.at(y).at(x) = 16;
    }
    if (direction == 'd') {
        grid_.at(y).at(x+1) = tile;
        grid_.at(y).at(x) = 16;
    }
    if (direction == 'q') {
        std::cout << "komento oli q" << std::endl;
    }




}





















