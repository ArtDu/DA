
#include "TTree.h"

char NODE = 'y';
char END = 'n';


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

void TTree::Insert( char* &key, unsigned long long &val ) {
    Insert( key, val, root );
}

void TTree::Insert( char* &key, unsigned long long &val, TNode* &node ) {
    if( node == nullptr ) {
        
        try {
            node = new TNode( key, val, 1 );
            std::cout << "OK" << std::endl;
            return;
        } catch ( const std::bad_alloc & ) {
            std::cout << "ERROR: not enough memory" << std::endl;
            node =  nullptr;
            return;
        }
    }

    if( strcmp(key, node->nodeData.key) == 0 ) {
        std::cout << "Exist" << std::endl;
        delete key;
        key = nullptr;
        return;
    }

    if( strcmp(key, node->nodeData.key) < 0 ) {
        Insert( key, val, node->leftPtr );
    }
    else {
        Insert( key, val, node->rightPtr );
    }

    node = Balance(node);

}

void TTree::Delete( char key[] ) {
    root = Delete(key, root);
}

TNode* TTree::Delete( char key[], TNode* &node ) {
    if( node == nullptr ) {
        std::cout << "NoSuchWord" << std::endl;
        return node;
    }

    if( strcmp(key, node->nodeData.key) == 0 ) {
        std::cout << "OK" << std::endl;
        TNode* l = node->leftPtr;
        TNode* r = node->rightPtr;
        delete node->nodeData.key;
        delete node;
        if( r == nullptr ) {
            return l;
        }
        TNode* min = r->FindMin(); //return min node-tree
        min->rightPtr = r->RemoveMin(); //return r tree without min node
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

void TTree::Save( const char* fileName ) {
    FILE *fp;
    fp = fopen(fileName, "w");
    if ( fp == NULL ) {
        std::cout << "ERROR: Couldn't create file" << std::endl;
    }
    else {
        Save( fp, root );
        std::cout << "OK" << std::endl;
        fclose (fp);
    }

}

void TTree::Save( FILE *file, TNode* &node ) {
    if ( node == nullptr ) {
        fwrite(&END, sizeof(char), 1, file);
        return;
    }

    fwrite(&NODE, sizeof(char), 1, file);
    fwrite(&(node->nodeData) , sizeof(TData), 1, file);

    Save( file, node->leftPtr );
    Save( file, node->rightPtr );

}


void TTree::Load( const char* fileName ) {
    FILE *fp;
    fp = fopen( fileName, "r" );
    if ( fp == nullptr ) {
        std::cout << "ERROR: Couldn't open file" << std::endl;
        return;
    }

    if( root ) {
        DeleteTree( root );
        root = nullptr;
    }




    if ( this->Load( fp, root ) ) {
        //std::cout << "ERROR: Couldn't load file" << std::endl;
    }
    else {
        std::cout << "OK" << std::endl;
    }

    fclose (fp);
}

bool TTree::Load( FILE *file, TNode* &node ) {

    TData tmpData;
    char mark;
    fread(&mark, sizeof(char), 1, file);

    if( mark == NODE ) {

        fread( &tmpData, sizeof(tmpData), 1, file );
        try {
            node = new TNode( tmpData.key, tmpData.val, tmpData.height );

        } catch ( const std::bad_alloc & ) {
            std::cout << "ERROR: not enough memory" << std::endl;
            return true;
        }
        
    }
    else {
        return false;
    }

    if( Load( file, node->leftPtr ) ) {
        return true;
    }

    if( Load( file, node->rightPtr ) ) {
        return true;
    }

    return false;

}