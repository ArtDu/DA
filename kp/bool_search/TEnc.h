//
// Created by art on 20.06.19.
//

#ifndef KP_ENC_H
#define KP_ENC_H

#include "TSimple9.h"

class TEnc {
public:
    TEnc() = default;


    void Push(uint32_t &numOfText);
    //encode all delays nums
    void PushDelay();

    std::vector<uint32_t> Decode();

    void Save(std::wofstream &out);
    void Load(std::wifstream &in);


    std::vector<uint32_t> encoded;
    std::vector<uint32_t> delay;
    uint32_t lastNum = 0;
};


#endif //KP_ENC_H
