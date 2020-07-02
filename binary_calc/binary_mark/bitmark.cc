#include "bitmark.h"
#include <assert.h>
#include <memory.h>
#include <iostream>
using namespace std;

#define DIVICE_8_BIT 3                      // 右移3位, 即除以8
#define BYTE_BIT (1<<DIVICE_8_BIT)          // 

CBitMark::CBitMark(size_t capacity) {
    assert(capacity && "capacity must > 0");
    size_t bytes = (capacity >> DIVICE_8_BIT);
    if (capacity % BYTE_BIT) bytes++;
    data = (unsigned char *)malloc(sizeof(unsigned char)*bytes);
    memset(data, 0, bytes);
    bsize = bytes;
}

CBitMark::~CBitMark() {
    free(data);
}

void CBitMark::Extend(size_t capacity) {
    assert(capacity && "capacity must > 0");
    size_t nsize = (capacity >> DIVICE_8_BIT); 
    if (capacity % BYTE_BIT) nsize++;
    if (nsize <= bsize) {
        cout << "no change" << endl;
        return;
    }
    data = (unsigned char *)realloc(data, nsize);
    bsize = nsize;
}

void CBitMark::Mark(size_t slot) {
    size_t bidx = (slot >> DIVICE_8_BIT);
    slot = slot % BYTE_BIT;
    if (bidx >= bsize) {
        cout << "out of range" << endl;
        return;
    }
    data[bidx] |= 1<<slot;
}

void CBitMark::Unmark(size_t slot) {
    size_t bidx = (slot >> DIVICE_8_BIT);
    slot = slot % BYTE_BIT;
    if (bidx >= bsize) {
        cout << "out of range" << endl;
        return;
    }
    data[bidx] &= ~(1<<slot);
}

void CBitMark::Display() {
    for (size_t i=0; i<bsize; i++) {
        unsigned char d = data[i];
        for (size_t j=0; j<BYTE_BIT; j++) {
            cout << (d & 1);
            d >>= 1;
        }
        cout << " ";
    }
    cout << endl;
}

vector<size_t> CBitMark::GetMarkList() {
    vector<size_t> result;

    for (size_t i=0; i<bsize; i++) {
        unsigned char d = data[i];
        for (size_t j=0; j<BYTE_BIT; j++) {
            if (d & 1<<j) result.push_back(i*BYTE_BIT+j);
        }
    }

    return result;
}