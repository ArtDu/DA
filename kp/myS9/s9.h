//
// Created by art on 20.05.19.
//

#ifndef MYS9_S9_H
#define MYS9_S9_H

#include <iostream>
#include <vector>

#include <assert.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <errno.h>
#include <limits.h>


#define UINT32_BITS (sizeof(uint32_t) * CHAR_BIT) //32

#define SELECTOR_MASK 0x0000000F //15

#define SELECTOR_BITS 4

#define CODE_BITS (UINT32_BITS - SELECTOR_BITS) //28

#define MAX_VALUE ((1UL << CODE_BITS) - 1) //28 bits 11...11

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

static const struct {
    uint32_t binItem;
    uint32_t decItem;
} binInDec[NSELECTORS] = {
        {1, 1},
        {2,  3},
        {3,  7},
        {4,  15},
        {5,  31},
        {7,  127},
        {9,  511},
        {14, 16383},
        {28, 268435455},
};


void simple9_encode(std::vector<uint32_t> &array);
void print_selector(uint32_t& selector);


#endif //MYS9_S9_H
