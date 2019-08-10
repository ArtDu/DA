#include <iostream>
#include <algorithm>
#include <vector>

class sectionItem {
public:
    int start;
    int finish;
    int index;
    sectionItem& operator= (const sectionItem &rhs){
        start = rhs.start;
        finish = rhs.finish;
        index = rhs.index;
        return *this;
    }
};

bool cmp(sectionItem &lhs, sectionItem &rhs) {
    return (lhs.finish < rhs.finish);
}


int main() {


    size_t n;
    std::cin >> n;

    std::vector<sectionItem> pointsNonSort(n);

    std::vector<sectionItem> ans;
    for (int i = 0; i < n; ++i) {
        pointsNonSort[i].index = i;
        std::cin >> pointsNonSort[i].start >> pointsNonSort[i].finish;
    }
    std::vector<sectionItem> points = pointsNonSort;

    int m;
    std::cin >> m;

    std::sort(points.begin(), points.end(), cmp);

    //for (auto k : pointsNonSort) std::cout << k.start << " " << k.finish << " " << k.index << std::endl;
    //for (auto k : points) std::cout << k.start << " " << k.finish << std::endl;

    int index = 0;
    // pick first section
    int lastCorrectSection = -1;
    for (; index < points.size(); ++index) {
        if (points[index].start <= 0 && points[index].finish >= 0) {
            lastCorrectSection = index;
        } else if (points[index].start > 0) {
            break;
        }
    }
    // fail
    if (lastCorrectSection == -1) {
        std::cout << 0 << std::endl;
        return 0;
    }
    ans.push_back(points[lastCorrectSection]);

    //pick the remaining sections
    bool complete = false;
    lastCorrectSection = -1;
    while (index < points.size()) {
        for (; index < points.size(); ++index) {
            if (points[index].start <= ans.back().finish && points[index].finish >= ans.back().finish) {
                lastCorrectSection = index;
                if (points[index].finish >= m){
                    complete = true;
                    break;
                }
            } else if (points[index].start > ans.back().finish) {
                break;
            }
        }
        //fail
        if (lastCorrectSection == -1) {
            std::cout << 0 << std::endl;
            return 0;
        }
        ans.push_back(points[lastCorrectSection]);
        if (m <= ans.back().finish || complete) {
            //complete
            break;
        }
        lastCorrectSection = -1;
    }

    if (m <= ans.back().finish) {
        std::cout << ans.size() << std::endl;
        for (auto j : ans) {
            std::cout << pointsNonSort[j.index].start << " " << pointsNonSort[j.index].finish << std::endl;
        }
    } else {
        std::cout << 0 << std::endl;
    }
    return 0;
}