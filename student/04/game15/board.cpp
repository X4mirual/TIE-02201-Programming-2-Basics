/* Game15 (or puzzle 15)
 *
 * Class: Board
 *
 * Program author
 * Name: Lauri Hiltunen
 * Student number: 274422
 * UserID: hiltunen
 * E-Mail: lauri.hiltunen@tuni.fi
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

void Board::make_board_by_shuffle(int seed_num) {
    std::vector<unsigned int> numbers
        {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
    std::default_random_engine randomEng(seed_num);
    std::uniform_int_distribution<int> distr(0, numbers.size() - 1);
    for(unsigned int i = 0; i < numbers.size(); ++i) {
        unsigned int random_index = distr(randomEng);
        unsigned int temp = numbers.at(i);
        numbers.at(i) = numbers.at(random_index);
        numbers.at(random_index) = temp;
    }
    check_solvability(numbers);
    grid_ = make_1D_to_2D_vector(numbers);
}

void Board::make_board_to_order(std::vector<unsigned int> numbers) {
    std::vector<unsigned int> req_numbers
    {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16};
    //Tarkista, että kaikki 16 lukua annettu
    //Päätä ohjelma (0), jos kaikkia lukuja ei annettu
    for (unsigned int i = 0; i < req_numbers.size(); ++i) {
        if (std::find(numbers.begin(), numbers.end(), req_numbers.at(i))
                == numbers.end()) {
            std::cout << "Number " << req_numbers.at(i)
                      << " is missing" << std::endl;
            exit(1);
        }
    }
    check_solvability(numbers);
    grid_ = make_1D_to_2D_vector(numbers);
}

void Board::print() {
    for(unsigned int x = 0; x < SIZE; ++x) {
        std::cout << std::string(PRINT_WIDTH * SIZE + 1, '-') << std::endl;
        for(unsigned int y = 0; y < SIZE; ++y) {
            std::cout << "|" << std::setw(PRINT_WIDTH - 1);
            if(grid_.at(x).at(y) != EMPTY) {
                std::cout << grid_.at(x).at(y);
            }
            else {
                std::cout << ".";
            }
        }
        std::cout << "|" << std::endl;
    }
    std::cout << std::string(PRINT_WIDTH * SIZE + 1, '-') << std::endl;
}

void Board::move_tiles(std::string komento) {
    char direction = komento.at(0);
    if (direction == 'q') {
        exit(0);
    }
    int num_lkm = komento.length()-2; //numeroiden lukumäärä komennossa
    unsigned int tile = std::stoi(komento.substr(2,num_lkm));
    int x = -1;
    int y = -1;
    for (unsigned int j = 0; j < grid_.size(); j++) {
        for (unsigned int i = 0; i < grid_.at(j).size(); i++) {
            if (grid_.at(j).at(i) == tile) {
                x = i;
                y = j;
                break;
            }
        }
    }

    std::string komennot = "wasd";
    if (std::find(komennot.begin(), komennot.end(), direction) == komennot.end()) {
        std::cout << "Unknown command: " << direction << std::endl;
    }
    else if (x == -1 && y == -1) {
        std::cout << "Invalid number: " << tile << std::endl;
    }
    else if (direction == 'w') {
        if (grid_.at(y-1).at(x) == EMPTY) {
            grid_.at(y-1).at(x) = tile;
            grid_.at(y).at(x) = EMPTY;
        }
        else {
            std::cout << "Impossible direction: " << direction
                      << std::endl;
        }
    }
    else if (direction == 'a') {
        if (grid_.at(y).at(x-1) == EMPTY) {
            grid_.at(y).at(x-1) = tile;
            grid_.at(y).at(x) = EMPTY;
        }
        else {
            std::cout << "Impossible direction: " << direction
                      << std::endl;
        }
    }
    else if (direction == 's') {
        if (grid_.at(y+1).at(x) == EMPTY) {
            grid_.at(y+1).at(x) = tile;
            grid_.at(y).at(x) = EMPTY;
        }
        else {
            std::cout << "Impossible direction: " << direction
                      << std::endl;
        }
    }
    else if (direction == 'd') {
        if (grid_.at(y).at(x+1) == EMPTY) {
            grid_.at(y).at(x+1) = tile;
            grid_.at(y).at(x) = EMPTY;
        }
        else {
            std::cout << "Impossible direction: " << direction
                      << std::endl;
        }
    }
}

void Board::check_if_won() {
    std::vector<unsigned int> one_d_grid = get_1D_grid_();
    if (std::is_sorted(one_d_grid.begin(), one_d_grid.end())) {
        std::cout << "You won!" << std::endl;
        exit(0);
    }
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

std::vector<unsigned int> Board::get_1D_grid_() {
    std::vector<unsigned int> numbers_1D;
    for(unsigned int i = 0; i < grid_.size(); ++i) {
        for(unsigned int j = 0; j < grid_.at(i).size(); ++j) {
            numbers_1D.push_back(grid_.at(i).at(j));
        }
    }
    return numbers_1D;
}

void Board::check_solvability(std::vector<unsigned int> numbers) {
    int inversion_count = get_inv_count(numbers);
    int empty_on_row = get_empty_row_num(numbers);
    if (empty_on_row % 2 != inversion_count % 2) { //on ratkaistavissa, jatketaan hommia
        std::cout << "Game is solvable: Go ahead!" << std::endl;
    }
    else { // ei ole ratkaistavissa, lopetetaan puuhastelu
        std::cout << "Game is not solvable. What a pity." << std::endl;
        exit(0);
    }
}

int Board::get_inv_count(std::vector<unsigned int> numbers) {
    int inv_count = 0;
    int vector_length = numbers.size();
    for (int i = 0; i < vector_length; ++i) {
        for (int j = 0; j < vector_length - i; ++j) {
            if (numbers.at(i) > numbers.at(i+j) && numbers.at(i) != EMPTY) {
                ++inv_count;
            }
        }
    }
    return inv_count;
}

int Board::get_empty_row_num(std::vector<unsigned int> numbers) {
    auto it = std::find(numbers.begin(), numbers.end(), 16);
    int index = std::distance(numbers.begin(), it);
    int row = index / 4;
    return row;
}
