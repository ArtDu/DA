
#ifndef KP_INVERTEDINDEX_H
#define KP_INVERTEDINDEX_H

#include "TEnc.h"

class TInvertedIndex {
public:

    TInvertedIndex();

    void Read(std::wifstream &in);
    void ReadArticle(std::wifstream &in, uint32_t &numOfArticle);
    void Load(std::wifstream &in);
    void Save(std::wofstream &out);


    ////////////////
    ////for queries
    ////////////////
    void ReadQueries(std::wifstream &in, std::wofstream &out);
    void Query(std::wstring &str, std::wofstream &out);

    int Priority(wchar_t &op);

    void Evaluate(std::vector<uint32_t> &val1, wchar_t &op, std::vector<uint32_t> &val2, std::vector<uint32_t> &result);
    void Evaluate(wchar_t &op, std::vector<uint32_t> &val1, std::vector<uint32_t> &result);

    void QueryIntersection(std::vector<uint32_t> &lhs, std::vector<uint32_t> &rhs, std::vector<uint32_t> &result);
    void QueryUnion(std::vector<uint32_t> &lhs, std::vector<uint32_t> &rhs, std::vector<uint32_t> &result);
    void QueryDifference(std::vector<uint32_t> &lhs, std::vector<uint32_t> &rhs, std::vector<uint32_t> &result);

    bool full_output;
private:
    // <word> <num of article>
    std::unordered_map<std::wstring, TEnc> words;
    // <num of article> <name of article>
    std::vector<std::wstring> names;
    std::vector<uint32_t > nums;


};


#endif //KP_INVERTEDINDEX_H
