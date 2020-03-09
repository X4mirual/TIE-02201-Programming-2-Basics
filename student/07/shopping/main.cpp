/* Kauppaketjut
 *
 * Kuvaus:
 * Ohjelma lukee tiedostosta kauppaketju-, lokaatio-, tuote- ja
 * hintatiedot. Ohjelma kertoo tämän jälkeen sille annettujen komentojen
 * mukaan tiedoista.
 *
 * Ohjelman tekijä
 * Nimi: Lauri Hiltunen
 * Opiskelijanumero: 274422
 * Käyttäjätunnus: hiltunen
 * Sähköpostiosoite: lauri.hiltune@tuni.fi
 *
 * Huomioitavaa ohjelmassa ja sen toteutuksessa:
 * Tiedot tiedostossa oltava muodossa
 * "kauppaketju;lokaatio;tuote;hinta" ja jokaisen tietoalkion oltava omalla
 * rivillään. Tyhjiä tietokenttiä ei voi olla syötetiedostossa
 * (esim ";;Hervanta;peruna;3" ei käy).
 * Antaessa moniosaisia komentoja toimii erottimena välilyönti ' '.
 *
 * */


#include <iostream>
#include <vector>
#include <map>
#include <set>
#include <string>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <utility>
#include <sstream>
#include <limits>
#include <iomanip>

using namespace std;

struct Product{
    string product_name;
    double price;
};

//Tietorakenne, johon kauppaketju, kaupan sijainti ja kaupan tuotteet ja
//niiden hinnat tallennetaan
map<string, map<string, vector<Product>>> chains;
vector<string> product_names;

//Jakaa merkkijono osiin.
//Parametrit: jaettava merkkijono, osien välinen erotin
//Paluuarvo: merkkijono jaettuna osiin
std::vector<std::string> split(const std::string& s, const char delimiter) {
    std::vector<std::string> result;
    std::string tmp = s;

    while(tmp.find(delimiter) != std::string::npos) {
        std::string new_part = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter)+1, tmp.size());
        if(new_part.empty() == false) {
            result.push_back(new_part);
        }
    }
    result.push_back(tmp);
    return result;
}

//Lisää tuotteen, tarvittaessa kauppaketjuun lokaation ja tarvittaessa
//kauppaketjun tietorakenteeseen.
//Parametrit: kauppaketju, lokaatio, lisättävä tuote, tuotteen hinta tai
//tieto ettei tuotetta ole varastossa
//Paluuarvo: ei paluuarvoa
void add_to_data_structure(string chain, string location, string product,
                           string price_information) {
    double price;
    map<string, vector<Product>> temp;

    //Jos tuote on loppuunmyyty, sen hinnaksi asetetaan maksimiluku
    if(price_information == "out-of-stock") {
        price = numeric_limits<int>::max();
    }
    else {
        price = stod(price_information);
    }
    //chain not found
    if(chains.find(chain) == chains.end()) {
        temp = {{location, {{product, price}}}};
        chains.insert(make_pair(chain, temp));
    }
    //chain found
    else{
        //chain not found, location not found
        if(chains.at(chain).find(location) == chains.at(chain).end()) {
            chains.at(chain).insert({{location, {{product, price}}}});
        }
        //chain found, location found
        else {
            bool product_already_in_structure = false;
                for(vector<Product>::iterator
                        it = chains.at(chain).at(location).begin();
                        it != chains.at(chain).at(location).end(); ++it) {
                    //chain found, location found, product found
                    if(it->product_name == product) {
                        it->price = price;
                        product_already_in_structure = true;
                    }
                }
            // chain found, location found, product not found
            if(product_already_in_structure == false) {
                chains.at(chain).at(location).push_back({product, price});
            }
        }
    }
    // If product not in list of product names, it is added
    if(find(product_names.begin(), product_names.end(), product) ==
            product_names.end()) {
        product_names.push_back(product);
    }
}

//Kysyy käyttäjältä luettavan tiedoston ja lukee sen rivi riviltä lisäten
//funktion "add_to_data_structure" avulla tiedot tietorakenteeseen
//Parametrit: ei parametreja
//Paluuarvo: tiedoston lukemisen onnistuminen (tämän perusteella päätetään
//ohjelman suorittamisen jatkamisesta). Paluuarvo false palautetaan
//välittömästi, jos rivin lukeminen tiedostosta ei onnistu.
bool read_file() {
    string file_name;
    cout << "Input file: ";
    getline(cin, file_name);
    ifstream tiedosto_olio(file_name);

    if(not tiedosto_olio) {
        cout << "Error: the input file cannot be opened" << endl;
        return false;
    }
    string row;
    std::vector<std::string> splitted_row;
    while(getline(tiedosto_olio,row)) {
        splitted_row = split(row, ';');

        //Check for erroneous lines, if yes, end program
        if(splitted_row.size() != 4 || find(splitted_row.begin(),
                splitted_row.end(), "") != splitted_row.end()) {
            cout << "Error: the input file has an erroneous line" << endl;
            return false;
        }

        add_to_data_structure(splitted_row.at(0), splitted_row.at(1),
          splitted_row.at(2), (splitted_row.at(3)));
    }
    return true;
}

//Tulostaa halvimman hinnan kysytylle tuotteelle sekä kauppaketjun ja
//lokaation, joista tuotetta on saatavissa tuohon hintaan.
//Parametrit: tuote (jolle halutaan halvin hinta ja vastaavat myyntipaikat)
//Paluuarvo: ei paluuarvoa
void print_cheapest_places(string product) {
    vector<string> cheapest_places;
    double cheapest_price_so_far = numeric_limits<double>::infinity();
    bool is_out_of_stock = false;

    //Käydään läpi tietorakenteessa oleva jokainen tuote, merkaten muistiin
    //kysytyn tuotteen halvin hinta ja sitä vastaavat lokaatiot ja niiden
    //kauppaketjut
    //Jokainen kauppaketju
    for(map<string, map<string, vector<Product>>>::iterator it1 =
            chains.begin(); it1 != chains.end(); ++it1) {
        //Kauppaketjun jokainen lokaatio
        for(map<string, vector<Product>>::iterator it2 =
                chains.at(it1->first).begin(); it2 !=
                chains.at(it1->first).end(); ++it2){
            //Lokaation jokainen tuote
            for(vector<Product>::iterator it3 =
                    chains.at(it1->first).at(it2->first).begin(); it3 !=
                    chains.at(it1->first).at(it2->first).end(); ++it3) {
                string temp;
                if(it3->product_name == product) {
                    //Maksimiluku hintana tarkoittaa, että tuotetta ei ole
                    //varastossa.
                    if(it3->price == numeric_limits<int>::max()) {
                        is_out_of_stock = true;
                    }
                    else if(it3->price < cheapest_price_so_far) {
                        cheapest_price_so_far = it3->price;
                        cheapest_places.clear();
                        temp = it1->first + " " + it2->first;
                        cheapest_places.push_back(temp);
                    }
                    else if(it3->price == cheapest_price_so_far) {
                        temp = it1->first + " " + it2->first;
                        cheapest_places.push_back(temp);
                    }
                }
            }
        }
    }
    //Tulostetaan tulokset.

    if(cheapest_price_so_far != numeric_limits<double>::infinity()) {
        cout << cheapest_price_so_far << " euros" << endl;
        for(string individual : cheapest_places) {
            cout << individual << endl;
        }
    }
    else if(is_out_of_stock == true) {
        cout << "The product is temporarily out of stock everywhere" << endl;
    }
    else {
        cout << "The product is not part of product selection" << endl;
    }
}

//Vertaa tuotenimien järjestystä, käytetään tuotteiden järjestelemiseen
//tuotenimien mukaan aakkosjärjestykseen.
//Parametrit: (stucteina) tuotteet, jotka halutaan järjestää nimensä mukaan
//Paluuarvo: tieto kahden tuotenimen aakkosjärjestyksestä
bool compare_product_names(Product a, Product b) {
    return a.product_name < b.product_name;
}

//Tulostaa tietyn ketjun tietyn lokaation tuotteet ja niiden hinnat (tai
//tiedon tuotteen olemisesta loppu).
//Parametrit: kauppaketju, lokaatio (jonka tuotevalikoima halutaan tulostaa)
//Paluuarvo: ei paluuarvoa
void print_selection(string chain, string location) {
    if(chains.find(chain) == chains.end()) {
        cout << "Error: unknown chain name" << endl;
    }
    else if(chains.at(chain).find(location) == chains.at(chain).end()) {
        cout << "Error: unknown store" << endl;
    }
    else {
        sort(chains.at(chain).at(location).begin(),
             chains.at(chain).at(location).end(), compare_product_names);
        for(vector<Product>::iterator it =
                chains.at(chain).at(location).begin();
                it != chains.at(chain).at(location).end(); ++it) {
            if(it->price != numeric_limits<int>::max()) {
                cout << it->product_name << " " << it->price << endl;
            }
            else {
                cout << it->product_name << " " << "out of stock" << endl;
            }
        }
    }
}

//Tarkistaa, että annetussa komennossa on oikea lukumäärä komponentteja.
//Parametrit: komento vektorina (jossa komennon komponentit vektorissa
//omina alkioinaan)
//Paluuarvo: oliko komennossa oikea lukumäärä komponentteja vai ei
bool is_command_length(vector<string> command_parts,
                       unsigned int right_length) {
    if(command_parts.size() != right_length) {
        cout << "Error: error in command " << command_parts.at(0) << endl;
        return false;
    }
    else {
        return true;
    }
}

int main() {
    if(read_file() == false) {
        return EXIT_FAILURE;
    }
    //Asetetaan tarkkuus kaikille lukujen tulostuksille
    cout << std::fixed << setprecision(2);

    //Järjestetään tuotenimien luettelo, mahdollista tulostusta
    //products-komennolla varten
    sort(product_names.begin(), product_names.end());
    string command;
    vector<string> command_parts;

    while(command != "quit") {
        cout << "> ";
        getline(cin, command);
        command_parts = split(command, ' ');

        if(command_parts.at(0) == "chains") {
            if(is_command_length(command_parts, 1) == true) {
                for(map<string, map<string, vector<Product>>>::iterator it =
                        chains.begin(); it != chains.end(); ++it) {
                    cout << it->first << endl;
                }
            }
        }
        else if(command_parts.at(0) == "stores") {
            if(is_command_length(command_parts, 2) == true) {
                string location = command_parts.at(1);
                if(chains.find(location) == chains.end()) {
                    cout << "Error: unknown chain name" << endl;
                }
                else {
                    for(auto it = chains.at(location).begin(); it !=
                            chains.at(location).end(); ++it) {
                        cout << it->first << endl;
                    }
                }
            }
        }
        else if(command_parts.at(0) == "selection") {
            if(is_command_length(command_parts, 3) == true) {
                print_selection(command_parts.at(1), command_parts.at(2));
            }
        }
        else if(command_parts.at(0) == "cheapest") {
            if(is_command_length(command_parts, 2) == true) {
                print_cheapest_places(command_parts.at(1));
            }
        }
        else if(command == "products") {
            if(is_command_length(command_parts, 1) == true) {
                for(string product_name : product_names) {
                    cout << product_name << endl;
                }
            }
        }
        else if(command != "quit") {
            if(is_command_length(command_parts, 1) == true) {
                cout << "Error: unknown command: " << command_parts.at(0)
                     << endl;
            }
        }
    }

    return EXIT_SUCCESS;
}





























