
#ifndef LAB_2_TTREE_H
#define LAB_2_TTREE_H

#include <string>

using namespace std;


struct TNode {
    uint64_t key;
    uint64_t pr;
    TNode *left;
    TNode *right;
    TNode *parent;


    TNode(uint64_t key, uint64_t pr);

};


class TTree {
public:

    TTree();

    TNode *CreateNode(uint64_t key, uint64_t pr);

    void RotateRight(TNode *node);

    void RotateLeft(TNode *node);

    void Insert(uint64_t key, uint64_t pr);

    void Delete(uint64_t key);

    void InsertMS(uint64_t key, uint64_t pr);

    void DeleteMS(uint64_t key);

    void PrintTree(TNode *node, uint64_t depth);

    void PrintTree();

    friend void split(TTree &t, TTree &t1, TTree &t2, int64_t key);

    friend void split(TNode *t, TNode *&t1, TNode *&t2, int64_t key);

    friend void merge(TTree &t, TTree &t1, TTree &t2);

    friend void merge(TNode *&t, TNode *t1, TNode *t2);

    /*void split( TTree &t1, TTree &t2, int64_t key);

    void split(TNode *t, TNode *&t1, TNode *&t2, int64_t key);*/

    //void merge( TTree )

private:

    TNode *root;


};


void split(TTree &t, TTree &t1, TTree &t2, int64_t key);

void split(TNode *t, TNode *&t1, TNode *&t2, int64_t key);

void merge(TTree &t, TTree &t1, TTree &t2);

void merge(TNode *&t, TNode *t1, TNode *t2);


#endif //LAB_2_TTREE_H
