
#ifndef LAB_2_TTREE_H
#define LAB_2_TTREE_H

#include <string>

#define RED "RED"
#define BLACK "BLACK"

using namespace std;


struct TNode {
    uint8_t height;
    string key;
    uint64_t val;
    TNode *left;
    TNode *right;
    TNode *parent;

    string color;

    TNode(string key, uint64_t val);

};

class TTree {
public:

    TTree();

    TNode *CreateNode(string key, uint64_t val);

    void Insert(string key, uint64_t val);

    void InsertFix(TNode *node);

    TNode* minElem(TNode* node);

    void DeleteNode(string key);
    void DeleteNodeFix(TNode* node);

    void Transplant(TNode* oldNode, TNode* newNode);

    TNode *rotateLeft(TNode *node);

    TNode *rotateRight(TNode *node);

    void PrintTree(TNode *node, uint64_t depth);

    void PrintTree();

    //void InsertFix(TNode* node);

    /*void Delete(string data);

    bool Search(string data);

    void PrintTree(TNode *node);


    ~TTree();*/

    TNode *root;

private:

    TNode *nil;


};


#endif //LAB_2_TTREE_H
