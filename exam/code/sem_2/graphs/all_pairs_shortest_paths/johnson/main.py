# code not complete
# O(V*VLogV)

from collections import defaultdict

maxint = 2 ** 31


class Edge_b_f:
    def __init__(self, src, to, weight):
        self.src = src
        self.to = to
        self.weight = weight


def relax(dist, u, v, w):
    if dist[v] > dist[u] + w:
        dist[v] = dist[u] + w


def bellman_ford(v_nums, edges):
    # Step 1: Initialize distances from src to all other vertices
    # as INFINITE
    dist = [2 ** 32] * (v_nums + 1)
    dist[0] = 0

    # Step 2: Relax all edges |V| - 1 times. A simple shortest
    # path from src to any other vertex can have at-most |V| - 1
    # edges
    for _ in range(v_nums - 1):
        for edge in edges:
            relax(dist, edge.src, edge.to, edge.weight)

    return dist


class HeapItem:
    def __init__(self, pos_in_graph, dist):
        self.pos_in_graph = pos_in_graph
        self.dist = dist


class Heap:
    def __init__(self):
        self.array = []
        # pos[positionInGraph] = position in Heap
        self.pos = []
        self.size = 0

    def in_heap(self, v):
        if self.pos[v] < self.size:
            return True
        return False

    def heapify(self, idx):
        smallest = idx
        left = 2 * idx + 1
        right = 2 * idx + 2

        if left < self.size and self.array[left].dist < self.array[smallest].dist:
            smallest = left

        if right < self.size and self.array[right].dist < self.array[smallest].dist:
            smallest = right

        if smallest != idx:
            self.swap_heap_node(self.array[smallest].pos_in_graph, self.array[idx].pos_in_graph, smallest, idx)

            self.heapify(smallest)

    def swap_heap_node(self, fst_graph_pos, snd_graph_pos, fst_heap_pos, snd_heap_pos):
        self.pos[fst_graph_pos] = snd_heap_pos
        self.pos[snd_graph_pos] = fst_heap_pos
        self.array[fst_heap_pos], self.array[snd_heap_pos] = self.array[snd_heap_pos], self.array[fst_heap_pos]

    def decrease_key(self, v, new_dist):
        pos = self.pos[v]

        self.array[pos].dist = new_dist

        # from bottom to up heapify
        while pos > 0 and self.array[(pos - 1) // 2].dist > self.array[pos].dist:
            self.swap_heap_node(self.array[(pos - 1) // 2].pos_in_graph, self.array[pos].pos_in_graph,
                                (pos - 1) // 2, pos)
            # move to parent index
            pos = (pos - 1) // 2

    def empty(self):
        return True if self.size == 0 else False

    def extract_min(self):

        if self.empty():
            return

        # 0 is position minimum in heap
        # size - 1 is position last in heap
        minimum = self.array[0]
        last = self.array[self.size - 1]
        # replace minimum with the last element
        self.pos[minimum.pos_in_graph] = self.size - 1
        self.pos[last.pos_in_graph] = 0
        self.array[0] = self.array[self.size - 1]
        # delete last element
        self.size -= 1

        self.heapify(0)
        return minimum


class Edge:
    def __init__(self, to, weight):
        self.to = to
        self.weight = weight


def dijkstra(edges, n, s):
    dist = [maxint] * n
    min_heap = Heap()

    # fill the min heap
    for v in range(n):
        min_heap.array.append(HeapItem(v, maxint))
        min_heap.pos.append(v)
    min_heap.size = n

    # mark start vertex
    dist[s] = 0
    min_heap.decrease_key(s, 0)

    while not min_heap.empty():

        minimum = min_heap.extract_min()
        u = minimum.pos_in_graph
        # if adjacent vertex in heap then vertex isn't complete
        for edge in edges[u]:
            v = edge.to
            w = edge.weight
            if min_heap.in_heap(v) and dist[u] != maxint and dist[v] > dist[u] + w:
                dist[v] = dist[u] + w
                min_heap.decrease_key(v, dist[v])

    # dist.pop(s)
    return dist


def johnson(edges, n):
    edges_b_f = []
    for v in range(1, n + 1):
        edges_b_f.append(Edge_b_f(0, v, 0))

    for u in range(1, n + 1):
        for v in edges[u]:
            edges_b_f.append(Edge_b_f(u, v.to, v.weight))

    h = bellman_ford(n, edges_b_f)

    for u in range(1, n + 1):
        for v in edges[u]:
            v.weight = v.weight + h[u] - h[v.to]

    # print all changed edges
    for u in range(1, n + 1):
        print(u, end=": ")
        for v in edges[u]:
            print(v.to, v.weight, sep=", ", end="; ")
        print()

    #  use djkstra for all v


"""
for test:

1
5 8
1 2 3
1 3 8
1 5 -4
2 5 7
2 4 1 
3 2 4
4 3 -5
5 4 6

"""


def main():
    t = int(input())
    for _ in range(t):
        n, m = list(map(int, input().split()))
        edges = defaultdict(list)
        for _ in range(m):
            src, to, weight = list(map(int, input().split()))
            edges[src].append(Edge(to, weight))

        dist = johnson(edges, n)

        # ans = ' '.join(map(str, dist))
        # print(ans)


if __name__ == "__main__":
    main()
