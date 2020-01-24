#include <iostream>

using namespace std;

int main()
{
    int annettu_luku;
    cout << "Enter a number: ";
    cin >> annettu_luku;
    int luku = annettu_luku * annettu_luku
            * annettu_luku;

    if (luku / annettu_luku / annettu_luku
            == annettu_luku) {
        cout << "The cube of " << annettu_luku
             << " is " << luku << "." << endl;
    }

    else {
        cout << "Error! The cube of "
             << annettu_luku << " is not "
             << luku << "." << endl;
    }
}
