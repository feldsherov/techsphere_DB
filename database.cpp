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

int DataBase::sync() {
    fapi.sync(conf);
    return 0;
}

void DataBase::dump_tree(int dpth, int cp) {
    fapi.sync(conf);
    path[dpth].get_page_num() = cp;
    fapi.read_page_from_disk(conf, path[dpth]);
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
}

void DataBase::check_tree(int dpth, int cp) {
    path[dpth].get_page_num() = cp;
    read_page(path[dpth]);
    Page &cpage = path[dpth];
    int lst = -1;
    for (int i = 0; i < (int)cpage.keys.size(); ++i) {
        if (!cpage.is_list()) {
            check_tree(dpth + 1, cpage.ptrs[i]);
            assert(lst == -1 || (path[dpth + 1].is_list() == lst));
            lst = path[dpth + 1].is_list();
        }
    }
}



int DataBase::search(const std::string &key, std::string &val) {
    return search_rec(0, 0, key, val);
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
    while (cp < (int)pg.keys_size() - 1 && key > pg.get_key(cp)) cp++;
    return cp;
}


void DataBase::split_child(Page &root, Page &left, Page &n_right) {
    n_right.get_page_num() = alloc_page();
    n_right.ptrs.clear();
    n_right.keys.clear();
    n_right.values.clear();
    
    //std::cerr << "Split: " << left.get_page_num() << " " << n_right.get_page_num() << std::endl;
    
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
    root.keys.insert(root.keys.begin() + cp, left.keys[cp_split - 1]);
    
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

void DataBase::merge_children(Page &root, Page &left, Page &right) {
    int cp = 0;
    while (cp < (int)root.ptrs.size() && root.ptrs[cp] != left.get_page_num()) ++cp;
    
    assert(cp + 1 < (int)root.ptrs.size());
    assert(right.get_page_num() == root.ptrs[cp + 1]);
    
    root.ptrs.erase(root.ptrs.begin() + cp + 1);
    root.keys.erase(root.keys.begin() + cp);
    
    left.keys.insert(left.keys.end(), right.keys.begin(), right.keys.end());
    left.ptrs.insert(left.ptrs.end(), right.ptrs.begin(), right.ptrs.end());
    left.values.insert(left.values.end(), right.values.begin(), right.values.end());
    
    right.keys.clear();
    right.ptrs.clear();
    right.values.clear();
    
    assert(right.is_list() == left.is_list());
    
    free_page(right.page_num);
}

void DataBase::balance_children(Page &root, Page &left, Page &right) {
    merge_children(root, left, right);
    
    if (left.num_bytes() >= conf.page_size) {
        split_child(root, left, right);
    }
}

int DataBase::search_rec(int dpth, int pg, const std::string &key, std::string &val) {
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
        return search_rec(dpth + 1, cpage.get_ptr(cp), key, val);
    }
}

bool DataBase::insert_deb(const std::string &key, const std::string &val) {
    //std::cerr << "========DUMP=======" << std::endl;
    //dump_tree(0, 0);
    //std::cerr << "========DUMP_END=======" << std::endl;
    std::string val1;
    search(key, val1);
    std::cerr << "Search: " << key << std::endl;
    std::cerr << "Correct: " << val << " Found: " << val1 << std::endl;
    if (val != val1) {
        std::cerr << "========DUMP=======" << std::endl;
        dump_tree(0, 0);
        std::cerr << "========DUMP_END=======" << std::endl;
    }
    return (val == val1);
}

int DataBase::insert(const std::string &key, const std::string &val) {
    int ret_code;
    ret_code = insert_safe(key, val);
    //assert(insert_deb(key, val));

    return ret_code;
}

int DataBase::insert_safe(const std::string &key, const std::string &val) {
    int ret_code = insert_rec(0, 0, key, val);
    
    if (path[0].num_bytes() > conf.page_size) {
        //std::cerr << "Разбиваем корень" << std::endl;
        Page n_root, n_right;
        n_root.get_page_num() = 0;
        path[0].get_page_num() = alloc_page();
        
        n_root.keys.push_back(path[0].keys.back());
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

bool DataBase::delete_deb(const std::string &key) {
    std::string val;
    std::cerr << "Deleted: " << key << std::endl;
    std::cerr << "========DUMP=======" << std::endl;
    dump_tree(0, 0);
    std::cerr << "========DUMP_END=======" << std::endl;
    search(key, val);
    return (val == "");
}

int DataBase::_delete(const std::string &key) {
    int ret_code = delete_safe(key);
    

    //assert(delete_deb(key));
    return ret_code;
}

int DataBase::delete_safe(const std::string &key) {
    int ret_code = delete_rec(0, 0,key);
    
    if (!path[0].is_list() && path[0].keys.size() == 1) {
        //std::cerr << "Поднимаем корень корень" << std::endl;
        free_page(path[1].get_page_num());
        path[1].get_page_num() = 0;
        write_page(path[1]);
    }
    else if (path[0].num_bytes() > conf.page_size) {
        //std::cerr << "Разделяем корень" << std::endl;
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

int DataBase::delete_rec(int dpth, int pg, const std::string &key) {
    path[dpth].get_page_num() = pg;
    read_page(path[dpth]);
    Page &cpage = path[dpth];
    
    int cp = find_place(cpage, key);
    
    if (cpage.is_list()) {
        //std::cerr << "Удаление из листа" << std::endl;
        if (cp < cpage.keys_size() && cpage.get_key(cp) == key) {
            cpage.values.erase(cpage.values.begin() + cp);
            cpage.keys.erase(cpage.keys.begin() + cp);
            return 0;
        }
        return -1;
    }
    else {
        //std::cerr << "Обрабатываем внутреннюю вершину" << std::endl;
        int ret_code = delete_rec(dpth + 1, path[dpth].ptrs[cp], key);
        if (cp < path[dpth].keys.size()) {
            path[dpth].keys[cp] = path[dpth + 1].keys.back();
        }
        
        if (path[dpth + 1].num_bytes() < conf.page_size / 3) {
            //std::cerr << "Балансируем внутреннюю вершину" << std::endl;
            //std::cerr << dpth << " " << cp << std::endl;
            Page extra_page;
            if (cp + 1 < cpage.ptrs.size()) {
                extra_page.get_page_num() = cpage.ptrs[cp + 1];
                read_page(extra_page);
                balance_children(path[dpth], path[dpth + 1], extra_page);
            }
            else {
                extra_page.get_page_num() = cpage.ptrs[cp - 1];
                read_page(extra_page);
                balance_children(path[dpth], extra_page, path[dpth + 1]);
            }
            if (path[dpth + 1].keys.size() > 0) {
                write_page(path[dpth + 1]);
            }
            if (extra_page.keys.size() > 0) {
                write_page(extra_page);
            }
        }
        else if (path[dpth + 1].num_bytes() > conf.page_size) {
            Page n_right;
            split_child(path[dpth], path[dpth + 1], n_right);
            write_page(path[dpth + 1]);
            write_page(n_right);
        }
        else {
            write_page(path[dpth + 1]);
        }
        return ret_code;
    }
}
