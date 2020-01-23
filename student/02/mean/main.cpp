#include <iostream>

// Write here a function counting the mean value

int main()
{
    std::cout << "From how many integer numbers you want to count the mean value? ";
    int lukujen_lkm = 0;
    std::cin >> lukujen_lkm;
    float summa = 0.0;
    float uusi = 0.0;

    if (lukujen_lkm > 0) {
        for ( int i = 1; i <= lukujen_lkm; ++i) {

            std::cout << "Input " << i << " number: ";
            std::cin >> uusi;
            summa = summa + uusi;
        }
        float keskiarvo= summa / lukujen_lkm;
        std::cout << "Mean value of the given numbers is " << keskiarvo << std::endl;
    }

    else {
        std::cout << "Cannot count mean value from " << lukujen_lkm
                  << " numbers" << std::endl;
    }










}
