# docs:
# https://www.geeksforgeeks.org/activity-selection-problem-greedy-algo-1/
# this code to solve problem:
# https://practice.geeksforgeeks.org/problems/n-meetings-in-one-room/0


"""
test nums
1
11
1 3 0 5 3 5 6 8 8 2 12
4 5 6 7 8 9 10 11 12 13 14

"""


def activity_selector(sf):
    L = [[] for _ in range(len(sf))]
    maximum = []
    for i in range(len(sf)):
        for j in range(i):
            if sf[i][1] > sf[j][2] and len(L[j]) > len(L[i]):
                L[i] = L[j].copy()
        L[i].append(sf[i][0])
        # print("L[{}]".format(i), L[i], sep=" ")
        maximum = L[i] if len(L[i]) > len(maximum) else maximum

    for i in maximum:
        print(i, end=' ')
    print()


t = int(input())

for _ in range(t):
    n = int(input())
    nums = [i for i in range(1, n + 1)]
    s = map(int, input().split())
    f = map(int, input().split())
    sf = list(zip(nums, s, f))
    sf.sort(key=lambda x: x[2])
    activity_selector(sf)
