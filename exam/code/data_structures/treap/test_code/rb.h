#ifndef RBT_H
#define RBT_H

#include <cstring>
#include <iostream>
#include <fstream>

// #include <iomanip> // DELETE

using ulli = unsigned long long int;

const short LEAF = -1; //2 байта чтобы всегда хранить -1

class TRBtree {
public:
    class TNode {
    public:
        TNode() {}; //иначе работать не будет
        TNode(bool, ulli, char*); //проводит инициализацию
        ~TNode();

        TNode* parent;
        TNode* left;
        TNode* right;
        char* key;
        ulli value;
        bool color;
    };

    TRBtree();
    void Reborn();
    TNode* Search(const char*); //возвращает указатель на ноду

    void Insert(TNode&);
    void RBInsertFixup(TNode*);

    void LeftRotate(TNode&);
    void RightRotate(TNode&);

    void RBTransPlant(TNode*, TNode*);
    TNode* FindMin(TNode*);

    void RBDelete(TNode*);
    void RBDeleteFixup(TNode*);

    void Serialize(const char*);
    void Serialize(std::ofstream&, TNode*);// output
    void Deserialize(const char*);
    void Deserialize(std::ifstream&, TNode*&);// input

    void PrintTree(TNode *node, uint64_t depth);
    void PrintTree();

    static const bool BLACK = false; 
    static const bool RED = true;
private:
    TNode* root;
    TNode* nil;
};

#endif
