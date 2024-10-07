#include <iostream>
#include <string>

#include "BloomFilter.h"
#include "HelpFunctions.h"
#include "VectorBlacklist.h"

const std::string BloomFilter::BLACKLIST_URL = "1";
const std::string BloomFilter::IS_URL_BLACKLISTED = "2";

BloomFilter::BloomFilter() {
    this->filterSize = DEFAULT_FILTER_SIZE;

    this->filter = {};
    this->filter.assign(DEFAULT_FILTER_SIZE, false);

    this->hashFunctions = {};
    this->hashFunctions.push_back(new NumHashFunc());

    this->blackList = new VectorBlacklist;
}

BloomFilter::BloomFilter(int size, std::vector<HashFunc*> hashFunctions) {
    // From it we can easily find the size of the filter and create the rest of it:
    this->filterSize = size;

    this->filter = {};
    this->filter.assign(this->filterSize, false);

    this->hashFunctions = hashFunctions;

    // We can always change it to another type of blacklist if we need:
    this->blackList = new VectorBlacklist;
}

BloomFilter::~BloomFilter() {
    for (HashFunc* hashFunction : this->hashFunctions) {
        if (hashFunction != nullptr)
            delete hashFunction;
    }

    if (this->blackList != nullptr)
        delete this->blackList;
}

std::vector<size_t> BloomFilter::applyHash(std::string str) {
    std::vector<size_t> hashIds = {};
    for (HashFunc* hashFunction : this->hashFunctions) {
        hashIds.push_back(hashFunction->hash(str));
    }

    return hashIds;
}

void BloomFilter::addToBlacklist(std::string url) {
    // Turn on all the bits of the hashed url, to 1:
    std::vector<size_t> bitIndexes = applyHash(url);
    for (size_t index : bitIndexes) 
        this->filter.at(index) = 1;

    this->blackList->blacklistURL(url);
}

bool BloomFilter::isURLSuspicous(std::string url) {
    std::vector<size_t> bitIndexes = applyHash(url);

    for (size_t index : bitIndexes) {
        // If we found any bit that is 0, the url is definitely not blacklisted:
        if (!this->filter.at(index))
            return false;
    }

    // If all bits are on, the url is possibly blacklisted:
    return true;
}

std::string BloomFilter::dealWithLine(std::string line) {
    std::vector<std::string> tokens = split(line);
    // All proper lines contain exactly 2 tokens, the operation and a url:
    if (tokens.size() != 2) 
        return "syntax fail";

    std::string operation = tokens.at(0);
    std::string url = tokens.at(1);
    if (operation == BloomFilter::BLACKLIST_URL) {
        // Add  url to the blacklist:
        addToBlacklist(url);
        return "add ok";

    } else if (operation == BloomFilter::IS_URL_BLACKLISTED) {
        bool isSuspicous = isURLSuspicous(url);

        if (!isSuspicous) {
            // The url is't suspicous, we stop here:
            return "false";
        }
        return this->blackList->isURLBlacklisted(url) ? "true" : "false";
    }
    return "syntax fail";
}

bool BloomFilter::getFilterIndex(size_t index) const {
    return this->filter.at(index);
}
int BloomFilter::getFilterSize(){
    return this->filterSize;
}
