
#include <stdint-gcc.h>
#include "TEnc.h"


void TEnc::Push(uint32_t &numOfText) {
    if (lastNum != 0) { // not empty
        if (lastNum != numOfText) { // no repeat
            delay.push_back(numOfText - lastNum); // push delta
            lastNum = numOfText;
        } else {
            return;
        }
    } else {
        delay.push_back(numOfText);
        lastNum = numOfText;
    }


    if (delay.size() == 28) {
        TSimple9_encode(delay, encoded);
        delay.clear();
    }
}

void TEnc::PushDelay() {
    if (!delay.empty()) {
        TSimple9_encode(delay, encoded);
        delay.clear();
    }
}

void TEnc::Decode(std::vector<uint32_t> &ans) {
    if (!delay.empty()) {
        TSimple9_encode(delay, encoded);
        delay.clear();
    }
    TSimple9_decode(encoded, ans);

}

void TEnc::Save(std::wofstream &out) {

    for (auto i : this->encoded) {
        out << i << L"\n";
    }
    out << L"0\n";
}

void TEnc::Load(std::wifstream &in) {
    uint32_t num;
    while (true) {
        in >> num;
        if(num == 0)
            break;
        encoded.push_back(num);
    }
}