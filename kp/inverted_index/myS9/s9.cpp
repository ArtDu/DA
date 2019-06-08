//
// Created by art on 20.05.19.
//

#include "s9.h"




static size_t vbyte_encode(size_t value, FILE *fp) {
    size_t nbytes = 0;
    uint8_t nibble;

    while (value >= 0x80) { //>=128
        nibble = (value & 0x7F) | 0x80;

        fwrite(&nibble, sizeof nibble, 1, fp);
        nbytes++;

        value >>= 7;
    }

    nibble = value & 0x7F;

    fwrite(&nibble, sizeof nibble, 1, fp);
    nbytes++;

    return nbytes;
}

static size_t vbyte_decode(size_t *value, FILE *fp) {
    size_t nbytes = 0;
    size_t shift = 0;
    uint8_t nibble;

    *value = 0;

    while (1) {
        fread(&nibble, sizeof nibble, 1, fp);
        nbytes++;

        *value |= ((nibble & 0x7F) << shift);

        shift += 7;

        if (nibble < 0x80)
            break;
    }

    return nbytes;
}

void print_selector(uint32_t& selector) {
    int32_t typeSelector = selector & SELECTOR_MASK;
    uint32_t shift = selectors[typeSelector].nbits;
    int32_t countOfElements = selectors[typeSelector].nitems;
    selector = selector >> SELECTOR_BITS;
    for (int i = 0; i < countOfElements; ++i) {
        std::cout << ( selector & binInDec[typeSelector].decItem ) << " ";
        selector = selector >> shift;
    }
    std::cout << std::endl;
}

void simple9_encode(std::vector<uint32_t> &array) {
    if (array.empty()) {
        return;
    }

    uint32_t index;
    uint32_t selector;
    uint32_t data;
    uint32_t shift;

    size_t nitems;
    size_t i;
    size_t arraySize = array.size();


    index = 0;

    while (index < arraySize) {
        for (selector = 0; selector < NSELECTORS; selector++) { // run for selectors
            data = selector; // control bits
            shift = SELECTOR_BITS; // start 4 bits
            nitems = 0; // count of elements in one uint_32

            for (i = index; i < arraySize; i++) {

                if (array[i] > MAX_VALUE) {
                    return;
                }

                if (nitems == selectors[selector].nitems) // selector is full
                    break;

                // element in array more then max in this selector
                if (array[i] > (1UL << selectors[selector].nbits) - 1)
                    break;

                // add element in data
                // {element 1001} or {element element 1000}
                data |= (array[i] << shift);

                shift += selectors[selector].nbits;

                nitems++;
            }

            // selector is full or elements are over
            if (nitems == selectors[selector].nitems || index + nitems == arraySize) {

                print_selector(data);

                index += nitems;

                break;
            }

        } /* End for selector ... */

    } /* End while index < n */
}


/*

size_t simple9_decode(uint32_t **array, size_t *n, FILE *fp) {
    uint32_t data;
    uint32_t select;
    uint32_t mask;

    size_t nbytes;
    size_t nitems;
    size_t i;

    assert(array);
    assert(n);
    assert(fp);

    nbytes = vbyte_decode(n, fp);

    */
/* Look up at the sky. So many stars. It's... beautiful. *//*

    *array = malloc(*n * sizeof **array);
    assert(*array);

    nitems = 0;

    while (nitems < *n) {
        fread(&data, sizeof data, 1, fp);

        nbytes += sizeof data;

        select = data & SELECTOR_MASK;

        data >>= SELECTOR_BITS;

        mask = (1 << selectors[select].nbits) - 1;

        for (i = 0; i < selectors[select].nitems; i++) {
            (*array)[nitems] = data & mask;

            nitems++;

            if (nitems == *n)
                break;

            data >>= selectors[select].nbits;
        }
    }

    return nbytes;
}

size_t simple9_decode_unrolled(uint32_t **array, size_t *n, FILE *fp) {
    uint32_t data;
    uint32_t select;
    uint32_t *ptr;

    size_t nbytes;
    size_t nitems;

    assert(array);
    assert(n);
    assert(fp);

    nbytes = vbyte_decode(n, fp);

    */
/* Due to the unrolled decoding loop there is no bounds checking.
     * To prevent a segmentation or bus fault during decoding we need
     * to allocated some extra space. The maximum offset the decoder
     * can run out of bounds is (the maximum elements that can be
     * packed into a word) - 1. *//*

    *array = malloc((*n + selectors[0].nitems - 1) * sizeof **array);
    assert(*array);

    ptr = *array;

    nitems = 0;

    while (nitems < *n) {
        fread(&data, sizeof data, 1, fp);

        nbytes += sizeof data;

        select = data & SELECTOR_MASK;

        data >>= SELECTOR_BITS;

        switch (select) {
            case 0: */
/* 28 -- 1 bit elements *//*

                ptr[nitems++] = (data) & 1;
                ptr[nitems++] = (data >> 1) & 1;
                ptr[nitems++] = (data >> 2) & 1;
                ptr[nitems++] = (data >> 3) & 1;
                ptr[nitems++] = (data >> 4) & 1;
                ptr[nitems++] = (data >> 5) & 1;
                ptr[nitems++] = (data >> 6) & 1;
                ptr[nitems++] = (data >> 7) & 1;
                ptr[nitems++] = (data >> 8) & 1;
                ptr[nitems++] = (data >> 9) & 1;
                ptr[nitems++] = (data >> 10) & 1;
                ptr[nitems++] = (data >> 11) & 1;
                ptr[nitems++] = (data >> 12) & 1;
                ptr[nitems++] = (data >> 13) & 1;
                ptr[nitems++] = (data >> 14) & 1;
                ptr[nitems++] = (data >> 15) & 1;
                ptr[nitems++] = (data >> 16) & 1;
                ptr[nitems++] = (data >> 17) & 1;
                ptr[nitems++] = (data >> 18) & 1;
                ptr[nitems++] = (data >> 19) & 1;
                ptr[nitems++] = (data >> 20) & 1;
                ptr[nitems++] = (data >> 21) & 1;
                ptr[nitems++] = (data >> 22) & 1;
                ptr[nitems++] = (data >> 23) & 1;
                ptr[nitems++] = (data >> 24) & 1;
                ptr[nitems++] = (data >> 25) & 1;
                ptr[nitems++] = (data >> 26) & 1;
                ptr[nitems++] = (data >> 27) & 1;
                break;

            case 1: */
/* 14 -- 2 bit elements *//*

                ptr[nitems++] = (data) & 3;
                ptr[nitems++] = (data >> 2) & 3;
                ptr[nitems++] = (data >> 4) & 3;
                ptr[nitems++] = (data >> 6) & 3;
                ptr[nitems++] = (data >> 8) & 3;
                ptr[nitems++] = (data >> 10) & 3;
                ptr[nitems++] = (data >> 12) & 3;
                ptr[nitems++] = (data >> 14) & 3;
                ptr[nitems++] = (data >> 16) & 3;
                ptr[nitems++] = (data >> 18) & 3;
                ptr[nitems++] = (data >> 20) & 3;
                ptr[nitems++] = (data >> 22) & 3;
                ptr[nitems++] = (data >> 24) & 3;
                ptr[nitems++] = (data >> 26) & 3;
                break;

            case 2: */
/* 9 -- 3 bit elements (1 wasted bit) *//*

                ptr[nitems++] = (data) & 7;
                ptr[nitems++] = (data >> 3) & 7;
                ptr[nitems++] = (data >> 6) & 7;
                ptr[nitems++] = (data >> 9) & 7;
                ptr[nitems++] = (data >> 12) & 7;
                ptr[nitems++] = (data >> 15) & 7;
                ptr[nitems++] = (data >> 18) & 7;
                ptr[nitems++] = (data >> 21) & 7;
                ptr[nitems++] = (data >> 24) & 7;
                break;

            case 3: */
/* 7 -- 4 bit elements *//*

                ptr[nitems++] = (data) & 15;
                ptr[nitems++] = (data >> 4) & 15;
                ptr[nitems++] = (data >> 8) & 15;
                ptr[nitems++] = (data >> 12) & 15;
                ptr[nitems++] = (data >> 16) & 15;
                ptr[nitems++] = (data >> 20) & 15;
                ptr[nitems++] = (data >> 24) & 15;
                break;

            case 4: */
/* 5 -- 5 bit elements (3 wasted bits) *//*

                ptr[nitems++] = (data) & 31;
                ptr[nitems++] = (data >> 5) & 31;
                ptr[nitems++] = (data >> 10) & 31;
                ptr[nitems++] = (data >> 15) & 31;
                ptr[nitems++] = (data >> 20) & 31;
                break;

            case 5: */
/* 4 -- 7 bit elements *//*

                ptr[nitems++] = (data) & 127;
                ptr[nitems++] = (data >> 7) & 127;
                ptr[nitems++] = (data >> 14) & 127;
                ptr[nitems++] = (data >> 21) & 127;
                break;

            case 6: */
/* 3 -- 9 bit elements (1 wasted bit) *//*

                ptr[nitems++] = (data) & 511;
                ptr[nitems++] = (data >> 9) & 511;
                ptr[nitems++] = (data >> 18) & 511;
                break;

            case 7: */
/* 2 -- 14 bit elements *//*

                ptr[nitems++] = (data) & 16383;
                ptr[nitems++] = (data >> 14) & 16383;
                break;

            case 8: */
/* 1 -- 28 bit element *//*

                ptr[nitems++] = data;
                break;
        }
    }

    return nbytes;
}
*/
