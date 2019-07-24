//
// Created by art on 04.03.19.
//

#include "KeysTree.h"

KTNode::KTNode(string key, int32_t list, int32_t dist)
        : _key(key), suffLink(nullptr), dist(dist) {
    this->_list.push_back(list);
}

KTNode::KTNode(string key, int32_t dist)
        : _key(key), suffLink(nullptr), dist(dist) {}

KeysTree::KeysTree() {
    root = new KTNode("", 0);
    //root->suffLink = root;
}

void KeysTree::BuildTree(vector<vector<string >> &patterns) {
    int32_t i = 1;
    for (auto pattern : patterns) {
        BuildOnePattern(pattern, i);
        i++;
    }

    AddSuffLinks();

    //TreePrint();

}

void KeysTree::BuildOnePattern(vector<string> &pattern, int32_t &pattNum) {

    KTNode *activeNode = root;
    map<string, KTNode *>::iterator it;

    int32_t i = 0;
    while (true) {
        if (i == pattern.size()) {
            activeNode->_list.push_back(pattNum);
            break;
        }
        it = activeNode->to.find(pattern[i]);
        if (it != activeNode->to.end()) {
            activeNode = it->second;
            i++;
        } else {
            for (; i < pattern.size(); ++i) {
                KTNode *tmp = new KTNode(pattern[i], i + 1);
                activeNode->to[pattern[i]] = tmp;
                activeNode = tmp;
            }
        }

    }

}

void KeysTree::AddSuffLinks() {
    KTNode *father,
            *child,
            *w,
            *w_;
    string x;

    queue<KTNode *> queueOfWidth;
    queueOfWidth.push(root);
    while (!queueOfWidth.empty()) {
        father = queueOfWidth.front();
        w = father->suffLink;
        queueOfWidth.pop();

        for (auto iChild : father->to) {
            x = iChild.first;
            child = iChild.second;

            queueOfWidth.push(child);

            if (w == nullptr) {
                child->suffLink = root;
                continue;
            }

            auto it = w->to.find(x);
            while (w != root && it == w->to.end()) {
                w = w->suffLink;
                it = w->to.find(x);
            }

            if (it != w->to.end()) {
                w_ = it->second;
                child->suffLink = w_;
            } else {
                child->suffLink = root;
            }


        }

    }
}

void KeysTree::Search(vector<pair<pair<int32_t, int32_t>, string >> &text) {

    map<string, KTNode *>::iterator it;

    size_t m = text.size();
    int32_t l = 0;
    int32_t c = 0;
    KTNode *w = root;
    do {

        it = w->to.find(text[c].second);
        while (it != w->to.end()) {

            KTNode *w_ = it->second;

            if (!w_->_list.empty()) {
                for (auto i : w_->_list) {
                    cout << text[l].first.first << ", " << text[l].first.second << ", " << i << "\n";
                }
            }
            KTNode *tmpW = w_->suffLink;
            while (tmpW != nullptr) {


                if (!tmpW->_list.empty()) {
                    int32_t newBegStr = c - tmpW->dist + 1;
                    for (auto i : tmpW->_list) {
                        cout << text[newBegStr].first.first << ", " << text[newBegStr].first.second << ", " << i
                             << "\n";

                    }

                }

                tmpW = tmpW->suffLink;
            }


            c++;
            w = w_;
            it = w->to.find(text[c].second);
        }

        if (w == root) {
            l++;
            c++;
        } else {
            w = w->suffLink;
            l = c - w->dist;
        }
    } while (c < m);
}

void KeysTree::NodePrint(KTNode *node, int dpth, std::string x) {
    for (int i = 0; i < dpth; ++i) {
        putchar('\t');
    }


    cout << x << "(" << node << ") -> " << node->suffLink << endl;

    //std:: cout << " node is " << node << " sufflink is " << node->sufflink << std::endl;

    for (auto it = node->to.begin(); it != node->to.end(); ++it) {
        NodePrint(it->second, dpth + 1, it->first);
    }
}

void KeysTree::TreePrint() {
    NodePrint(root, 0, "");
}
