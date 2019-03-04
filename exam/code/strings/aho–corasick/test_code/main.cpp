#include "TBohr.h"


int main() {
    std::vector<std::pair<int, int> > grid;
    std::vector<TLetter> input;
    std::vector<TLetter> patterns;
    std::string line, word;
    TLetter pattern;
    TBohr b;
    int index = 0;
    while (std::getline(std::cin, pattern) && !pattern.empty()) {
        std::stringstream AlineStream(pattern);
        while (AlineStream >> word) {
            for(unsigned int i = 0; i < word.length(); ++i) {
                word[i] = tolower(word[i]);
            }

            patterns.push_back(word);
            index++;
        }

        b.Push(patterns);
        b.pieceIndex.push_back(index);

        index = 0;
        pattern.clear();
        patterns.clear();

    }

    int lineIndex = 1, wordIndex = 1;

    while (std::getline(std::cin, line)) {
        std::stringstream lineStream(line);
        while (lineStream >> word) {
            for(unsigned int i = 0; i < word.length(); ++i) {
                word[i] = tolower(word[i]);
            }
            input.push_back(word);
            grid.push_back(std::make_pair(lineIndex, wordIndex));
            wordIndex++;
        }

        wordIndex = 1;
        lineIndex++;

    }
    input.shrink_to_fit();
    grid.shrink_to_fit();
    b.Search(input, grid);
    return 0;
}
