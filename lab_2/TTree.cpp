
#include "TTree.h"

TTree::TTree() : root(nullptr) {}

TTree::~TTree() {
    DeleteTree(root);
}

void TTree::DeleteTree() {
    DeleteTree(root);
    root = nullptr;
}

void TTree::DeleteTree(TNode* &node) {
    if( node == nullptr ) {
        return;
    }

    DeleteTree( node->leftPtr );
    DeleteTree( node->rightPtr );

    delete node;
}

void TTree::Insert( char* key, unsigned long long &val ) {
    root = Insert( key, val, root );
}

TNode* TTree::Insert( char* key, unsigned long long &val, TNode* &node ) {
    if( node == nullptr ) {
        std::cout << "OK" << std::endl;
        TNode* tmp = new TNode( key, val, 1 );
        return tmp;
    }

    if( strcmp(key, node->nodeData.key) == 0 ) {
        std::cout << "Exist" << std::endl;
        return node;
    }

    if( strcmp(key, node->nodeData.key) < 0 ) {
        node->leftPtr = Insert( key, val, node->leftPtr );
    }
    else {
        node->rightPtr = Insert( key, val, node->rightPtr );
    }

    return Balance(node);

}

void TTree::Delete( char *key ) {
    root = Delete(key, root);
}

TNode* TTree::Delete( char *key, TNode *&node ) {
    if( node == nullptr ) {
        std::cout << "NoSuchWord" << std::endl;
        return node;
    }

    if( strcmp(key, node->nodeData.key) == 0 ) {
        std::cout << "OK" << std::endl;
        TNode* l = node->leftPtr;
        TNode* r = node->rightPtr;
        delete node;
        if( r == nullptr ) {
            return l;
        }
        TNode* min = r->FindMin();
        min->rightPtr = r->RemoveMin();
        min->leftPtr = l;
        return Balance(min);
    }

    if( strcmp(key, node->nodeData.key) < 0 ) {
        node->leftPtr = Delete( key, node->leftPtr );
    }
    else {
        node->rightPtr = Delete( key, node->rightPtr );
    }

    return Balance(node);


}


void TTree::Search(char *key) {
    Search( key, root);
}

void TTree::Search(char *key, TNode *node) {
    if( node == nullptr ) {
        std::cout << "NoSuchWord" << std::endl;
        return;
    }

    if( strcmp(key, node->nodeData.key) == 0 ) {
        std::cout << "OK: " << node->nodeData.val <<  std::endl;
        return;
    }

    if( strcmp(key, node->nodeData.key) < 0 ) {
        Search( key, node->leftPtr );
    }
    else {
        Search( key, node->rightPtr );
    }
}

void TTree::Print() {
    Print(root, 0);
}

void TTree::Print(TNode *node, const int level) {

    if ( node == nullptr ) {
        return;
    }

    Print(node->rightPtr, level + 1);

    for (int i = 0; i < level; ++i) {
        std::cout << "\t";
    }
    std::cout << node->nodeData.key << std::endl;

    Print(node->leftPtr, level + 1);

}

void TTree::Save(FILE *file) {
    Save( file, root );
}

void TTree::Save(FILE *file, TNode *node) {
    if ( node == nullptr ) {
        return;
    }

    fwrite(&(node->nodeData) , sizeof(TData), 1, file);

    Save( file, node->leftPtr );
    Save( file, node->rightPtr );

}

void TTree::Load(FILE *file) {
    TData tmp;
    while ( fread( &tmp, sizeof(TData), 1, file ) == 1 ) {

        root = Load( tmp.key, tmp.val, root );
    }
}

TNode* TTree::Load( char* key, unsigned long long &val, TNode* node ) {
    if( node == nullptr ) {

        TNode* tmp = new TNode( key, val, 1 );
        return tmp;
    }

    if( strcmp(key, node->nodeData.key) == 0 ) {
        return node;
    }

    if( strcmp(key, node->nodeData.key) < 0 ) {
        node->leftPtr = Load( key, val, node->leftPtr );
    }
    else {
        node->rightPtr = Load( key, val, node->rightPtr );
    }

    return Balance(node);
}