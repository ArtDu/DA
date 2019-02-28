//
// Created by art on 18.02.19.
//

#include <algorithm>
#include "TSuffixTree.h"


TNode::TNode(std::string::iterator begin, std::string::iterator end) :
        begin(begin), end(end), suffLink(nullptr) {}

TSuffixTree::TSuffixTree(std::string str) {

    text = str;
    root = new TNode(str.end(), str.end());
    lastAdded = root;
    root->parentNode = root;

    //add fst leaf
    lastLeaf = new TNode(text.begin(), text.end());
    lastLeaf->parentNode = root;
    root->to[*(lastLeaf->begin)] = lastLeaf;
    activeNode = lastLeaf;
    skipByRule1 = 1;


    for (std::string::iterator it = text.begin(); it != text.end(); ++it) {
        //add it to end of all suffixes
        Build(it);

        /*std::cout << "phase: " << *it << "\n";
        NodePrint(root, 0);
        std::cout << std::endl;*/

    }
}

void TSuffixTree::Build(std::string::iterator &position) {
    lastAdded = root;

    lenOfLastAddedEdge = std::distance(lastLeaf->begin, position + 1);
    activeLen = std::distance(text.begin() + skipByRule1 - 1, position + 1) - lenOfLastAddedEdge;
    activeNode = lastLeaf;

    completePhase = false;
    for (std::string::iterator i = text.begin() + skipByRule1; i != position + 1; ++i) {

        ImprovedAlgo(i, position + 1);

        if (completePhase) {
            break;
        }
    }

}

void TSuffixTree::ImprovedAlgo(std::string::iterator positionBegin, std::string::iterator positionEnd) {
    if (activeNode->parentNode == root || activeNode->parentNode->suffLink == nullptr) {
        //start from root
        activeLen--;
        lenOfLastAddedEdge += activeLen;

        activeNode = root;
        activeLen = 0;
    } else {
        //start from node
        //"xalpha" added need to add "alpha"

        activeLen--;
        positionBegin = positionBegin + activeLen;
        activeNode = activeNode->parentNode->suffLink;

        activeLen -= std::distance(activeNode->begin, activeNode->end); //cause this edge's len add when downhill
    }

    NaiveAlgo(positionBegin, positionEnd);
}

void TSuffixTree::NaiveAlgo(std::string::iterator positionBegin, //suffix[posBeg, posEnd - 1]
                            std::string::iterator positionEnd) {

    auto it = activeNode->to.find(*positionBegin);
    if (it != activeNode->to.end()) {
        activeLen += std::distance(activeNode->begin, activeNode->end);
        activeNode = it->second;
    } else {
        //add node to root
        //rule 2(a)
        TNode *leaf = new TNode(positionBegin, text.end());
        skipByRule1++;
        leaf->parentNode = activeNode;
        activeNode->to[*(leaf->begin)] = leaf;


        activeLen += std::distance(activeNode->begin, activeNode->end);
        activeNode = leaf;
        lastLeaf = leaf;

        return;
    }

    std::string::iterator i = positionBegin, // in text j..i
            j = activeNode->begin;         // in edge

    int64_t lenG = lenOfLastAddedEdge;
    //find end
    while (true) {

        //skip/count
        int64_t lenOfEdge = std::distance(activeNode->begin, activeNode->end);
        if (lenOfEdge < lenG) { //skip edge
            j = activeNode->end;
            i = i + lenOfEdge;
            lenG = lenG - lenOfEdge;

        } else {

            i = i + lenG;
            j = j + lenG;
            if (*(j - 1) != *(positionEnd - 1)) {
                i--;
                j--;
            }
            lenG = 0;
            lenOfLastAddedEdge = 0;
        }


        if (*(i - 1) == *(j - 1) && i == positionEnd) {
            //suffix over
            //rule 3
            lenOfLastAddedEdge = std::distance(activeNode->begin, j);
            completePhase = true;
            break;
        }

        if (j == activeNode->end) {
            //edge over
            //suffix ain't over

            it = activeNode->to.find(*i);

            if (it != activeNode->to.end()) {
                // continuation path exists
                // downhill
                activeLen += std::distance(activeNode->begin, activeNode->end);
                activeNode = it->second;
                j = activeNode->begin;
                continue;
            } else {
                // split
                // new edge with text[i+1]
                // rule 2(a)
                TNode *tmpNode = new TNode(i, text.end());
                skipByRule1++;
                tmpNode->parentNode = activeNode;
                activeNode->to[*(tmpNode->begin)] = tmpNode;
                lastLeaf = tmpNode;


                activeLen += std::distance(activeNode->begin, activeNode->end);
                activeNode = tmpNode;
                lenOfLastAddedEdge = std::distance(activeNode->begin, i + 1);
            }
            break;
        } else {
            // edge ain't over

            //split
            //new edge with text[i ... positionEnd ]
            //rule 2(b)

            TNode *rightNode = new TNode(i, text.end());
            skipByRule1++;
            TNode *newNode = new TNode(activeNode->begin, j);

            activeNode->begin = j;
            activeNode->parentNode->to[*(newNode->begin)] = newNode;

            rightNode->parentNode = newNode;

            newNode->to[*(rightNode->begin)] = rightNode;
            newNode->to[*(activeNode->begin)] = activeNode;
            newNode->parentNode = activeNode->parentNode;

            activeNode->parentNode = newNode;

            activeLen += std::distance(newNode->begin, newNode->end);
            activeNode = rightNode;
            lastLeaf = rightNode;
            lenOfLastAddedEdge = std::distance(activeNode->begin, i + 1);

            if (lastAdded != root) {
                lastAdded->suffLink = newNode;
            }
            lastAdded = newNode;

            break;

        }

    }
}

void TSuffixTree::NodePrint(TNode *node, int dpth) {
    for (int i = 0; i < dpth; ++i) {
        putchar('\t');
    }

    for (std::string::iterator str = node->begin; str != node->end; ++str) {
        std::cout << *str;
    }
    std::cout << std::endl;
    //std::cout << " (" << node << ") -> (" << node->suffLink << ")" << std::endl;

    for (std::map<char, TNode *>::iterator it = node->to.begin(); it != node->to.end(); ++it) {
        NodePrint(it->second, dpth + 1);
    }
}

void TSuffixTree::TreePrint() {
    NodePrint(root, 0);
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
