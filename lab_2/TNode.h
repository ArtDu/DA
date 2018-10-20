//
// Created by art on 18.10.18.
//

#ifndef LAB_2_TNODE_H
#define LAB_2_TNODE_H

#include <cstring>

class TTree;

typedef struct TTmpData {
    char key[257];
    unsigned long long val;
    int height;
    TTmpData() {

        val = 0;
        height = 0;
    }
    TTmpData& operator= ( TTmpData& right ) {
        val = right.val;
        strcpy(key,right.key);
        height = right.height;
        return right;
    }
} TData;



class TNode {

    friend class TTree;
    friend int Height( TNode* node );
    friend TNode* RotateRight( TNode* node );
    friend TNode* RotateLeft( TNode* node );
    friend TNode* RemoveMin( TNode* node );
    friend TNode* Balance( TNode* node );

public:
    TNode();
    TNode( const TData& data );
    TNode& operator= (TNode& right);
    TNode* FindMin();
    ~TNode();
    int BFactor();
    void FixHeight();


private:
    TNode* leftPtr;
    TNode* rightPtr;
    TData nodeData;
};


#endif //LAB_2_TNODE_H
