/* Game15 (or puzzle 15) : Template code
 *
 * Desc:
 *  This program generates a 15 puzzle. The board is SIZE x SIZE,
 * (original was 4x4) and every round the player chooses a direction and
 * a number tile, making the given tile to be moved to the given direction.
 *  Game will end when the numbers 1-15 (1-16) are in the ascending order,
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
 *
 * */

#include "board.hh"
#include <iostream>
#include <string>
#include <random>

void initBoard(Board& kentta) {

    //Siirrä suuri osa privateksi board cpp:hen ja käsittele public-function
    //kutsun kautta.
    //Toteuta tarkastelu, jos syötetään muuta kuin 'y' tai 'n'

    std::cout << "Random initialization (y/n): ";
    std::string arvottukko; //voidaanko laittaa getlinen sisaan?
    getline(std::cin, arvottukko);

    if (arvottukko == "y") {
        std::cout << "Enter a seed value (or an empty line): ";
        std::string s;
        int seed_num;
        getline(std::cin, s);
        if (s == "") {
            seed_num = rand() % 100;
        }
        else {
            seed_num = stoi(s);
        }
        kentta.my_shuffle(seed_num);
    }
    else if (arvottukko == "n") {
        std::cout << "Enter the numbers 1-16 in a "
                     "desired order (16 means empty):" << std::endl;
        std::string annettu_kentta;
        getline(std::cin, annettu_kentta);
        kentta.make_board_to_order(annettu_kentta);
    }
    else {
        std::cout << "tee tähän virheviesti (koska ei y tai n)" << std::endl;
    }
    kentta.print();

}

//void printBoard( const Board& board, std::ostream& stream )



void pelataan(Board& kentta) {
    //Sitten pelataan!
    while (true) { // ei vielä tarkastelua ratkaistavuudesta
        std::cout << "Dir (command, number): ";
        std::string komento;
        getline(std::cin, komento);
        kentta.move_tiles(komento);
        kentta.print();
    }

}

int main() {
    Board kentta = Board();
    initBoard(kentta);
    pelataan(kentta);
    kentta.print();
    
    
    
    
    
    
    
    
    
    

    return EXIT_SUCCESS;
}
