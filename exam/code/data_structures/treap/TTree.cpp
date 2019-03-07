
#include "TTree.h"

#include <iostream>

TNode::TNode(uint64_t key, uint64_t pr) : key(key), pr(pr), left(nullptr), right(nullptr),
                                          parent(nullptr) {}

TTree::TTree() {
    root = nullptr;
}

TNode *TTree::CreateNode(uint64_t key, uint64_t pr) {
    auto node = new TNode(key, pr);
    return node;
}

void split( TTree &t, TTree &t1, TTree &t2, int64_t key) {
    split(t.root, t1.root, t2.root, key);
}

void split(TNode *t, TNode *&t1, TNode *&t2, int64_t key) {
    if (t == nullptr) {
        t1 = t2 = nullptr;
    } else if (key >= t->key) {
        split(t->right, t->right, t2, key);
        t1 = t;
    } else {
        split(t->left, t1, t->left, key);
        t2 = t;
    }
}

void merge(TTree &t, TTree &t1, TTree &t2) {
    t.root = nullptr;
    merge(t.root, t1.root, t2.root);
}

void merge(TNode *&t, TNode *t1, TNode *t2) {
    if (t1 == nullptr && t2 != nullptr) {
        t = t2;
    }
    else if (t1 != nullptr && t2 == nullptr) {
        t = t1;
    }
    else if (t1->pr > t2->pr) {
        merge(t1->right, t1->right, t2);
        t = t1;
    }
    else {
        merge(t2->left, t1, t2->left);
        t = t2;
    }
}


void TTree::Insert(uint64_t key, uint64_t pr) {

    TNode *parentNode = nullptr;
    TNode *activeNode = root;


    while (true) {
        if (activeNode == nullptr) {
            activeNode = CreateNode(key, pr);
            break;
        } else if (key == activeNode->key) {
            return;
        } else if (key < activeNode->key) {
            parentNode = activeNode;
            activeNode = activeNode->left;
        } else {
            parentNode = activeNode;
            activeNode = activeNode->right;
        }
    }

    if (parentNode == nullptr) {
        root = activeNode;
    } else if (key < parentNode->key) {
        parentNode->left = activeNode;
    } else {
        parentNode->right = activeNode;
    }
    activeNode->parent = parentNode;


    while (activeNode->parent != nullptr && activeNode->parent->pr < activeNode->pr) {
        if (activeNode->parent->left == activeNode) {
            RotateRight(activeNode->parent);
        } else {
            RotateLeft(activeNode->parent);
        }
    }

}

void TTree::InsertMS(uint64_t key, uint64_t pr) {
    TTree t1, t2;
    TTree keyTree, tmpTree;
    keyTree.root = CreateNode(key, pr);


    split(*this, t1, t2, key);


    merge(tmpTree, t1, keyTree);

    merge(*this, tmpTree, t2);


}

void TTree::DeleteMS(uint64_t key) {
    TTree t1, t2;

    split(*this, t1, t2, key);

    cout << "t1:\n";
    t1.PrintTree();
    cout << "*********\n";
    cout << "t2:\n";
    t2.PrintTree();
    cout << "*********\n";

    TNode* parentNode = nullptr;
    TNode* activeNode = t1.root;
    if(activeNode != nullptr) {
        while(activeNode->right != nullptr) {
            parentNode = activeNode;
            activeNode = activeNode->right;
        }
        if(activeNode->key == key) {
            if(parentNode == nullptr) {
                t1.root = activeNode->left;
            }
            else if(parentNode->right == activeNode) {
                parentNode->right = activeNode->left;
            }
            else {
                parentNode->left = activeNode->left;
            }
            delete activeNode;
        }
    }

    cout << "t1:\n";
    t1.PrintTree();
    cout << "*********\n";

    merge(*this, t1, t2);


}


void TTree::Delete(uint64_t key) {

    TNode *activeNode = root;
    while (true) {
        if (activeNode == nullptr) {
            return;
        } else if (activeNode->key == key) {
            break;
        } else if (key < activeNode->key) {
            activeNode = activeNode->left;
        } else {
            activeNode = activeNode->right;
        }
    }

    int64_t maxPr = 0;
    while (activeNode->left != nullptr && activeNode->right != nullptr) {
        maxPr = max(activeNode->left->pr, activeNode->right->pr);
        if (maxPr == activeNode->left->pr) {
            RotateRight(activeNode);
        }
        else {
            RotateLeft(activeNode);
        }
    }

    if(activeNode->left != nullptr) {
        if(activeNode->parent->left == activeNode) {
            activeNode->parent->left = activeNode->left;
            activeNode->parent->left->parent = activeNode->parent;
        }
        else {
            activeNode->parent->right = activeNode->left;
            activeNode->parent->right->parent = activeNode->parent;
        }

    }
    else if (activeNode->right != nullptr) {
        if(activeNode->parent->left == activeNode) {
            activeNode->parent->left = activeNode->right;
            activeNode->parent->left->parent = activeNode->parent;
        }
        else {
            activeNode->parent->right = activeNode->right;
            activeNode->parent->right->parent = activeNode->parent;
        }

    }
    else {
        if(activeNode->parent->left == activeNode) {
            activeNode->parent->left = nullptr;
        }
        else {
            activeNode->parent->right = nullptr;
        }
    }
    delete activeNode;

}

void TTree::RotateRight(TNode *node) {
    TNode *main;
    main = node->left;
    node->left = main->right;
    main->right = node;

    main->parent = node->parent;

    if (node->parent == nullptr) {
        root = main;
    } else if (node->parent->left == node) {
        node->parent->left = main;
    } else {
        node->parent->right = main;
    }

    node->parent = main;
    if (node->left != nullptr) {
        node->left->parent = node;
    }
}

void TTree::RotateLeft(TNode *node) {
    TNode *main = node->right;
    node->right = main->left;
    main->left = node;

    main->parent = node->parent;
    if (node->parent == nullptr) {
        root = main;
    } else if (node->parent->left == node) {
        node->parent->left = main;
    } else {
        node->parent->right = main;
    }

    node->parent = main;
    if (node->right != nullptr) {
        node->right->parent = node;
    }
}


void TTree::PrintTree() {
    PrintTree(root, 0);
}

void TTree::PrintTree(TNode *node, uint64_t depth) {
    if (node == nullptr) {
        return;
    }

    PrintTree(node->right, depth + 1);

    for (int i = 0; i < depth; ++i) {
        cout << "\t";
    }
    cout << node->key;
    cout << "(" << node->pr << ")";
    cout << "\n";

    PrintTree(node->left, depth + 1);

}