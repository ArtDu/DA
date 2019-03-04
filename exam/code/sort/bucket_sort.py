
import sys


def bucket_sort(A):
    n = len(A)
    B = [[] for i in range(n)]
    _ans = []
    for i in range(n):
        B[int(n*float(A[i]))].append(A[i])
    for i in range(n):
        if B[i] is not False:
            B[i].sort()
            _ans = _ans + B[i]
    return _ans


arr = (sys.stdin.read()).split()

ans = bucket_sort(arr)
print(ans)
