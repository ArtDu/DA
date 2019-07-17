

#include "TInvertedIndex.h"

//#include <sys/time.h>

TInvertedIndex::TInvertedIndex() : full_output(false) {}

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
            else if (!word.empty()) {
                words[word].Push(numOfArticle);
                word.clear();
            }

        }

        if (!word.empty())
            words[word].Push(numOfArticle);


        word.clear();
    }
}

void TInvertedIndex::Save(std::wofstream &out) {

    for (auto &i : names) {
        out << i << L"\n";
    }
    out << L"_\n";
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
        if (str == L"_")
            break;
        names.push_back(str);
        nums.push_back(numOfArticle);
        numOfArticle++;
    }
    while (true) {
        in >> str;
        if (str == L"_")
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


void
TInvertedIndex::QueryIntersection(std::vector<uint32_t> &lhs, std::vector<uint32_t> &rhs,
                                  std::vector<uint32_t> &result) {

    std::set_intersection(lhs.begin(), lhs.end(),
                          rhs.begin(), rhs.end(),
                          std::back_inserter(result));

}

void TInvertedIndex::QueryUnion(std::vector<uint32_t> &lhs, std::vector<uint32_t> &rhs, std::vector<uint32_t> &result) {

    std::set_union(lhs.begin(), lhs.end(),
                   rhs.begin(), rhs.end(),
                   std::back_inserter(result));

}

void TInvertedIndex::QueryDifference(std::vector<uint32_t> &lhs,
                                     std::vector<uint32_t> &rhs, std::vector<uint32_t> &result) {
    std::set_difference(lhs.begin(), lhs.end(),
                        rhs.begin(), rhs.end(),
                        std::back_inserter(result));
}

void
TInvertedIndex::Evaluate(std::vector<uint32_t> &val1, wchar_t &op, std::vector<uint32_t> &val2,
                         std::vector<uint32_t> &result) {


    switch (op) {
        case L'&':
            QueryIntersection(val1, val2, result);
            break;
        case L'|':
            QueryUnion(val1, val2, result);
            break;
        default:
            break;
    }
}

void TInvertedIndex::Evaluate(wchar_t &op, std::vector<uint32_t> &val1, std::vector<uint32_t> &result) {
    QueryDifference(nums, val1, result);
}

void TInvertedIndex::ReadQueries(std::wifstream &in, std::wofstream &out) {
    std::wstring str;
    while (getline(in, str))
        Query(str, out);
}

void TInvertedIndex::Query(std::wstring &str, std::wofstream &out) {

    /*struct timeval  tv;
    gettimeofday(&tv, NULL);

    double time_begin = ((double)tv.tv_sec) * 1000 +
                        ((double)tv.tv_usec) / 1000;
*/
    std::vector<uint32_t> emptyVec;

    //parse and evaluate expression
    std::stack<wchar_t> operators;
    std::stack<std::vector<uint32_t>> values;

    for (int i = 0; i < str.size(); ++i) {

        //skip whitespaces
        if (str[i] == L' ')
            continue;

        if (str[i] == L'(') {
            operators.push(L'(');
        } else if (iswalnum(str[i])) { // if it's word
            std::wstring word;
            while (i < str.size() && iswalnum(str[i])) {
                word += static_cast<wchar_t >(towlower(str[i]));
                i++;
            }
            i--;
            if (words.find(word) != words.end()) {
                std::vector<uint32_t> articles;
                words[word].Decode(articles);
                values.push(articles);
            } else {
                values.push(emptyVec);
            }
        } else if (str[i] == L')') {
            while (!operators.empty() && operators.top() != L'(') {
                std::vector<uint32_t> tmp;
                wchar_t op = operators.top();
                operators.pop();

                if (op == L'~') {

                    Evaluate(op, values.top(), tmp);
                    tmp.swap(values.top());

                } else {

                    std::vector<uint32_t> val1 = values.top();
                    values.pop();

                    Evaluate(val1, op, values.top(), tmp);
                    tmp.swap(values.top());
                }
            }
            operators.pop();

        } else { //else it operator
            wchar_t rightOp = str[i];
            while (!operators.empty() && Priority(operators.top()) >= Priority(rightOp)) {
                std::vector<uint32_t> tmp;
                wchar_t op = operators.top();
                operators.pop();

                if (op == L'~') {
                    Evaluate(op, values.top(), tmp);
                    tmp.swap(values.top());
                } else {

                    std::vector<uint32_t> val1 = values.top();
                    values.pop();

                    Evaluate(val1, op, values.top(), tmp);
                    tmp.swap(values.top());
                }
            }
            operators.push(rightOp);
        }
    }

    while (!operators.empty()) {
        std::vector<uint32_t> tmp;
        wchar_t op = operators.top();
        operators.pop();

        if (op == L'~') {
            Evaluate(op, values.top(), tmp);
            tmp.swap(values.top());
        } else {
            std::vector<uint32_t> val1 = values.top();
            values.pop();

            Evaluate(val1, op, values.top(), tmp);
            tmp.swap(values.top());
        }
    }

    //write answer
    if (!values.empty()) {
        std::vector<uint32_t> ans = values.top();
        if (!ans.empty()) {
            out << ans.size() << L"\n";
            if (full_output)
                for (auto &i : ans) {
                    out << names[i - 1] << L"\n";
                }
        } else {
            out << 0 << L"\n";
        }
    } else {
        out << 0 << L"\n";
    }

    /*gettimeofday(&tv, NULL);
    double time_end = ((double)tv.tv_sec) * 1000 +
                      ((double)tv.tv_usec) / 1000 ;

    double total_time_ms = time_end - time_begin;

    printf("TOTAL TIME (ms) = %f\n", total_time_ms);*/

}

