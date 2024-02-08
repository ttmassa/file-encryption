#include "encryption.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char* filename = "C://Users//timot//Documents//C//file-encryption//build//file.txt";

    char* fileContent = readFile(filename);
    char* key = generateKey(strlen(fileContent));
    char* binaryForm = stringToBinary(key);

    printf("Binary form: %s", binaryForm);

    free(binaryForm);

    return 0;
}