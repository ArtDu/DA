# docs:
# https://www.geeksforgeeks.org/dijkstras-algorithm-for-adjacency-list-representation-greedy-algo-8/
# problem:
# https://practice.geeksforgeeks.org/problems/shortest-path-from-1-to-n/0


"""
for test:
2
9
4

"""

from collections import defaultdict

maxint = 2 ** 32


class Edge:
    def __init__(self, to, weight):
        self.to = to
        self.weight = weight


def relax(min_set, dist, src, to, weight):
    if not min_set[to] and dist[to] > dist[src] + weight:
        dist[to] = dist[src] + weight


def find_min(min_set, dist, V):
    m = maxint
    m_index = -1
    for v in range(V):
        if not min_set[v] and dist[v] < m:
            m = dist[v]
            m_index = v
    return m_index


def print_dist(dist, V):
    for v in range(V):
        print(dist[v], end=" ")
    print()


def dijkstra(edges, V, s):
    dist = [maxint for _ in range(V)]
    dist[s] = 0
    min_set = [False for _ in range(V)]  # the vertices which we don't look

    for _ in range(V):
        u = find_min(min_set, dist, V)

        min_set[u] = True

        for v in edges[u]:
            relax(min_set, dist, u, v.to, v.weight)

    print(dist[n])


if __name__ == "__main__":

    t = int(input())
    for _ in range(t):
        edges = defaultdict(list)
        n = int(input())
        for i in range(1, n):
            j = i + 1
            edges[i].append(Edge(j, 1))
            j = 3 * i
            if j <= n:
                edges[i].append(Edge(j, 1))
        dijkstra(edges, n + 1, 1)
