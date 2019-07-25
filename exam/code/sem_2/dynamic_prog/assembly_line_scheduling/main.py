def carAssembly(S, T, begin, end):
    num_station = len(S[0])

    f1 = [0] * num_station
    f2 = [0] * num_station

    f1[0] = begin[0] + S[0][0]
    f2[0] = begin[1] + S[1][0]

    for i in range(1, num_station):
        f1[i] = min(f1[i - 1] + S[0][i], f2[i - 1] + S[0][i] + T[1][i])

        f2[i] = min(f2[i - 1] + S[1][i], f1[i - 1] + S[1][i] + T[0][i])

    return min(f1[num_station - 1] + end[0], f2[num_station - 1] + end[1])


S = [[4, 5, 3, 2],
     [2, 10, 1, 4]]
T = [[0, 7, 4, 5],
     [0, 9, 2, 8]]
begin = [10, 12]
end = [18, 7]

print(carAssembly(S, T, begin, end))
