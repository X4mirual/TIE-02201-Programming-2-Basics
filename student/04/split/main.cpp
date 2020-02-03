#include <iostream>
#include <string>
#include <vector>


std::vector<std::string> split(std::string line, char separator, bool totuusarvo=false) {
    std::vector<std::string> valmis;
    if (totuusarvo == false) {
        size_t pos = 0;
        std::string segment;
        while ((pos = line.find(separator)) != std::string::npos) {
            segment = line.substr(0, pos);
            valmis.push_back(segment);
            line.erase(0, pos + 1);
        }
        valmis.push_back(line);
    }
    else {
        size_t pos = 0;
        std::string segment;
        while ((pos = line.find(separator)) != std::string::npos) {
            if (pos!= 0) {
                segment = line.substr(0, pos);
                valmis.push_back(segment);
                line.erase(0, pos + 1);
            }
            else {
                line.erase(0,1);
            }
    }
    valmis.push_back(line);
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
