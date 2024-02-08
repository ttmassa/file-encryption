#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <stdio.h>

char* readFile(char* filename);
char* generateKey(int keyLength);
char* stringToBinary(char* input);
FILE* encryptFile(char *file);

#endif