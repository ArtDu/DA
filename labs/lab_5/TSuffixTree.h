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


    std::string::iterator begin, end;

    TNode* suffLink;
    TNode* parentNode;

    TNode(std::string::iterator begin, std::string::iterator end);

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


    void NodePrint(TNode *node, int dpth);

    void Build(std::string::iterator& position);

    void NaiveAlgo(std::string::iterator positionBegin, std::string::iterator positionEnd);
    void ImprovedAlgo(std::string::iterator positionBegin, std::string::iterator positionEnd);
};


#endif //LAB_5_TSUFFIXTREE_H
