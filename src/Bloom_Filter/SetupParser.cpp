#include "SetupParser.h"

#include "NumHashFunc.h"
#include "HelpFunctions.h"
#include <stdexcept>

SetupParser::SetupParser() : functions({new NumHashFunc(1, 1), new NumHashFunc(1, 2)}), usedTable(functions.size(), false) {}

SetupParser::~SetupParser() {
    // We delete all the functions the Bloom Filter doesn't use.
    // Those it does use, are the responsibility of the Bloom Filter class.
    for (size_t index = 0; index < usedTable.size(); index++) {
        if (!usedTable.at(index))
            delete(functions.at(index));
    }
}

std::pair<int, std::vector<HashFunc*>> SetupParser::ParseSetup(std::string setupString) {
    std::vector<std::string> inputVector = split(setupString);
    if (inputVector.size() < 2)
        throw std::runtime_error("We must get a size and a function id!");

    // Check that the filter size is proper:
    int filterSize;
    try {
        filterSize = std::stoi(inputVector.at(0));
    } catch (...) {
        throw std::runtime_error("The first word is not a number!");
    }
    if (filterSize <= 0)
        throw std::runtime_error("Filter size cannot be negative!");

    // Set the ranges of the functions to the filter size we just got:
    for (HashFunc* func : this->functions)
        func->setRange(filterSize);

    // Parse which functions we need to use:
    size_t size = this->functions.size();
    for (size_t i = 1; i < inputVector.size(); ++i) {
        int functionID;
        try {
            functionID = std::stoi(inputVector.at(i));
        } catch (...) {
            throw std::runtime_error("The function id is not a number!");
        }
        
        if (functionID <= 0 || functionID > size)
            throw std::runtime_error("No function id found!");
        else
            usedTable.at(functionID - 1) = true;
    }

    // Return only the functions we needed:
    std::vector<HashFunc*> bloomFilterFunctions = {};
    for (int i=0; i<size; i++)
        if (usedTable.at(i))
            bloomFilterFunctions.push_back(this->functions.at(i));

    return std::pair<int, std::vector<HashFunc*>> (filterSize, bloomFilterFunctions);

}