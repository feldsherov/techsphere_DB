//
//  database.h
//  fdb2
//
//  Created by Святослав Фельдшеров on 13.04.15.
//  Copyright (c) 2015 Святослав Фельдшеров. All rights reserved.
//

#ifndef __fdb2__database__
#define __fdb2__database__

#include <boost/filesystem.hpp>

#include "types.h"
#include "bitset.h"
#include "page.h"
#include "filesystem.h"

class DataBase {
    static const int MAX_PATH_LEN = 32;
    static const int DEFAULT_DB_SIZE = 536870912u; /*512 MB*/
    static const int MIN_DB_SIZE = 1048576u; /*1 MB*/
    static const int DEFAULT_PAGE_SIZE = 4096u; /*4 KB*/
    static const int MIN_PAGE_SIZE = 512u; /*0.5 KB*/
    static const int DEFAULT_CACHE_SIZE = 16777216; /*16 MB*/
    DBC conf;
    Bitset b;
    Page path[MAX_PATH_LEN];
    FileSystemApi fapi;
    
    int bitset_size(DBC _conf);
    
    void write_meta(DBC _conf);
    void read_meta(DBC &_conf);
    void write_page(Page &pg);
    void read_page(Page &pg);
    void write_bitset(Bitset &b);
    void read_bitset(Bitset &b);
    
    void dump_tree(int dpth, int cp);
    
    int alloc_page();
    int free_page(int pg);
    
    void split_child(Page &root, Page &left, Page &n_right);
    int find_place(Page &pg, const std::string &key);
    
    int rec_search(int dpth, int pg, const std::string &key, std::string &val);
    
    bool insert_deb(const std::string &key, const std::string &val);
    
    int insert_safe(const std::string &key, const std::string &val);
    /* вставляет ключ в дерево учитывая возможность разделения корня*/
    
    int insert_rec(int dpth, int pg, const std::string &key, const std::string &val);
    /*insert_rec вставляет ключ в дерево, но не записывает корень в stable storage и возможно оставляет переполненным*/
public:
    DataBase(const char *pth, DBC conf);
    int search(const std::string &key, std::string &val);
    int insert(const std::string &key, const std::string &val);
    
};

#endif /* defined(__fdb2__database__) */
