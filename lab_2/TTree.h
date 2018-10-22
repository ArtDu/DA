
#ifndef LAB_2_TTREE_H
#define LAB_2_TTREE_H
#include <iostream>
#include <cstddef>
#include "TNode.h"

class TTree {
    int Height( TNode* node );
    TNode* RotateRight( TNode* node );
    TNode* RotateLeft( TNode* node );
    TNode* Balance( TNode* node );
public:
    TTree();
    ~TTree();
    void DeleteTree();
    void DeleteTree( TNode* &node );
    void Insert( char key[], unsigned long long &val );
    bool Insert( char key[], unsigned long long &val, TNode* &node );
    void Delete( char key[] );
    TNode* Delete( char key[], TNode* &node );


    TNode* FindMin();
    TNode* FindMin( TNode* node );
    TNode* RemoveMin();
    TNode* RemoveMin( TNode* node );
    int BFactor( TNode* node );
    void FixHeight( TNode* &node );

    void Save( const char* fileName );
    void Save( FILE* &file, TNode* &node );
    void Load( const char* fileName );
    bool Load( FILE* &file, TNode* &node );
    void Print();
    void Print( TNode* node, const int level );
    void Search( char* key );
    void Search( char* key, TNode* node );
private:
    TNode* root;
};


#endif //LAB_2_TTREE_H
