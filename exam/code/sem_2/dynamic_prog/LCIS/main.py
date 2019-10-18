# docs:
# https://www.geeksforgeeks.org/longest-common-increasing-subsequence-lcs-lis/
# checker:
# https://practice.geeksforgeeks.org/problems/longest-common-increasing-subsequence/0


"""
for test:

1
4
3 4 9 1
7
5 3  8  9  10  2  1

"""


def LCIS(arr1, n, arr2, m):
    # table[j] = length of LCIS ending with arr2[j]
    table = [0 for _ in range(m)]

    maximum = 0

    for i in range(n):
        current = 0  # count of common elements that < a[i]
        # print("current : {}".format(current))
        # print(i, ":", sep=" ")
        for j in range(m):

            # print("\tj = {} ".format(j), end="")
            # print(": {} ==".format(arr1[i]), "{}".format(arr2[j]), sep=" ")
            if arr1[i] == arr2[j]:
                table[j] = current + 1
                # print("\t\t", end="")
                # print("t[{}] = {}".format(j, table[j]))
                if table[j] > maximum:
                    maximum = table[j]

            # cause increasing subsequence
            # we take latest common subsequence size
            if arr1[i] > arr2[j]:
                if table[j] > current:
                    # print("\t\t=========")
                    # print("\t\t", table, sep="")
                    # print("\t\tcurrent = {}".format(current))
                    # print("\t\tarr1[{i}] > arr2[{j}] and table[{j}] > current".format(i = i, j = j))
                    current = table[j]
                    # print("\t\t\tcurrent = {}".format(current))
                    # print("\t\t=========")
        # print(table, maximum, sep="\n")

    return maximum


if __name__ == "__main__":
    t = int(input())

    for _ in range(t):
        a = int(input())
        arr1 = list(map(int, input().split()))
        b = int(input())
        arr2 = list(map(int, input().split()))

        print(LCIS(arr1, a, arr2, b))
