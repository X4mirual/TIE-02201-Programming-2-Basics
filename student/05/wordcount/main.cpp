#include <iostream>
#include <vector>
#include <map>
#include <string>
#include <fstream>
#include <algorithm>
#include <iomanip>
#include <utility>
#include <sstream>

using namespace std;

int main()
{
    string inputti;
    cout << "Input file: ";
    getline(cin, inputti);
    ifstream tiedosto_olio(inputti);

    if(not tiedosto_olio) {
        cout << "Error! The file " << inputti
             << " cannot be opened." << endl;
        exit(1);
    }

    map<string, vector<int>> mappi;
    string sana;


    string rivi;
    int rivi_nro = 1;
    size_t pos = 0;
    while(getline(tiedosto_olio, rivi)){
        while((pos = rivi.find(' ')) != std::string::npos) {
            sana = rivi.substr(0, pos);
            rivi.erase(0, pos+1);
            if(mappi.find(sana) == mappi.end()) {
                mappi.insert({sana, {rivi_nro}});
            }
            else {
                mappi.at(sana).push_back(rivi_nro);
            }
        }
        sana = rivi;
        if(mappi.find(sana) == mappi.end()) {
            mappi.insert({sana, {rivi_nro}});
        }
        else {
            mappi.at(sana).push_back(rivi_nro);
        }
        ++rivi_nro;
    }



    map<string, vector<int>>::iterator iter;
    iter = mappi.begin();

    while(iter != mappi.end()) {
        cout << iter->first << " "
             << iter->second.size() << ": ";
        unsigned int u = 0;
        while(u < iter->second.size()) {
            cout << iter->second.at(u);
            if(u+1 < iter->second.size()) {
                cout << ", ";
            }
            ++u;
        }

        ++iter;
    cout << endl;
    }

}




















