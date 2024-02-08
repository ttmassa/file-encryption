#include "encryption.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char* filename = "C://Users//timot//Documents//C//file-encryption//build//file.txt";

    char* fileContent = readFile(filename);

    printf("Random key:\n%s\n", generateKey(strlen(fileContent)));

    free(fileContent);

    return 0;
}