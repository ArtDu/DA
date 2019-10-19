# O(V^3)


def floyd_warshall(w):
    n = len(w)

    d_last = w

    for k in range(n):
        d = [[0] * n for _ in range(n)]
        for i in range(n):
            for j in range(n):
                d[i][j] = min(d_last[i][j], d_last[i][k] + d_last[k][j])
        d_last = d
        print(d)


if __name__ == "__main__":
    N = int(input())
    W = []

    for _ in range(N):
        tmp = list(map(int, input().split()))
        W.append(tmp)

    floyd_warshall(W)

# for test:
#
# 5
# 0 3 8 9223372036854775807 -4
# 9223372036854775807 0 9223372036854775807 1 7
# 9223372036854775807 4 0 9223372036854775807 9223372036854775807
# 2 9223372036854775807 -5 0 9223372036854775807
# 9223372036854775807 9223372036854775807 9223372036854775807 6 0
