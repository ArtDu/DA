class Node:
    def __init__(self, key):
        self.key = key
        self.p = None
        self.left = None
        self.right = None

    def get(self):
        return self.key

    def set(self, key):
        self.key = key


class BinSearchTree:
    def __init__(self):
        self.root = None

    def in_order_walk(self, node):
        if node is not None:
            self.in_order_walk(node.left)
            print(node.key)
            self.in_order_walk(node.right)

    def tree_search(self, cur_node, elem):
        if cur_node is None or elem == cur_node.key:
            return cur_node
        if elem < cur_node.key:
            return self.tree_search(cur_node.left, elem)
        else:
            return self.tree_search(cur_node.right, elem)

    def insert(self, int_elem):
        elem = Node(int_elem)
        trail_pnt = None
        tmp = self.root
        while tmp is not None:
            trail_pnt = tmp
            if elem.key < tmp.key:
                tmp = tmp.left
            else:
                tmp = tmp.right
        elem.p = trail_pnt
        if trail_pnt is None:
            self.root = elem
        elif elem.key < trail_pnt.key:
            trail_pnt.left = elem
        else:
            trail_pnt.right = elem

    def min(self, node):
        while node.left is not None:
            node = node.left
        return node

    def max(self, node):
        while node.right is not None:
            node = node.right
        return node

    def transplant(self, u, v):
        if u.p is None:
            self.root = v
        elif u == u.p.left:
            u.p.left = v
        else:
            u.p.right = v
        if v is not None:
            v.p = u.p

    def delete_node(self, elem):
        if elem.left is None:
            self.transplant(elem, elem.right)
        elif elem.right is None:
            self.transplant(elem, elem.left)
        else:
            y = self.min(elem.right)
            if y.p != elem:
                self.transplant(y, y.right)
                y.right = elem.right
                y.right.p = y
            self.transplant(elem, y)
            y.left = elem.left
            y.left.p = y

    def successor(self, node):
        if node.right is not None:
            return self.min(node.right)
        y = node.p
        if y is not None and y.right == node:
            node = y
            y = y.p
        return y

    def predecessor(self, node):
        if node.left is not None:
            return self.max(node.left)
        y = node.p
        if y is not None and y.left == node:
            node = y
            y = y.p
        return y


tree = BinSearchTree()
tree.insert(5)
tree.insert(6)
tree.insert(4)

print(tree.predecessor(tree.tree_search(tree.root, 6)).get())
print(tree.predecessor(tree.tree_search(tree.root, 5)).get())
# tree.successor(tree.tree_search(tree.root, 6)).get()