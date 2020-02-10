/* Game15 (or puzzle 15)
 *
 * Desc:
 * This program generates a 15 puzzle. The board is 4 x 4,
 * and every round the player chooses a direction and
 * a number tile, making the given tile to be moved to the given direction.
 * Game will end when the numbers 1-15 (1-16) are in the ascending order,
 * starting from top left and proceeding row by row.
 * Empty space is represented by the number 16 in the code (constant EMPTY)
 * and by dot when printing the game board.
 *
 * Program author
 * Name: Lauri Hiltunen
 * Student number: 274422
 * UserID: hiltunen
 * E-Mail: lauri.hiltune@tuni.fi
 *
 * Notes about the program and it's implementation:
 * Space ' ' used as separator when entering commands. Do not give
 * unnecessary spaces, tabs or enter-inputs when giving commands
 * for the program.
 *
 * */

#include "board.hh"
#include <iostream>
#include <string>
#include <random>


// Tekee merkkijonosta 1d vektorin<unsigned int>,
// jossa jokainen luku on oma alkionsa
std::vector<unsigned int> int_line_to_vector(std::string line) {
    std::vector<unsigned int> kentta_1d;
    size_t pos = 0;
    unsigned int segment;
    char separator = ' ';
    while ((pos = line.find(separator)) != std::string::npos) {
        if (pos!= 0) {
            unsigned int segment = std::stoi(line.substr(0, pos));
            kentta_1d.push_back(segment);
            line.erase(0, pos + 1);
        }
        else {
            line.erase(0,1);
        }
    }
    // Viimeinen alkio lisättävä vielä vektoriin
    kentta_1d.push_back(stoi(line));
    return kentta_1d;
}

// C++ vaatii funktiolta tietynlaisen paluuarvon, joten eri funktiota
// merkkijonoista ja luvuista koostuville vektoreille
std::vector<std::string> string_line_to_vector(std::string line) {
    std::vector<std::string> kentta_1d;
    size_t pos = 0;
    std::string segment;
    char separator = ' ';
    while ((pos = line.find(separator)) != std::string::npos) {
        if (pos!= 0) {
            segment = line.substr(0, pos);
            kentta_1d.push_back(segment);
            line.erase(0, pos + 1);
        }
        else {
            line.erase(0,1);
        }
    }
    // Viimeinen alkio lisättävä vielä vektoriin
    kentta_1d.push_back(line);
    return kentta_1d;
}

// Alustaa koko pelin ja alustaa pelikentän
void init_board(Board& kentta) {
    std::cout << "Random initialization (y/n): ";
    std::string arvottukko;
    getline(std::cin, arvottukko);

    while (arvottukko != "y" && arvottukko != "n") {
        std::cout << "Unknown choice: " << arvottukko << std::endl;
        std::cout << "Random initialization (y/n): ";
        getline(std::cin, arvottukko);
    }

    if (arvottukko == "y") {
        std::cout << "Enter a seed value (or an empty line): ";
        std::string s;
        int seed_num;
        getline(std::cin, s);
        if (s == "") { // jos käyttäjä ei syötä siemenlukua
            seed_num = time(NULL);
        }
        else {
            seed_num = stoi(s);
        }
        kentta.make_board_by_shuffle(seed_num);
    }

    else {
        std::cout << "Enter the numbers 1-16 in a "
                     "desired order (16 means empty):" << std::endl;
        std::string line;
        std::vector<unsigned int> kentta_1d;
        bool is_int = true;
        // Käyttäjän on pakko antaa 16kpl lukuja
        while (kentta_1d.size() != 16) {
            getline(std::cin, line);
            kentta_1d = int_line_to_vector(line);
        }
        kentta.make_board_to_order(kentta_1d);
    }
    kentta.print();
    kentta.check_if_won();
}

// Pyörittää peliä, kunnes se tulee päätetyksi jossain funktiossa
void play(Board& kentta) {
    while (true) {
        std::cout << "Dir (command, number): ";
        std::string komento;
        getline(std::cin, komento);
        bool is_int = false;
        std::vector<std::string> komento_vector =
                string_line_to_vector(komento);
        kentta.move_tiles(komento_vector);
        kentta.check_if_won();
        kentta.print();
    }
}

int main() {
    Board kentta = Board();
    init_board(kentta);
    play(kentta);
    // Ohjelman suoritus päätetään funktiossa, jossa se päättyy
}
