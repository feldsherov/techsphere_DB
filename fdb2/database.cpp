//
//  database.cpp
//  fdb2
//
//  Created by Святослав Фельдшеров on 13.04.15.
//  Copyright (c) 2015 Святослав Фельдшеров. All rights reserved.
//

#include "database.h"

DataBase::DataBase(const char *pth, DBC _conf) : fapi(pth), b(0) {
    if (boost::filesystem::exists(pth)) {
        conf = _conf;
        b.resize(bitset_size(conf));
        b.set(0, 1);
        write_meta(conf);
        write_bitset(b);
        Page pg;
        pg.is_list() = 1;
        pg.get_page_num() = 0;
        write_page(pg);
    }
    else {
        read_meta(conf);
        read_bitset(b);
    }
}

int DataBase::bitset_size(DBC _conf) {
    return ((int)conf.db_size / conf.page_size + 7) / 8;
}

void DataBase::write_meta(DBC _conf) {
    fapi.write_meta(_conf);
}

void DataBase::read_meta(DBC &_conf) {
    fapi.read_meta(conf);
}

void DataBase::write_page(Page &pg) {
    fapi.write_page(conf, pg);
}

void DataBase::read_page(Page &pg) {
    fapi.read_page(conf, pg);
}

void DataBase::write_bitset(Bitset &b) {
    fapi.write_bitset(conf, b);
}

void DataBase::read_bitset(Bitset &b) {
    fapi.read_bitset(conf, b);
}

void DataBase::dump_tree(int dpth, int cp) {
    path[dpth].get_page_num() = cp;
    read_page(path[dpth]);
    Page &cpage = path[dpth];
    for (int j = 0; j < dpth; ++j) {
        std::cerr << '\t';
    }
    std::cerr << cp << " " << cpage.is_list() << std::endl;
    for (int i = 0; i < (int)cpage.keys.size(); ++i) {
        for (int j = 0; j < dpth; ++j) {
            std::cerr << '\t';
        }
        std::cerr << dpth << " " << cp << " " << cpage.keys[i] << " ";
        if (cpage.is_list()) {
            std::cerr << cpage.values[i] << std::endl;
        }
        else {
            std::cerr << std::endl;
            dump_tree(dpth + 1, cpage.ptrs[i]);
        }
    }
    if (!cpage.is_list() && cpage.keys.size() > 0) {
        dump_tree(dpth + 1, cpage.ptrs[cpage.keys.size()]);
    }
}


int DataBase::search(const std::string &key, std::string &val) {
    return rec_search(0, 0, key, val);
}

int DataBase::alloc_page() {
    int to = bitset_size(conf);
    for (int i = 0; i < to; ++i) {
        if (!b.get(i)) {
            b.set(i, 1);
            write_bitset(b);
            return i;
        }
    }
    assert(false);
    return -1;
}

int DataBase::free_page(int pg) {
    b.set(pg, 0);
    write_bitset(b);
    return 0;
}

int DataBase::find_place(Page &pg, const std::string &key) {
    int cp = 0;
    while (cp < pg.keys_size() && key > pg.get_key(cp)) cp++;
    return cp;
}


void DataBase::split_child(Page &root, Page &left, Page &n_right) {
    n_right.get_page_num() = alloc_page();
    
    int cp = 0;
    while (cp < (int)root.ptrs.size() && root.ptrs[cp] != left.get_page_num()) ++cp;
    assert(cp < (int)root.ptrs.size());
    
    int size_curr = left.num_bytes();
    
    int cp_split = 0, size_used = 0;
    while (cp_split < left.keys.size() && size_used < size_curr / 2) {
        size_used += left.keys[cp_split].size() + sizeof(int);
        size_used += sizeof(int);
        if (left.is_list()) {
            size_used += left.values[cp_split].size() + sizeof(int);
        }
        
        cp_split++;
    }
    
    //std::cerr << "Разбивка " << cp_split << std::endl;
    
    root.ptrs.insert(root.ptrs.begin() + cp + 1, n_right.get_page_num());
    if (cp == root.keys.size()) {
        root.keys.push_back(left.keys[cp_split - 1]);
    }
    else {
        root.keys.insert(root.keys.begin() + cp, left.keys[cp_split - 1]);
    }
    
    /*std::cerr << "ROOT KEYS:" << std::endl;
    for (int i = 0; i < (int)root.keys.size(); ++i) {
        std::cerr << root.keys[i] << " ";
    }
    std::cerr << std::endl;

    
    std::cerr << "ROOT PTRS:" << std::endl;
    for (int i = 0; i < (int)root.ptrs.size(); ++i) {
        std::cerr << root.ptrs[i] << " ";
    }
    std::cerr << std::endl;
    
    std::cerr << "ROOT VALS:" << std::endl;
    for (int i = 0; i < (int)root.values.size(); ++i) {
        std::cerr << root.values[i] << " ";
    }
    std::cerr << std::endl;*/

    
    /*балансируем количество ключей между левым и правым сыном*/
    n_right.is_list() = left.is_list();
    
    n_right.keys.insert(n_right.keys.begin(), left.keys.begin() + cp_split, left.keys.end());
    left.keys.resize(cp_split);
    
    if (!n_right.is_list()) {
        n_right.ptrs.insert(n_right.ptrs.begin(), left.ptrs.begin() + cp_split, left.ptrs.end());
        left.ptrs.resize(cp_split);
    }
    
    if (n_right.is_list()) {
        n_right.values.insert(n_right.values.begin(), left.values.begin() + cp_split, left.values.end());
        left.values.resize(cp_split);
    }
}

int DataBase::rec_search(int dpth, int pg, const std::string &key, std::string &val) {
    path[dpth].get_page_num() = pg;
    read_page(path[dpth]);
    Page &cpage = path[dpth];

    int cp = find_place(cpage, key);
    
    if (cpage.is_list()) {
        if (cp < cpage.keys_size() && cpage.get_key(cp) == key) {
            val = cpage.get_value(cp);
            return 0;
        }
        return -1;
    }
    else {
        return rec_search(dpth + 1, cpage.get_ptr(cp), key, val);
    }
}

bool DataBase::insert_deb(const std::string &key, const std::string &val) {
    //std::cerr << "========DUMP=======" << std::endl;
    //dump_tree(0, 0);
    //std::cerr << "========DUMP_END=======" << std::endl;
    std::string val1;
    search(key, val1);
    //std::cerr << "Search: " << key << std::endl;
    //std::cerr << "Correct: " << val << " Found: " << val1 << std::endl;
    return (val == val1);
}

int DataBase::insert(const std::string &key, const std::string &val) {
    int ret_code = insert_safe(key, val);
    assert(insert_deb(key, val));
    
    return ret_code;
}

int DataBase::insert_safe(const std::string &key, const std::string &val) {
    int ret_code = insert_rec(0, 0, key, val);
    
    if (path[0].num_bytes() > conf.page_size) {
        //std::cerr << "Разбиваем корень" << std::endl;
        Page n_root, n_right;
        n_root.get_page_num() = 0;
        path[0].get_page_num() = alloc_page();
        
        n_root.ptrs.push_back(path[0].page_num);
        
        split_child(n_root, path[0], n_right);
        write_page(n_root);
        write_page(path[0]);
        write_page(n_right);
    }
    else {
        write_page(path[0]);
    }
    return ret_code;
}

int DataBase::insert_rec(int dpth, int pg, const std::string &key, const std::string &val) {
    path[dpth].get_page_num() = pg;
    read_page(path[dpth]);
    Page &cpage = path[dpth];

    int cp = find_place(cpage, key);
    
    if (cpage.is_list()) {
        //std::cerr << "Вставка в лист " << dpth << " " << pg << std::endl;
        if (cp < cpage.keys_size() && cpage.get_key(cp) == key) {
            //std::cerr << "Повторяющийся ключ." << std::endl;
            cpage.get_value(cp) = val;
            return 0;
        }
        //std::cerr << "Уникальный ключ" << std::endl;
        //std::cerr << cp << std::endl;
        cpage.keys.insert(cpage.keys.begin() + cp, key);
        cpage.values.insert(cpage.values.begin() + cp, val);
    }
    else {
        //std::cerr << "Вставка НЕ в лист " << dpth << " " << pg << std::endl;
        insert_rec(dpth + 1, cpage.get_ptr(cp), key, val);
        
        if (cp < path[dpth].keys.size()) {
            path[dpth].keys[cp] = path[dpth + 1].keys.back();
        }
        
        if (path[dpth + 1].num_bytes() <= conf.page_size) {
            write_page(path[dpth + 1]);
        }
        else {
            //std::cerr << "Разбиваем не корневую страничку." << std::endl;
            Page n_right;
            split_child(path[dpth], path[dpth + 1], n_right);
            write_page(path[dpth + 1]);
            write_page(n_right);
        }
    }
    return 0;
}

