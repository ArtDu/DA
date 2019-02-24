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



    //int i = 0;
    for (std::string::iterator it = text.begin(); it != text.end(); ++it) {
        //add to end to all suffix
        //std::cout << i << "\n";
        //++i;
        Build(it);

        /*std:: cout << "phase: "<< *it << "\n";
        NodePrint(root, 0);
        std::cout << std::endl;*/

    }
}

void TSuffixTree::Build(std::string::iterator &position) {
    //int j = 0;
    for (std::string::iterator i = text.begin(); i != position + 1; ++i) {

        //std::cout << j << "\n";
        //j++;

        ImprovedAlgo(i, position);
        //NaiveAlgo(i, position);
    }
}

void TSuffixTree::ImprovedAlgo(std::string::iterator positionBegin, std::string::iterator positionEnd) {
    if (activeNode->parentNode == root || activeNode->parentNode->suffLink == nullptr || true) {
        activeNode = root;
    } else {

        //positionBegin = positionBegin + (positionEnd - positionBegin) - (activeNode->end - 1) ;

        activeNode = activeNode->parentNode->suffLink;
    }

    NaiveAlgo(positionBegin, positionEnd);
}

void TSuffixTree::NaiveAlgo(std::string::iterator positionBegin,
        std::string::iterator positionEnd) {

    auto it = activeNode->to.find(*positionBegin);
    if (it != activeNode->to.end()) {
        activeNode = it->second;
    } else {
        //add node to root
        //rule 2(a)
        //std::string tmpString = text.substr(positionBegin, positionEnd + 1 - positionBegin);
        TNode *leaf = new TNode(positionBegin, positionEnd + 1);
        leaf->parentNode = activeNode;
        activeNode->to[*(leaf->begin)] = leaf;
        activeNode = leaf;
        return;
    }

    std::string::iterator i = positionBegin, // in text j..i
            j = activeNode->begin;         // in edge

    //find end
    //int kek = 0;
    while (true) {

        //std::cout << kek << "\n";
        //kek++;

        if (i == positionEnd && *i == *j && j != activeNode->end) {
            //suffix[j..i+1] over and edge ain't over
            //rule 3
            break;
        }


        while (*i == *j && i != positionEnd + 1 && j != activeNode->end) {
            ++i; // in text j..i
            ++j; // in edge
        }
        if (j == activeNode->end) {
            //edge over
            if (i == positionEnd) {
                //suffix[j..i] over
                auto it = activeNode->to.find(*i);
                if (it != activeNode->to.end()) {
                    // continuation path exists
                    // => suffix[i+1] == newEdge[0]
                    //rule 3

                    break;
                }

                if (activeNode->to.empty()) {
                    // it's leaf
                    // add to end (rule 1)
                    activeNode->end++;
                } else {
                    //split
                    //new edge with text[i+1]
                    //rule 2(a)
                    TNode *tmpNode = new TNode(i, positionEnd + 1);
                    tmpNode->parentNode = activeNode;
                    activeNode->to[*(tmpNode->begin)] = tmpNode;

                    if (lastAdded != root && lastAdded->begin + 1 == activeNode->begin) {
                        lastAdded->suffLink = activeNode;
                    }
                    lastAdded = activeNode;

                    activeNode = tmpNode;
                }
                break;
            } else {
                //suffix[j..i] ain't over
                //downhill

                auto it = activeNode->to.find(*i);
                if (it != activeNode->to.end()) {
                    // continuation path exists
                    activeNode = it->second;
                    j = activeNode->begin;
                    continue;
                }
                break;
            }
        } else {
            // edge ain't over
            if (*(i-1) == *(j-1) && i == positionEnd + 1) {
                //suffix[j..i+1] over
                //rule 3
                break;
            }

            //split
            //new edge with text[i+1]
            //rule 2(b)

            //std::string right = text.substr(i, positionEnd + 1 - i);
            //std::string newNodeStr = activeNode->tag.substr(0, j);
            TNode *rightNode = new TNode(i, positionEnd + 1);
            TNode *newNode = new TNode(activeNode->begin, j);

            activeNode->begin = j;
            activeNode->parentNode->to[*(newNode->begin)] = newNode;

            rightNode->parentNode = newNode;

            newNode->to[*(rightNode->begin)] = rightNode;
            newNode->to[*(activeNode->begin)] = activeNode;
            newNode->parentNode = activeNode->parentNode;

            activeNode->parentNode = newNode;
            activeNode = rightNode;




            if (lastAdded != root && lastAdded->begin + 1 == activeNode->begin) {
                lastAdded->suffLink = newNode;
            }
            lastAdded = rightNode;

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
    //std:: cout << " (" << node << ") -> (" << node->suffLink << ")" << std::endl;

    for (std::map<char, TNode *>::iterator it = node->to.begin(); it != node->to.end(); ++it) {
        NodePrint(it->second, dpth + 1);
    }
}

void TSuffixTree::TreePrint() {
    NodePrint(root, 0);
}