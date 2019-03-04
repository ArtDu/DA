//
// Created by art on 04.03.19.
//

#ifndef AHOCORASICK_KEYSTREE_H
#define AHOCORASICK_KEYSTREE_H

#include <iostream>
#include <map>
#include <vector>
#include <string>
#include <queue>

using namespace std;

class KTNode {
public:
    map<string, KTNode *> to;
    string _key;
    vector<int32_t> _list;
    int32_t dist;

    KTNode *suffLink;

    KTNode(string key, int32_t list, int32_t dist);
    KTNode(string key, int32_t dist);
};


class KeysTree {
public:

    KeysTree();

    void BuildTree(vector<vector<string >> &patterns);

    void Search(vector<pair<pair<int32_t, int32_t>, string >> &text);

    void TreePrint();

private:

    void NodePrint(KTNode *node, int dpth, std::string x);

    void AddSuffLinks();

    void BuildOnePattern(vector<string> &pattern, int32_t &pattNum);

    KTNode *root;

};


#endif //AHOCORASICK_KEYSTREE_H
