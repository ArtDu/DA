# docs:
# https://www.geeksforgeeks.org/activity-selection-problem-greedy-algo-1/
# this code to solve problem:
# https://practice.geeksforgeeks.org/problems/n-meetings-in-one-room/0


def activity_selector(sf):
    k = 0
    print(sf[k][0], end=" ")
    for m in range(1, len(sf)):
        if sf[m][1] >= sf[k][2]:
            print(sf[m][0], end=" ")
            k = m
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
