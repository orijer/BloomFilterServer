#include "HelpFunctions.h"

std::vector<std::string> split(std::string str) {
    std::vector<std::string> splited_str{};
    std::stringstream stream_str(str);
    std::string single_word = "";

    // Every iteration puts a full word to 'single_word', 
    // then pushes it to the end of the vector:
    while (stream_str >> single_word) {
        splited_str.push_back(single_word);
    }

    return splited_str;
}
