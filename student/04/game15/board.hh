/* Game15 (or puzzle 15)
 *
 * Class: Board
 * Describes a two-dimensional grid for puzzle 15 with necessary functions to
 * make the grid vector, check when game is finished etc.
 *
 * Program author
 * Name: Lauri Hiltunen
 * Student number: 274422
 * UserID: hiltunen
 * E-Mail: lauri.hiltunen@tuni.fi
 *
 * */

#ifndef BOARD_HH
#define BOARD_HH
#include <vector>
#include <iostream>

const int SIZE = 4;

class Board
{
public:
    // Tekee 2d pelikentän grid_ annetusta siemenluvusta tai
    // käyttäen tietokoneen kelloa siemenlukuna
    void make_board_by_shuffle(int seed_num);

    // Teekee 2d pelikentän grid_ käyttäjän syöttämällä lukujen järjestyksellä.
    // Jos 16 lukua annettu ja jokin luvuista [1,16] puuttuu, tulostaa
    // pienimmän puuttuvan luvun ja ohjelma päätetään (0)
    void make_board_to_order(std::vector<unsigned int> numbers);

    // Tulostaa pelikentän
    void print();

    // Siirtää pelikentän lukuja käyttäjän antaman komennon mukaan
    void move_tiles(std::string komento);

    // Tarkistaa onko peli voitettu, ja päättää ohjelman, jos on
    void check_if_won();

private:
    // Tekee 1d vektorista 2d vektorin ja palauttaa sen
    std::vector<std::vector<unsigned int>>
    make_1D_to_2D_vector(std::vector<unsigned int> numbers);

    // Palauttaa (2d) grid_-vektorin 1d-vektorina
    std::vector<unsigned int> get_1D_grid_();

    // Tarkistaa kentän ratkottavuuden. Ajetaan kentän muodostuksen jälkeen
    // ennen pelaamista
    void check_solvability(std::vector<unsigned int> numbers);

    // Hakee kentän inversioiden lukumäärän
    int get_inv_count(std::vector<unsigned int> numbers);

    // Hakee, millä rivillä tyhjä (luku 16) on kentällä
    int get_empty_row_num(std::vector<unsigned int> numbers);

    // Pelikenttä 15-pelille, 2d-vektori
    std::vector<std::vector<unsigned int>> grid_;
};

#endif // BOARD_HH
