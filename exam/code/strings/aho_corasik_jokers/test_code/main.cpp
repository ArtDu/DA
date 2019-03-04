#include "TBohr.h"

int main() {
    std::vector<std::pair<int, int> > grid;
    std::vector<TLetter> input;
    std::string line, word;
    std::string pattern;
    std::getline(std::cin, pattern);
    int lineIndex = 1, wordIndex = 1;
    TBohr b;
    while (std::getline(std::cin, line)) {
        std::stringstream lineStream(line);
        while (lineStream >> word) {
            input.push_back(word);
            grid.push_back(std::make_pair(lineIndex, wordIndex));
            wordIndex++;
        }
        wordIndex = 1;
        lineIndex++;
        //if (lineIndex>1)
        //	break;
    }
    //std::cout<<"Input succs"<<std::endl;
    input.shrink_to_fit();
    grid.shrink_to_fit();
    b.Search(input, pattern, grid);
    return 0;
}
