#include <iostream>
#include "mydb.h"

const int DEFAULT_DB_SIZE = 536870912u; /*512 MB*/
const int DEFAULT_PAGE_SIZE = 4096u; /*4 KB*/
const int DEFAULT_CACHE_SIZE = 16777216; /*16 MB*/


int main(int argc, const char * argv[]) {
    // insert code here...
    DBC conf = {.page_size = DEFAULT_PAGE_SIZE / 8, .db_size = DEFAULT_DB_SIZE, .cache_size = DEFAULT_CACHE_SIZE};
    DB *dbnew = dbcreate("mydb", &conf);
    /*db_insert(dbnew, (void *)"Key1", 5, (void *)"val1val1val1val1val1val1val1val1val1val1val1val1val1val1val1val1", 64);
    db_insert(dbnew, (void *)"key2", 5, (void *)"val2val2val2val2val2val2val2val2val2val2val2val2val2val2val2val2", 64);
    db_insert(dbnew, (void *)"Key3", 5, (void *)"val3val3val3val3val3val3val3val3val3val3val3val3val3val3val3val3", 64);
    db_insert(dbnew, (void *)"key4", 5, (void *)"val4val4val4val4val4val4val4val4val4val4val4val4val4val4val4val4", 64);
    db_insert(dbnew, (void *)"Key5", 5, (void *)"val5val5val5val5val5val5val5val5val5val5val5val5val5val5val5val5", 64);
    
    db_insert(dbnew, (void *)"Flers-de-l'Orne", 16, (void *)"3DfaB9004aBAA1dd93f3DfaB9004aBAA1dd93f", 42);
    db_insert(dbnew, (void *)"Karangrumak", 12, (void *)"aE6a5fB03795af1569faE6a5fB03795af1569f", 42);
    db_insert(dbnew, (void *)"Kuninkaanoja", 14, (void *)"6acdD397Ab13b4D361e6acdD397Ab13b4D361e", 42);
    db_insert(dbnew, (void *)"Mala Rakowiza", 14, (void *)"54d288469EE2b6A60D054d288469EE2b6A60D0", 42);
    db_insert(dbnew, (void *)"Mergeh Darshir", 15, (void *)"A282c77939df551F22AA282c77939df551F22A", 42);
    db_insert(dbnew, (void *)"Mount Charles", 14, (void *)"9b6306b8A8F18E3AbbC9b6306b8A8F18E3AbbC", 42);
    db_insert(dbnew, (void *)"Nizhankovichi", 13, (void *)"a4D6e278DedF9D1BCaEa4D6e278DedF9D1BCaE", 42);
    db_insert(dbnew, (void *)"Novoye Sindrovo", 16, (void *)"9Dcc5951EF1EA0ff6e5", 21);
    db_insert(dbnew, (void *)"Rgulo Nahu", 11, (void *)"68D63A1febbbc1cecaC", 21);
    db_insert(dbnew, (void *)"Ugol Tretiy", 12, (void *)"b252eE6FecFd6dcF83f", 21);
    db_insert(dbnew, (void *)"Winninghausen", 14, (void *)"bbAeBb8B7dCBbB0b14D", 21);
    db_insert(dbnew, (void *)"Yerryk-Kata", 12, (void *)"3Ab43464cFBE1Bd77e4", 21);
    
    db_delete(dbnew, (void *)"Flers-de-l'Orne", 16);
    db_delete(dbnew, (void *)"Karangrumak", 12);
    db_delete(dbnew, (void *)"Kuninkaanoja", 14);
    db_delete(dbnew, (void *)"Mala Rakowiza", 14);
    db_delete(dbnew, (void *)"Mergeh Darshir", 15);
    db_delete(dbnew, (void *)"Mount Charles", 14);
    db_delete(dbnew, (void *)"Nizhankovichi", 13);
    db_delete(dbnew, (void *)"Novoye Sindrovo", 16);
    db_delete(dbnew, (void *)"Rgulo Nahu", 11);
    db_delete(dbnew, (void *)"Ugol Tretiy", 12);
    db_delete(dbnew, (void *)"Winninghausen", 14);
    db_delete(dbnew, (void *)"Yerryk-Kata", 12);
    char *buff;
    size_t tp;
    db_select(dbnew, (void *)"Yerryk-Kata", 12, (void **)&buff, &tp);
    std::cerr << buff << " " << tp << std:: endl;*/
    
    db_insert(dbnew, (void *)"Key1aaaaaaaaaaaaaaaaaaaaaa", 25, (void *)"val1val1val1val1val1val1val1val1val1val1val1val1val1val1val1val1", 64);
    db_insert(dbnew, (void *)"Key2aaaaaaaaaaaaaaaaaaaaaa", 25, (void *)"val2val1val1val1val1val1val1val1val1val1val1val1val1val1val1val1", 64);
    db_insert(dbnew, (void *)"Key3aaaaaaaaaaaaaaaaaaaaaa", 25, (void *)"val3val1val1val1val1val1val1val1val1val1val1val1val1val1val1val1", 64);
    db_insert(dbnew, (void *)"Key4aaaaaaaaaaaaaaaaaaaaaa", 25, (void *)"val4val1val1val1val1val1val1val1val1val1val1val1val1val1val1val1", 64);
    db_insert(dbnew, (void *)"Key5aaaaaaaaaaaaaaaaaaaaaa", 25, (void *)"val5val1val1val1val1val1val1val1val1val1val1val1val1val1val1val1", 64);
    db_insert(dbnew, (void *)"Key6aaaaaaaaaaaaaaaaaaaaaa", 25, (void *)"val6val1val1val1val1val1val1val1val1val1val1val1val1val1val1val1", 64);
    db_insert(dbnew, (void *)"Key7aaaaaaaaaaaaaaaaaaaaaa", 25, (void *)"val7val1val1val1val1val1val1val1val1val1val1val1val1val1val1val1", 64);
    db_insert(dbnew, (void *)"Key8aaaaaaaaaaaaaaaaaaaaaa", 25, (void *)"val8val1val1val1val1val1val1val1val1val1val1val1val1val1val1val1", 64);
    db_insert(dbnew, (void *)"Key9aaaaaaaaaaaaaaaaaaaaaa", 25, (void *)"val9val1val1val1val1val1val1val1val1val1val1val1val1val1val1val1", 64);
    db_insert(dbnew, (void *)"Key10aaaaaaaaaaaaaaaaaaaaaa", 25, (void *)"val10val1val1val1val1val1val1val1val1val1val1val1val1val1val1val1", 64);
    db_insert(dbnew, (void *)"Key11aaaaaaaaaaaaaaaaaaaaaa", 25, (void *)"val11val1val1val1val1val1val1val1val1val1val1val1val1val1val1val1", 64);
    db_insert(dbnew, (void *)"Key12aaaaaaaaaaaaaaaaaaaaaa", 25, (void *)"val12val1val1val1val1val1val1val1val1val1val1val1val1val1val1val1", 64);
    db_insert(dbnew, (void *)"Key13aaaaaaaaaaaaaaaaaaaaaa", 25, (void *)"val13val1val1val1val1val1val1val1val1val1val1val1val1val1val1val1", 64);
    db_insert(dbnew, (void *)"Key14aaaaaaaaaaaaaaaaaaaaaa", 25, (void *)"val14val1val1val1val1val1val1val1val1val1val1val1val1val1val1val1", 64);
    db_insert(dbnew, (void *)"Key15aaaaaaaaaaaaaaaaaaaaaa", 25, (void *)"val15val1val1val1val1val1val1val1val1val1val1val1val1val1val1val1", 64);
    db_insert(dbnew, (void *)"Key16aaaaaaaaaaaaaaaaaaaaaa", 25, (void *)"val16val1val1val1val1val1val1val1val1val1val1val1val1val1val1val1", 64);
    db_insert(dbnew, (void *)"Key17aaaaaaaaaaaaaaaaaaaaaa", 25, (void *)"val17val1val1val1val1val1val1val1val1val1val1val1val1val1val1val1", 64);
    db_insert(dbnew, (void *)"Key18aaaaaaaaaaaaaaaaaaaaaa", 25, (void *)"val18val1val1val1val1val1val1val1val1val1val1val1val1val1val1val1", 64);
    db_insert(dbnew, (void *)"Key19aaaaaaaaaaaaaaaaaaaaaa", 25, (void *)"val19val1val1val1val1val1val1val1val1val1val1val1val1val1val1val1", 64);
    db_insert(dbnew, (void *)"Key20aaaaaaaaaaaaaaaaaaaaaa", 25, (void *)"val20val1val1val1val1val1val1val1val1val1val1val1val1val1val1val1", 64);
    db_insert(dbnew, (void *)"Key21aaaaaaaaaaaaaaaaaaaaaa", 25, (void *)"val21val1val1val1val1val1val1val1val1val1val1val1val1val1val1val1", 64);
    db_insert(dbnew, (void *)"Key22aaaaaaaaaaaaaaaaaaaaaa", 25, (void *)"val22val1val1val1val1val1val1val1val1val1val1val1val1val1val1val1", 64);
    db_insert(dbnew, (void *)"Key23aaaaaaaaaaaaaaaaaaaaaa", 25, (void *)"val23val1val1val1val1val1val1val1val1val1val1val1val1val1val1val1", 64);
    db_insert(dbnew, (void *)"Key24aaaaaaaaaaaaaaaaaaaaaa", 25, (void *)"val24val1val1val1val1val1val1val1val1val1val1val1val1val1val1val1", 64);
    db_insert(dbnew, (void *)"Key25aaaaaaaaaaaaaaaaaaaaaa", 25, (void *)"val25val1val1val1val1val1val1val1val1val1val1val1val1val1val1val1", 64);
    db_insert(dbnew, (void *)"Key26aaaaaaaaaaaaaaaaaaaaaa", 25, (void *)"val26val1val1val1val1val1val1val1val1val1val1val1val1val1val1val1", 64);
    db_insert(dbnew, (void *)"Key27aaaaaaaaaaaaaaaaaaaaaa", 25, (void *)"val27val1val1val1val1val1val1val1val1val1val1val1val1val1val1val1", 64);
    db_insert(dbnew, (void *)"Key28aaaaaaaaaaaaaaaaaaaaaa", 25, (void *)"val28val1val1val1val1val1val1val1val1val1val1val1val1val1val1val1", 64);
    db_insert(dbnew, (void *)"Key29aaaaaaaaaaaaaaaaaaaaaa", 25, (void *)"val29val1val1val1val1val1val1val1val1val1val1val1val1val1val1val1", 64);
    db_insert(dbnew, (void *)"Key30aaaaaaaaaaaaaaaaaaaaaa", 25, (void *)"val29val1val1val1val1val1val1val1val1val1val1val1val1val1val1val1", 64);
    db_insert(dbnew, (void *)"Key31aaaaaaaaaaaaaaaaaaaaaa", 25, (void *)"val29val1val1val1val1val1val1val1val1val1val1val1val1val1val1val1", 64);
    db_insert(dbnew, (void *)"Key32aaaaaaaaaaaaaaaaaaaaaa", 25, (void *)"val29val1val1val1val1val1val1val1val1val1val1val1val1val1val1val1", 64);
    db_insert(dbnew, (void *)"Key33aaaaaaaaaaaaaaaaaaaaaa", 25, (void *)"val29val1val1val1val1val1val1val1val1val1val1val1val1val1val1val1", 64);
    db_insert(dbnew, (void *)"Key34aaaaaaaaaaaaaaaaaaaaaa", 25, (void *)"val29val1val1val1val1val1val1val1val1val1val1val1val1val1val1val1", 64);
    db_insert(dbnew, (void *)"Key35aaaaaaaaaaaaaaaaaaaaaa", 25, (void *)"val29val1val1val1val1val1val1val1val1val1val1val1val1val1val1val1", 64);
    db_insert(dbnew, (void *)"Key36aaaaaaaaaaaaaaaaaaaaaa", 25, (void *)"val29val1val1val1val1val1val1val1val1val1val1val1val1val1val1val1", 64);
    db_insert(dbnew, (void *)"Key37aaaaaaaaaaaaaaaaaaaaaa", 25, (void *)"val29val1val1val1val1val1val1val1val1val1val1val1val1val1val1val1", 64);
    db_insert(dbnew, (void *)"Key38aaaaaaaaaaaaaaaaaaaaaa", 25, (void *)"val29val1val1val1val1val1val1val1val1val1val1val1val1val1val1val1", 64);
    db_insert(dbnew, (void *)"Key39aaaaaaaaaaaaaaaaaaaaaa", 25, (void *)"val29val1val1val1val1val1val1val1val1val1val1val1val1val1val1val1", 64);
    db_insert(dbnew, (void *)"Key40aaaaaaaaaaaaaaaaaaaaaa", 25, (void *)"val29val1val1val1val1val1val1val1val1val1val1val1val1val1val1val1", 64);
    db_insert(dbnew, (void *)"Key41aaaaaaaaaaaaaaaaaaaaaa", 25, (void *)"val29val1val1val1val1val1val1val1val1val1val1val1val1val1val1val1", 64);
    db_insert(dbnew, (void *)"Key42aaaaaaaaaaaaaaaaaaaaaa", 25, (void *)"val29val1val1val1val1val1val1val1val1val1val1val1val1val1val1val1", 64);
    db_insert(dbnew, (void *)"Key43aaaaaaaaaaaaaaaaaaaaaa", 25, (void *)"val29val1val1val1val1val1val1val1val1val1val1val1val1val1val1val1", 64);
    db_insert(dbnew, (void *)"Key44aaaaaaaaaaaaaaaaaaaaaa", 25, (void *)"val29val1val1val1val1val1val1val1val1val1val1val1val1val1val1val1", 64);
    db_insert(dbnew, (void *)"Key45aaaaaaaaaaaaaaaaaaaaaa", 25, (void *)"val29val1val1val1val1val1val1val1val1val1val1val1val1val1val1val1", 64);
    db_insert(dbnew, (void *)"Key46aaaaaaaaaaaaaaaaaaaaaa", 25, (void *)"val29val1val1val1val1val1val1val1val1val1val1val1val1val1val1val1", 64);
    db_insert(dbnew, (void *)"Key47aaaaaaaaaaaaaaaaaaaaaa", 25, (void *)"val29val1val1val1val1val1val1val1val1val1val1val1val1val1val1val1", 64);
    db_insert(dbnew, (void *)"Key48aaaaaaaaaaaaaaaaaaaaaa", 25, (void *)"val29val1val1val1val1val1val1val1val1val1val1val1val1val1val1val1", 64);
    db_insert(dbnew, (void *)"Key49aaaaaaaaaaaaaaaaaaaaaa", 25, (void *)"val29val1val1val1val1val1val1val1val1val1val1val1val1val1val1val1", 64);
    db_insert(dbnew, (void *)"Key50aaaaaaaaaaaaaaaaaaaaaa", 25, (void *)"val29val1val1val1val1val1val1val1val1val1val1val1val1val1val1val1", 64);
    db_insert(dbnew, (void *)"Key51aaaaaaaaaaaaaaaaaaaaaa", 25, (void *)"val29val1val1val1val1val1val1val1val1val1val1val1val1val1val1val1", 64);
    db_insert(dbnew, (void *)"Key52aaaaaaaaaaaaaaaaaaaaaa", 25, (void *)"val29val1val1val1val1val1val1val1val1val1val1val1val1val1val1val1", 64);
    db_insert(dbnew, (void *)"Key53aaaaaaaaaaaaaaaaaaaaaa", 25, (void *)"val29val1val1val1val1val1val1val1val1val1val1val1val1val1val1val1", 64);
    db_insert(dbnew, (void *)"Key54aaaaaaaaaaaaaaaaaaaaaa", 25, (void *)"val29val1val1val1val1val1val1val1val1val1val1val1val1val1val1val1", 64);
    db_insert(dbnew, (void *)"Key55aaaaaaaaaaaaaaaaaaaaaa", 25, (void *)"val29val1val1val1val1val1val1val1val1val1val1val1val1val1val1val1", 64);
    db_insert(dbnew, (void *)"Key56aaaaaaaaaaaaaaaaaaaaaa", 25, (void *)"val29val1val1val1val1val1val1val1val1val1val1val1val1val1val1val1", 64);
    db_insert(dbnew, (void *)"Key57aaaaaaaaaaaaaaaaaaaaaa", 25, (void *)"val29val1val1val1val1val1val1val1val1val1val1val1val1val1val1val1", 64);
    db_insert(dbnew, (void *)"Key58aaaaaaaaaaaaaaaaaaaaaa", 25, (void *)"val29val1val1val1val1val1val1val1val1val1val1val1val1val1val1val1", 64);
    db_insert(dbnew, (void *)"Key59aaaaaaaaaaaaaaaaaaaaaa", 25, (void *)"val29val1val1val1val1val1val1val1val1val1val1val1val1val1val1val1", 64);
    db_insert(dbnew, (void *)"Key60aaaaaaaaaaaaaaaaaaaaaa", 25, (void *)"val29val1val1val1val1val1val1val1val1val1val1val1val1val1val1val1", 64);
    db_insert(dbnew, (void *)"Key61aaaaaaaaaaaaaaaaaaaaaa", 25, (void *)"val29val1val1val1val1val1val1val1val1val1val1val1val1val1val1val1", 64);
    db_insert(dbnew, (void *)"Key62aaaaaaaaaaaaaaaaaaaaaa", 25, (void *)"val29val1val1val1val1val1val1val1val1val1val1val1val1val1val1val1", 64);
    db_insert(dbnew, (void *)"Key63aaaaaaaaaaaaaaaaaaaaaa", 25, (void *)"val29val1val1val1val1val1val1val1val1val1val1val1val1val1val1val1", 64);
    db_insert(dbnew, (void *)"Key64aaaaaaaaaaaaaaaaaaaaaa", 25, (void *)"val29val1val1val1val1val1val1val1val1val1val1val1val1val1val1val1", 64);
    db_insert(dbnew, (void *)"Key65aaaaaaaaaaaaaaaaaaaaaa", 25, (void *)"val29val1val1val1val1val1val1val1val1val1val1val1val1val1val1val1", 64);
    db_insert(dbnew, (void *)"Key66aaaaaaaaaaaaaaaaaaaaaa", 25, (void *)"val29val1val1val1val1val1val1val1val1val1val1val1val1val1val1val1", 64);
    db_insert(dbnew, (void *)"Key67aaaaaaaaaaaaaaaaaaaaaa", 25, (void *)"val29val1val1val1val1val1val1val1val1val1val1val1val1val1val1val1", 64);
    db_insert(dbnew, (void *)"Key68aaaaaaaaaaaaaaaaaaaaaa", 25, (void *)"val29val1val1val1val1val1val1val1val1val1val1val1val1val1val1val1", 64);
    db_insert(dbnew, (void *)"Key69aaaaaaaaaaaaaaaaaaaaaa", 25, (void *)"val29val1val1val1val1val1val1val1val1val1val1val1val1val1val1val1", 64);
    db_insert(dbnew, (void *)"Key70aaaaaaaaaaaaaaaaaaaaaa", 25, (void *)"val29val1val1val1val1val1val1val1val1val1val1val1val1val1val1val1", 64);
    db_insert(dbnew, (void *)"Key71aaaaaaaaaaaaaaaaaaaaaa", 25, (void *)"val29val1val1val1val1val1val1val1val1val1val1val1val1val1val1val1", 64);
    db_insert(dbnew, (void *)"Key72aaaaaaaaaaaaaaaaaaaaaa", 25, (void *)"val29val1val1val1val1val1val1val1val1val1val1val1val1val1val1val1", 64);
    db_insert(dbnew, (void *)"Key73aaaaaaaaaaaaaaaaaaaaaa", 25, (void *)"val29val1val1val1val1val1val1val1val1val1val1val1val1val1val1val1", 64);
    db_insert(dbnew, (void *)"Key74aaaaaaaaaaaaaaaaaaaaaa", 25, (void *)"val29val1val1val1val1val1val1val1val1val1val1val1val1val1val1val1", 64);
    db_insert(dbnew, (void *)"Key75aaaaaaaaaaaaaaaaaaaaaa", 25, (void *)"val29val1val1val1val1val1val1val1val1val1val1val1val1val1val1val1", 64);
    db_insert(dbnew, (void *)"Key76aaaaaaaaaaaaaaaaaaaaaa", 25, (void *)"val29val1val1val1val1val1val1val1val1val1val1val1val1val1val1val1", 64);
    db_insert(dbnew, (void *)"Key77aaaaaaaaaaaaaaaaaaaaaa", 25, (void *)"val29val1val1val1val1val1val1val1val1val1val1val1val1val1val1val1", 64);
    db_insert(dbnew, (void *)"Key78aaaaaaaaaaaaaaaaaaaaaa", 25, (void *)"val29val1val1val1val1val1val1val1val1val1val1val1val1val1val1val1", 64);
    db_insert(dbnew, (void *)"Key79aaaaaaaaaaaaaaaaaaaaaa", 25, (void *)"val29val1val1val1val1val1val1val1val1val1val1val1val1val1val1val1", 64);
    db_insert(dbnew, (void *)"Key80aaaaaaaaaaaaaaaaaaaaaa", 25, (void *)"val29val1val1val1val1val1val1val1val1val1val1val1val1val1val1val1", 64);
    db_insert(dbnew, (void *)"Key81aaaaaaaaaaaaaaaaaaaaaa", 25, (void *)"val29val1val1val1val1val1val1val1val1val1val1val1val1val1val1val1", 64);
    db_insert(dbnew, (void *)"Key82aaaaaaaaaaaaaaaaaaaaaa", 25, (void *)"val29val1val1val1val1val1val1val1val1val1val1val1val1val1val1val1", 64);
    db_insert(dbnew, (void *)"Key83aaaaaaaaaaaaaaaaaaaaaa", 25, (void *)"val29val1val1val1val1val1val1val1val1val1val1val1val1val1val1val1", 64);
    db_insert(dbnew, (void *)"Key84aaaaaaaaaaaaaaaaaaaaaa", 25, (void *)"val29val1val1val1val1val1val1val1val1val1val1val1val1val1val1val1", 64);
    db_insert(dbnew, (void *)"Key85aaaaaaaaaaaaaaaaaaaaaa", 25, (void *)"val29val1val1val1val1val1val1val1val1val1val1val1val1val1val1val1", 64);
    db_insert(dbnew, (void *)"Key86aaaaaaaaaaaaaaaaaaaaaa", 25, (void *)"val29val1val1val1val1val1val1val1val1val1val1val1val1val1val1val1", 64);
    db_insert(dbnew, (void *)"Key87aaaaaaaaaaaaaaaaaaaaaa", 25, (void *)"val29val1val1val1val1val1val1val1val1val1val1val1val1val1val1val1", 64);
    db_insert(dbnew, (void *)"Key88aaaaaaaaaaaaaaaaaaaaaa", 25, (void *)"val29val1val1val1val1val1val1val1val1val1val1val1val1val1val1val1", 64);
    db_insert(dbnew, (void *)"Key89aaaaaaaaaaaaaaaaaaaaaa", 25, (void *)"val29val1val1val1val1val1val1val1val1val1val1val1val1val1val1val1", 64);
    db_insert(dbnew, (void *)"Key90aaaaaaaaaaaaaaaaaaaaaa", 25, (void *)"val29val1val1val1val1val1val1val1val1val1val1val1val1val1val1val1", 64);
    db_insert(dbnew, (void *)"Key91aaaaaaaaaaaaaaaaaaaaaa", 25, (void *)"val29val1val1val1val1val1val1val1val1val1val1val1val1val1val1val1", 64);
    db_insert(dbnew, (void *)"Key92aaaaaaaaaaaaaaaaaaaaaa", 25, (void *)"val29val1val1val1val1val1val1val1val1val1val1val1val1val1val1val1", 64);
    db_insert(dbnew, (void *)"Key93aaaaaaaaaaaaaaaaaaaaaa", 25, (void *)"val29val1val1val1val1val1val1val1val1val1val1val1val1val1val1val1", 64);
    db_insert(dbnew, (void *)"Key94aaaaaaaaaaaaaaaaaaaaaa", 25, (void *)"val29val1val1val1val1val1val1val1val1val1val1val1val1val1val1val1", 64);
    
    
    
    db_delete(dbnew, (void *)"Key17aaaaaaaaaaaaaaaaaaaaaa", 25);
    db_delete(dbnew, (void *)"Key18aaaaaaaaaaaaaaaaaaaaaa", 25);
    db_delete(dbnew, (void *)"Key19aaaaaaaaaaaaaaaaaaaaaa", 25);
    db_delete(dbnew, (void *)"Key20aaaaaaaaaaaaaaaaaaaaaa", 25);
    db_delete(dbnew, (void *)"Key21aaaaaaaaaaaaaaaaaaaaaa", 25);
    db_delete(dbnew, (void *)"Key22aaaaaaaaaaaaaaaaaaaaaa", 25);
    db_delete(dbnew, (void *)"Key23aaaaaaaaaaaaaaaaaaaaaa", 25);
    db_delete(dbnew, (void *)"Key24aaaaaaaaaaaaaaaaaaaaaa", 25);
    db_delete(dbnew, (void *)"Key25aaaaaaaaaaaaaaaaaaaaaa", 25);
    db_delete(dbnew, (void *)"Key26aaaaaaaaaaaaaaaaaaaaaa", 25);
    db_delete(dbnew, (void *)"Key27aaaaaaaaaaaaaaaaaaaaaa", 25);
    db_delete(dbnew, (void *)"Key28aaaaaaaaaaaaaaaaaaaaaa", 25);
    db_delete(dbnew, (void *)"Key29aaaaaaaaaaaaaaaaaaaaaa", 25);
    db_delete(dbnew, (void *)"Key30aaaaaaaaaaaaaaaaaaaaaa", 25);
    db_delete(dbnew, (void *)"Key31aaaaaaaaaaaaaaaaaaaaaa", 25);
    db_delete(dbnew, (void *)"Key32aaaaaaaaaaaaaaaaaaaaaa", 25);
    db_delete(dbnew, (void *)"Key33aaaaaaaaaaaaaaaaaaaaaa", 25);
    db_delete(dbnew, (void *)"Key34aaaaaaaaaaaaaaaaaaaaaa", 25);
    db_delete(dbnew, (void *)"Key35aaaaaaaaaaaaaaaaaaaaaa", 25);
    db_delete(dbnew, (void *)"Key36aaaaaaaaaaaaaaaaaaaaaa", 25);
    db_delete(dbnew, (void *)"Key37aaaaaaaaaaaaaaaaaaaaaa", 25);
    db_delete(dbnew, (void *)"Key38aaaaaaaaaaaaaaaaaaaaaa", 25);
    db_delete(dbnew, (void *)"Key39aaaaaaaaaaaaaaaaaaaaaa", 25);

    return 0;
}
