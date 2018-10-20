
#ifndef LAB_2_TTREE_H
#define LAB_2_TTREE_H
#include <iostream>
#include <cstddef>
#include "TNode.h"

class TTree {
public:
    TTree();
    ~TTree();
    void DeleteTree();
    void DeleteTree( TNode* &node );
    void Insert( char* key, unsigned long long &val );
    TNode* Insert( char* key, unsigned long long &val, TNode* &node );
    void Delete( char* key );
    TNode* Delete( char* key, TNode* &node );

    /*void Save( FILE* file );
    void Save( FILE* file, TNode* node );
    void Print();
    void Print( TNode* node, const int level );*/
    void Search( char* key);
    void Search( char* key, TNode* node);
private:
    TNode* root;
};


#endif //LAB_2_TTREE_H
