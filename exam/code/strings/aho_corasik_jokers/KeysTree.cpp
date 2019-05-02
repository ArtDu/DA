//
// Created by art on 04.03.19.
//

#include "KeysTree.h"

/*KTNode::KTNode(string key, int32_t list, int32_t dist)
        : _key(key), suffLink(nullptr), dist(dist) {
    this->_list.push_back(list);
}*/

KTNode::KTNode(string key, int32_t dist)
        : _key(key), dist(dist) {
    suffLink = nullptr;
}

/*KTNode::~KTNode() {
    for (auto i : this->to) {
        delete i.second;
    }

}

KeysTree::~KeysTree() {
    this->C.clear();
    delete root;

}*/

/*void KeysTree::DeleteNode(KTNode *node) {

    if(node == nullptr)
        return;

    for (auto i : node->to) {
        DeleteNode(i.second);
        i.second = nullptr;
    }
    node->to.clear();
    delete node;
}*/

KeysTree::KeysTree() {

    root = new KTNode("", 0);

}

void KeysTree::BuildTree(vector<pair<vector<string>, int32_t >> &patterns) {

    sizeOfPatterns = patterns.size();

    for (auto pattern : patterns) {
        BuildOnePattern(pattern.first, pattern.second);

    }

    AddSuffLinks();

    //TreePrint();

}

void KeysTree::BuildOnePattern(vector<string> &pattern, int32_t &fstBeg) {

    KTNode *activeNode = root;
    map<string, KTNode *>::iterator it;

    int32_t i = 0;
    while (true) {
        if (i == pattern.size()) {
            activeNode->_list.push_back(fstBeg);
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
    C.resize(m, 0);

    int32_t l = 0;
    int32_t c = 0;
    KTNode *w = root;
    do {

        it = w->to.find(text[c].second);
        while (it != w->to.end()) {

            KTNode *w_ = it->second;

            //есть вхождение в узле, лежащем на той же ветке
            if (!w_->_list.empty()) {
                for (auto i : w_->_list) {
                    if (l - i >= 0) {
                        C[l - i]++;
                    }
                    //cout << text[l].first.first << ", " << text[l].first.second << ", " << i << "\n";
                } 
            }
            KTNode *tmpW = w_->suffLink;
            while (tmpW != nullptr) {

                //есть вхождения в узлах, в прохождение связи выхода(прохождение по связям неудач)
                if (!tmpW->_list.empty()) {
                    int32_t newBegStr = c - tmpW->dist + 1;
                    for (auto i : tmpW->_list) {

                        C[newBegStr - i]++;
                        //cout << text[newBegStr].first.first << ", " << text[newBegStr].first.second << ", " << i
                        //    << "\n";

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


    for (int j = 0; j < C.size(); ++j) {
        if (sizeOfPatterns == C[j]) {
            cout << text[j].first.first << ", " << text[j].first.second << endl;
        }
    }

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
