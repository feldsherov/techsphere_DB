//
//  filesystem.h
//  fdb2
//
//  Created by Святослав Фельдшеров on 12.04.15.
//  Copyright (c) 2015 Святослав Фельдшеров. All rights reserved.
//

#ifndef __fdb2__filesystem__
#define __fdb2__filesystem__

#include <string>
#include <unistd.h>
#include <fstream>
#include <cassert>
#include <list>
#include <set>

#include "types.h"
#include "bitset.h"
#include "page.h"

#include <boost/filesystem.hpp>

class FileSystemApi {
private:
    std::fstream file;
    
    std::list<Page> lru;
    std::set<int> cached;
    ssize_t ccache_size;
    
    inline int get_bitset_offset(DBC &conf);
    inline int get_page_offset(DBC &conf, Page &pg);
    inline int get_bitset_size(DBC &conf);
    
    void get_from_cache(DBC &conf, Page &pg);
    void fetch(DBC &conf, Page &pg);
    void push_to_cache(DBC &conf, Page &pg);
    void del_from_cache(DBC &conf, Page &pg);
    void balance_cache(DBC &conf);
    
public:
    FileSystemApi(const std::string &path);
    void read_meta(DBC &conf);
    void write_meta(DBC &conf);
    void read_bitset(DBC &conf, Bitset &b);
    void write_bitset(DBC &conf, Bitset &b);
    void read_page(DBC &conf, Page &pg);
    void write_page(DBC &conf, Page &pg);
    
    void flush_page(DBC &conf, Page &pg);
    void read_page_from_disk(DBC &conf, Page &pg);
    
    void sync(DBC &conf);
};

#endif /* defined(__fdb2__filesystem__) */
