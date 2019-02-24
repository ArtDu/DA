//
// Created by art on 18.02.19.
//

#include "TSuffixTree.h"


TNode::TNode(std::string marker) :
        tag(marker), suffLink(nullptr) {}

TSuffixTree::TSuffixTree(std::string str) {

    text = str;
    root = new TNode("");
    activeNode = root;
    root->parentNode = root;


    std::string tmpString = text.substr(0, 1);
    TNode *tmpNode = new TNode(tmpString);
    root->to[tmpString[0]] = tmpNode;
    tmpNode->parentNode = root;
    lastAdded = root;
    fullStringLeaf = tmpNode;
    activeNode = tmpNode;
    activeEdge = tmpString;
    for (int i = 1; i < str.size(); ++i) {
        //add to end to all suffix

        Build(i);

        /*std:: cout << "phase: "<< text[i] << "\n";
        NodePrint(root, 0);
        std::cout << std::endl;*/

    }
}

void TSuffixTree::NaiveAlgo(int positionBegin, int positionEnd) {

    auto it = activeNode->to.find(text[positionBegin]);
    if (it != activeNode->to.end()) {
        activeNode = it->second;
    } else {
        //add node to root
        //rule 2(a)
        std::string tmpString = text.substr(positionBegin, positionEnd + 1 - positionBegin);
        TNode *tmpNode = new TNode(tmpString);
        tmpNode->parentNode = activeNode;
        activeNode->to[tmpString[0]] = tmpNode;
        activeNode = tmpNode;
        return;
    }

    int i = positionBegin, // in text j..i
            j = 0;         // in edge

    //find end
    while (true) {

        if (i == positionEnd && text[i] == activeNode->tag[j] && j < activeNode->tag.size()) {
            //suffix[j..i+1] over and edge ain't over
            //rule 3
            break;
        }


        while (text[i] == activeNode->tag[j] && i < positionEnd + 1 && j < activeNode->tag.size()) {
            ++i; // in text j..i
            ++j; // in edge
        }
        if (j == activeNode->tag.size()) {
            //edge over
            if (i == positionEnd) {
                //suffix[j..i] over
                auto it = activeNode->to.find(text[i]);
                if (it != activeNode->to.end()) {
                    // continuation path exists
                    // => suffix[i+1] == newEdge[0]
                    //rule 3

                    break;
                }

                if (activeNode->to.empty()) {
                    // it's leaf
                    // add to end (rule 1)
                    activeNode->tag.push_back(text[positionEnd]);
                } else {
                    //split
                    //new edge with text[i+1]
                    //rule 2(a)
                    TNode *tmpNode = new TNode(text.substr(i, positionEnd + 1 - i));
                    tmpNode->parentNode = activeNode;
                    activeNode->to[text[i]] = tmpNode;

                    if (lastAdded != root && lastAdded != activeNode && lastAdded->tag.substr(1, lastAdded->tag.size() - 1) == activeNode->tag) {
                        lastAdded->suffLink = activeNode;
                    }
                    lastAdded = activeNode;

                    activeNode = tmpNode;
                }
                break;
            } else {
                //suffix[j..i] ain't over
                //downhill
                j = 0;
                auto it = activeNode->to.find(text[i]);
                if (it != activeNode->to.end()) {
                    // continuation path exists
                    activeNode = it->second;
                    continue;
                }
            }
        } else {
            // edge ain't over
            if (i == positionEnd + 1) {
                //suffix[j..i+1] over
                //rule 3
                break;
            }

            //split
            //new edge with text[i+1]
            //rule 2(b)
            std::string right = text.substr(i, positionEnd + 1 - i);
            std::string newNodeStr = activeNode->tag.substr(0, j);
            TNode *rightNode = new TNode(right);
            TNode *newNode = new TNode(newNodeStr);
            newNode->to[right[0]] = rightNode;
            newNode->parentNode = activeNode->parentNode;
            rightNode->parentNode = newNode;
            activeNode->tag = activeNode->tag.substr(j, activeNode->tag.size() - j);
            newNode->to[activeNode->tag[0]] = activeNode;
            activeNode->parentNode->to[newNodeStr[0]] = newNode;
            activeNode->parentNode = newNode;

            activeNode = rightNode;
            if (lastAdded != root && lastAdded != activeNode && lastAdded->tag.substr(1, lastAdded->tag.size() - 1) == activeNode->tag) {
                lastAdded->suffLink = activeNode;
            }
            lastAdded = newNode;

            break;

        }

    }
}

void TSuffixTree::ImprovedAlgo(int positionBegin, int positionEnd) {
    if (activeNode->parentNode == root || activeNode->parentNode->suffLink == nullptr) {
        activeNode = root;
    } else {

        positionBegin = positionBegin + (positionEnd - positionBegin) - (activeNode->tag.size() - 1) ;
        activeNode = activeNode->parentNode->suffLink;
    }

    NaiveAlgo(positionBegin, positionEnd);
}

void TSuffixTree::Build(int &position) {
    for (int i = 0; i < position + 1; ++i) {


        ImprovedAlgo(i, position);
        //NaiveAlgo(i, position);
    }
}
//fefbeafbdebcfeccabdecdeaebafbebdecfdbbdcbefdaffbdedfafefaabe
void TSuffixTree::NodePrint(TNode *node, int dpth) {
    for (int i = 0; i < dpth; ++i) {
        putchar('\t');
    }

    for (int j = 0; j < node->tag.size(); ++j) {
        std::cout << node->tag[j];
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