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
    TTmpData( char* &key, unsigned long long &val, int &height ) {
        this->val = val;
        this->height = height;
        strcpy(this->key, key);
    }
    TTmpData( const TTmpData &data ) {
        val = data.val;
        strcpy(key,data.key);
        height = data.height;
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

    friend TNode* Balance( TNode* node );

public:
    TNode();
    TNode( const TData& data );
    TNode( char* &key, unsigned long long &val, int &&height );
    TNode( char* &key, unsigned long long &val, int  &height );
    TNode& operator= (TNode& right);
    TNode* FindMin();
    TNode* FindMin( TNode* node );
    TNode* RemoveMin();
    TNode* RemoveMin( TNode* node );
    ~TNode() {}
    int BFactor();
    void FixHeight();


private:
    TNode* leftPtr;
    TNode* rightPtr;
    TData nodeData;
};


#endif //LAB_2_TNODE_H
