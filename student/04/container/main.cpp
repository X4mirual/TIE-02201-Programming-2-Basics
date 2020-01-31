#include <cstdlib>
#include <iostream>
#include <vector>


void read_integers(std::vector<int>& ints, int count)
{
    int new_integer = 0;
    for(int i = 0; i < count; ++i)
    {
        std::cin >> new_integer;
        ints.push_back(new_integer);
    }
}

bool same_values(std::vector<int>& integers) {
    for (unsigned int i = 0; i < integers.size() - 1; ++i) {
        if (integers.at(i) != integers.at(i+1)) {
            return false;
        }
    }
    return true;
}

bool is_ordered_non_strict_ascending(
        std::vector<int>&integers) {
    for (unsigned int i = 0; i < integers.size() - 1; ++i) {
        if (integers.at(i) > integers.at(i+1)) {
            return false;
        }
    }
    return true;
}

bool is_arithmetic_series(std::vector<int>& integers) {
    int k = 0;
    if (integers.size() > 1) {
        k = 1;
        int erotus = integers.at(0) - integers.at(1);
        for (unsigned int i = 0; i < integers.size() - 1; ++i) {
            if (integers.at(i) - integers.at(i+1) != erotus) {
                k = 0;
            }
        }
    }
    if (k == 0) {
        return false;
    }
    else {
        return true;
    }
}

bool is_geometric_series(std::vector<int>& integers) {
    int k = 0;
    if (integers.size() > 1) {
        k = 1;
        int kertoja = integers.at(1) / integers.at(0);
        for (unsigned int i = 0; i < integers.size() - 1; ++i) {
            if (integers.at(i+1) / integers.at(i) != kertoja) {
                k = 0;
                    }
                }
            }
    if (k == 0) {
        return false;
    }
    else {
        return true;
    }
}

int main()
{
    std::cout << "How many integers are there? ";
    int how_many = 0;
    std::cin >> how_many;

    std::cout << "Enter the integers: ";
    std::vector<int> integers;
    read_integers(integers, how_many);

    if(same_values(integers))
        std::cout << "All the integers are the same" << std::endl;
    else
        std::cout << "All the integers are not the same" << std::endl;

    if(is_ordered_non_strict_ascending(integers))
        std::cout << "The integers are in a non-strict ascending order" << std::endl;
    else
        std::cout << "The integers are not in a non-strict ascending order" << std::endl;

    if(is_arithmetic_series(integers))
        std::cout << "The integers form an arithmetic series" << std::endl;
    else
        std::cout << "The integers do not form an arithmetic series" << std::endl;

    if(is_geometric_series(integers))
        std::cout << "The integers form a geometric series" << std::endl;
    else
        std::cout << "The integers do not form a geometric series" << std::endl;

    return EXIT_SUCCESS;
}
