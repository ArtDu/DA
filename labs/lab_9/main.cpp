#include <iostream>
#include <vector>
#include <set>
#include <algorithm>


bool Dfs(std::vector<char> &used, std::vector<int> &matching, std::vector<std::vector<int>> &adjList, int v) {
    if (used[v]) return false;
    used[v] = true;
    for (auto to : adjList[v]) {
        if (matching[to] == -1 || Dfs(used, matching, adjList, matching[to])) {
            matching[to] = v;
            return true;
        }
    }
    return false;
}

void Kuhn(int n, std::vector<std::vector<int>> &adjList) {
    std::vector<int> matching(n + 1, -1);
    std::vector<char> used;
    for (int v = 1; v <= n; ++v) {
        used.assign(n + 1, false);
        Dfs(used, matching, adjList, v);
    }

    int u, v;
    std::set<std::pair<int, int>> ans;
    for (int i = 1; i <= n; ++i) {
        if (matching[i] != -1) {
            u = std::min(matching[i], i);
            v = std::max(matching[i], i);
            /*printf("%d %d\n", u, v);*/
            ans.insert(std::make_pair(u, v));
        }
    }

    std::cout << ans.size() << std::endl;

//    std::sort(ans.begin(), ans.end());

    int last_u = -1;
    int last_v = -1;
    for (auto i : ans) {
        /*if(last_u != i.first || last_v != i.second) {
            std::cout << i.first << " " << i.second << "\n";
        }
        last_u = i.first; last_v = i.second;*/

        std::cout << i.first << " " << i.second << "\n";
    }

}

/*
9 8
1 9
2 9
3 8
2 7
3 7
3 6
4 7
5 7
 */



int main() {

    int n, m, u, v;
    std::cin >> n >> m;

    std::vector<std::vector<int>> adjList(n + 1);

    for (int i = 0; i < m; ++i) {
        std::cin >> u >> v;
        adjList[u].push_back(v);
        adjList[v].push_back(u);
    }

    Kuhn(n, adjList);

    return 0;
}