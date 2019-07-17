
#include "TSimple9.h"

void TSimple9_encode(std::vector<uint32_t> &array, std::vector<uint32_t> &encodeArray) {

    uint32_t index;
    uint32_t selector;
    uint32_t data;
    uint32_t shift;

    size_t nitems;
    size_t i;
    size_t arraySize = array.size();


    index = 0;


    while (index < arraySize) {
        for (selector = 0; selector < NSELECTORS; selector++) { // choose selector
            data = selector; // control bits
            shift = SELECTOR_BITS; // start 4 bits
            nitems = 0; // count of elements in one uint_32

            for (i = index; i < arraySize; ++i) { // filling selector

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

                encodeArray.push_back(data);
                index += nitems;

                break;
            }

        } /* End for selector ... */

    } /* End while index < n */
}

void TSimple9_decode(std::vector<uint32_t> &vec, std::vector<uint32_t > &ans) {

    uint32_t lastElement = 0;
    uint32_t element;

    for (auto selector : vec) { //take selector
        uint32_t typeSelector = selector & SELECTOR_MASK;

        uint32_t  countOfElements = selectors[typeSelector].nitems; // count of elements in one selector

        uint32_t shift = selectors[typeSelector].nbits;

        uint32_t mask = (1u << selectors[typeSelector].nbits) - 1;

        selector = selector >> SELECTOR_BITS; // skip control bits

        for (int i = 0; i < countOfElements; ++i) {
            element = (selector & mask);
            if (element) {
                if (lastElement != 0) {
                    // remove deltas
                    lastElement += element;
                    ans.push_back(lastElement);
                } else {
                    lastElement = element;
                    ans.push_back(element);
                }
            }
            selector = selector >> shift;
        }
    }

}