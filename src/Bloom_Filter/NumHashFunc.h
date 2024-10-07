#pragma once
#ifndef NUMHASHFUNC
#define NUMHASHFUNC

#include <functional>

#include "HashFunc.h"

// The class for the url hashing function that hashes once: the 1-hash function. 
class NumHashFunc: public HashFunc
{
    private:
        // The function we use when actually hashing:
        static const std::hash<std::string> hasher;

        // The number of times the function hashes it's result before returning the value.
        // (For example: if timesToHash is 2, the function hashes a value, hashes the result and then returns the final value)
        size_t timesToHash;

    public:
        // Default constructor: creates a 1-hash function with output range 8.
        NumHashFunc();

        /**
         * A constructor that creates a hash function with a specific output range,
           that hashes the result of itself a specific number of times.
         * @param range The range of the hash function 0, ... , range-1.
         * @param timesToHash The number of times the function hashes it's result before returning the value.
           (For example: if timesToHash is 2, the function hashes a value, hashes the result and then returns the final value)
        */
        NumHashFunc(size_t range, size_t timesToHash);

        /**
         * Hashes a URL using the std::hash function, into the correct range.
         * @param url The input URL to be hashed
         * @return The hash value in the range.
         */
        size_t hash(std::string url) override;
};

#endif