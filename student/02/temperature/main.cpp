#include <iostream>

using namespace std;

int main()
{
    cout << "Enter a temperature: ";
    int annettu = 0;
    cin >> annettu;

    cout << annettu
         << " degrees Celsius is "
         << (annettu * 1.8) + 32
         << " degrees Fahrenheit"
         << endl;

    cout << annettu
         << " degrees Fahrenheit is "
         << (annettu - 32) / 1.8
         << " degrees Celsius"
         << endl;


    return 0;
}
