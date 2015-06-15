//
//  filesystem.cpp
//  fdb2
//
//  Created by Святослав Фельдшеров on 12.04.15.
//  Copyright (c) 2015 Святослав Фельдшеров. All rights reserved.
//

#include "filesystem.h"

FileSystemApi::FileSystemApi(const std::string &path) {
    if (!boost::filesystem::exists(path)) {
        std::ofstream f(path);
    }
    file.open(path);
    file.setf(std::ios::binary);
    file.setf(std::ios::unitbuf);
    
    ccache_size = 0;
}

void FileSystemApi::open(const std::string &path) {
    assert(!file.is_open());
    if (!boost::filesystem::exists(path)) {
        std::ofstream f(path);
    }
    file.open(path);
    file.setf(std::ios::binary);
    file.setf(std::ios::unitbuf);
    
    ccache_size = 0;
}

void FileSystemApi::read_meta(DBC &conf) {
    assert(file.is_open());
    file.seekg(0, std::ios_base::beg);
    file.read((char *) &conf, sizeof(DBC));
}

void FileSystemApi::write_meta(DBC &conf) {
    assert(file.is_open());
    file.seekp(0, std::ios_base::beg);
    file.write((char *) &conf, sizeof(DBC));
}

inline int FileSystemApi::get_bitset_offset(DBC &conf) {
    return sizeof(DBC);
}

inline int FileSystemApi::get_bitset_size(DBC &conf) {
    return (int)(conf.db_size / conf.page_size + 7) / 8;
}

inline int FileSystemApi::get_page_offset(DBC &conf, Page &pg) {
    return get_bitset_offset(conf) + get_bitset_size(conf) + (int)conf.page_size * pg.get_page_num();
}


void FileSystemApi::write_bitset(DBC &conf, Bitset &b) {
    assert(file.is_open());
    assert(file.good());
    file.seekp(get_bitset_offset(conf), std::ios_base::beg);
    file.write(b.as_bytes(), b.num_blocks());
    file.seekg(get_bitset_offset(conf), std::ios_base::beg);
    char *buff = new char[get_bitset_size(conf)];
    file.read(buff, get_bitset_size(conf));
    delete[] buff;
}

void FileSystemApi::read_bitset(DBC &conf, Bitset &b) {
    assert(file.good());
    file.seekg(get_bitset_offset(conf), std::ios_base::beg);
    char *buff = new char[get_bitset_size(conf)];
    file.read(buff, get_bitset_size(conf));
    b.from_bytes(get_bitset_size(conf), buff);
    delete[] buff;
}

void FileSystemApi::write_page(DBC &conf, Page &pg) {
    push_to_cache(conf, pg);
}

void FileSystemApi::push_to_cache(DBC &conf, Page &pg) {
    if (cached.count(pg.get_page_num())) {
        del_from_cache(conf, pg);
    }
    cached.insert(pg.get_page_num());
    lru.push_front(pg);
    ccache_size += pg.num_bytes();
    
    balance_cache(conf);
    return;
}

void FileSystemApi::del_from_cache(DBC &conf, Page &pg) {
    cached.erase(pg.get_page_num());
    for (std::list<Page>::iterator it = lru.begin(); it != lru.end(); ++it) {
        if (it->get_page_num() == pg.get_page_num()) {
            ccache_size -= it->num_bytes();
            lru.erase(it);
            return;
        }
    }
}

void FileSystemApi::balance_cache(DBC &conf) {
    if (ccache_size <= conf.cache_size) {
        return;
    }
    
    while (ccache_size > conf.cache_size) {
        //std::cerr << lru.back().get_page_num() << std::endl;
        ccache_size -= lru.back().num_bytes();
        cached.erase(lru.back().get_page_num());
        flush_page(conf, lru.back());
        lru.pop_back();
    }
    return;
}

void FileSystemApi::read_page(DBC &conf, Page &pg) {
    //std::cerr << "read_page: "  << pg.get_page_num() << std::endl;
    if (cached.count(pg.get_page_num())) {
        get_from_cache(conf, pg);
        return;
    }
    fetch(conf, pg);
    return;
}

void FileSystemApi::fetch(DBC &conf, Page &pg) {
    //std::cerr << "fetch: "  << pg.get_page_num() << std::endl;
    if (cached.count(pg.get_page_num())) {
        del_from_cache(conf, pg);
    }
    read_page_from_disk(conf, pg);
    cached.insert(pg.get_page_num());
    lru.push_front(pg);
    ccache_size += pg.num_bytes();
    balance_cache(conf);
    return;
}

void FileSystemApi::get_from_cache(DBC &conf, Page &pg) {
    assert(cached.count(pg.get_page_num()));
    for (std::list<Page>::iterator it = lru.begin(); it != lru.end(); ++it) {
        if (it->get_page_num() == pg.get_page_num()) {
            pg = *it;
            return;
        }
    }
}

void FileSystemApi::flush_page(DBC &conf, Page &pg) {
    assert(file.good());
    file.seekp(get_page_offset(conf, pg), std::ios_base::beg);
    assert(pg.num_bytes() <= conf.page_size);
    file.write(pg.as_bytes((int)conf.page_size), conf.page_size);
}

void FileSystemApi::read_page_from_disk(DBC &conf, Page &pg) {
    assert(file.is_open());
    file.seekg(get_page_offset(conf, pg), std::ios_base::beg);
    char *buff = new char[conf.page_size];
    file.read(buff, conf.page_size);
    pg.from_bytes(buff);
    delete[] buff;
}

void FileSystemApi::sync(DBC &conf) {
    for (std::list<Page>::iterator it = lru.begin(); it != lru.end(); ++it) {
        flush_page(conf, *it);
    }
    return;
}


