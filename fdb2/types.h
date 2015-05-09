//
//  types.h
//  fdb2
//
//  Created by Святослав Фельдшеров on 13.04.15.
//  Copyright (c) 2015 Святослав Фельдшеров. All rights reserved.
//

#ifndef fdb2_types_h
#define fdb2_types_h

struct DBT {
    void  *data;
    size_t size;
};

struct DB {
    /* Public API */
    /* Returns 0 on OK, -1 on Error */
    int (*close)(struct DB *db);
    int (*_delete)(struct DB *db, struct DBT *key);
    int (*insert)(struct DB *db, struct DBT *key, struct DBT *data);
    /* * * * * * * * * * * * * *
     * Returns malloc'ed data into 'struct DBT *data'.
     * Caller must free data->data. 'struct DBT *data' must be alloced in
     * caller.
     * * * * * * * * * * * * * */
    int (*select)(struct DB *db, struct DBT *key, struct DBT *data);
    /* Sync cached pages with disk
     * */
    int (*sync)(struct DB *db);
    /* For future uses - sync cached pages with disk
     * int (*sync)(const struct DB *db)
     * */
    /* Private API */
    int db_id;
}; /* Need for supporting multiple backends (HASH/BTREE) */

struct DBC {
    /* Maximum on-disk file size
     * 512MB by default
     * */
    size_t db_size;
    /* Page (node/data) size
     * 4KB by default
     * */
    size_t page_size;
    /* Maximum cached memory size
     * 16MB by default
     * */
    size_t cache_size;
};

#endif
