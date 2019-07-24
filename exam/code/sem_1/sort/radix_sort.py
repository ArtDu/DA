
import sys


def counting_sort(A, index):
    B = [0] * (len(A))  # result list
    tmp = [int(A[i][index]) for i in range(len(A))]
    k = (max(tmp)+1)
    C = [0] * k  # preprocess list
    for i in tmp:
        C[i] += 1
    for i in range(1, k):
        C[i] += C[i-1]
    for i in range(len(A)-1, -1, -1):
        B[C[int(A[i][index])] - 1] = A[i]
        C[int(A[i][index])] -= 1
    return B


def radix_sort(A):
    for i in range(len(A[0])-1, -1, -1):
        B = counting_sort(A, i)
    return B


arr = (sys.stdin.read()).split()

ans = radix_sort(arr)
print(ans)
