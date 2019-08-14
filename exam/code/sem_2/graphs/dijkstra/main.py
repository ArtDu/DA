from heapq import heappush, heappop
from collections import defaultdict


class Edge:
    def __init__(self, to, weight):
        self.to = to
        self.weight = weight


class Vertex:

    def __init__(self, num):
        self.d = 2 ** 32
        self.num = num

    def __lt__(self, other):
        return self.d < other.d

def relax(dist, src, to, weight):

def dijkstra(edges, V, s):
    pq = []
    for i in range(V):
        tmp = Vertex(i)
        if i == s:
            tmp.d = 0
        heappush(pq, tmp)

    while len(pq) != 0:
        vertex = heappop(pq)
        for adjacencyVertex in edges[vertex]:


if __name__ == "__main__":
    N, M, S = list(map(int, input().split()))
    edges = defaultdict(list)
    for _ in range(M):
        src, to, weight = list(map(int, input().split()))
        edges[src].append(Edge(to, weight))

    dijkstra(edges, N, S)
