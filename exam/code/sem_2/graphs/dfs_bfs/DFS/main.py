# this code for this problem:
# [https://practice.geeksforgeeks.org/problems/depth-first-traversal-for-a-graph/1]
# docs:
# [https://www.geeksforgeeks.org/depth-first-search-or-dfs-for-a-graph/]

import collections


def dfs_aux(visited, adj_list, u):
    visited[u] = True
    print(u, end=" ")

    for v in adj_list[u]:
        if not visited[v]:
            dfs_aux(visited, adj_list, v)


def dfs(adj_list, v):
    """
    :param adj_list: given adjacency list of graph
    :param v: number of nodes in N.
    :return: print the dfs of the graph from node 0, newline is given by driver code
    """
    visited = [False] * v

    dfs_aux(visited, adj_list, 0)


if __name__ == "__main__":
    t = int(input())
    for _ in range(t):
        N, E = input().split()
        N, E = int(N), int(E)
        E_list = list(map(int, input().split()))
        adjacency_list = collections.defaultdict(list)
        for i in range(0, E * 2, 2):
            adjacency_list[E_list[i]].append(E_list[i + 1])
        dfs(adjacency_list, N)
        print()
