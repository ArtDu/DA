from collections import defaultdict

maxint = 2 ** 32


class Edge:
    def __init__(self, to, weight):
        self.to = to
        self.weight = weight


def relax(spt_set, dist, src, to, weight):
    if dist[to] > dist[src] + weight and spt_set[to] == False:
        dist[to] = dist[src] + weight


def find_min(spt_set, dist, V):
    m = maxint
    m_index = -1
    for v in range(V):
        if spt_set[v] == False and dist[v] < m:
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
    spt_set = [False for _ in range(V)]

    for _ in range(V):
        v = find_min(spt_set, dist, V)

        spt_set[v] = True

        for i in edges[v]:
            relax(spt_set, dist, v, i.to, i.weight)

    # print_dist(dist, V)
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

    # N, M, S = list(map(int, input().split()))
    # edges = defaultdict(list)
    # for _ in range(M):
    #     src, to, weight = list(map(int, input().split()))
    #     edges[src].append(Edge(to, weight))
    #     edges[to].append(Edge(src, weight))
    #
    # dijkstra(edges, N, S)
