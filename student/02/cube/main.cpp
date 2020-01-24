#include <iostream>

using namespace std;

int main()
{
    int annettu_luku;
    cout << "Enter a number: ";
    cin >> annettu_luku;
    if (annettu_luku != 0) {
        int luku = annettu_luku * annettu_luku
                * annettu_luku;

        if (luku / annettu_luku / annettu_luku
                == annettu_luku) {
            cout << "The cube of " << annettu_luku
                 << " is " << luku << "." << endl;
        } else {
            cout << "Error! The cube of "
                 << annettu_luku << " is not "
                 << luku << "." << endl;

        }
    } else {
        cout << "The cube of 0 is 0." << endl;
    }



}
