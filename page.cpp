//
//  page.cpp
//  fdb2
//
//  Created by Святослав Фельдшеров on 13.04.15.
//  Copyright (c) 2015 Святослав Фельдшеров. All rights reserved.
//

#include "page.h"


Page::Page() {
    page_num = 0;
    is_list_ = 0;
}

Page::Page(const char *src) {
    from_bytes(src);
}


void Page::from_bytes(const char *src) {
    ptrs.clear();
    keys.clear();
    values.clear();
    
    size_t *sssrc = (size_t *) src;
    llsn = *sssrc;
    ++sssrc;
    src = (char *) sssrc;
    
    bool *bsrc = ((bool *) src);
    is_list_ = *bsrc;
    ++bsrc;
    int *isrc = (int*) bsrc;
    page_num = *isrc;
    ++isrc;
    int sz = *isrc;
    ++isrc;
    char *csrc = (char *)isrc;
    
    //std::cerr << "Прочитали константы" << std::endl;
    
    for (int i = 0; i < sz; ++i) {
        isrc = (int *)csrc;
        int k_s = *isrc;
        ++isrc;
        csrc = (char *)isrc;
        keys.push_back(std::string(csrc, k_s));
        csrc += k_s;
    }
    
    //std::cerr << "Прочитали ключи" << std::endl;
    
    if (!is_list_) {
        isrc = (int *)csrc;
        for (int i = 0; i < sz; ++i) {
            ptrs.push_back(*isrc);
            ++isrc;
        }
        csrc = (char *)isrc;
    }
    
    //std::cerr << "Прочитали указатели" << std::endl;
    
    if (is_list_) {
        for (int i = 0; i < sz; ++i) {
            isrc = (int *)csrc;
            int v_s = *isrc;
            ++isrc;
            csrc = (char *)isrc;
            values.push_back(std::string(csrc, v_s));
            csrc += v_s;
        }
    }
    //std::cerr << "Прочитали значения" << std::endl;
    
}

const char* Page::as_bytes(int len) {
    outp_buff.clear();
    outp_buff.append((char *) &llsn, sizeof(size_t));
    outp_buff.append((char *) &is_list_, sizeof(bool));
    outp_buff.append((char *) &page_num, sizeof(int));
    int sz = (int)keys.size();
    outp_buff.append((char *)&sz, sizeof(int));
    for (int i = 0; i < (int)keys.size(); ++i) {
        int cs = (int)keys[i].size();
        outp_buff.append((char*) &cs, sizeof(int));
        outp_buff.append(keys[i].begin(), keys[i].end());
    }
    for (int i = 0; i < (int)ptrs.size(); ++i) {
        outp_buff.append((char *) &ptrs[i], sizeof(int));
    }
    for (int i = 0; i < (int)values.size(); ++i) {
        int cs = (int)values[i].size();
        outp_buff.append((char*) &cs, sizeof(int));
        outp_buff.append(values[i].begin(), values[i].end());
    }
    outp_buff.resize(std::max(len, (int)outp_buff.size()), '\0');
    return outp_buff.c_str();
}


std::string& Page::get_key(int i) {
    return keys[i];
}

std::string& Page::get_value(int i) {
    return values[i];
}

int& Page::get_ptr(int i) {
    return ptrs[i];
}

bool& Page::is_list() {
    return is_list_;
}

int& Page::get_page_num() {
    return page_num;
}

size_t& Page::get_llsn() {
    return llsn;
}

int Page::num_bytes() {
    int ans = sizeof(is_list_) + sizeof(int) + sizeof(int) + sizeof(llsn); //is_list_ + page_num + sz + llsn
    for (auto s: keys) {
        ans += s.size() + sizeof(int); // key size + value
    }
    
    for (auto s: values) {
        ans += s.size() + sizeof(int); //value size + value
    }
    
    ans += sizeof(int) * ptrs.size(); //ptrs
    
    return ans;
}


int Page::keys_size() {
    return (int)keys.size();
}

int Page::values_size() {
    return (int)values.size();
}

int Page::ptrs_size() {
    return (int)ptrs.size();
}

