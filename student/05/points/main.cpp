#include <iostream>
#include <map>
#include <string>
#include <fstream>

using namespace std;

int main()
{
    string inputti = "";
    cout << "Input file: ";
    getline(cin, inputti);
    ifstream tiedosto_olio(inputti);

    map<string, int> mappi;
    string nimi;
    int pisteet;
    string rivi;

    if(not tiedosto_olio) {
        cout << "Error! The file " << inputti
             << " cannot be opened." << endl;
        exit(1);
    }

    while(getline(tiedosto_olio, rivi)) {
        size_t pos = rivi.find(':');
        nimi = rivi.substr(0, pos+1);
        string temp = rivi.substr(pos+1);
        pisteet = stoi(temp);

        if(mappi.find(nimi) == mappi.end()) {
            mappi.insert({nimi, pisteet});
        }
        else {
            mappi.at(nimi) += pisteet;
        }
    }

    map<string, int>::iterator iter;
    iter = mappi.begin();

    cout << "Final scores:" << endl;
    while(iter != mappi.end()) {
        cout << iter->first << " " << iter->second << endl;
        ++iter;
    }


}
