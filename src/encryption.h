#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <stdio.h>

char* readFile(char* filename);
char* generateKey(int keyLength);
char* stringToBinary(char* input);
char* xorComparaison(char* input, char* key);
FILE* encryptFile(char *file, char* key);
char binaryToChar(char* octet);
void decryptFile(char* file, char* key);

#endif