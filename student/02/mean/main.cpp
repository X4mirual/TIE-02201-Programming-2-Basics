#include <iostream>

// Write here a function counting the mean value

int main()
{
    std::cout << "From how many integer numbers you want to count the mean value? ";
    int lukujen_lkm = 0;
    std::cin >> lukujen_lkm;

    if (lukujen_lkm > 0) {
        return 0;
    }

    else {
        std::cout << "Cannot count mean value from " << lukujen_lkm
                  << " numbers" << std::endl;
    }










}
