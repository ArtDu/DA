
#include "TTree.h"
#include <ctime>
#include <cstring>

char NODE = 'y';
char END = 'n';



int TTree::Height(TNode* node) {
    return node ? node->height : 0;
}

int TTree::BFactor( TNode* node ) {
    return Height( node->rightPtr ) - Height( node->leftPtr );
}

void TTree::FixHeight( TNode* &node ) {
    int hl = Height( node->leftPtr );
    int hr = Height( node->rightPtr );
    node->height = ( hl > hr ? hl : hr ) + 1;
}

TNode* TTree::RotateRight( TNode* node ) {
    TNode* l = node->leftPtr;
    node->leftPtr = l->rightPtr;
    l->rightPtr = node;
    FixHeight( node );
    FixHeight( l );
    return l;
}

TNode* TTree::RotateLeft( TNode* node ) {
    TNode* r = node->rightPtr;
    node->rightPtr = r->leftPtr;
    r->leftPtr = node;
    FixHeight( node );
    FixHeight( r );
    return r;
}

TNode* TTree::Balance( TNode* node ) {
    FixHeight( node );
    if( BFactor( node ) == 2 )
    {
        if( BFactor( node->rightPtr ) < 0 )
            node->rightPtr = RotateRight(node->rightPtr);
        return RotateLeft(node);
    }
    if( BFactor( node ) == -2 )
    {
        if( BFactor( node->leftPtr ) > 0  )
            node->leftPtr = RotateLeft(node->leftPtr);
        return RotateRight(node);
    }
    return node;
}


TNode* TTree::FindMin( TNode* node ) {
    return node->leftPtr ? FindMin(node->leftPtr) : node;
}

TNode* TTree::RemoveMin( TNode* node ) {
    if( node->leftPtr == nullptr )
        return node->rightPtr;
    node->leftPtr = RemoveMin(node->leftPtr);
    return Balance(node);
}




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

void TTree::Insert( char key[], unsigned long long &val ) {
     

    Insert( key, val, root );

      

}

bool TTree::Insert( char key[], unsigned long long &val, TNode* &node ) {

    if( node == nullptr ) {
        

        node = (TNode *)malloc(sizeof(TNode));

        node->leftPtr = nullptr;
        node->rightPtr = nullptr;
        node->val = val;
        node->height = 1;
        strcpy(node->key, key);


        std::cout << "OK" << std::endl;

        return true;

        

    }

    if( strcmp(key, node->key) == 0 ) {
        std::cout << "Exist" << std::endl;
        key = nullptr;
        return false;
    }

    bool flaq = false;

    if( strcmp(key, node->key) < 0 ) {
        flaq = Insert( key, val, node->leftPtr );
    }
    else {
        flaq = Insert( key, val, node->rightPtr );
    }

    if ( flaq ) {
        node = Balance(node);
    }
    return flaq;
}

void TTree::Delete( char key[] ) {
    root = Delete(key, root);
}

TNode* TTree::Delete( char key[], TNode* &node ) {
    if( node == nullptr ) {
        std::cout << "NoSuchWord" << std::endl;
        return node;
    }

    if( strcmp(key, node->key) == 0 ) {
        std::cout << "OK" << std::endl;
        TNode* l = node->leftPtr;
        TNode* r = node->rightPtr;
        delete node;
        if( r == nullptr ) {
            return l;
        }
        TNode* min = FindMin( r ); //return min node-tree
        min->rightPtr = RemoveMin( r ); //return r tree without min node
        min->leftPtr = l;
        return Balance(min);
    }

    if( strcmp(key, node->key) < 0 ) {
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

    if( strcmp(key, node->key) == 0 ) {
        std::cout << "OK: " << node->val <<  std::endl;
        return;
    }

    if( strcmp(key, node->key) < 0 ) {
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
    std::cout << node->key << std::endl;

    Print(node->leftPtr, level + 1);

}

void TTree::Save( const char* fileName ) {
    FILE *fp;
    fp = fopen(fileName, "wb");
    if ( fp == nullptr ) {
        std::cout << "ERROR: Couldn't create file" << std::endl;
    }
    else {
        Save( fp, root );
        std::cout << "OK" << std::endl;
        fclose (fp);
    }

}

void TTree::Save( FILE* &file, TNode* &node ) {

    if ( node == nullptr ) {
        fwrite(&END, sizeof(char), 1, file);
        return;
    }

    fwrite(&NODE, sizeof(char), 1, file);


    size_t length = strlen(node->key);

    fwrite(&length, sizeof(length), 1, file);
    fwrite(node->key, sizeof(char), length, file);
    fwrite(&node->val, sizeof(node->val), 1, file);
    fwrite(&node->height, sizeof(node->height), 1, file);


    Save( file, node->leftPtr );
    Save( file, node->rightPtr );

}


void TTree::Load( const char* fileName ) {
    FILE *fp;
    fp = fopen( fileName, "rb" );
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

bool TTree::Load( FILE* &file, TNode* &node ) {


    char* key;
    unsigned long long val;
    int height;
    size_t length;
    char mark;
    fread(&mark, sizeof(char), 1, file);

    if( mark == NODE ) {


        fread(&length, sizeof(length), 1, file);
        key = (char *)malloc(sizeof(char) * (length + 1));
        fread(key, sizeof(char), length, file);
        key[length] = '\0';
        fread(&val, sizeof(val), 1, file);
        fread(&height, sizeof(height), 1, file);


        try {
            node = (TNode *)malloc(sizeof(TNode));
            node->leftPtr = nullptr;
            node->rightPtr = nullptr;
            node->val = val;
            node->height = 1;
            strcpy(node->key, key);

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
