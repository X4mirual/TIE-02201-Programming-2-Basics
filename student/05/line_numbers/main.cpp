#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
    string inputti = "";
    cout << "Input file: ";
    getline(cin, inputti);
    string outputti = "";
    cout << "Output file: ";
    getline(cin, outputti);
    ifstream tiedosto_olio(inputti);

    if(not tiedosto_olio) {
        cout << "Error! The file "
            << inputti
            << " cannot be opened." << endl;
        exit(1);
    }

    else {
        ofstream ulostus_tiedosto(outputti);
        int i = 1;
        string rivi = "";
        while(getline(tiedosto_olio, rivi)){
            ulostus_tiedosto << i << " " << rivi << endl;
            ++i;
        }
    }


}
