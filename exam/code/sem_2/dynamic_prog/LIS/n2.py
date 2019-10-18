# this code to solve the problem:
# https://practice.geeksforgeeks.org/problems/longest-increasing-subsequence/0
# docs:
# https://www.geeksforgeeks.org/longest-increasing-subsequence-dp-3/


def LIS(a):
    d = [0 for _ in range(len(a))]
    maximum = 1
    for i in range(len(a)):
        d[i] = 1
        for j in range(i):
            if a[j] < a[i] and d[j] + 1 > d[i]:
                d[i] = d[j] + 1
                if d[i] > maximum:
                    maximum = d[i]
    return maximum


if __name__ == '__main__':
    t = int(input())
    for _ in range(t):
        n = int(input())
        sequence = list(map(int, input().split()))
        print(LIS(sequence))
