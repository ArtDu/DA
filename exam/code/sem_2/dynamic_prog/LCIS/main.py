def LCIS(arr1, n, arr2, m):
    table = [0 for _ in range(m)]

    maximum = 0

    for i in range(n):
        current = 0
        for j in range(m):

            if arr1[i] == arr2[j]:
                table[j] = current + 1
                if table[j] > maximum:
                    maximum = table[j]

            # cause increasing subsequence
            # we take latest subsequence size
            if arr1[i] > arr2[j]:
                if table[j] > current:
                    current = table[j]

    return maximum


if __name__ == "__main__":
    t = int(input())

    for _ in range(t):
        a = int(input())
        arr1 = list(map(int, input().split()))
        b = int(input())
        arr2 = list(map(int, input().split()))

        print(LCIS(arr1, a, arr2, b))
