# https://www.geeksforgeeks.org/assembly-line-scheduling-dp-34/

def carAssembly(S, T, begin, end):
    """
        begin[0] = edge from start to fst station on line 1
        begin[1] = edge from start to snd station on line 2

        f1[station] = min cost to reach this station on 1st line;
        f2[station] = min cost to reach this station on 2nd line;

        S[line][station] = cost for work on this station and line;
        T[from line][to station on other line] = cost for transition

        end[0] = edge from last station on line fst to finish
        end[1] = edge from last station on line snd to finish

    """
    num_station = len(S[0])

    f0 = [0] * num_station
    f1 = [0] * num_station

    f0[0] = begin[0] + S[0][0]
    f1[0] = begin[1] + S[1][0]

    for i in range(1, num_station):
        f0[i] = min(f0[i - 1] + S[0][i], f1[i - 1] + S[0][i] + T[1][i])
        f1[i] = min(f1[i - 1] + S[1][i], f0[i - 1] + S[1][i] + T[0][i])

    return min(f0[num_station - 1] + end[0], f1[num_station - 1] + end[1])


S = [[4, 5, 3, 2],
     [2, 10, 1, 4]]
T = [[0, 7, 4, 5],
     [0, 9, 2, 8]]
begin = [10, 12]
end = [18, 7]

print(carAssembly(S, T, begin, end))
