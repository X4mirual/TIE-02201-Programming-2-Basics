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

using namespace std;


struct Product{
    string product_name;
    double price;
};
map<string, map<string, vector<Product>>> chains;
map<string, vector<Product>> location;
vector<Product> products;

//Näin halutaan tulostaa
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
        cout << "Error! The file " << file_name
             << " cannot be opened." << endl;
        return false;
        //korjaa??
    }
    string row;
    std::vector<std::string> splitted_row; //rivi splitattuna haluttuihin osiin
    string chain;
    string location;
    string product;
    map<string, vector<Product>> temp;
    double price;
    string price_information;
    while(getline(tiedosto_olio,row)) { //read file until all lines read
        splitted_row = split(row, ';');
        chain = splitted_row.at(0);
        location = splitted_row.at(1);
        product = splitted_row.at(2);
        price_information = (splitted_row.at(3));
        if(price_information == "out-of-stock") { // omaan funktioonsa tietorakenteeseen tallentaminen
            price = -1;
        }
        if(chains.find(chain) == chains.end()){ //chain not found
            temp = {{location, {{product, price}}}};
            chains.insert(make_pair(chain, temp));
        }
        else{ //chain found
            if(chains.at(chain).find(location) == chains.at(chain).end()){ //chain not found, location not found
                chains.at(chain).insert({{location, {{product, price}}}});
            }
            else { //chain found, location found
                chains.at(chain).at(location).push_back({product, price});
            }
            //todo: what if the product itself (within chain and location) is already found?
        }


    }

}

int main()
{
    lue_tiedosto();
    string command;
    while(command != "quit") {
        cout << "> ";
        getline(cin, command);

        if(command == "chains") {
            for(map<string, map<string, vector<Product>>>::iterator it = chains.begin(); it != chains.end(); ++it) {
                cout << it->first << endl;
            }
        }

    }

    return 0;
}





























