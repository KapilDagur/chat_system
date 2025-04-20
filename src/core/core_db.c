#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#include "core_db.h"

int open_db(sqlite3 **db, const char *filename) {
    if (!db || !filename) return SQLITE_ERROR;
    return sqlite3_open(filename, db);
}

void close_db(sqlite3 *db) {
    if (db) sqlite3_close(db);
}

int exec_sql(sqlite3 *db, const char *sql,
             int (*callback)(void*, int, char**, char**),
             void *arg) {
    if (!db || !sql) return SQLITE_ERROR;

    char *errmsg = NULL;
    int rc = sqlite3_exec(db, sql, callback, arg, &errmsg);
    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", errmsg);
        sqlite3_free(errmsg);
    }
    return rc;
}

int prepare_stmt(sqlite3 *db, sqlite3_stmt **stmt, const char *sql) {
    if (!db || !stmt || !sql) return SQLITE_ERROR;
    return sqlite3_prepare_v2(db, sql, -1, stmt, NULL);
}

int bind_text(sqlite3_stmt *stmt, int index, const char *text) {
    if (!stmt) return SQLITE_ERROR;
    return text ? 
        sqlite3_bind_text(stmt, index, text, -1, SQLITE_TRANSIENT) :
        sqlite3_bind_null(stmt, index);
}

int bind_int(sqlite3_stmt *stmt, int index, int value) {
    if (!stmt) return SQLITE_ERROR;
    return sqlite3_bind_int(stmt, index, value);
}

int bind_int64(sqlite3_stmt *stmt, int index, sqlite3_int64 value) {
    if (!stmt) return SQLITE_ERROR;
    return sqlite3_bind_int64(stmt, index, value);
}

int bind_double(sqlite3_stmt *stmt, int index, double value) {
    if (!stmt) return SQLITE_ERROR;
    return sqlite3_bind_double(stmt, index, value);
}

int bind_null(sqlite3_stmt *stmt, int index) {
    if (!stmt) return SQLITE_ERROR;
    return sqlite3_bind_null(stmt, index);
}

int step_stmt(sqlite3_stmt *stmt) {
    if (!stmt) return SQLITE_ERROR;
    return sqlite3_step(stmt);
}

void finalize_stmt(sqlite3_stmt **stmt) {
    if (stmt && *stmt) {
        sqlite3_finalize(*stmt);
        *stmt = NULL;
    }
}

int col_int(sqlite3_stmt *stmt, int col) {
    if (!stmt) return 0;
    return sqlite3_column_int(stmt, col);
}

int col_int64(sqlite3_stmt *stmt, int col) {
    if (!stmt) return 0;
    return sqlite3_column_int64(stmt, col);
}

double col_double(sqlite3_stmt *stmt, int col) {
    if (!stmt) return 0.0;
    return sqlite3_column_double(stmt, col);
}

const unsigned char* col_text(sqlite3_stmt *stmt, int col) {
    if (!stmt) return NULL;
    return sqlite3_column_text(stmt, col);
}

int col_count(sqlite3_stmt *stmt) {
    return stmt ? sqlite3_column_count(stmt) : 0;
}

int begin_txn(sqlite3 *db) {
    return exec_sql(db, "BEGIN TRANSACTION;", NULL, NULL);
}

int commit_txn(sqlite3 *db) {
    return exec_sql(db, "COMMIT;", NULL, NULL);
}

int rollback_txn(sqlite3 *db) {
    return exec_sql(db, "ROLLBACK;", NULL, NULL);
}

sqlite3_int64 last_insert_id(sqlite3 *db) {
    return db ? sqlite3_last_insert_rowid(db) : -1;
}