#include <iostream>
#include <string>
#include <algorithm>

using namespace std;

bool tarkistus(string avain) {
    if (avain.length() != 26) {
        cout << "Error! The encryption key must contain"
                " 26 characters." << endl;
        return false;
    }
    string aakkoset = "abcdefghijklmnopqrstuvwxyz";
    for (int n = 0; n < 26; ++n) {
        if (islower(avain.at(n)) == false) {
            cout << "Error! The encryption key must contain only lower "
                    "case characters." << endl;
            return false;
        }
        else if (avain.find(aakkoset.at(n)) == string::npos) {
            cout << "Error! The encryption key must contain all "
                    "alphabets a-z." << endl;
            return false;
        }
    return true;
    }
}

void kryptaus(string avain, string& teksti){
    string aakkoset = "abcdefghijklmnopqrstuvwxyz";
    int pituus = teksti.length(); //Tekstin pituus
    for (int i = 0; i < pituus; ++i) {
        char kirjain = teksti.at(i); //e: 'k'
        //int monesko = aakkoset.find(kirjain); //e: 11
        char avaimesta = avain.at(aakkoset.find(kirjain));
        teksti.at(i) = avaimesta;

    }
}

int main()
{
    string avain;
    cout << "Enter the encryption key: ";
    getline(cin, avain);

    if (tarkistus(avain) == false) {
        cout << "peruna" << endl;
        return EXIT_FAILURE;
    }

    string teksti;
    cout << "Enter the text to be encrypted: ";
    getline(cin, teksti);

    kryptaus(avain, teksti);

    cout << "Encrypted text: "<< teksti << endl;
}
