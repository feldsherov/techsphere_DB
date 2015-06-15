//
//  log.test.cpp
//  fdb2
//
//  Created by Святослав Фельдшеров on 15.06.15.
//  Copyright (c) 2015 Святослав Фельдшеров. All rights reserved.
//

#include <stdio.h>
#include <iostream>

#include "../log.h"

void create_page_1(std::string &pg) {
    bool is_list = 0;
    int page_num = 0;
    int sz = 2;
    size_t lsn = 5;
    std::vector<std::string> keys(sz), values(sz);
    std::vector<int> ptrs({1, 2, 3});
    keys[0] = "key1";
    keys[1] = "key2";
    values[0] = "val1";
    values[1] = "val2";
    
    pg.clear();
    pg.append((char*) &lsn, sizeof(size_t));
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

void write_log(Log &lg) {
    std::cout << "Count of records: " << lg.count_records() << std::endl;
    
    Log::Record rc;
    for (int i = 0; i < lg.count_records(); ++i) {
        lg.set_rec_to(i);
        lg.get_record(rc);
        std::cout << "=======================start record " << i << "==============" << std::endl;
        std::cout << "Rec: " << i << "; rec_type :" << (int) rc.opr << " rec_size :" << rc.size << std::endl;
        
        if (rc.opr == Log::Operation::write) {
            Page &pg1 = rc.pg;
            std::string spg2;
            std::cout << "lsn: " << pg1.get_llsn() << std::endl;
            std::cout << "is_list: " << pg1.is_list() << std::endl;
            std::cout << "page_num: " << pg1.get_page_num() << std::endl;
            std::cout << "sz: " << pg1.keys_size() << std::endl;
            
            std::cout << "-----------------------" << std::endl;
            std::cout << "KEYS:" << std::endl;
            for (int i = 0; i < (int)pg1.keys_size(); ++i) {
                std::cout << pg1.get_key(i) << std::endl;
            }
            
            
            std::cout << "-----------------------" << std::endl;
            std::cout << "PTRS:" << std::endl;
            for (int i = 0; i < (int)pg1.ptrs_size(); ++i) {
                std::cout << pg1.get_ptr(i) << " ";
            }
            std::cout << std::endl;
            
            std::cout << "-----------------------" << std::endl;
            std::cout << "VALUES:" << std::endl;
            for (int i = 0; i < (int)pg1.values_size(); ++i) {
                std::cout << pg1.get_value(i) << std::endl;
            }
            
            std::cout << "-----------------------" << std::endl;
            
            spg2.append(pg1.as_bytes(pg1.num_bytes()), pg1.num_bytes());
            
            std::cout << "pg1.num_bytes(): " << pg1.num_bytes() << std::endl;
        }
        std::cout << "======================end record " << i << "===============" << std::endl;
        
    }
}

int main () {
    DBC conf;
    std::string spg1;
    Page pg;
    Log lg("file", conf);
    create_page_1(spg1);
    pg.from_bytes(spg1.c_str());
    
    lg.append_page(pg);
    lg.append_commit();
    lg.append_page(pg);
    lg.append_commit();
    lg.append_check_point();
    
    write_log(lg);
    
    lg.set_eof_to_rec(1);
    lg.append_page(pg);
    lg.append_commit();
    
    write_log(lg);
    
    return 0;
}
