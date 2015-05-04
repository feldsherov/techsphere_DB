//
//  bitset.h
//  fdb2
//
//  Created by Святослав Фельдшеров on 13.04.15.
//  Copyright (c) 2015 Святослав Фельдшеров. All rights reserved.
//

#ifndef __fdb2__bitset__
#define __fdb2__bitset__

#include <string>
#include <cassert>

class Bitset {
    std::string base;
public:
    Bitset(int n);
    const char* as_bytes();
    void from_bytes(int sz, const char *src);

    void resize(int n);
    
    size_t num_blocks();
    size_t size();
    bool get(int pos);
    void set(int pos, int val);
};



#endif /* defined(__fdb2__bitset__) */
