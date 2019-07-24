
def counting_sort(A):
    B = [0] * (len(A))  # result list
    k = (max(A)+1)
    C = [0] * k  # preprocess list
    for i in A:
        C[i] += 1
    for i in range(1, k):
        C[i] += C[i-1]
    for i in range(len(A)-1, -1, -1):
        B[C[A[i]]-1] = A[i]
        C[A[i]] -= 1
    return B


arr = [int(x) for x in input().split()]
ans = counting_sort(arr)
print(ans)
