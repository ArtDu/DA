#include <map>
#include <sstream>
#include <vector>
#include <iostream>
#include <string>

#ifndef TBOHR_H_
#define TBOHR_H_

typedef std::string TLetter;

class TBohrItem {
friend class TBohr;
private:
	TBohrItem();
	std::map<TLetter, TBohrItem*> path;
	TBohrItem* sufflink;
	std::vector<int> success; //pattern id
	virtual ~TBohrItem();
};

class TBohr {
public:
	TBohr();
	TBohrItem* Next(TBohrItem* item, TLetter letter);
	TBohrItem* Move(TBohrItem* item, TLetter letter);
	void Parse(const std::string&);
	void Push(const std::vector<TLetter>&);
	void PushLetter(TBohrItem *node, TLetter let, int patid);
	TBohrItem* FindSufflink(TBohrItem* child, TBohrItem* parent,
			const TLetter letter);
	void Search(std::vector<TLetter>&, std::string& pattern,
			std::vector<std::pair<int, int> >&);

	void Linkate();
	virtual ~TBohr();
private:
	TBohrItem* root;
	int patternSize;
	int pieces;
	std::vector<int> pieceTailIndex;
};

#endif /* TBOHR_H_ */
