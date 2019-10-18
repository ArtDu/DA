#
# checker:
# [https://practice.geeksforgeeks.org/problems/bfs-traversal-of-graph/1]
# docs:
# [https://www.geeksforgeeks.org/breadth-first-search-or-bfs-for-a-graph/]


import collections


def bfs(g, N):
    # for this time complexity V + E
    # this part = V
    visited = [False for _ in range(N)]

    queue = list()
    queue.append(0)
    visited[0] = True

    while len(queue) != 0:

        elem = queue.pop(0)
        print(elem, end=" ")

        # this part = E
        for v in g[elem]:
            if not visited[v]:
                queue.append(v)
                visited[v] = True


if __name__ == "__main__":
    t = int(input())
    for _ in range(t):
        N, E = input().split()
        N, E = int(N), int(E)
        E_list = list(map(int, input().split()))
        adjacency_list = collections.defaultdict(list)
        for i in range(0, E * 2, 2):
            adjacency_list[E_list[i]].append(E_list[i + 1])
        bfs(adjacency_list, N)
        print()

