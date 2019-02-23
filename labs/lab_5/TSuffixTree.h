//
// Created by art on 18.02.19.
//

#ifndef LAB_5_TSUFFIXTREE_H
#define LAB_5_TSUFFIXTREE_H

#include <iostream>
#include <map>
#include <string>


class TNode {

public:
    std::map<char, TNode *> to;
    std::string tag;

    TNode(std::string marker);

    ~TNode() {};
};


class TSuffixTree {
public:
    TSuffixTree(std::string str);

    void TreePrint();

private:
    std::string text;
    TNode *root;
    TNode *activeNode;
    TNode *parentNode;


    void NodePrint(TNode *node, int dpth);

    void Build(int &position);

    void FindEnd(int positionBegin, int positionEnd);
};


#endif //LAB_5_TSUFFIXTREE_H
