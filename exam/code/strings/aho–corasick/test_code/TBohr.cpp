#include "TBohr.h"

#include <queue>

TBohr::TBohr() :
        patternSize(0), pieces(0) {
    root = new TBohrItem;
    root->sufflink = root;
}

TBohrItem* TBohr::Move(TBohrItem* item, TLetter letter) {

    try {
        item = item->path.at(letter);
    } catch (std::out_of_range&) {

        if (item == root)
            item = root;
        else
            item = Move(item->sufflink, letter);
    }
    return item;
}
TBohrItem* TBohr::Next(TBohrItem* item, TLetter letter) {

    if (!item)
        return nullptr;
    try {
        item = item->path.at(letter);
    } catch (std::out_of_range&) {
        item = nullptr;
    }
    return item;
}

void TBohr::Linkate() {

    TBohrItem *node, *child;
    std::queue<TBohrItem *> queue;
    queue.push(root);
    while (!queue.empty()) {
        node = queue.front();
        queue.pop();
        std::map<TLetter, TBohrItem *>::iterator childPairIt;
        for (childPairIt = node->path.begin(); childPairIt != node->path.end();
             ++childPairIt) {
            child = childPairIt->second;
            queue.push(child);
            child->sufflink = FindSufflink(child, node, childPairIt->first);


            child->success.insert(child->success.end(),
                                  child->sufflink->success.begin(),
                                  child->sufflink->success.end());


            child->success.shrink_to_fit();
        }
    }
}

TBohrItem* TBohr::FindSufflink(TBohrItem* child, TBohrItem* parent,
                               const TLetter letter) {
    TBohrItem *linkup = parent->sufflink, *check;
    while (true) {
        check = Next(linkup, letter);
        if (check)
            return (check != child) ? check : root;
        if (linkup == root)
            return root;
        linkup = linkup->sufflink;

    }
}

void TBohr::Push(const std::vector<TLetter>& str) {

    TBohrItem *bohr = root, *next;
    for (size_t i = 0; i < str.size(); ++i) {
        next = Next(bohr, str[i]);
        if (!next) {
            next = new TBohrItem;
            next->sufflink = root;
            bohr->path.insert(std::pair<TLetter, TBohrItem*>(str[i], next));
        }
        bohr = next;
    }
    bohr->success.push_back(pieces);
    pieces++;
}
void TBohr::Search(std::vector<TLetter>& text,
                   std::vector<std::pair<int, int> >& grid) {



    Linkate();

    /*TreePrint();
    return;*/

    int m = text.size();
    TBohrItem* node = root;
    int occurrence;
    int c;
    for (c = 0; c < m; ++c) {

        for (size_t i = 0; i < node->success.size(); ++i) {
            occurrence = c - pieceIndex[node->success[i]] ;
            std::cout << grid[occurrence].first << ", "  << grid[occurrence].second << ", " << node->success[i] + 1 << std::endl;
        }

        node = Move(node, text[c]);

    }

    for (size_t i = 0; i < node->success.size(); ++i) {
        occurrence = c - pieceIndex[node->success[i]] ;
        std::cout << grid[occurrence].first << ", "  << grid[occurrence].second << ", " << node->success[i] + 1 << std::endl;
    }
}



void TBohr::NodePrint(TBohrItem *node, int dpth, std::string x)
{
    for (int i = 0; i < dpth; ++i) {
        putchar('\t');
    }


    std::cout << x << "(" << node << ") [ ";
    for (auto i : node->success) {
        std::cout << i << ", ";
    }
    std::cout << " ] -> " << node->sufflink << std::endl;

    //std:: cout << " node is " << node << " sufflink is " << node->sufflink << std::endl;

    for (auto it = node->path.begin(); it != node->path.end(); ++it) {
        NodePrint(it->second, dpth + 1, it->first);
    }
}

void TBohr::TreePrint()
{
    NodePrint(root, 0, "");
}
