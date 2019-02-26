//
// Created by art on 18.02.19.
//

#include "TSuffixTree.h"


TNode::TNode(std::string::iterator begin, std::string::iterator end) :
        begin(begin), end(end), suffLink(nullptr) {}

TSuffixTree::TSuffixTree(std::string str) {

    text = str;
    root = new TNode(str.end(), str.end());
    lastAdded = root;
    activeNode = root;
    root->parentNode = root;

    firstLeaf = new TNode(text.begin(), text.begin());
    firstLeaf->parentNode = root;
    root->to[*(firstLeaf->begin)] = firstLeaf;
    activeNode = firstLeaf;


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
    activeNode = firstLeaf;
    firstLeaf->end++;
    activeLen = std::distance(text.begin(), firstLeaf->end) - std::distance(firstLeaf->begin, firstLeaf->end);
    lenOfLastAddedEdge =  std::distance(firstLeaf->begin, firstLeaf->end);

    for (std::string::iterator i = text.begin() + 1; i != position + 1; ++i) {

        ImprovedAlgo(i, position + 1);
        /*std::cout << "extension: " << *i << "\n";
        NodePrint(root, 0);
        std::cout << std::endl;*/
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
        //lenOfLastAddedEdge += activeLen;
        activeLen--;
        positionBegin = positionBegin + activeLen;

        activeNode = activeNode->parentNode->suffLink;

        activeLen -= std::distance(activeNode->begin, activeNode->end);
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
        TNode *leaf = new TNode(positionBegin, positionEnd);
        leaf->parentNode = activeNode;
        activeNode->to[*(leaf->begin)] = leaf;


        activeLen += std::distance(activeNode->begin, activeNode->end);
        activeNode = leaf;

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
            if (lenG == 0) {
                lenOfLastAddedEdge = std::distance(activeNode->begin, j + 1);
                //activeLen = activeLen - (std::distance(activeNode->begin, activeNode->end) - std::distance(activeNode->begin, j+1));
                break;
            }

            i = i + lenG;
            j = j + lenG;
            if (*(j - 1) != *(positionEnd - 1)) {
                i--;
                j--;
            }
            lenG = 0;
        }

        /*while (*i == *j && i != positionEnd && j != activeNode->end) {
            ++i; // in text j..i
            ++j; // in edge
        }*/

        if (*i == '\0') {
            i--;
            j--;
        }


        if (*(i - 1) == *(j - 1) && i == positionEnd) {
            //suffix over
            //rule 3
            lenOfLastAddedEdge = std::distance(activeNode->begin, j);
            //activeLen = activeLen - (std::distance(activeNode->begin, activeNode->end) - std::distance(activeNode->begin, j));
            break;
        }

        if (j == activeNode->end) {
            //edge over
            //suffix ain't over

            it = activeNode->to.find(*i);

            if (activeNode->to.empty()) {
                // it's leaf
                // add to end (rule 1)
                activeNode->end = positionEnd;
                lenOfLastAddedEdge = std::distance(activeNode->begin, activeNode->end);
            } else if (it != activeNode->to.end()) {
                // continuation path exists
                //downhill
                activeLen += std::distance(activeNode->begin, activeNode->end);
                activeNode = it->second;
                j = activeNode->begin;
                continue;
            } else {
                //split
                //new edge with text[i+1]
                //rule 2(a)
                TNode *tmpNode = new TNode(i, positionEnd);
                tmpNode->parentNode = activeNode;
                activeNode->to[*(tmpNode->begin)] = tmpNode;


                activeLen += std::distance(activeNode->begin, activeNode->end);
                activeNode = tmpNode;
                lenOfLastAddedEdge = std::distance(activeNode->begin, activeNode->end);
            }
            break;
        } else {
            // edge ain't over



            //split
            //new edge with text[i ... positionEnd ]
            //rule 2(b)

            TNode *rightNode = new TNode(i, positionEnd);
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
            lenOfLastAddedEdge = std::distance(activeNode->begin, activeNode->end);

            if (lastAdded != root) {
                lastAdded->suffLink = newNode;
            }
            lastAdded = newNode;

            break;

        }

    }
}


//fefbeafbdebcfeccabdecdeaebafbebdecfdbbdcbefdaffbdedfafefaabe

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