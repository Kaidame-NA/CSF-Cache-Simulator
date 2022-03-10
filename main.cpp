#include <iostream>
#include "Cache.h"

enum return_codes {
    NO_ERROR=0,
    INVALID_NUMBER_OF_PARAMETERS,
    INVALID_PARAMETER
};

int main(int argc, char **argv)
{
    if(argc != 7) {
        std::cerr << "Invalid number of parameters\n";
        return INVALID_NUMBER_OF_PARAMETERS;
    }
    return NO_ERROR;
}
