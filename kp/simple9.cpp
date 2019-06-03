//
// Created by art on 20.05.19.
//

#include "simple9.h"

void print_selector(uint32_t& selector) {
    int32_t typeSelector = selector & SELECTOR_MASK;
    std::cout << typeSelector << " ";
    uint32_t shift = selectors[typeSelector].nbits;
    int32_t countOfElements = selectors[typeSelector].nitems;
    selector = selector >> SELECTOR_BITS;
    for (int i = 0; i < countOfElements; ++i) {
        std::cout << ( selector & binInDec[typeSelector].decItem ) << " ";
        selector = selector >> shift;
    }
    std::cout << std::endl;
}

void simple9_encode(std::vector<uint32_t> &array, std::vector<uint32_t> &encodeArray) {

    uint32_t index;
    uint32_t selector;
    uint32_t data;
    uint32_t shift;

    size_t nitems;
    size_t i;
    size_t arraySize = array.size();


    index = 0;
    auto curNum = array.begin();
    auto iCurNum = array.begin();

    while (index < arraySize) {
        for (selector = 0; selector < NSELECTORS; selector++) { // run for selectors
            data = selector; // control bits
            shift = SELECTOR_BITS; // start 4 bits
            nitems = 0; // count of elements in one uint_32

            for (i = index, iCurNum = curNum; i < arraySize; i++, ++iCurNum) {

                if (*iCurNum > MAX_VALUE) {
                    return;
                }

                if (nitems == selectors[selector].nitems) // selector is full
                    break;

                // element in array more then max in this selector
                if (*iCurNum > (1UL << selectors[selector].nbits) - 1)
                    break;

                // add element in data
                // {element 1001} or {element element 1000}
                data |= (*iCurNum << shift);

                shift += selectors[selector].nbits;

                nitems++;
            }

            // selector is full or elements are over
            if (nitems == selectors[selector].nitems || index + nitems == arraySize) {

                //print_selector(data);
                encodeArray.push_back(data);

                index += nitems;
                curNum = iCurNum;

                break;
            }

        } /* End for selector ... */

    } /* End while index < n */
}
std::vector<uint32_t > simple9_decode(std::vector<uint32_t >& vec){
    std::vector<uint32_t> ans;
    uint32_t lastElement = 0;
    for (auto selector : vec) {
        int32_t typeSelector = selector & SELECTOR_MASK;
        uint32_t shift = selectors[typeSelector].nbits;
        int32_t countOfElements = selectors[typeSelector].nitems;
        selector = selector >> SELECTOR_BITS;
        uint32_t element;

        for (int i = 0; i < countOfElements; ++i) {
            element = (selector & binInDec[typeSelector].decItem);
            if (element) {
                if(lastElement != 0) {
                    lastElement += element;
                    ans.push_back(lastElement);
                }
                else {
                    lastElement = element;
                    ans.push_back(element);
                }
            }
            selector = selector >> shift;
        }
    }
    return ans;
}