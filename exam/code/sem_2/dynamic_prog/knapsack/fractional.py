class Item:
    def __init__(self, w, v):
        self.w = w
        self.val = v
        self.cost = v / w

    def __lt__(self, other):
        return self.cost < other.cost


def fractional_knapsack_problem(N, W, w, val):
    items = list()
    for i in range(len(w)):
        items.append(Item(int(w[i]), int(val[i])))

    items.sort(reverse=True)

    ans = 0
    for i in items:
        curW = i.w
        curV = i.val
        if W - curW >= 0:
            W -= curW
            ans += curV
        else:
            ans += W * i.cost
            break
    return ans


if __name__ == '__main__':
    t = int(input())
    for _ in range(t):
        N, W = map(int, input().split())
        wval = input().split()
        val = wval[::2]
        w = wval[1::2]
        print('%.2f' % (fractional_knapsack_problem(N, W, w, val)))
