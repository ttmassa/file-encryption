#ifndef DB_MANAGER_H
#define DB_MANAGER_H

#include <sqlite3.h>

void storeFile(const char* fileName, char* key);
char* getKey(char* fileName);
void initializeDb();

#endif // DB_MANAGER_H