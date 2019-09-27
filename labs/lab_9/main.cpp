#include <iostream>
#include <vector>


bool dfs(std::vector<char> &used, std::vector<int> &matching, std::vector<std::vector<int>> &adj_list, int v) {
    if (used[v]) return false;
    used[v] = true;
    for (auto to : adj_list[v]) {
        if (matching[to] == -1 || dfs(used, matching, adj_list, matching[to])) {
            matching[to] = v;
            return true;
        }
    }
    return false;
}

void kuhn(int n, std::vector<std::vector<int>> &adj_list) {
    std::vector<int> matching(n + 1, -1);
    std::vector<char> used;
    for (int v = 1; v <= n; ++v) {
        used.assign(n + 1, false);
        dfs(used, matching, adj_list, v);
    }

    int u,v;
    int u_last = -1, v_last = -1;
    for (int i = 1; i <= n; ++i)
        if (matching[i] != -1) {
            u = std::min(matching[i], i);
            v = std::max(matching[i], i);
            if (u_last != u || v_last != v) {
                printf("%d %d\n", u, v);
                u_last = u;
                v_last = v;
            }
        }


}


int main() {

    int n, m, u, v;
    std::cin >> n >> m;

    std::vector<std::vector<int>> adj_list(n + 1);

    for (int i = 0; i < m; ++i) {
        std::cin >> u >> v;
        adj_list[u].push_back(v);
        adj_list[v].push_back(u);
    }

    kuhn(n, adj_list);

    return 0;
}