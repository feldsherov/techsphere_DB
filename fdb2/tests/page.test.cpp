#include <iostream>
#include <fstream>
#include <vector>
#include <string>

#include "../page.h"

void create_page_1(std::string &pg) {
    bool is_list = 1;
    int page_num = 0;
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

    for (int i = 0; i < sz + 1; ++i) {
       pg.append((char*) &ptrs[i], sizeof(int));
    }

    for (int i = 0; i < sz; ++i) {
        int cs = values[i].size();
        pg.append((char *) &cs, sizeof(int));
        pg.append(values[i].c_str(), values[i].size());
    }
}

int main() {
    std::string spg1, spg2;
    create_page_1(spg1);
    std::cout << "SPG1 created" << std::endl;
    Page pg1(spg1.c_str());
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
    for (int i = 0; i < (int)pg1.keys_size() + 1; ++i) {
        std::cout << pg1.get_ptr(i) << " ";
    }
    std::cout << std::endl;
    
    std::cout << "-----------------------" << std::endl;
    std::cout << "VALUES:" << std::endl;
    for (int i = 0; i < (int)pg1.keys_size(); ++i) {
        std::cout << pg1.get_value(i) << std::endl;
    }
  
    std::cout << "-----------------------" << std::endl;
    
    spg2.append(pg1.as_bytes(), pg1.num_bytes());
    
    std::cout << "spg1.size(), pg1.num_bytes(): " << spg1.size() << ", " << pg1.num_bytes() << std::endl;
    std::cout << "spg1 == spg2: " << (spg1 == spg2) << std::endl;
    return 0;
}
