
//with bug in DeleteFix


#include "TTree.h"

#include <iostream>

TNode::TNode(string key, uint64_t val) : key(key), val(val), left(nullptr), right(nullptr), height(0),
                                         parent(nullptr) {}

TTree::TTree() {
    nil = new TNode("", 0);
    nil->color = BLACK;
    root = nil;
}

TNode *TTree::CreateNode(string key, uint64_t val) {
    auto node = new TNode(key, val);
    node->left = node->right = nil;
    node->parent = nil;
}

TNode *TTree::rotateLeft(TNode *node) {
    TNode *main;
    main = node->right;
    node->right = main->left;
    main->left = node;

    main->parent = node->parent;
    //change child in node->p
    if (main->parent == nil) {
        root = main;
    } else if (node->parent->left == node) {
        node->parent->left = main;
    } else {
        node->parent->right = main;
    }

    if (node->right != nil) {
        node->right->parent = node;
    }
    main->left->parent = main;

    return main;
}


TNode *TTree::rotateRight(TNode *node) {
    TNode *main;
    main = node->left;
    node->left = main->right;
    main->right = node;

    main->parent = node->parent;
    //change child in node->p
    if (main->parent == nil) {
        root = main;
    } else if (node->parent->left == node) {
        node->parent->left = main;
    } else {
        node->parent->right = main;
    }

    if (node->left != nil) {
        node->left->parent = node;
    }
    main->right->parent = main;

    return main;
}

void TTree::Transplant(TNode *oldNode, TNode *newNode) {
    if (oldNode->parent == nil) {
        root = newNode;
    } else if (oldNode == oldNode->parent->left) {
        oldNode->parent->left = newNode;
    } else {
        oldNode->parent->right = newNode;
    }
    newNode->parent = oldNode->parent;

}

TNode *TTree::minElem(TNode *node) {
    while (node->left != nil) {
        node = node->left;
    }
    return node;
}

void TTree::DeleteNode(string key) {

    TNode *activeNode = root;

    while (true) {

        if (activeNode == nil) {
            return;
        }

        if (activeNode->key == key) {
            break;
        } else if (key < activeNode->key) {
            activeNode = activeNode->left;
        } else {
            activeNode = activeNode->right;
        }
    }

    TNode *nextElem = activeNode;
    TNode *nextElemChild;
    string origColorNextElem = nextElem->color;

    if (activeNode->left == nil) {
        nextElemChild = activeNode->right;
        Transplant(activeNode, activeNode->right);
    } else if (activeNode->right == nil) {
        nextElemChild = activeNode->left;
        Transplant(activeNode, activeNode->left);
    } else {
        nextElem = minElem(activeNode->right);
        origColorNextElem = nextElem->color;
        nextElemChild = nextElem->right;
        if (nextElem->parent == activeNode) {
            nextElemChild->parent = nextElem;
        } else {
            Transplant(nextElem, nextElem->right);
            nextElem->right = activeNode->right;
            nextElem->right->parent = nextElem;
        }
        Transplant(activeNode, nextElem);
        nextElem->left = activeNode->left;
        nextElem->left->parent = nextElem;
        nextElem->color = activeNode->color;
    }

    if (origColorNextElem == BLACK) {
        DeleteNodeFix(nextElemChild);
    }


}

void TTree::DeleteNodeFix(TNode *node) {
    while (node != root && node->color == BLACK) {
        if (node->parent->left == node) {
            TNode *bros = node->parent->right;
            if (bros->color == RED) {
                bros->color = BLACK;
                node->parent->color = RED;
                if (node->parent->parent == nil) {
                    root = rotateLeft(node->parent);
                } else if (node->parent->parent->left == node->parent) {
                    node->parent->parent->left = rotateLeft(node->parent);
                } else {
                    node->parent->parent->right = rotateLeft(node->parent);
                }
                bros = node->parent->right;
            } else {
                if (bros->right->color == BLACK && bros->left->color == BLACK) {
                    bros->color = RED;
                    node = node->parent;
                } else if (bros->left->color == RED) {
                    bros->left->color = BLACK;
                    bros->color = RED;
                    if (bros->parent == nil) {
                        root = rotateRight(bros);
                    } else if (bros->parent->left == bros) {
                        bros->parent->left = rotateRight(bros);
                    } else {
                        bros->parent->right = rotateRight(bros);
                    }
                    bros = bros->parent;
                }
                else {

                    bros->color = bros->parent->color;
                    bros->right->color = BLACK;
                    node->parent->color = BLACK;

                    if (node->parent->parent == nil) {
                        root = rotateLeft(node->parent);
                    } else if (node->parent->parent->left == node->parent) {
                        node->parent->parent->left = rotateLeft(node->parent);
                    } else {
                        node->parent->parent->right = rotateLeft(node->parent);
                    }


                    node = root;
                }
            }
        } else {
            TNode *bros = node->parent->left;
            if (bros->color == RED) {
                bros->color = BLACK;
                node->parent->color = RED;
                if (node->parent->parent == nil) {
                    root = rotateRight(node->parent);
                } else if (node->parent->parent->right == node->parent) {
                    node->parent->parent->right = rotateRight(node->parent);
                } else {
                    node->parent->parent->left = rotateRight(node->parent);
                }
                bros = node->parent->left;
            } else {
                if (bros->left->color == BLACK && bros->right->color == BLACK) {
                    bros->color = RED;
                    node = node->parent;
                } else if (bros->right->color == RED) {
                    bros->right->color = BLACK;
                    bros->color = RED;
                    if (bros->parent == nil) {
                        root = rotateLeft(bros);
                    } else if (bros->parent->right == bros) {
                        bros->parent->right = rotateLeft(bros);
                    } else {
                        bros->parent->left = rotateLeft(bros);
                    }
                    bros = bros->parent;
                }
                else {

                    bros->color = bros->parent->color;
                    bros->left->color = BLACK;
                    node->parent->color = BLACK;

                    if (node->parent->parent == nil) {
                        root = rotateRight(node->parent);
                    } else if (node->parent->parent->right == node->parent) {
                        node->parent->parent->right = rotateRight(node->parent);
                    } else {
                        node->parent->parent->left = rotateRight(node->parent);
                    }


                    node = root;
                }
            }
        }
    }
    node->color = BLACK;
}


void TTree::Insert(string key, uint64_t val) {

    TNode *parentNode = nil;
    TNode *activeNode = root;


    while (true) {
        if (activeNode == nil) {
            activeNode = CreateNode(key, val);
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

    if (parentNode == nil) {
        root = activeNode;
    } else if (key < parentNode->key) {
        parentNode->left = activeNode;
    } else {
        parentNode->right = activeNode;
    }
    activeNode->parent = parentNode;
    activeNode->left = activeNode->right = nil;
    activeNode->color = RED;
    InsertFix(activeNode);

}

void TTree::InsertFix(TNode *node) {

    TNode *uncle;
    while (node->parent->color == RED) {
        if (node->parent->parent->left == node->parent) {
            uncle = node->parent->parent->right;
            if (uncle->color == RED) {
                node->parent->color = BLACK; // father - black
                uncle->color = BLACK; // uncle black
                node->parent->parent->color = RED; // gfather - red
                node = node->parent->parent; // x = gfather
            } else if (node->parent->right == node) {
                node = node->parent; // x = father
                node->parent->left = rotateLeft(node);    // rotateLeft(x)
            } else {
                node->parent->color = BLACK; // father - black
                node->parent->parent->color = RED; // gfather - red
                // rotateRight(gfather)
                if (node->parent->parent->parent == nil) {
                    root = rotateRight(node->parent->parent);
                } else if (node->parent->parent->parent->left == node->parent->parent) {
                    node->parent->parent->parent->left = rotateRight(node->parent->parent);
                } else {
                    node->parent->parent->parent->right = rotateRight(node->parent->parent);
                }

            }
        } else {
            uncle = node->parent->parent->left;
            if (uncle->color == RED) {
                node->parent->color = BLACK;
                uncle->color = BLACK;
                node->parent->parent->color = RED;
                node = node->parent->parent;
            } else if (node->parent->left == node) {
                node = node->parent;
                node->parent->right = rotateRight(node);
            } else {
                node->parent->color = BLACK;
                node->parent->parent->color = RED;
                //node->parent->parent = rotateLeft(node->parent->parent);
                if (node->parent->parent->parent == nil) {
                    root = rotateLeft(node->parent->parent);
                } else if (node->parent->parent->parent->left == node->parent->parent) {
                    node->parent->parent->parent->left = rotateLeft(node->parent->parent);
                } else {
                    node->parent->parent->parent->right = rotateLeft(node->parent->parent);
                }
            }
        }
    }
    root->color = BLACK;
}

void TTree::PrintTree() {
    PrintTree(root, 0);
}

void TTree::PrintTree(TNode *node, uint64_t depth) {
    if (node == nil) {
        return;
    }

    PrintTree(node->right, depth + 1);

    for (int i = 0; i < depth; ++i) {
        cout << "\t";
    }
    cout << node->key << "(" << node->color << ")\n";

    PrintTree(node->left, depth + 1);

}