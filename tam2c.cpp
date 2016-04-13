#include <iostream>
#include "tam2c.hpp"

int main(int argc, char* argv[])
{
    if(argc != 2)
    {
        std::cout <<
            "Usage: " << argv[0] << " <filename>.tam\n"
            " - Traduce TAM assembly in C using tamlibc.\n"
            " - Will output \"<filename>.tam.c\" in the same directory."
            << std::endl;
        exit(1);
    }

    return 0;
}
