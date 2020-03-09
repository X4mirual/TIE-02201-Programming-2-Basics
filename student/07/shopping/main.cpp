/* Kauppaketjut
 *
 * Kuvaus:
 * Ohjelma lukee tiedostosta kauppaketju-, (liikkeen) nimi-, tuote- ja
 * hintatiedot. Ohjelma kertoo tämän jälkeen sille annettujen komentojen
 * mukaan tiedoista.
 *
 * Program author
 * Name: Lauri Hiltunen
 * Student number: 274422
 * UserID: hiltunen
 * E-Mail: lauri.hiltune@tuni.fi
 *
 * Huomioitavaa ohjelmassa ja sen toteutuksessa:
 * Tiedot tiedostossa oltava muodossa
 * "kauppaketju;nimi;tuote;hinta" ja jokaisen tietoalkion oltava omalla
 * rivillään. Antaessa moniosaisia komentoja (kuten kysyessä ketjuun kuuluvia
 * liikkeitä) toimii erottimena välilyönti ' '.
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
map<string, map<string, vector<Product>>> chains;
map<string, vector<Product>> location;
vector<Product> products;
vector<string> product_names;

//Näin halutaan tulostuksen toimivan
//cout << chains.at("S-Market").at("Hervantakeskus").at(2).product_name << endl;


std::vector<std::string> split(const std::string& s, const char delimiter, bool ignore_empty = false){
    std::vector<std::string> result;
    std::string tmp = s;

    while(tmp.find(delimiter) != std::string::npos)
    {
        std::string new_part = tmp.substr(0, tmp.find(delimiter));
        tmp = tmp.substr(tmp.find(delimiter)+1, tmp.size());
        if(not (ignore_empty and new_part.empty()))
        {
            result.push_back(new_part);
        }
    }
    if(not (ignore_empty and tmp.empty()))
    {
        result.push_back(tmp);
    }
    return result;
}

bool lue_tiedosto() {
    string file_name;
    cout << "Input file: ";
    getline(cin, file_name);
    ifstream tiedosto_olio(file_name);

    if(not tiedosto_olio) {
        cout << "Error: the input file cannot be opened" << endl;
        return false;
    }
    string row;
    std::vector<std::string> splitted_row; //rivi splitattuna haluttuihin osiin
    string chain;
    string location;
    string product;
    map<string, vector<Product>> temp;
    double price;
    string price_information;

    while(getline(tiedosto_olio,row)) {
        splitted_row = split(row, ';');
        //Check for erroneous lines
        if(splitted_row.size() != 4 || find(splitted_row.begin(),
                splitted_row.end(), "") != splitted_row.end()) {
            cout << "Error: the input file has an erroneous line" << endl;
            return false;
        }

        //jaa omaan funktioon tästä eteen päin? (e: add_to_data_structure)

        chain = splitted_row.at(0);
        location = splitted_row.at(1);
        product = splitted_row.at(2);
        price_information = (splitted_row.at(3));
        if(price_information == "out-of-stock") {
            price = numeric_limits<int>::max();
        }
        else {
            price = stod(price_information);
        }
        if(chains.find(chain) == chains.end()) { //chain not found
            temp = {{location, {{product, price}}}};
            chains.insert(make_pair(chain, temp));
        }
        else{ //chain found
            if(chains.at(chain).find(location) == chains.at(chain).end()) { //chain not found, location not found
                chains.at(chain).insert({{location, {{product, price}}}});
            }
            else { //chain found, location found
                int i = 0;
                    for(vector<Product>::iterator it = chains.at(chain).at(location).begin();
                    it != chains.at(chain).at(location).end(); ++it) {
                        if(it->product_name == product) { //chain found, location found, product found
                            it->price = price;
                            i = 1;
                        }
                    }
                if(i == 0) { // chain found, location found, product not found
                    chains.at(chain).at(location).push_back({product, price});
                }
                else {
                    i = 0;
                }
            }
        }
        if(find(product_names.begin(), product_names.end(), product) == product_names.end()) { //product found in list
            product_names.push_back(product);
        }
    }
    return true;
}

void print_cheapest_places(string product) {
    vector<string> cheapest_places;
    double cheapest_price_so_far = numeric_limits<double>::infinity();
    bool out_of_stock = false;

    //Käydään läpi tietorakenteessa oleva jokainen tuote, merkaten muistiin
    //halvimpien sijainnit (liikkeet) ja hinta
    for(map<string, map<string, vector<Product>>>::iterator it1 = chains.begin(); it1 != chains.end(); ++it1) {
        for(map<string, vector<Product>>::iterator it2 = chains.at(it1->first).begin(); it2 != chains.at(it1->first).end(); ++it2){
            for(vector<Product>::iterator it3 = chains.at(it1->first).at(it2->first).begin(); it3 != chains.at(it1->first).at(it2->first).end(); ++it3) {
                string temp;
                if(it3->product_name == product) {
                    if(it3->price == numeric_limits<int>::max()) {
                        out_of_stock = true;
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
    //Tulostetaan tulokset

    if(cheapest_price_so_far != numeric_limits<double>::infinity()) {
        cout << cheapest_price_so_far << endl;
        for(string cheap_individual : cheapest_places) {
            cout << cheap_individual << endl;
        }
    }
    else if(out_of_stock == true) {
        cout << "The product is temporarily out of stock everywhere" << endl;
    }
    else {
        cout << "The product is not part of product selection" << endl;
    }
}

bool pro_compare(Product a, Product b) {
    return a.product_name < b.product_name;
}

void print_selection(string chain, string location) {
    if(chains.find(chain) == chains.end()) {
        cout << "Error: unknown chain name" << endl;
    }
    else if(chains.at(chain).find(location) == chains.at(chain).end()) {
        cout << "Error: unknown store" << endl;
    }
    else {
        sort(chains.at(chain).at(location).begin(), chains.at(chain).at(location).end(), pro_compare);
        for(vector<Product>::iterator it = chains.at(chain).at(location).begin();
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

bool is_command_length(vector<string> command_parts, int right_num) {
    if(command_parts.size() != right_num) {
        cout << "Error: error in command " << command_parts.at(0) << endl;
        return false;
    }
    else {
        return true;
    }
}

int main() {
    if(lue_tiedosto() == false) {
        return EXIT_FAILURE;
    }
    //Asetetaan tarkkuus kaikille lukujen tulostuksille
    cout << std::fixed << setprecision(2);

    sort(product_names.begin(), product_names.end());
    string command;
    vector<string> command_parts;
    while(command != "quit") {
        cout << "> ";
        getline(cin, command);
        command_parts = split(command, ' ');
        if(command_parts.at(0) == "chains") {
            if(is_command_length(command_parts, 1) == true) {
                for(map<string, map<string, vector<Product>>>::iterator it = chains.begin(); it != chains.end(); ++it) {
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
                    for(auto it = chains.at(location).begin(); it != chains.at(location).end(); ++it) {
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
                string product = command_parts.at(1);
                print_cheapest_places(product);
            }
        }
        else if(command == "products") {
            if(is_command_length(command_parts, 2) == true) {
                for(string product_name : product_names) {
                    cout << product_name << endl;
                }
            }
        }
        else if(command != "quit") {
            if(is_command_length(command_parts, 2) == true) {
                cout << "Error: unknown command: " << command_parts.at(0) << endl;
            }
        }
    }

    return EXIT_SUCCESS;
}





























