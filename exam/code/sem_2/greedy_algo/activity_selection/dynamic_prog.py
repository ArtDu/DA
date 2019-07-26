def activity_selector(sf):
    L = [[] for _ in range(len(sf))]
    maximum = []
    for i in range(len(sf)):
        for j in range(i):
            if sf[i][1] > sf[j][2] and len(L[j]) > len(L[i]):
                L[i] = L[j].copy()
        L[i].append(sf[i][0])
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
