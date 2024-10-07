#pragma once
#ifndef IBLACKLIST
#define IBLACKLIST

#include <string>

// An interface containing what a blacklist of url's needs to do.
class IBlacklist {
public:
    virtual ~IBlacklist() = default;
    /**
     * Adds a url to the blacklist.
     * @param url The url to blacklist.
     * @note This does not check if the given string is already blacklisted.
    */
    virtual void blacklistURL(std::string url) = 0;

    /**
     * Checks if a url is blacklisted or not.
     * @param url The url to check.
     * @return true IFF the given url is blacklisted.
    */
    virtual bool isURLBlacklisted(std::string url) = 0;
};

#endif