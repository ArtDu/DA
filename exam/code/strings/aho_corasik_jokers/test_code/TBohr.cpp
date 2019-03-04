#include "TBohr.h"

#include <queue>

TBohrItem::TBohrItem():sufflink(nullptr){}

TBohrItem::~TBohrItem(){
	for(auto item: path)
		delete item.second;
}

TBohr::TBohr() :
		patternSize(0), pieces(0) {
	root = new TBohrItem;
	root->sufflink = root;
}
TBohr::~TBohr(){
	delete root;
}

TBohrItem* TBohr::Move(TBohrItem* item, TLetter letter) {
	auto res = item->path.find(letter);
 	while(res == item->path.end()){
 		if(item->sufflink == item)
    		//root
    		return root;
    	item = item->sufflink;
    	res = item->path.find(letter);
    }
	item = res->second;
	return item;
}
TBohrItem* TBohr::Next(TBohrItem* item, TLetter letter) {
	if (!item)
		return nullptr;
	auto res = item->path.find(letter);
	if(res != item->path.end())
		item = res->second;
	else
		item = nullptr;
	return item;
}
void TBohr::Parse(const std::string& line) {
	std::stringstream input(line);
	std::string token;
	std::vector<TLetter> pattern;
	int index = -1;
	while (input >> token) {
		if (token == "?") {
			if (pattern.size() != 0) {
				Push(pattern);
				//std::cout<<index+1-pattern.size()<<std::endl;
				pieceTailIndex.push_back(index);
				pattern.clear();
			}

		} else {
			pattern.push_back(token);
		}
		index++;
	}
	if (pattern.size() != 0) {
		Push(pattern);
		//std::cout<<index+1-pattern.size()<<std::endl;
		pieceTailIndex.push_back(index);
	}
	this->patternSize=index+1;
}

void TBohr::Linkate() {
	//need to navigate through all childs of node
	//then through all childs of childs and so on
	//it is horizontal navigation through tree
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
			child->sufflink = FindSufflink(child,node, childPairIt->first);

			//vector concatenation
			child->success.insert(child->success.end(),
					child->sufflink->success.begin(),
					child->sufflink->success.end());

			//optimize memory
			//size will not change more
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
//void Bohr::PushLetter(BohrItem *node, Letter let, int patid) {
//	BohrItem *next;
//	next = Next(node, let);
//	if (!next) {
//		next = new BohrItem;
//		next->sufflink = root;
//		node->path.insert(std::pair<Letter, BohrItem*>(let, next));
//	}
//	node = next;
//	if (patid > 0)
//		node->success.push_back(patid);
//}
void TBohr::Push(const std::vector<TLetter>& str) {
	//should rewrite to
	//(BohrItem*, letter)
	TBohrItem *bohr = root, *next;
	size_t strLen = str.size();
	for (size_t i = 0; i < strLen; ++i) {
		next = Next(bohr, str[i]);
		if (!next) {
			next = new TBohrItem;
			next->sufflink = root;
			bohr->path.insert(std::pair<TLetter, TBohrItem*>(str[i], next));
		}
		bohr = next;
	}
//	patterns.push_back(str);
	bohr->success.push_back(pieces);
	pieces++;
}
void TBohr::Search(std::vector<TLetter>& text, std::string& pattern,
		std::vector<std::pair<int, int> >& grid) {
	Parse(pattern);
	Linkate();
	int m = text.size();
	std::vector<int> answer(m, 0);
	TBohrItem* node = root;
	int occurrence;
	int c;
	for (c = 0; c < m; ++c) {

		for (size_t i = 0; i < node->success.size(); ++i) {
			occurrence = c - pieceTailIndex[node->success[i]] - 1;
			if (occurrence >= 0)
				answer[occurrence] += 1;
		}

		node = Move(node, text[c]);
	}
	//last move check
	for (size_t i = 0; i < node->success.size(); ++i) {
		occurrence = c - pieceTailIndex[node->success[i]] - 1;
		if (occurrence >= 0)
			answer[occurrence] += 1;
	}

	for (c = 0; c < m; ++c)
		//if (answer[c] == pieces)
		if (answer[c] == pieces && c + patternSize <= m)
			std::cout << grid[c].first << ", " << grid[c].second << std::endl;

}

