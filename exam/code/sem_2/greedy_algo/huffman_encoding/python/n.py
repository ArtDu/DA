# checker:
# https://practice.geeksforgeeks.org/problems/huffman-encoding/0
# docs:
# https://www.geeksforgeeks.org/efficient-huffman-coding-for-sorted-input-greedy-algo-4/

from collections import deque

"""
for test

1
abcdef
5 9 12 13 16 45

"""


class HuffmanCodeItem:

    def __init__(self, letter, freq, left=None, right=None):
        self.letter = letter
        self.freq = freq
        self.left = left
        self.right = right


class HuffmanCode:

    def __init__(self, letters, frequencies):
        self.queue_1 = deque()
        self.queue_2 = deque()
        for i in range(len(letters)):
            self.queue_1.append(HuffmanCodeItem(letters[i], frequencies[i]))

        # building huffman tree
        # we need first condition for first iteration case where we take 2 elements
        # from q1, merge them and push into q2
        while len(self.queue_1) != 0 or len(self.queue_2) != 1:
            left = self.find_min_and_pop()
            right = self.find_min_and_pop()

            self.queue_2.append(HuffmanCodeItem('$', left.freq + right.freq, left, right))

    def find_min_and_pop(self):
        if not self.queue_1:
            return self.queue_2.popleft()

        if not self.queue_2:
            return self.queue_1.popleft()

        if self.queue_1[0].freq <= self.queue_2[0].freq:
            return self.queue_1.popleft()
        return self.queue_2.popleft()

    def print_ans_aux(self, item, str_collector):
        if item is None:
            return

        if item.letter != '$':
            print(str_collector, end=' ')

        self.print_ans_aux(item.left, str_collector + '0')
        self.print_ans_aux(item.right, str_collector + '1')

    def print_ans(self):
        ans = self.queue_2.popleft()
        self.print_ans_aux(ans, '')


if __name__ == '__main__':

    t = int(input())
    for _ in range(t):
        l = list(input())
        f = list(map(int, input().split()))
        coded = HuffmanCode(l, f)
        coded.print_ans()
