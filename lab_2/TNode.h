#ifndef LAB_2_TNODE_H
#define LAB_2_TNODE_H

#include <cstring>

struct TNode {
    TNode() : leftPtr(nullptr), rightPtr(nullptr) {

        val = 0;
        height = 0;
    }
    TNode( char* key, unsigned long long val, int height ) {
        this->val = val;
        this->height = height;
        strcpy(this->key,key);
        leftPtr = nullptr;
        rightPtr = nullptr;
    }
    TNode* leftPtr;
    TNode* rightPtr;
    char key[257];
    unsigned long long val;
    int height;
};


#endif //LAB_2_TNODE_H
