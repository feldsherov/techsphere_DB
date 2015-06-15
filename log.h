//
//  log.h
//  fdb2
//
//  Created by Святослав Фельдшеров on 21.05.15.
//  Copyright (c) 2015 Святослав Фельдшеров. All rights reserved.
//

#ifndef __fdb2__log__
#define __fdb2__log__

#include <stdio.h>
#include <fstream>
#include <string>
#include <vector>

#include "types.h"
#include "page.h"

#include <boost/filesystem.hpp>

class Log{
private:
    std::vector<off_t> offsets;
    std::fstream file;
    std::string log_path;
    size_t c_lsn;
    off_t cpos;
    DBC conf;
    
    void scan_log();
public:
    class Record;
    enum Operation {write, commit, check_point, alloc_page, free_page};
    
    Log(const char *pth, DBC _conf);
    
    void append_page(Page &pg);
    void append_commit();
    void append_check_point();
    void append_alloc_page(int pg);
    void append_free_page(int pg);
    void get_record(Record &rec);
    
    size_t count_records();
    void set_rec_to(size_t i);
    void set_eof_to_rec(size_t i);
};

struct Log::Record{
    Log::Operation opr;
    size_t lsn;
    int size;
    int pgn;
    Page pg;
};

#endif /* defined(__fdb2__log__) */
