#ifndef _MYDB_H_
#define _MYDB_H_

#include <cstdlib>
#include <algorithm>
#include <vector>
#include <map>

#include "database.h"
#include "types.h"

extern "C" {

    /* check `man dbopen` */

    /* Open DB if it exists, otherwise create DB */
    struct DB *dbcreate(const char *file, struct DBC *conf);

    int db_close(struct DB *db);
    int db_delete(struct DB *, void *, size_t);
    int db_select(struct DB *, void *, size_t, void **, size_t *);
    int db_insert(struct DB *, void *, size_t, void * , size_t  );
    
    int api_close(struct DB* db);
    int api_select(struct DB *db, struct DBT *key, struct DBT *data);
    int api_insert(struct DB *db, struct DBT *key, struct DBT *data);
    
    /* Sync cached pages with disk */
    int db_sync(const struct DB *db);
}
#endif