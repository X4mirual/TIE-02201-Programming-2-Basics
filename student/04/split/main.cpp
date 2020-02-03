#include <iostream>
#include <string>
#include <vector>


std::vector<std::string> split(std::string line, char separator) {
    std::vector<std::string> valmis;
    std::string segment;
    separator = '_';
    std::stringstream testii("peruna_kala_kukko_kiusaus");
    while(std::getline(testii, segment, separator)) {
        valmis.push_back(segment);
    }
    return valmis;
}


int main()
{
    std::string line = "";
    std::cout << "Enter a string: ";
    getline(std::cin, line);
    std::cout << "Enter the separator character: ";
    char separator = getchar();

    std::vector< std::string > parts  = split(line, separator);
    std::cout << "Splitted string including empty parts: " << std::endl;
    for( auto part : parts ) {
        std::cout << part << std::endl;
    }

    std::vector< std::string > parts_no_empty  = split(line, separator, true);
    std::cout << "Splitted string ignoring empty parts: " << std::endl;
    for( auto part : parts_no_empty ) {
        std::cout << part << std::endl;
    }
}
