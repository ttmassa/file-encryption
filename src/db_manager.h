#ifndef DB_MANAGER_H
#define DB_MANAGER_H

#include <sqlite3.h>

void storeFile(const char* fileName, char* key);
void initializeDb();

#endif // DB_MANAGER_H