#pragma once
#ifndef VECTORBLACKLIST
#define VECTORBLACKLIST

#include <vector>
#include <string>

#include "IBlacklist.h"

// A class that contains the asic logic of a blacklist that uses a vector to save the blacklisted urls.
class VectorBlacklist : public IBlacklist {
private:
    std::vector<std::string> blacklist;    // The blacklisted URLs

public:
    VectorBlacklist();

    /**
     * Adds a url to the blacklist.
     * @param url The url to blacklist.
     * @note This does not check if the given string is already blacklisted.
    */
    virtual void blacklistURL(std::string url) override;

    /**
     * Checks if a url is blacklisted or not.
     * @param url The url to check.
     * @return true IFF the given url is blacklisted.
    */
    virtual bool isURLBlacklisted(std::string url) override;
};

#endif