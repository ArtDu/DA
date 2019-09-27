import collections


def dfs_aux(visited, g, v):
    visited[v] = True
    print(v, end=" ")

    for j in g[v]:
        if not visited[j]:
            dfs_aux(visited, g, j)


def dfs(g, N):
    '''
    :param g: given adjacency list of graph
    :param N: number of nodes in N.
    :return: print the dfs of the graph from node 0, newline is given by driver code
    '''
    visited = [False] * N

    dfs_aux(visited, g, 0)


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
