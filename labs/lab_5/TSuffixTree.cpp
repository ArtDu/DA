//
// Created by art on 18.02.19.
//

#include "TSuffixTree.h"


TNode::TNode(std::string marker) :
        tag(marker) {}

TSuffixTree::TSuffixTree(std::string str) {

    text = str;
    root = new TNode("");
    activeNode = root;
    parentNode = root;

    for (int i = 0; i < str.size(); ++i) {
        //add to end to all suffix
        Build(i);
    }
}

void TSuffixTree::FindEnd(int positionBegin, int positionEnd) {

    int i = positionBegin, j = 0;
    while (true) {
        j = 0;
        if (i == positionEnd && text[i] == activeNode->tag[j] && j < activeNode->tag.size()) {
            break;
        }


        while (text[i] == activeNode->tag[j] && i < positionEnd + 1 && j < activeNode->tag.size()) {
            ++i; // in text j..i
            ++j; // in edge
        }
        if (j == activeNode->tag.size()) { //edge over
            if (i == positionEnd) {
                auto it = activeNode->to.find(text[i]);
                if (it != activeNode->to.end()) { // continuation path exists
                    break;
                }
                // and suffix over
                // add to end (rule 1)
                if (activeNode->to.size() == 0) {
                    activeNode->tag.push_back(text[positionEnd]);
                } else {
                    //rule 2(a)
                    TNode *tmpNode = new TNode(text.substr(i, positionEnd + 1 - i));
                    activeNode->to[text[i]] = tmpNode;
                }
                break;
            } else {
                //downhill
                auto it = activeNode->to.find(text[i]);
                if (it != activeNode->to.end()) { // continuation path exists
                    parentNode = activeNode;
                    activeNode = it->second;
                    continue;
                } else { // add to end of edge
                    if (activeNode->to.size() == 0) {
                        activeNode->tag.push_back(text[positionEnd]);
                    } else {
                        //rule 2(a)
                        TNode *tmpNode = new TNode(text.substr(i, positionEnd + 1 - i));
                        activeNode->to[text[i]] = tmpNode;
                    }
                    break;
                }
            }
        } else { // edge ain't over

            if (i == positionEnd + 1) { //rule 3 (suffix over)
                break;
            }

            //split (rule 2)

            std::string right = text.substr(i, positionEnd + 1 - i);
            std::string newNodeStr = activeNode->tag.substr(0, j);
            TNode *rightNode = new TNode(right);
            TNode *newNode = new TNode(newNodeStr);
            newNode->to[right[0]] = rightNode;
            activeNode->tag = activeNode->tag.substr(j, activeNode->tag.size() - j);
            newNode->to[activeNode->tag[0]] = activeNode;
            parentNode->to[newNodeStr[0]] = newNode;
            break;

        }

    }
}

void TSuffixTree::Build(int &position) {
    for (int i = 0; i < position + 1; ++i) {
        auto it = root->to.find(text[i]);
        if (it != root->to.end()) {
            parentNode = root;
            activeNode = it->second;
            //0 1
            FindEnd(i, position);
        } else {
            std::string tmpString = text.substr(i, position + 1 - i);
            TNode *tmpNode = new TNode(tmpString);
            root->to[tmpString[0]] = tmpNode;
        }
    }
}

void TSuffixTree::NodePrint(TNode *node, int dpth) {
    for (int i = 0; i < dpth; ++i) {
        putchar('\t');
    }

    for (int j = 0; j < node->tag.size(); ++j) {
        std::cout << node->tag[j];
    }
    std::cout << std::endl;

    //std:: cout << " node is " << node << " sufflink is " << node->suffixLink << std::endl;
    for (std::map<char, TNode *>::iterator it = node->to.begin(); it != node->to.end(); ++it) {
        NodePrint(it->second, dpth + 1);
    }
}

void TSuffixTree::TreePrint() {
    NodePrint(root, 0);
}