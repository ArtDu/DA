# this code to solve the problem:
# https://practice.geeksforgeeks.org/problems/longest-increasing-subsequence/0
# docs:
# https://www.geeksforgeeks.org/longest-increasing-subsequence-dp-3/


def CeilIndex(A, l, r, key):
    while r - l > 1:
        m = l + ((r - l) // 2)
        if A[m] < key:
            l = m
        else:
            r = m
            if A[m] == key:
                break

    return r


def LIS(a):
    table = [0 for _ in range(len(a))]

    table[0] = a[0]
    size = 1
    for i in range(1, len(a)):
        if table[0] > a[i]:
            table[0] = a[i]
        elif table[size - 1] < a[i]:
            table[size] = a[i]
            size += 1
        else:
            table[CeilIndex(table, -1, size - 1, a[i])] = a[i]
    return size


if __name__ == '__main__':
    t = int(input())
    for _ in range(t):
        n = int(input())
        sequence = list(map(int, input().split()))
        print(LIS(sequence))
