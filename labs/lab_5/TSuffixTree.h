//
// Created by art on 18.02.19.
//

#ifndef LAB_5_TSUFFIXTREE_H
#define LAB_5_TSUFFIXTREE_H

#include <iostream>
#include <map>
#include <string>
#include <vector>


class TNode {

public:
    std::map<char, TNode *> to;


    std::string::iterator begin, end; //string in edge (text[ begin, end - 1 ])

    TNode *suffLink;
    TNode *parentNode; // for rule 2b(split)

    TNode(std::string::iterator begin, std::string::iterator end);

    ~TNode() {};
};


class TSuffixTree {
public:
    TSuffixTree(std::string str);

    void TreePrint();

    std::vector<int> Search(std::string pattern);
    virtual ~TSuffixTree();

private:
    std::string text;
    TNode *root;
    TNode *activeNode;
    TNode *lastAdded;
    TNode *lastLeaf;

    bool completePhase;

    int64_t activeLen; //last added suffix's len from begin to edge before leaf
    int64_t lenOfLastAddedEdge; //len of full last added
    int64_t skipByRule1;


    void NodePrint(TNode *node, int dpth);

    void Build(std::string::iterator &position);

    void NaiveAlgo(std::string::iterator positionBegin, std::string::iterator positionEnd);

    void ImprovedAlgo(std::string::iterator positionBegin, std::string::iterator positionEnd);

    void RecursiveDestroy(TNode *node);

    void SearchLeafs(TNode *node, std::vector<int> &answer, int patternLocations);
};


#endif //LAB_5_TSUFFIXTREE_H
