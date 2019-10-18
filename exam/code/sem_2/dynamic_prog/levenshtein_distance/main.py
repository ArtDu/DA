# checker:
# https://practice.geeksforgeeks.org/problems/edit-distance/0
# docs:
# https://www.geeksforgeeks.org/edit-distance-dp-5/


def edit_distance(s1, s2, l1, l2):
    mem = [[0 for _ in range(l2 + 1)] for _ in range(l1 + 1)]

    for i in range(l1 + 1):
        for j in range(l2 + 1):

            if i == 0:
                mem[i][j] = j
            elif j == 0:
                mem[i][j] = i
            else:
                if s1[i - 1] == s2[j - 1]:
                    mem[i][j] = mem[i - 1][j - 1]
                else:
                    mem[i][j] = 1 + \
                                min(mem[i - 1][j - 1],
                                    mem[i - 1][j],
                                    mem[i][j - 1]
                                    )

    return mem[l1][l2]


t = int(input())

for _ in range(t):
    len1, len2 = map(int, input().split())
    str1, str2 = input().split()
    print(edit_distance(str1, str2, len1, len2))
