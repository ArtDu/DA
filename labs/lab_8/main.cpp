#include <iostream>
#include <algorithm>
#include <vector>

class TSectionItem {
public:
    int start;
    int finish;
    int index;

    TSectionItem &operator=(const TSectionItem &rhs) = default;
};

bool Cmp(TSectionItem &lhs, TSectionItem &rhs) {
    return (lhs.start < rhs.start);
}

bool CmpIndex(TSectionItem &lhs, TSectionItem &rhs) {
    return (lhs.index < rhs.index);
}

void SegmentSelection(std::vector<TSectionItem> &points, int m) {
    std::vector<TSectionItem> ans;

    // sort by left(start) point
    std::sort(points.begin(), points.end(), Cmp);

    int index = 0;
    // pick first correct section
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
        return;
    }
    //else
    ans.push_back(points[lastCorrectSection]);

    //pick the remaining sections
    bool complete = false;
    lastCorrectSection = -1;
    while (index < points.size()) {
        // find next correct section
        for (; index < points.size(); ++index) {
            if (points[index].start <= ans.back().finish && points[index].finish >= ans.back().finish) {
                lastCorrectSection = index;
                // if complete
                if (points[index].finish >= m) {
                    complete = true;
                    break;
                }
            } else if (points[index].start > ans.back().finish) { // last section was best
                break;
            }
        }
        //fail
        if (lastCorrectSection == -1) {
            std::cout << 0 << std::endl;
            return;
        }
        //else
        ans.push_back(points[lastCorrectSection]);
        if (m <= ans.back().finish || complete) {
            //complete
            break;
        }
        lastCorrectSection = -1;
    }


    if (m <= ans.back().finish) {
        std::cout << ans.size() << std::endl;
        // sort by index
        std::sort(ans.begin(), ans.end(), CmpIndex);
        for (auto j : ans) {
            std::cout << j.start << " " << j.finish << std::endl;
        }
    } else {
        std::cout << 0 << std::endl;
    }
}

int main() {


    size_t n;
    std::cin >> n;

    std::vector<TSectionItem> points(n);

    for (int i = 0; i < n; ++i) {
        points[i].index = i;
        std::cin >> points[i].start >> points[i].finish;
    }

    int m;
    std::cin >> m;

    SegmentSelection(points, m);

    return 0;
}