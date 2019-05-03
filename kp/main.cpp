#include "invertedIndex.h"
#include <algorithm>

struct rowCol {
    int row;
    int col;
};


bool mycomparer(const rowCol &lhs, const rowCol &rhs) {
    return lhs.row < rhs.row;
}


int main() {


    invertedIndex iv(std::cin);


    std::vector<rowCol> v1;
    std::vector<rowCol> v2;

    rowCol tmpRC;
    tmpRC.row = 1;
    tmpRC.col = 2;
    v1.push_back(tmpRC);
    tmpRC.row = 2;
    tmpRC.col = 3;
    v1.push_back(tmpRC);
    tmpRC.row = 3;
    tmpRC.col = 4;
    v1.push_back(tmpRC);

    tmpRC.row = 2;
    tmpRC.col = 5;
    v2.push_back(tmpRC);

    std::vector<rowCol> v(10);                      // 0  0  0  0  0  0  0  0  0  0
    std::vector<rowCol>::iterator it;

    it = std::set_intersection(v1.begin(), v1.end(),
                               v2.begin(), v2.end(), v.begin(), mycomparer);
    // 10 20 0  0  0  0  0  0  0  0
    v.resize(it - v.begin());                      // 10 20

    std::cout << "The intersection has " << (v.size()) << " elements:\n";
    for (it = v.begin(); it != v.end(); ++it)
        std::cout << ' ' << it.base()->row << " " << it.base()->col << "\t";
    std::cout << '\n';


    return 0;
}