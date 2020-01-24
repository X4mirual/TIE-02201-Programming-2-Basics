#include <iostream>

using namespace std;

unsigned long int factorial(int n) {
    if (n > 1) {
        return n * factorial(n - 1);
    }
    else {
        return 1;
    }
}
void tulostus(int arvottavat, int kok) {
    cout << "The probability of guessing all "
         << arvottavat << " balls correctly is 1/"
         << factorial(kok) / (factorial(kok-arvottavat) *
                   factorial(arvottavat)) << endl;
}

int main() {
    cout << "Enter the total number of lottery "
            "balls: ";
    int lp_kokonaislkm;
    cin >> lp_kokonaislkm;
    cout << "Enter the number of drawn balls: ";
    int lp_arvottavienlkm;
    cin >> lp_arvottavienlkm;

    if (lp_kokonaislkm > 0 and lp_arvottavienlkm > 0) {
        tulostus(lp_arvottavienlkm, lp_kokonaislkm);

    } else {
        cout << "The number of balls must be a positive number."
             << endl;
    }
    return EXIT_SUCCESS;
}
