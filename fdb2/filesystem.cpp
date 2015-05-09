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

int FileSystemApi::get_bitset_offset(DBC &conf) {
    return sizeof(DBC);
}

int FileSystemApi::get_bitset_size(DBC &conf) {
    return (int)(conf.db_size / conf.page_size + 7) / 8;
}

int FileSystemApi::get_page_offset(DBC &conf, Page &pg) {
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
    std::cerr << "!" << (int)buff[0] << "!" << std::endl;
    b.from_bytes(get_bitset_size(conf), buff);
    delete[] buff;
}

void FileSystemApi::write_page(DBC &conf, Page &pg) {
    assert(file.good());
    file.seekp(get_page_offset(conf, pg), std::ios_base::beg);
    assert(pg.num_bytes() <= conf.page_size);
    file.write(pg.as_bytes((int)conf.page_size), conf.page_size);
}

void FileSystemApi::read_page(DBC &conf, Page &pg) {
    assert(file.is_open());
    file.seekg(get_page_offset(conf, pg), std::ios_base::beg);
    char *buff = new char[conf.page_size];
    file.read(buff, conf.page_size);
    pg.from_bytes(buff);
    delete[] buff;
}





