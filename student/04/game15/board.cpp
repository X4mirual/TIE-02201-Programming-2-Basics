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
#include <string>



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
    std::vector<unsigned int> req_numbers
    {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
    std::stringstream iss(syotetty);
    int i;
    while (iss >> i) {
        numbers.push_back(i);
    }
    for (int i = 0; i < req_numbers.size(); ++i) {
        if (std::find(numbers.begin(), numbers.end(), req_numbers.at(i))
                == numbers.end()) {
            std::cout << "Number " << req_numbers.at(i)
                      << " is missing" << std::endl;
            exit(0);
        }
    }
    grid_ = make_1D_to_2D_vector(numbers);

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
    if (direction == 'q') {
        exit(1);
    }
    int num_lkm = komento.length()-2; //numeroiden lukumäärä komennossa
    int tile = std::stoi(komento.substr(2,num_lkm));
    int x = -1;
    int y = -1;
    for (int j = 0; j < grid_.size(); j++) {
        for (int i = 0; i < grid_.at(j).size(); i++) {
            if (grid_.at(j).at(i) == tile) {
                x = i;
                y = j;
                break;
            }
        }
    }
    int tyhja = 16;
    std::string komennot = "wasd";
    if (std::find(komennot.begin(), komennot.end(), direction) == komennot.end()) {
        std::cout << "Unknown command: " << direction << std::endl;
    }
    else if (x == -1 && y == -1) {
        std::cout << "Invalid number: " << tile << std::endl;
    }
    else if (direction == 'w') {
        if (grid_.at(y-1).at(x) == tyhja) {
            grid_.at(y-1).at(x) = tile;
            grid_.at(y).at(x) = tyhja;
        }
        else {
            std::cout << "Impossible direction: " << direction
                      << std::endl;
        }
    }
    else if (direction == 'a') {
        if (grid_.at(y).at(x-1) == tyhja) {
            grid_.at(y).at(x-1) = tile;
            grid_.at(y).at(x) = tyhja;
        }
        else {
            std::cout << "Impossible direction: " << direction
                      << std::endl;
        }
    }
    else if (direction == 's') {
        if (grid_.at(y+1).at(x) == tyhja) {
            grid_.at(y+1).at(x) = tile;
            grid_.at(y).at(x) = tyhja;
        }
        else {
            std::cout << "Impossible direction: " << direction
                      << std::endl;
        }
    }
    else if (direction == 'd') {
        if (grid_.at(y).at(x+1) == tyhja) {
            grid_.at(y).at(x+1) = tile;
            grid_.at(y).at(x) = tyhja;
        }
        else {
            std::cout << "Impossible direction: " << direction
                      << std::endl;
        }
    }


}
