//
//  page.h
//  fdb2
//
//  Created by Святослав Фельдшеров on 13.04.15.
//  Copyright (c) 2015 Святослав Фельдшеров. All rights reserved.
//

#ifndef __fdb2__page__
#define __fdb2__page__

#include <vector>
#include <string>
#include <cassert>
#include <iostream>

class DataBase;

/* 
 формат страницы:
 is_list | page_num | sz (количество ключей) | ключи | указатели | [значения, если is_list == 1]
*/

class Page {
    bool is_list_;
    size_t llsn;
    int page_num;
    std::string outp_buff;
    std::vector<std::string> keys, values;
    std::vector<int> ptrs;
    
public:
    Page();
    Page(const char *src);
    
    void from_bytes(const char *src);
    const char* as_bytes(int len);
    
    std::string& get_key(int i);
    std::string& get_value(int i);
    int& get_ptr(int i);
    bool& is_list();
    int& get_page_num();
    size_t& get_llsn();
    
    int num_bytes();
    int keys_size();
    int values_size();
    int ptrs_size();
    
    friend DataBase;
    /*
     хочу зафрендить, потому что в операциях с b-tree эти векторы keys, values, ptrs будут сильно перестраиваться
     В будущем разумно реализовать подходящее API
     */
};

#endif /* defined(__fdb2__page__) */
