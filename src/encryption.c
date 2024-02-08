#include <stdio.h>
#include <string.h>
#include <stdlib.h>

char* readFile(char* filename) {
    FILE* file = fopen(filename, "r");

    if (file == NULL) {
        fprintf(stderr, "Error opening file: %s\n", filename);
        return NULL;
    }

    // fseek = move pointer into the file
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    fseek(file, 0, SEEK_SET);

    // Allocate memory for the file content
    char* content = (char*)malloc(file_size + 1); // +1 for null terminator

    if (content == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        fclose(file);
        return NULL;
    }

    fread(content, sizeof(char), file_size, file);

    // Null-terminate the content
    content[file_size] = '\0';

    fclose(file);

    return content;
}

char* generateKey(int keyLength) {
    char* key = (char*)malloc(keyLength * sizeof(char));

    for (int i = 0; i < keyLength; i++) {
        //Generate a random integer in the printable characters ASCII range
        int randomAscii = rand() % (127 - 33) + 33;
        key[i] = (char)randomAscii;
    }

    key[keyLength] = '\0';

    return key;
}