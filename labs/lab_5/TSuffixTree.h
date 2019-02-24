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

    TNode* suffLink;
    TNode* parentNode;

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
    TNode *lastAdded;
    std::string activeEdge;
    TNode *fullStringLeaf;


    void NodePrint(TNode *node, int dpth);

    void Build(int &position);

    void NaiveAlgo(int positionBegin, int positionEnd);
    void ImprovedAlgo(int positionBegin, int positionEnd);
};


#endif //LAB_5_TSUFFIXTREE_H
