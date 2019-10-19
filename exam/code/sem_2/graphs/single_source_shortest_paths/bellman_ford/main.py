# docs:
# https://www.geeksforgeeks.org/bellman-ford-algorithm-dp-23/
# problem(exist in graph negative cycle?):
# https://practice.geeksforgeeks.org/problems/negative-weight-cycle/0
#
# time complexity: O(V * E)
#


class Edge_b_f:
    def __init__(self, src, to, weight):
        self.src = src
        self.to = to
        self.weight = weight


def relax(dist, u, v, w):
    if dist[v] > dist[u] + w:
        dist[v] = dist[u] + w


def bellman_ford(v_nums, edges):
    dist = [2 ** 32] * (v_nums + 1)
    dist[0] = 0

    # Relax all edges |V| - 1 times. A simple shortest
    # path from src to any other vertex can have at-most |V| - 1
    # edges
    for _ in range(v_nums - 1):  # O(V)
        for edge in edges: # O(E)
            relax(dist, edge.src, edge.to, edge.weight)

    # Check for negative-weight cycles.  The above step
    # guarantees shortest distances if graph doesn't contain
    # negative weight cycle.  If we get a shorter path, then there
    # is a cycle.
    for i in edges:
        if dist[i.to] > dist[i.src] + i.weight:
            return False

    return True  # true - no negative loops


if __name__ == "__main__":
    t = int(input())
    for _ in range(t):
        v, e = list(map(int, input().split()))
        tmp_arr = list(map(int, input().split()))
        adjacency_list = []
        for i in range(0, len(tmp_arr), 3):
            adjacency_list.append(Edge_b_f(tmp_arr[i], tmp_arr[i + 1], tmp_arr[i + 2]))

        print(0) if bellman_ford(v, adjacency_list) else print(1)
