#include <sqlite3.h>
#include <string.h>
#include <stdio.h>

static int callback(void *key, int argc, char **argv, char **azColName){
   char** result = (char**)key;
   *result = strdup(argv[0]);
   return 0;
}

void storeFile(const char* fileName, const char* key) {
    sqlite3 *db;
    char *err_msg = 0;

    int rc  = sqlite3_open("../database/test.db", &db);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
    }

    char sql[256];
    sprintf(sql, "INSERT INTO KEYS(Name, Key) VALUES('%s', '%s')", fileName, key);
    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
    }

    sqlite3_close(db);
}

char* getKey(char* fileName) {
    sqlite3 *db;
    char *err_msg = 0;
    char* key = NULL;

    int rc  = sqlite3_open("../database/test.db", &db);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return NULL;
    }

    char sql[256];
    sprintf(sql, "SELECT Key FROM KEYS WHERE Name = '%s'", fileName);
    rc = sqlite3_exec(db, sql, callback, &key, &err_msg);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
        return NULL;
    }

    sqlite3_close(db);

    return key;
}

void initializeDb() {
    sqlite3 *db;
    char *err_msg = 0;

    int rc  = sqlite3_open("./database/test.db", &db);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
        sqlite3_close(db);
        return;
    }

    char *sql = "CREATE TABLE IF NOT EXISTS KEYS(Id INTEGER PRIMARY KEY, Name TEXT UNIQUE,Key TEXT);";

    rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

    if (rc != SQLITE_OK) {
        fprintf(stderr, "SQL error: %s\n", err_msg);
        sqlite3_free(err_msg);
        sqlite3_close(db);
    }

    sqlite3_close(db);
}