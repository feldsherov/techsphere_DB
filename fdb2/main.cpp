#include <iostream>
#include "mydb.h"

const int DEFAULT_DB_SIZE = 536870912u; /*512 MB*/
const int DEFAULT_PAGE_SIZE = 4096u; /*4 KB*/
const int DEFAULT_CACHE_SIZE = 16777216; /*16 MB*/


int main(int argc, const char * argv[]) {
    // insert code here...
    DBC conf = {.page_size = DEFAULT_PAGE_SIZE, .db_size = DEFAULT_DB_SIZE, .cache_size = DEFAULT_CACHE_SIZE};
    DB *dbnew = dbcreate("mydb", &conf);
    db_insert(dbnew, (void *)"Key1", 5, (void *)"val1", 5 );
    db_insert(dbnew, (void *)"key2", 5, (void *)"val2", 5);
    db_insert(dbnew, (void *)"Key3", 5, (void *)"val3", 5);
    db_insert(dbnew, (void *)"key4", 5, (void *)"val4", 5);
    db_insert(dbnew, (void *)"Key5", 5, (void *)"val5", 5);
    
    db_insert(dbnew, (void *)"Flers-de-l'Orne", 16, (void *)"3DfaB9004aBAA1dd93f", 21);
    db_insert(dbnew, (void *)"Karangrumak", 12, (void *)"aE6a5fB03795af1569f", 21);
    db_insert(dbnew, (void *)"Kuninkaanoja", 14, (void *)"6acdD397Ab13b4D361e", 21);
    db_insert(dbnew, (void *)"Mala Rakowiza", 14, (void *)"54d288469EE2b6A60D0", 21);
    db_insert(dbnew, (void *)"Mergeh Darshir", 15, (void *)"A282c77939df551F22A", 21);
    db_insert(dbnew, (void *)"Mount Charles", 14, (void *)"9b6306b8A8F18E3AbbC", 21);
    db_insert(dbnew, (void *)"Nizhankovichi", 13, (void *)"a4D6e278DedF9D1BCaE", 21);
    db_insert(dbnew, (void *)"Novoye Sindrovo", 16, (void *)"9Dcc5951EF1EA0ff6e5", 21);
    db_insert(dbnew, (void *)"Rgulo Nahu", 11, (void *)"68D63A1febbbc1cecaC", 21);
    db_insert(dbnew, (void *)"Ugol Tretiy", 12, (void *)"b252eE6FecFd6dcF83f", 21);
    db_insert(dbnew, (void *)"Winninghausen", 14, (void *)"bbAeBb8B7dCBbB0b14D", 21);
    db_insert(dbnew, (void *)"Yerryk-Kata", 12, (void *)"3Ab43464cFBE1Bd77e4", 21);
    return 0;
}
