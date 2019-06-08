//
// Created by art on 20.05.19.
//

#ifndef KP_SIMPLE9_H
#define KP_SIMPLE9_H


#include <iostream>
#include <vector>

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <limits.h>



#define SELECTOR_MASK 0x0000000F //15

#define SELECTOR_BITS 4

#define NSELECTORS 9

static const struct {
    uint32_t nitems;
    uint32_t nbits;
    uint32_t nwaste;
} selectors[NSELECTORS] = {
        {28, 1,  0},
        {14, 2,  0},
        {9,  3,  1},
        {7,  4,  0},
        {5,  5,  3},
        {4,  7,  0},
        {3,  9,  1},
        {2,  14, 0},
        {1,  28, 0},
};


void simple9_encode(std::vector<uint32_t> &array, std::vector<uint32_t > &encodeArray);

std::vector<uint32_t> simple9_decode(std::vector<uint32_t> &vec);


#endif //KP_SIMPLE9_H
