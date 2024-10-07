#pragma once
#ifndef HASHFUNC
#define HASHFUNC

#include <iostream>

// A class the represents a hash function that hashes urls.
class HashFunc
{
protected:
    // The range of values of the hash function: 0, ... , range-1.
    int *range;

public:
    // The number of unique hash functions we want to support.
    static const int NUM_OF_UNIQUE_FUNCTIONS = 2;

    /**
     * Constructor that creates a hash function with a specific output range.
     * @param range the range of the outpu range 0, ... , range-1.
     */
    HashFunc(int range);

    // Destructor.
    ~HashFunc();

    /**
     * The abstract function that does the hashing.
     * @param url The url to hash.
     * @return the hashed value of the given url.
     */
    virtual std::size_t hash(std::string url) = 0;

    /**
     * Sets the range of the hash function to a new value.
    */
    void setRange(int newRange);
};

#endif