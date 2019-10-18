# checker:
# https://practice.geeksforgeeks.org/problems/huffman-encoding/0
# docs:
# https://www.geeksforgeeks.org/huffman-coding-greedy-algo-3/


"""
for test

1
abcdef
5 9 12 13 16 45

"""


from heapq import heappush, heappop


class HuffmanItem:

    def __init__(self, frequency, letter, left_son, right_son):
        self.freq = frequency
        self.alpha = letter
        self.left = left_son
        self.right = right_son

    def __lt__(self, other):
        return self.freq < other.freq


def print_codes(tree, str_collector):
    if tree is None:
        return

    if tree.alpha != '$':
        print(str_collector, end=' ')

    print_codes(tree.left, str_collector + '0')
    print_codes(tree.right, str_collector + '1')


if __name__ == '__main__':

    t = int(input())
    for _ in range(t):
        alpha = list(input())
        freq = list(map(int, input().split()))

        pq = []  # инициализация priority_queue
        for i in range(len(alpha)):
            # вставка в очередь элемента alpha[i] и приоритетом freq[i]
            heappush(pq, HuffmanItem(freq[i], alpha[i], None, None))

        while len(pq) != 1:
            left = heappop(pq)
            right = heappop(pq)
            top = HuffmanItem(left.freq + right.freq, '$', left, right)
            heappush(pq, top)

        print_codes(heappop(pq), "")
        print()
