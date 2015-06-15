//
//  log.cpp
//  fdb2
//
//  Created by Святослав Фельдшеров on 21.05.15.
//  Copyright (c) 2015 Святослав Фельдшеров. All rights reserved.
//

#include "log.h"


Log::Log(const char *pth, DBC _conf): conf(_conf), c_lsn(0), cpos(0), log_path(pth) {
    log_path += "_log";
    if (!boost::filesystem::exists(log_path)) {
        std::ofstream f(log_path);
    }
    file.open(log_path.c_str());
    file.setf(std::ios::binary);
    file.setf(std::ios::unitbuf);
    
    file.seekp(0, std::ios::end);
    cpos = file.tellp();
    
    scan_log();
    
    char *cp_lsn = (char *)&c_lsn;
    if (!offsets.empty()) {
        file.seekp(offsets.back() + sizeof(int), std::ios::beg); //last record + skeep size
        file.read(cp_lsn, sizeof(size_t));
        ++c_lsn;
    }
    std::cerr << "Initial lsn " << c_lsn << std::endl;
}

void Log::scan_log() {
    int csize;
    char *cp_csize = (char *)&csize;
    off_t cf = 0;
    file.seekg(0, std::ios::beg);
    
    while (cf < cpos) {
        offsets.push_back(cf);
        file.read(cp_csize, sizeof(int));
        file.seekg(csize - sizeof(int), std::ios::cur);
        cf = file.tellg();
    }
}

void Log::append_page(Page &pg) {
    std::string record;
    int c_size = pg.num_bytes() + 2 * sizeof(int) + sizeof(size_t); // pagesize + lsn (size_t) + size of record(int) + operation(int)
    int c_op = (int)Operation::write;
    record.append((char *) &c_size, sizeof(int));
    record.append((char *) &c_lsn, sizeof(size_t));
    pg.get_llsn() = c_lsn++;
    
    record.append((char *) &c_op, sizeof(int));
    
    int pg_size = pg.num_bytes();
    record.append(pg.as_bytes(pg_size), pg_size);
    
    file.seekp(cpos, std::ios::beg);
    offsets.push_back(file.tellp());
    file.write(record.c_str(), c_size);
    cpos = offsets.back() + c_size;
}

void Log::append_commit() {
    std::string record;
    int c_size = 2 * sizeof(int) + sizeof(size_t); //lsn (size_t) + size of record(int) + operation(int)
    
    int c_op = (int)Operation::commit;
    record.append((char *) &c_size, sizeof(int));
    record.append((char *) &c_lsn, sizeof(size_t));
    ++c_lsn;
    record.append((char *) &c_op, sizeof(int));
    
    file.seekp(cpos, std::ios::beg);
    offsets.push_back(file.tellp());
    file.write(record.c_str(), c_size);
    cpos = offsets.back() + c_size;
}

void Log::append_check_point() {
    std::string record;
    int c_size = 2 * sizeof(int) + sizeof(size_t); //lsn (size_t) + size of record(int) + operation(int)
    
    int c_op = (int)Operation::check_point;
    record.append((char *) &c_size, sizeof(int));
    record.append((char *) &c_lsn, sizeof(size_t));
    ++c_lsn;
    record.append((char *) &c_op, sizeof(int));
    
    file.seekp(cpos, std::ios::beg);
    offsets.push_back(file.tellp());
    file.write(record.c_str(), c_size);
    cpos = offsets.back() + c_size;
}

void Log::append_alloc_page(int pg) {
    std::string record;
    int c_size = 3 * sizeof(int) + sizeof(size_t); //lsn (size_t) + size of record(int) + operation(int)
    
    int c_op = (int)Operation::alloc_page;
    record.append((char *) &c_size, sizeof(int));
    record.append((char *) &c_lsn, sizeof(size_t));
    ++c_lsn;
    record.append((char *) &c_op, sizeof(int));
    record.append((char *) &pg, sizeof(int));
    
    
    file.seekp(cpos, std::ios::beg);
    offsets.push_back(file.tellp());
    file.write(record.c_str(), c_size);
    cpos = offsets.back() + c_size;
}

void Log::append_free_page(int pg) {
    std::string record;
    int c_size = 3 * sizeof(int) + sizeof(size_t); //lsn (size_t) + size of record(int) + operation(int)
    
    int c_op = (int)Operation::free_page;
    record.append((char *) &c_size, sizeof(int));
    record.append((char *) &c_lsn, sizeof(size_t));
    ++c_lsn;
    record.append((char *) &c_op, sizeof(int));
    record.append((char *) &pg, sizeof(int));
    
    
    file.seekp(cpos, std::ios::beg);
    offsets.push_back(file.tellp());
    file.write(record.c_str(), c_size);
    cpos = offsets.back() + c_size;
}

void Log::get_record(Record &rec) {
    int csize, opr;
    size_t lsn;
    int metasize = 2 * sizeof(int) + sizeof(size_t);
    
    //std::cerr << "before: " << csize << std::endl;
    char *cp = (char *)&csize;
    file.read(cp, sizeof(int));
    rec.size = csize;
    //std::cerr << "after: " << csize << std::endl;
    
    cp = (char *)&lsn;
    file.read(cp, sizeof(size_t));
    rec.lsn = lsn;
    
    cp = (char *)&opr;
    file.read(cp, sizeof(int));
    rec.opr = (Operation) opr;
    
    if (rec.opr == Operation::write) {
        char *buff = new char[csize];
        file.read(buff, csize - metasize);
        rec.pg.from_bytes(buff);
        delete[] buff;
    }
    
    if (rec.opr == Operation::alloc_page || rec.opr == Operation::free_page) {
        cp = (char *)&rec.pgn;
        file.read(cp, sizeof(int));
    }
}

size_t Log::count_records() {
    return offsets.size();
}

void Log::set_rec_to(size_t i) {
    assert(0 <= i && i < (int)offsets.size());
    file.seekg(offsets[i]);
    //std::cerr << offsets[i] << std::endl;
    file.seekp(offsets[i]);
}

void Log::set_eof_to_rec(size_t i) {
    assert(0 <= i < (ssize_t)offsets.size() - 1);
    cpos = offsets[i + 1];
    offsets.resize(i + 1);
    boost::filesystem::resize_file(log_path, cpos);
}


