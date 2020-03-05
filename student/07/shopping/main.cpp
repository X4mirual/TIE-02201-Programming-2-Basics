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
    string splitted;
    while(getline(tiedosto_olio,row)) {
        splitted = split(row, ';');
        Product tuote = {splitted.at(2), splitted.at(3)};

    }

}

int main()
{
    lue_tiedosto();
    while (true) {

    }
}





























