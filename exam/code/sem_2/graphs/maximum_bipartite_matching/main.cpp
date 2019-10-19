#include <iostream>
#include <vector>
#include <set>
#include <queue>
#include <algorithm>


bool Dfs(std::vector<char> &used, std::vector<int> &matching, const std::vector<std::set<int>> &adjList, int v) {
    if (used[v])
        return false;
    used[v] = true;

    for (auto to : adjList[v]) {
        if (matching[to] == -1 || Dfs(used, matching, adjList, matching[to])) {
            matching[to] = v;
            return true;
        }
    }

    return false;
}

void Kuhn(const int &n, const std::vector<std::set<int>> &adjList, const std::vector<char> &part) {

    std::vector<int> matching(n + 1, -1);
    std::vector<char> used;
    for (int v = 1; v <= n; ++v) {
        if (part[v] == 0) {
            used.assign(n + 1, false);
            Dfs(used, matching, adjList, v);
        }

    }

    int u, v;
    std::set<std::pair<int, int>> ans;
    for (int i = 1; i <= n; ++i) {
        if (matching[i] != -1) {
            u = std::min(matching[i], i);
            v = std::max(matching[i], i);
            ans.insert(std::make_pair(u, v));
        }
    }

    std::cout << ans.size() << std::endl;

    for (auto i : ans) {
        std::cout << i.first << " " << i.second << "\n";
    }

}

void Bfs(const std::vector<std::set<int>> &adjList, std::vector<char> &color, const int &src) {

    std::queue<int> q;
    q.push(src);

    // Assign first color to source
    color[src] = 0;

    while (!q.empty()) {
        int u = q.front();
        q.pop();

        for (auto v : adjList[u]) {
            if (color[v] == -1) {
                color[v] = !color[u];
                q.push(v);
            }
        }
    }
}

std::vector<char> DivideToBipartite(const std::vector<std::set<int>> &adjList, const int &n) {
    // -1  = no color
    //  0  = first color
    //  1  = second color
    std::vector<char> color(n + 1, -1);

    for (int i = 1; i <= n; ++i) {
        if (color[i] == -1)
            Bfs(adjList, color, i);
    }

    return color;

}

int main() {

    int n, m, u, v;
    std::cin >> n >> m;

    std::vector<std::set<int>> adjList(n + 1);

    for (int i = 0; i < m; ++i) {
        std::cin >> u >> v;
        adjList[u].insert(v);
        adjList[v].insert(u);
    }


    std::vector<char> color = DivideToBipartite(adjList, n);

    Kuhn(n, adjList, color);

    return 0;
}