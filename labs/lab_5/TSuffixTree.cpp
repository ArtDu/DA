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
    for (std::string::iterator i = text.begin(); i != position + 1; ++i) {

        ImprovedAlgo(i, position + 1);

    }
}

void TSuffixTree::ImprovedAlgo(std::string::iterator positionBegin, std::string::iterator positionEnd) {
    if (activeNode->parentNode == root || activeNode->parentNode->suffLink == nullptr) {
        activeNode = root;
        activeLen = 0;
    } else {

        //int64_t tmpLen = std::distance(positionBegin, activeNode->parentNode->end);
        activeLen--;
        positionBegin = positionBegin + activeLen;

        activeNode = activeNode->parentNode->suffLink;
        activeLen -= std::distance(activeNode->begin, activeNode->end);
    }

    NaiveAlgo(positionBegin, positionEnd);
}

void TSuffixTree::NaiveAlgo(std::string::iterator positionBegin,
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

    //find end
    while (true) {

        while (*i == *j && i != positionEnd && j != activeNode->end) {
            ++i; // in text j..i
            ++j; // in edge
        }

        if (*(i - 1) == *(j - 1) && i == positionEnd) {
            //suffix over
            //rule 3

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


            if (lastAdded != root ) {
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