import sys


def extend_shortest_paths(L, W):
    n = len(L)
    l = [[0] * n for _ in range(n)]
    for i in range(n):
        for j in range(n):
            l[i][j] = sys.maxsize
            for k in range(n):
                l[i][j] = min(l[i][j], L[i][k] + W[k][j])
    return l


def slow_all_pairs_shortest_paths(W):
    n = len(W)
    L_last = W
    print(L_last)
    for m in range(1, n - 1):
        L_last = extend_shortest_paths(L_last, W)
        print(L_last)
    # return L[n - 1]


def fast_all_pairs_shortest_paths(W):
    n = len(W)
    L_last = W
    print(L_last)
    m = 1
    while m < n - 1:
        L_last = extend_shortest_paths(L_last, L_last)
        m *= 2
        print(L_last)
    # return L[n - 1]


if __name__ == "__main__":
    n = int(input())
    w = []

    for _ in range(n):
        tmp = list(map(int, input().split()))
        w.append(tmp)

    fast_all_pairs_shortest_paths(w)

#
# 5
# 0 3 8 9223372036854775807 -4
# 9223372036854775807 0 9223372036854775807 1 7
# 9223372036854775807 4 0 9223372036854775807 9223372036854775807
# 2 9223372036854775807 -5 0 9223372036854775807
# 9223372036854775807 9223372036854775807 9223372036854775807 6 0
