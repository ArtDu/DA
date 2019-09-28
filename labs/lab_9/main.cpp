#include <iostream>
#include <vector>
#include <set>
#include <algorithm>


bool Dfs(std::vector<char> &used, std::vector<int> &matching, std::vector<std::set<int>> &adjList, int v) {
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

void Kuhn(int n, std::vector<std::set<int>> &adjList, std::vector<char> &part) {
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

int main() {

    int n, m, u, v;
    std::cin >> n >> m;

    std::vector<std::set<int>> adjList(n + 1);

    for (int i = 0; i < m; ++i) {
        std::cin >> u >> v;
        adjList[u].insert(v);
        adjList[v].insert(u);
    }


    std::vector<char> part(n + 1, -1);
    std::vector<int> q(n + 1);
    for (int st = 1; st <= n; ++st)
        if (part[st] == -1) {
            int h = 0, t = 0;
            q[t++] = st;
            part[st] = 0;
            while (h < t) {
                int v = q[h++];
                for (auto to : adjList[v]) {
                    if (part[to] == -1)
                        part[to] = !part[v], q[t++] = to;
                }
            }
        }


    Kuhn(n, adjList, part);

    return 0;
}