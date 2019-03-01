#include "TSuffixTree.h"

TSuffixTree::TSuffixTree(std::string str) {
    text = str;
    root = new TNode(text.end(), text.end());
    lastAdded = root;
    activeNode = root;
    activeLen = 0;
    activeEdge = text.begin();
    remainder = 0;
    root->sufflink = root;

    for (std::string::iterator it = text.begin(); it != text.end(); ++it) {
        AddLetter(it);
        /*std:: cout << "phase: "<< *it << "\n";
        NodePrint(root, 0);
        std::cout << std::endl;*/
    }
}

TNode::TNode(std::string::iterator begin, std::string::iterator end) :
        begin(begin), end(end), sufflink(nullptr) {}



void TSuffixTree::AddLetter(std::string::iterator add) {
    lastAdded = root;
    ++remainder;
    while (remainder) {
        if (activeLen == 0) {
            activeEdge = add;
        }
        std::map<char, TNode *>::iterator it = activeNode->to.find(*activeEdge);
        TNode *next;
        if (it == activeNode->to.end()) {
            //RULE 2 no symbol from current node
            //add leaf
            TNode *leaf = new TNode(add, text.end());
            activeNode->to[*activeEdge] = leaf;
            if (lastAdded != root)
                //something was added last time
                lastAdded->sufflink = activeNode;
            lastAdded = activeNode;
        } else {
            //such path with this start symbol exists
            next = it->second; // node with this start symbol
            //can we go through entire edge?
            //reception №1 (jump with count)
            if (CheckEdge(add, next)) {
                continue;
            }

            if (*(next->begin + activeLen) == *add) {
                //RULE 3 already has that path
                //stop everything and proceed to next phase
                ++activeLen;
                if (lastAdded != root)
                    lastAdded->sufflink = activeNode;
                lastAdded = activeNode;
                break;
            }
            // RULE 2 with edge breaking
            TNode *split = new TNode(next->begin, next->begin + activeLen);
            TNode *leaf = new TNode(add, text.end());
            activeNode->to[*activeEdge] = split;

            split->to[*add] = leaf;
            next->begin += activeLen;
            split->to[*next->begin] = next;
            if (lastAdded != root)
                lastAdded->sufflink = split;
            lastAdded = split; //enqueue to add sufflink
        }
        --remainder;
        if (activeNode == root && activeLen) {
            --activeLen;
            activeEdge = add - remainder + 1;
        } else {
            //"xalpha" added need to add "alpha"
            //go to sufflink
            activeNode = activeNode->sufflink;
        }
    }
}

bool TSuffixTree::CheckEdge(std::string::iterator position, TNode *node) {
    int edgeLen;
    //look to original string
    if (position + 1 < node->end)
        //inside edge
        edgeLen = position + 1 - node->begin;
    else
        edgeLen = node->end - node->begin;
    //checking if we can go through entire edge
    if (activeLen >= edgeLen) {
        activeEdge += edgeLen;
        activeLen -= edgeLen;
        activeNode = node;
        //successfully passed edge
        return true;
    }
    //need to apply some rule
    //which one checked in main function
    return false;
}


void TSuffixTree::SearchLeafs(TNode *node, std::vector<int> &answer, int patternLocation) {
    if (node->end == text.end()) {
        //leaf found
        answer.push_back(text.size() - patternLocation + 1);
    } else {
        TNode *child;
        int addDepth;
        //run through all eddges from this node
        //and run dfs at them
        for (auto it = node->to.begin(); it != node->to.end(); ++it) {
            child = it->second;
            addDepth = child->end - child->begin; //edge length
            SearchLeafs(child, answer, patternLocation + addDepth);
        }
    }
}

std::vector<int> TSuffixTree::Search(std::string pattern) {
    std::vector<int> answer;
    std::string::iterator patPos = pattern.begin();
    int patternLocation = 0; //symbols passed at edges
    TNode *node = root; ///starts from root
    if (pattern.size() > text.size()) {
        //pattern larger than text
        return answer;
    }
    //search for all pattern
    for ( patPos = pattern.begin(); patPos != pattern.end(); ++patPos) {
        auto pathTo = node->to.find(*patPos);
        if (pathTo == node->to.end()) {
            //mismatch
            //no such symbol from node
            return answer;
        }
        node = pathTo->second;
        patternLocation += node->end - node->begin;
        for (std::string::iterator edgePos = node->begin;
             edgePos != node->end && patPos != pattern.end(); ++edgePos, patPos++) {
            if (*edgePos != *patPos) {
                //mismatch inside edge
                return answer;
            }
        }
        if (patPos == pattern.end())
            //exactly at node
            break;
        --patPos;
    }
    //node found run dfs for it
    SearchLeafs(node, answer, patternLocation);
    //sort pattern indexes 
    std::sort(answer.begin(), answer.end());
    return answer;
}

TSuffixTree::~TSuffixTree() {
    RecursiveDestroy(root);
}

void TSuffixTree::RecursiveDestroy(TNode *node) {
    for (auto it = node->to.begin(); it != node->to.end(); ++it)
        RecursiveDestroy(it->second);
    delete node;
}


void TSuffixTree::NodePrint(TNode *node, int dpth)
{
    for (int i = 0; i < dpth; ++i) {
        putchar('\t');
    }


    for (std::string::iterator str = node->begin; str != node->end; ++str) {
        std::cout << *str;
    }
    std::cout <<  std::endl;
    //std:: cout << " (" << node << ") -> (" << node->sufflink << ")" << std::endl;

    for (std::map<char, TNode *>::iterator it = node->to.begin(); it != node->to.end(); ++it) {
        NodePrint(it->second, dpth + 1);
    }
}




void TSuffixTree::TreePrint()
{
    NodePrint(root, 0);
}

