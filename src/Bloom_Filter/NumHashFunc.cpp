#include "NumHashFunc.h"

const std::hash<std::string> NumHashFunc::hasher{};

 NumHashFunc::NumHashFunc() : HashFunc(8) {
     this->timesToHash = 1;
}

 NumHashFunc::NumHashFunc(size_t range, size_t timesToHash) : HashFunc(range){
     this->timesToHash = timesToHash;
}

size_t NumHashFunc::hash(std::string url) {
    size_t output = hasher(url);
    for (int i = 2; i <= this->timesToHash; ++i) {
        output = hasher(std::to_string(output));
    }
    
    return output % *(this->range);
}
