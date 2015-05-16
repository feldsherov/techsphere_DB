#include "mydb.h"

namespace  {
    std::map<int, DataBase*> opened;
    int cp = 0;
}

extern "C" {

    struct DB *dbcreate(const char *file, struct DBC *conf) {
        DB* dbnew = new DB;
        DataBase *db = new DataBase(file, *conf);
        dbnew->db_id = cp;
        dbnew->insert = api_insert;
        dbnew->select = api_select;
        dbnew->close = api_close;
        dbnew->_delete = api_delete;
        opened[cp++] = db;
        return dbnew;
    }
    
    int api_close(struct DB* db) {
        DataBase *cdb = opened[db->db_id];
        cdb->sync();
        opened.erase(db->db_id);
        delete cdb;
        return 0;
    }
    
    int api_select(struct DB *db, struct DBT *key, struct DBT *data) {
        std::string k((char *)key->data, key->size), v;
        DataBase *cdb = opened[db->db_id];
        if (!cdb->search(k, v)) {
            data->data = (void *)new char[v.size()];
            std::copy(v.c_str(), v.c_str() + v.size(), (char *) data->data);
            data->size = v.size();
            return 0;
        }
        else {
            data->size = 0;
            data->data = NULL;
            return -1;
        }
    }
    
    int api_insert(struct DB *db, struct DBT *key, struct DBT *data) {
        std::string k((char *)key->data, key->size), v((char *)data->data, data->size);
        DataBase *cdb = opened[db->db_id];
        return cdb->insert(k, v);
    }

    int api_delete(struct DB *db, struct DBT *key) {
        std::string k((char *)key->data, key->size);
        DataBase *cdb = opened[db->db_id];
        return cdb->_delete(k);
    }
    
    int db_close(struct DB *db) {
        return db->close(db);
    }

    int db_delete(struct DB *db, void *key, size_t key_len) {
        struct DBT keyt = {
            .data = key,
            .size = key_len
        };
        return db->_delete(db, &keyt);
    }

    int db_select(struct DB *db, void *key, size_t key_len,
        void **val, size_t *val_len) {
        struct DBT keyt = {
            .data = key,
            .size = key_len
        };
        struct DBT valt = {0, 0};
        int rc = db->select(db, &keyt, &valt);
        *val = valt.data;
        *val_len = valt.size;
        return rc;
    }

    int db_insert(struct DB *db, void *key, size_t key_len,
           void *val, size_t val_len) {
        struct DBT keyt = {
            .data = key,
            .size = key_len
        };
        struct DBT valt = {
            .data = val,
            .size = val_len
        };
        return db->insert(db, &keyt, &valt);
    }
    
    int db_flush(const struct DB *db) {
        DataBase *cdb = opened[db->db_id];
        cdb->sync();
        return  0;
    }

}
