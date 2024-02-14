#include <sqlite3.h>
#include <stdio.h>

void storeFile(const char* fileName, const char* key) {
    sqlite3 *db;
    char *err_msg = 0;

    int rc  = sqlite3_open("C:/Users/timot/Documents/C/file-encryption/test.db", &db);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
    }

    char sql[256];
    sprintf(sql, "INSERT INTO KEYS(Filepath, Key) VALUES('%s', '%s')", fileName, key);
    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
    }

    sqlite3_close(db);
}

void storeKey(char* key) {
    sqlite3 *db;
    char *err_msg = 0;

    int rc  = sqlite3_open("C:/Users/timot/Documents/C/file-encryption/test.db", &db);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
    }

    char sql[256];
    sprintf(sql, "INSERT INTO KEYS(Filepath) VALUES('%s')", key);

    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
    }

    sqlite3_close(db);
}

void initializeDb() {
    sqlite3 *db;
    char *err_msg = 0;

    int rc  = sqlite3_open("C:/Users/timot/Documents/C/file-encryption/test.db", &db);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    char *sql = "CREATE TABLE IF NOT EXISTS KEYS(Id INTEGER PRIMARY KEY, Filepath TEXT UNIQUE,Key TEXT);";

    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
    }

    sqlite3_close(db);
}