#pragma once
#ifndef BLOOMFILTER
#define BLOOMFILTER

#include <vector>
#include <string>

#include "NumHashFunc.h"
#include "IBlacklist.h"

// A class that contains the logic of the Bloom Filter.
class BloomFilter {
private:
    static const std::string BLACKLIST_URL;
    static const std::string IS_URL_BLACKLISTED;

    const int DEFAULT_FILTER_SIZE = 8;

    int filterSize;                        // The size of the filter.
    std::vector<bool> filter;              // The bit array representing the filter.
    std::vector<HashFunc*> hashFunctions;  // A list of pointers to hash functions.
    IBlacklist *blackList;                  // The blacklisted URLs
                          

public:
    // Default Constructor for BloomFilter
    BloomFilter();

    /**
     * @constructor for BloomFilter taking a string parameter
     * @param str A proper string parameter used for configuration:
       (first word- the filter size, the following words- which hashing functions to use)
     */
    BloomFilter(int size, std::vector<HashFunc*> hashFunctions);

    // Destructor
    ~BloomFilter();

    /**
     * Applies the hashing functions of the filter on a given string, and return the results vector
       (All the indexes that should be 1 if the string is in the filter)
     * @param str The URL to be processed
     * @return A vector of the hash values
     */
    std::vector<size_t> applyHash(std::string str);

    /**
     * Checks if the url is possibly blacklisted or definitely isn't blacklisted.
     * @param url The url to check.
     * @return true if the given url is possibly blacklisted, and false if it definitely isn't.
     */
    bool isURLSuspicous(std::string url);

    /**
     * Adds a specific URL to the blacklist, and updates the bit list of the filter.
     * @param url The url to blacklist
     * @note This does not check if the given string is already blacklisted.
     */
    void addToBlacklist(std::string url);

    /**
     * Processes a line of input and performs the corresponding operation
     * @param line The input line to be processed
     * @note probably better to put it in a different class later.
     */
    std::string dealWithLine(std::string line);

    /**
     * @Get the value at a specific index in the filter.
     * @param index The index to be checked
     * @return The value at the specified index in the filter
     */
    bool getFilterIndex(size_t index) const;

    /**
     * @return the size of the filter (how many bits we keep)
    */
    int getFilterSize();
};

#endif
