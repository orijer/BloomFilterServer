#include "HashFunc.h"

HashFunc::HashFunc(int range) {
    this->range = new int;
    *(this->range) = range;
}

HashFunc::~HashFunc() {
    delete this->range;
}

void HashFunc::setRange(int newRange) {
    *(this->range) = newRange;
}