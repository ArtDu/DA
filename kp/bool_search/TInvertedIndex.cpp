//
// Created by art on 03.05.19.
//

//karma
//index --input ../../examples/small --output index.txt
//search --index index.txt --input ../../examples/queries --output answer.txt --full-output

//my
//index --input ../test_code/tests/00.t --output ../index.txt
//search --index ../index.txt --input ../examples/queries --output ../answer.txt --full-output

#include "TInvertedIndex.h"



void TInvertedIndex::Read(std::wifstream &in) {
    //find title

    std::wstring str;
    std::wstring nameOfDoc;
    uint32_t numOfArticle = 1;

    while (getline(in, str)) {
        if (!str.empty()) {
            //take name of doc
            size_t pos = str.find(L"title");
            nameOfDoc = str.substr(pos + 7, str.size() - pos - 7 - 2);

            //read doc's inner
            ReadArticle(in, numOfArticle);
            numOfArticle++;

            //push name of doc
            names.push_back(nameOfDoc);
        }
    }

}

void TInvertedIndex::ReadArticle(std::wifstream &in, uint32_t &numOfArticle) {

    std::wstring str;
    std::wstring word;
    while (in >> str) {

        if (str == L"</doc>") {
            break;
        }

        //convert the word into a normal form
        for (auto &c : str) {
            if (iswalnum(c)) {
                word += static_cast<wchar_t >(towlower(c));
            }

        }

        if(!word.empty())
            words[word].Push(numOfArticle);


        word.clear();
    }
}

void TInvertedIndex::Save(std::wofstream &out) {
    for (auto &i : names) {
        out << i << L"\n";
    }
    out << L"0\n";
    for (auto &i : words) {
        out << i.first << L"\n";

        i.second.PushDelay();
        i.second.Save(out);
    }
    out << L"_";
}

void TInvertedIndex::Load(std::wifstream &in) {
    uint32_t numOfArticle = 1;
    std::wstring str;
    while (true) {
        getline(in, str);
        if(str == L"0")
            break;
        names.push_back(str);
        nums.push_back(numOfArticle);
        numOfArticle++;
    }
    while (true) {
        in >> str;
        if(str == L"_")
            break;
        words[str].Load(in);
    }

}



///////////////////////////////////
///////////// for queries
///////////////////////////////////

int TInvertedIndex::Priority(wchar_t &op) {
    if (op == L'~') return 3;
    if (op == L'&') return 2;
    if (op == L'|') return 1;
    return 0;
}


std::vector<uint32_t>
TInvertedIndex::QueryIntersection(std::vector<uint32_t> &lhs, std::vector<uint32_t> &rhs) {
    std::vector<uint32_t> res;

    std::set_intersection(lhs.begin(), lhs.end(),
                          rhs.begin(), rhs.end(),
                          std::back_inserter(res));

    return res;
}

std::vector<uint32_t> TInvertedIndex::QueryUnion(std::vector<uint32_t> &lhs, std::vector<uint32_t> &rhs) {
    std::vector<uint32_t> res;

    std::set_union(lhs.begin(), lhs.end(),
                   rhs.begin(), rhs.end(),
                   std::back_inserter(res));

    return res;
}

std::vector<uint32_t> TInvertedIndex::QueryDifference(std::vector<uint32_t> &lhs,
                                                      std::vector<uint32_t> &rhs) {
    std::vector<uint32_t> res;

    std::set_difference(lhs.begin(), lhs.end(),
                        rhs.begin(), rhs.end(),
                        std::back_inserter(res));

    return res;
}

std::vector<uint32_t>
TInvertedIndex::Evaluate(std::vector<uint32_t> &val1, wchar_t &op, std::vector<uint32_t> &val2) {

    std::vector<uint32_t> res;
    switch (op) {
        case L'&':
            return QueryIntersection(val1, val2);
        case L'|':
            return QueryUnion(val1, val2);
        default:
            return res;
    }
}

std::vector<uint32_t> TInvertedIndex::Evaluate(wchar_t &op, std::vector<uint32_t> &val1) {
    return QueryDifference(nums, val1);
}

void TInvertedIndex::ReadQueries(std::wifstream &in, std::wofstream &out) {
    std::wstring str;
    while(getline(in, str))
        Query(str, out);
}

void TInvertedIndex::Query(std::wstring &str, std::wofstream &out) {

    //parse and evaluate expression
    std::stack<wchar_t> operators;
    std::stack<std::vector<uint32_t>> values;

    for (int i = 0; i < str.size(); ++i) {

        //skip whitespaces
        if (str[i] == L' ')
            continue;

        if (str[i] == L'(') {
            operators.push(L'(');
        } else if (iswalnum(str[i])) {
            std::wstring word;
            while (i < str.size() && iswalnum(str[i])) {
                word += static_cast<wchar_t >(towlower(str[i]));
                i++;
            }
            if(words.find(word) != words.end()) {
                values.push(words[word].Decode());
            }
        } else if (str[i] == L')') {
            while (!operators.empty() && operators.top() != L'(') {

                wchar_t op = operators.top();
                operators.pop();

                if (op == L'~') {
                    std::vector<uint32_t> val1 = values.top();
                    values.pop();
                    values.push(Evaluate(op, val1));
                } else {
                    std::vector<uint32_t> val1 = values.top();
                    values.pop();
                    std::vector<uint32_t> val2 = values.top();
                    values.pop();
                    values.push(Evaluate(val1, op, val2));
                }
            }
            operators.pop();

        }
            //operator
        else {
            wchar_t rightOp = str[i];
            while (!operators.empty() && Priority(operators.top()) >= Priority(rightOp)) {
                wchar_t op = operators.top();
                operators.pop();

                if (op == L'~') {
                    std::vector<uint32_t> val1 = values.top();
                    values.pop();
                    values.push(Evaluate(op, val1));
                } else {
                    std::vector<uint32_t> val1 = values.top();
                    values.pop();
                    std::vector<uint32_t> val2 = values.top();
                    values.pop();
                    values.push(Evaluate(val1, op, val2));
                }
            }
            operators.push(rightOp);
        }
    }

    while (!operators.empty()) {
        wchar_t op = operators.top();
        operators.pop();

        if (op == L'~') {
            std::vector<uint32_t> val1 = values.top();
            values.pop();
            values.push(Evaluate(op, val1));
        } else {
            std::vector<uint32_t> val1 = values.top();
            values.pop();
            std::vector<uint32_t> val2 = values.top();
            values.pop();
            values.push(Evaluate(val1, op, val2));
        }
    }

    //write answer
    if (!values.empty()) {
        std::vector<uint32_t> ans = values.top();
        if (!ans.empty()) {
            out << ans.size() << L"\n";
            if(full_output)
                for (auto &i : ans) {
                    out << names[i-1] << L"\n";
                }
        }
        else {
            out << 0 << L"\n";
        }
    }
    else {
        out << 0 << L"\n";
    }

}

