#ifndef TSUFTREE_H
#define TSUFTREE_H

#include <iostream>
#include <vector>
#include <map>
#include <memory>
#include <string>
#include <algorithm>

class TNode
{
public:
    std::map<char, TNode *> to;
    std::string::iterator begin, end;
    TNode *sufflink;
    TNode(std::string::iterator begin, std::string::iterator end);
    ~TNode() {};
};

class TSuffixTree
{
public:
    TSuffixTree(std::string str);
    std::vector<int> Search(std::string pattern);
    void TreePrint();
    virtual ~TSuffixTree();
private:
    void NodePrint(TNode *node, int dpth);
    std::string text;
    TNode *root;
    TNode *lastAdded, *activeNode;
    int activeLen;
    std::string::iterator activeEdge; //active tag
    int remainder;    
    void RecursiveDestroy(TNode *node);
    bool CheckEdge(std::string::iterator position, TNode *node);
    void AddLetter(std::string::iterator add);
    void SearchLeafs(TNode *node, std::vector<int> &answer, int patternLocations);
};



#endif