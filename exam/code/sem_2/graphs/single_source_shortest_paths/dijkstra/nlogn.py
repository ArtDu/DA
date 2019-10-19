# A Python program for Dijkstra's shortest
# path algorithm for adjacency
# list representation of graph

# docs:
# https://www.geeksforgeeks.org/dijkstras-algorithm-for-adjacency-list-representation-greedy-algo-8/
# problem:
# https://practice.geeksforgeeks.org/problems/shortest-path-from-1-to-n/0


"""



Complexity: O(E * LogV)
E - we look each edge in graph and execute decrease_key
LogV - decrease_key operation in binary heap

for test:
2
9
4

"""

from collections import defaultdict

maxint = 2 ** 32


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
        self.array[0] = last
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
            if min_heap.in_heap(v) and dist[v] > dist[u] + w:
                dist[v] = dist[u] + w
                min_heap.decrease_key(v, dist[v])

    # dist.pop(s)
    return dist


def main():
    t = int(input())
    for _ in range(t):
        n, m = list(map(int, input().split()))
        edges = defaultdict(list)
        for _ in range(m):
            src, to, weight = list(map(int, input().split()))
            edges[src - 1].append(Edge(to - 1, weight))
            edges[to - 1].append(Edge(src - 1, weight))

        s = int(input()) - 1

        dist = dijkstra(edges, n, s)

        ans = ' '.join(map(str, dist))
        print(ans)


if __name__ == "__main__":
    main()
