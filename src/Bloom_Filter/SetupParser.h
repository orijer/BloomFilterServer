#pragma once
#ifndef SETUPPARSER
#define SETUPPARSER

#include <vector>
#include <string>
#include <utility> //for std::pair
#include "HashFunc.h"

// The class the parses he setup string of the filter, and returns the vector of hash functions we need for the bloom filter.
class SetupParser {
private:
    /**
     * A vector containing a pointer to all the has functions we support.
     * @note We delete all the unused functions after the setup.
    */
    std::vector<HashFunc*> functions;

    // Here we save which functions are used in the filter and which arent.
    std::vector<bool> usedTable;

public:
    // Default Constructor that creates the functions vector with the hash functions mentioned in the exercise.
    SetupParser();

    // We delete all the function that Bloom filter doesn't use.
    ~SetupParser();

    /**
     * Parses the string that is given for the setup of the bloom filter, and returns the resulting size and functions needed.
     * @param setupString the string the user gave to setup the bloom filter.
     * @return a pair, such that the first element is the size of the bloom filter, and the second is the vector of functions needed.
     * @note throws a runtime exception if the setupString isn't proper (use with try catch) 
     */
    std::pair<int, std::vector<HashFunc*>> ParseSetup(std::string setupString);
};

#endif