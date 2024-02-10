#ifndef ENCRYPTION_H
#define ENCRYPTION_H

#include <stdio.h>

char* readFile(char* filename);
char* generateKey(int keyLength);

char* stringToBinary(char* input);
char* xorComparaison(char* input, char* key);
char binaryToChar(char* octet);

void encryptFile(char *file, char* key);
void decryptFile(char* file, char* key);

#endif