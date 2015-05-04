//
//  bitset.cpp
//  fdb2
//
//  Created by Святослав Фельдшеров on 13.04.15.
//  Copyright (c) 2015 Святослав Фельдшеров. All rights reserved.
//

#include "bitset.h"


Bitset::Bitset(int n) : base(n, '\0') {
    this->from_bytes(n, base.c_str());
}

const char * Bitset::as_bytes() {
    return base.c_str();
}

void Bitset::from_bytes(int sz, const char *src) {
    base.clear();
    base.append(src, sz);
}

void Bitset::resize(int n) {
    base.resize(n, '\0');
}

size_t Bitset::num_blocks() {
    return base.size();
}

size_t Bitset::size() {
    return base.size() * 8;
}

bool Bitset::get(int pos) {
    return ((base[pos / 8] >> (pos % 8)) & 1);
}

void Bitset::set(int pos, int val) {
    assert(val == 1 || val == 0);
    if (get(pos) != val) {
        base[pos / 8] = (base[pos / 8] ^ (1 << (pos % 8)));
    }
}