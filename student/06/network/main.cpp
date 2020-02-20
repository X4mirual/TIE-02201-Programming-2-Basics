#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <utility>

const std::string HELP_TEXT = "S = store id1 i2\nP = print id\n"
                              "C = count id\nD = depth id\n";

using namespace std;

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

void p_rekrytyt(vector<pair<string, string>> vektori, string henkilo, string pisteet);

void print_alainen(vector<pair<string, string>> vektori, string henkilo,
                    vector<pair<string, string>>::iterator it, string pisteet) {
    pisteet += "..";
    if(it->first == henkilo) {
        cout << pisteet << it->second << endl;
        henkilo = it->second;
        p_rekrytyt(vektori, henkilo, pisteet);
    }
}

void p_rekrytyt(vector<pair<string, string>> vektori, string henkilo, string pisteet) {
    vector<pair<string, string>>::iterator it;
    for(it = vektori.begin(); it != vektori.end(); ++it) {
        print_alainen(vektori, henkilo, it, pisteet);
    }
}

unsigned int kerro_verkoston_suuruus(vector<pair<string, string>> vektori, string henkilo) {
    vector<pair<string, string>>::iterator it;
    unsigned int verkoston_koko = 0;
    for(it = vektori.begin(); it != vektori.end(); ++it) {
        if(it->first == henkilo) {
            ++verkoston_koko;
            verkoston_koko += kerro_verkoston_suuruus(vektori, it->second);
        }
    }
    return verkoston_koko;
}




int main()
{
    // TODO: Implement the datastructure here
    // Vektorissa pareja(rekryyjä, rekrytty)
    std::vector<std::pair<std::string, std::string>> vektori;

    while(true){
        std::string line;
        std::cout << "> ";
        getline(std::cin, line);
        std::vector<std::string> parts = split(line, ' ', true);

        std::string command = parts.at(0);

        if(command == "S" or command == "s"){
            if(parts.size() != 3){
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id1 = parts.at(1);
            std::string id2 = parts.at(2);

            // TODO: Implement the command here!
            vektori.push_back(make_pair(id1, id2));

        } else if(command == "P" or command == "p"){
            if(parts.size() != 2){
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            // TODO: Implement the command here!
            string pisteet = "";
            p_rekrytyt(vektori, id, pisteet);

        } else if(command == "C" or command == "c"){
            if(parts.size() != 2){
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            // TODO: Implement the command here!
            cout << kerro_verkoston_suuruus(vektori, id) << endl;

        } else if(command == "D" or command == "d"){
            if(parts.size() != 2){
                std::cout << "Erroneous parameters!" << std::endl << HELP_TEXT;
                continue;
            }
            std::string id = parts.at(1);

            // TODO: Implement the command here!

        } else if(command == "Q" or command == "q"){
           return EXIT_SUCCESS;
        } else {
            std::cout << "Erroneous command!" << std::endl << HELP_TEXT;
        }
    }
}
