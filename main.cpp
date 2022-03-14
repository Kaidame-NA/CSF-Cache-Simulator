/*
 * The implementation of the command line program
 * CSF Assignment 3
 * Edward Wang: ewang43@jhu.edu
 * Sam Chordia: schordi1@jhu.edu
 */
#include <iostream>
#include <string>
#include "Cache.h"

enum return_codes
{
    NO_ERROR = 0,
    INVALID_NUMBER_OF_PARAMETERS,
    INVALID_PARAMETER
};

using std::cerr;
using std::cin;
using std::cout;
using std::string;

bool isValidNonnegativeInt(string str);
int intLog2(int x);
bool areParametersValid(char **argv);


int main(int argc, char **argv)
{
    // Check number of parameters
    if (argc != 7)
    {
        cerr << "Invalid number of parameters\n";
        return INVALID_NUMBER_OF_PARAMETERS;
    }
    // Check parameters are valid
    if (!areParametersValid(argv))
    {
        cerr << "Invalid parameter\n";
        return INVALID_PARAMETER;
    }
    string sets = argv[1], blocks = argv[2], bytes = argv[3];
    string writeAllocate = argv[4], writeThrough = argv[5], replacementPolicy = argv[6];
    
    Cache cache(stoi(sets), stoi(blocks), stoi(bytes), writeAllocate, writeThrough, replacementPolicy);

    char command;
    string address, value;
    cin >> command >> address >> value;
    while (command && !cin.eof())
    {
        if (command == 's') 
        {
            cache.store(stoi(address, 0 , 16));
        }
        else if (command == 'l')
        {
            cache.load(stoi(address, 0 , 16));
        }
        cin >> command >> address >> value;
    }
    cout << "Total loads: " << cache.getTotalLoads() << "\nTotal stores: " << cache.getTotalStores() << "\nLoad hits: " << cache.getLoadHits() << "\nLoad misses: " << cache.getLoadMisses() << "\nStore hits: " << cache.getStoreHits() << "\nStore misses: " << cache.getStoreMisses() << "\nTotal cycle: " << cache.getTotalCycles() << "\n";
    return NO_ERROR;
}

// Takes in a string and returns true if the string is a nonnegative integer
bool isValidNonnegativeInt(string str)
{
    for(unsigned int i = 0; i < str.length(); ++i) 
    {
        if(!isdigit(str.at(i))) 
        {
            return false;
        }
    }
    return true;
}

// Takes the log base 2 of an integer. Returns -1 if the result is not an integer and the result of the log if the result
// is an integer
int intLog2(int x)
{
    int result = 0;
    while (x != 1)
    {
        if (x % 2 == 1)
        {
            return -1;
        }
        ++result;
        x >>= 1;
    }
    return result;
}

// Takes in an array of parameters and checks to make sure they are valid
bool areParametersValid(char **argv)
{
    string sets = argv[1], blocks = argv[2], bytes = argv[3];
    string writeAllocate = argv[4], writeThrough = argv[5], replacementPolicy = argv[6];
    if (writeAllocate != "write-allocate" && writeAllocate != "no-write-allocate")
    {
        return false;
    }
    if (writeThrough != "write-through" && writeThrough != "write-back")
    {
        return false;
    }
    if (replacementPolicy != "fifo" && replacementPolicy != "lru")
    {
        return false;
    }
    if (writeAllocate == "no-write-allocate" && writeThrough == "write-back")
    {
        return false;
    }
    if (!isValidNonnegativeInt(sets) || !isValidNonnegativeInt(blocks) || !isValidNonnegativeInt(bytes))
    {
        return false;
    }
    int numSets = stoi(sets), numBlocks = stoi(blocks), numBytes = stoi(bytes);
    if(numSets == 0 || numBlocks == 0 || numBytes == 0) {
        return false;
    }
    if (intLog2(numSets) == -1 || intLog2(numBlocks) == -1 || intLog2(numBytes) == -1)
    {
        return false;
    }
    if (numBytes < 4)
    {
        return false;
    }
    return true;
}
