#include <iostream>
#include <string>

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
    }
}

string kryptaus(string avain, string teksti){
    for (int i = 0; i < 26; ++i) {
        teksti.at(i) = avain.at(i);
    }

}


int main()
{
    string avain;
    cout << "Enter the encryption key: ";
    getline(cin, avain);
    string teksti;
    cout << "Enter the text to be encrypted: ";
    getline(cin, teksti);

    tarkistus(avain)

}
