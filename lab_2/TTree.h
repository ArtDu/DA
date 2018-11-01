
#ifndef LAB_2_TTREE_H
#define LAB_2_TTREE_H

#include <stdint.h>
#include <cstring>
#include <cstdio>

struct TData {
    char *key;
    unsigned long long value;
};

struct TNode {
    uint8_t height;
    TData *data;
    TNode *left;
    TNode *right;
};

class TTree {
public:

    TTree();
    void Insert(TData data);
    void Delete(TData data);
    bool Search(TData &data);
    bool Save(const char* filename);
    bool Load(const char* filename);
    void Erase();
    void PrintTree(TNode *node);

    ~TTree();

private:

    TNode *root;
    TNode *CreateNode(TData data);
    void DeleteNode(TNode *&node);
    TNode *InsertSub(TNode *node, TData data);
    TNode *Balance(TNode *node);
    TNode *RotateLeft(TNode *q);
    TNode *RotateRight(TNode *q);
    void SetHeight(TNode *node);
    TNode *Min(TNode *node);
    TNode *DeleteSub(TNode *node, TData data);
    TNode *DelMin(TNode *node);
    int BalFact(TNode *node);
    int GetHeight(TNode *node);
    bool SearchSub(TNode *&node, TData &data);
    bool SaveSub(FILE *f, TNode *node);
    bool LoadSub(FILE *f, TNode *&node);

};


#endif //LAB_2_TTREE_H
