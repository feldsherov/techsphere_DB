//
//  filesistem.test.cpp
//  fdb2
//
//  Created by Святослав Фельдшеров on 02.05.15.
//  Copyright (c) 2015 Святослав Фельдшеров. All rights reserved.
//

#include <stdio.h>
#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "../page.h"
#include "../filesystem.h"
#include "../bitset.h"
#include "../types.h"

const int DEFAULT_DB_SIZE = 536870912u; /*512 MB*/
const int DEFAULT_PAGE_SIZE = 4096u; /*4 KB*/
const int DEFAULT_CACHE_SIZE = 16777216; /*16 MB*/


void create_page_1(std::string &pg, FileSystemApi &api) {
    bool is_list = 0;
    int page_num = 2;
    int sz = 2;
    std::vector<std::string> keys(sz), values(sz);
    std::vector<int> ptrs({1, 2, 3});
    keys[0] = "key1";
    keys[1] = "key2";
    values[0] = "val1";
    values[1] = "val2";
    pg.clear();
    pg.append((char*) &is_list, sizeof(bool));
    pg.append((char*) &page_num, sizeof(int));
    pg.append((char*) &sz, sizeof(int));
    for (int i = 0; i < sz; ++i) {
        int cs = keys[i].size();
        pg.append((char *) &cs, sizeof(int));
        pg.append(keys[i].c_str(), keys[i].size());
    }

    for (int i = 0; i < sz; ++i) {
        pg.append((char*) &ptrs[i], sizeof(int));
    }
    
    /*for (int i = 0; i < sz; ++i) {
        int cs = values[i].size();
        pg.append((char *) &cs, sizeof(int));
        pg.append(values[i].c_str(), values[i].size());
    }*/
}

int main() {
    FileSystemApi api("testfile");
    std::cout << "===========DBC===========" << std::endl;
    
    DBC conf = {DEFAULT_DB_SIZE, DEFAULT_PAGE_SIZE, DEFAULT_CACHE_SIZE}, conf1;
    
    api.write_meta(conf);
    api.read_meta(conf1);
    
    std::cout << "conf, conf1" << std::endl;
    std::cout << "db_size: " << conf.db_size << " " << conf1.db_size << std::endl;
    std::cout << "page_size : " << conf.page_size << " " << conf1.page_size << std::endl;
    std::cout << "cache_size : " << conf.cache_size << " " << conf1.cache_size << std::endl;
    
    std::cout << "===========page===========" << std::endl;
    std::string spg1, spg2;
    create_page_1(spg1, api);
    std::cout << "SPG1 created" << std::endl;
    Page pg1(spg1.c_str()), pg2;
    pg2.get_page_num() = 2;
    api.write_page(conf, pg1);
    api.read_page(conf, pg2);
    std::cout << "is_list: " << pg2.is_list() << std::endl;
    std::cout << "page_num: " << pg2.get_page_num() << std::endl;
    std::cout << "sz: " << pg2.keys_size() << std::endl;
    
    std::cout << "-----------------------" << std::endl;
    std::cout << "KEYS:" << std::endl;
    for (int i = 0; i < (int)pg2.keys_size(); ++i) {
        std::cout << pg2.get_key(i) << std::endl;
    }
    
    std::cout << "-----------------------" << std::endl;
    std::cout << "PTRS:" << std::endl;
    for (int i = 0; i < (int)pg2.ptrs_size(); ++i) {
        std::cout << pg2.get_ptr(i) << " ";
    }
    std::cout << std::endl;
    
    std::cout << "-----------------------" << std::endl;
    std::cout << "VALUES:" << std::endl;
    for (int i = 0; i < (int)pg2.values_size(); ++i) {
        std::cout << pg2.get_value(i) << std::endl;
    }
    
    std::cout << "-----------------------" << std::endl;

    spg2.append(pg2.as_bytes(pg2.num_bytes()), pg2.num_bytes());
    
    std::cout << "pg1.num_bytes(), pg2.num_bytes(): " << pg1.num_bytes() << ", " << pg2.num_bytes() << std::endl;
    std::cout << "spg1 == spg2: " << (spg1 == spg2) << std::endl;
    
    for (int i = 0; i < (int)spg1.size(); ++i) {
        std::cerr << (int)spg1[i] << " ";
    }
    std::cerr << std::endl;
    
    for (int i = 0; i < (int)spg2.size(); ++i) {
        std::cerr << (int)spg2[i] << " ";
    }
    std::cerr << std::endl;
    
    
    std::cout << "===========bitset===========" << std::endl;
    Bitset b((int)(conf.db_size / conf.page_size + 7) / 8), b1(0);

    b.set(2, 1);
    b.set(3, 1);
    b.set(3, 0);
    std::cerr << "n.num_blocks(): " << b.num_blocks() << std::endl;
    api.write_bitset(conf, b);
    api.read_bitset(conf, b1);
    
    std::cout << "b.num_blocks() == b1.num_blocks(): " << (b.num_blocks() == b1.num_blocks()) << std::endl;
    
    std::cout << "b:" << std::endl;
    for (int i = 0; i < 100; ++i) {
        std::cout << b.get(i);
    }
    std::cout << std::endl;
    
    
    std::cout << "b1:" << std::endl;
    for (int i = 0; i < 100; ++i) {
        std::cout << b1.get(i);
    }
    std::cout << std::endl;
    return 0;
}
