
#include "TNode.h"

TNode::TNode() : leftPtr(nullptr), rightPtr(nullptr) {}

TNode::TNode(const TData &data) : nodeData(data) {}

TNode::TNode( char* key, unsigned long long &val, int &&height )
    : leftPtr(nullptr), rightPtr(nullptr), nodeData(key, val, height) {}

TNode::TNode( char* key, unsigned long long &val, int  &height )
        : leftPtr(nullptr), rightPtr(nullptr), nodeData(key, val, height) {}

TNode& TNode::operator=(TNode &right) {
    this->nodeData = right.nodeData;
    this->rightPtr = right.rightPtr;
    this->leftPtr = right.leftPtr;
    return *this;
}

int Height(TNode* node) {
    return node ? node->nodeData.height : 0;
}

int TNode::BFactor() {
    return Height( this->rightPtr ) - Height( this->leftPtr );
}

void TNode::FixHeight() {
    int hl = Height( this->leftPtr );
    int hr = Height( this->rightPtr );
    this->nodeData.height = ( hl > hr ? hl : hr ) + 1;
}

TNode* RotateRight( TNode* node ) {
    TNode* l = node->leftPtr;
    node->leftPtr = l->rightPtr;
    l->rightPtr = node;
    node->FixHeight();
    l->FixHeight();
    return l;
}

TNode* RotateLeft( TNode* node ) {
    TNode* r = node->rightPtr;
    node->rightPtr = r->leftPtr;
    r->leftPtr = node;
    node->FixHeight();
    r->FixHeight();
    return r;
}

TNode* Balance( TNode* node ) {
    node->FixHeight();
    if( node->BFactor() == 2 )
    {
        if( node->rightPtr->BFactor() < 0 )
            node->rightPtr = RotateRight(node->rightPtr);
        return RotateLeft(node);
    }
    if( node->BFactor() == -2 )
    {
        if( node->leftPtr->BFactor() > 0  )
            node->leftPtr = RotateLeft(node->leftPtr);
        return RotateRight(node);
    }
    return node;
}

TNode* TNode::FindMin() {
    return this->leftPtr ? FindMin(this->leftPtr) : this;
}

TNode* TNode::FindMin( TNode* node ) {
    return node->leftPtr ? FindMin(node->leftPtr) : node;
}

TNode* TNode::RemoveMin( TNode* node ) {
    if( node->leftPtr == nullptr )
        return node->rightPtr;
    node->leftPtr = RemoveMin(node->leftPtr);
    return Balance(node);
}

TNode* TNode::RemoveMin() {
    if( this->leftPtr == nullptr )
        return this->rightPtr;
    this->leftPtr = RemoveMin(this->leftPtr);
    return Balance(this);
}
