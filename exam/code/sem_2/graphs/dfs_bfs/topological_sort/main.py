import collections


def topoSortAux(stack, visited, g, v):
    visited[v] = True

    for k in g[v]:
        if not visited[k]:
            topoSortAux(stack, visited, g, k)

    stack.append(v)


def topoSort(n, graph):
    visited = [False] * n
    stack = []

    for j in range(n):
        if not visited[j]:
            topoSortAux(stack, visited, graph, j)
    return list(reversed(stack))


if __name__ == "__main__":
    t = int(input())
    for _ in range(t):
        e, N = list(map(int, input().strip().split()))
        arr = list(map(int, input().strip().split()))
        graph = collections.defaultdict(list)
        for i in range(0, e * 2, 2):
            graph[arr[i]].append(arr[i + 1])

        res = topoSort(N, graph)
        # print res
        valid = True
        for i in range(N):
            n = len(graph[res[i]])
            for j in range(len(graph[res[i]])):
                for k in range(i + 1, N):
                    if res[k] == graph[res[i]][j]:
                        n -= 1
            # print n
            if n != 0:
                valid = False
                break
        if valid:
            print(1)
        else:
            print(0)
