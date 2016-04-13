#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "tam2c.hpp"

int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        std::cout <<
            "Usage: " << argv[0] << " <filename.tam>\n"
            " - Traduce TAM assembly in C using tamlibc.\n"
            " - Will output \"<filename>.tam.c\" in the same directory."
            << std::endl;
        exit(1);
    }

    size_t nb_line = 0;
    std::ifstream tam_file(argv[1]);
    for(std::string line = ""; std::getline(tam_file, line); ++nb_line)
    {
        std::cout << line << "\n";
    }

    return 0;
}
