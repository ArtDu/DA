# docs:
# https://www.geeksforgeeks.org/strongly-connected-components/
# problem:
# https://practice.geeksforgeeks.org/problems/strongly-connected-components-kosarajus-algo/1


from collections import defaultdict


def DFS_fill_stack(visited, stack, graph, v):
    visited[v] = True

    for i in graph[v]:
        if not visited[i]:
            DFS_fill_stack(visited, stack, graph, i)

    stack.append(v)


def transposeG(G):
    gTrans = defaultdict(list)

    for vertex in G:
        for adjacencyVertex in G[vertex]:
            gTrans[adjacencyVertex].append(vertex)

    return gTrans


def DFS_print_SCCs(visited, graph, v):
    visited[v] = True

    # print(v, end=" ")

    for adjacencyVertex in graph[v]:
        if not visited[adjacencyVertex]:
            DFS_print_SCCs(visited, graph, adjacencyVertex)


def SCCs(V, g):
    visited = [False] * V
    stack = []

    for i in range(V):
        if not visited[i]:
            DFS_fill_stack(visited, stack, g, i)

    gTrans = transposeG(g)

    ans = 0
    visited = [False] * V
    while len(stack) != 0:
        elem = stack.pop()
        if not visited[elem]:
            DFS_print_SCCs(visited, gTrans, elem)
            ans += 1
            # print()

    return ans


if __name__ == "__main__":
    t = int(input())
    for _ in range(t):
        N, M = input().split()
        N, M = int(N), int(M)
        M_list = list(map(int, input().split()))
        adjacency_list = defaultdict(list)
        for i in range(0, M * 2, 2):
            adjacency_list[M_list[i]].append(M_list[i + 1])
        print(SCCs(N, adjacency_list))
