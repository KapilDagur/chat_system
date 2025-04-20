#ifndef CHAT_SYSTEM_CORE_DB_H
#define CHAT_SYSTEM_CORE_DB_H


#include <sqlite3.h>

// Open / Close
int open_db(sqlite3 **db, const char *filename);
void close_db(sqlite3 *db);

// Raw SQL
int exec_sql(sqlite3 *db, const char *sql,
             int (*callback)(void*, int, char**, char**),
             void *arg);

// Prepared Statements
int prepare_stmt(sqlite3 *db, sqlite3_stmt **stmt, const char *sql);
int bind_text(sqlite3_stmt *stmt, int index, const char *text);
int bind_int(sqlite3_stmt *stmt, int index, int value);
int bind_int64(sqlite3_stmt *stmt, int index, sqlite3_int64 value);
int bind_double(sqlite3_stmt *stmt, int index, double value);
int bind_null(sqlite3_stmt *stmt, int index);
int step_stmt(sqlite3_stmt *stmt);
void finalize_stmt(sqlite3_stmt **stmt);

// Row Access
int col_int(sqlite3_stmt *stmt, int col);
int col_int64(sqlite3_stmt *stmt, int col);
double col_double(sqlite3_stmt *stmt, int col);
const unsigned char* col_text(sqlite3_stmt *stmt, int col);
int col_count(sqlite3_stmt *stmt);

// Transactions
int begin_txn(sqlite3 *db);
int commit_txn(sqlite3 *db);
int rollback_txn(sqlite3 *db);

// Utility
sqlite3_int64 last_insert_id(sqlite3 *db);

#endif