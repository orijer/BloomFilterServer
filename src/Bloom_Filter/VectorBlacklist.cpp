#include "VectorBlacklist.h"

VectorBlacklist::VectorBlacklist() {
    this->blacklist = {};
}

void VectorBlacklist::blacklistURL(std::string url) {
    this->blacklist.push_back(url);
}

bool VectorBlacklist::isURLBlacklisted(std::string url) {
    for (const std::string str : this->blacklist) {
        if (str == url) {
            // We found a match:
            return true;
        }
    }
    
    // If we are here, it's because we looked and didn't find any match:
    return false;
}