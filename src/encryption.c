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
    char* key = (char*)malloc(keyLength + 1 * sizeof(char));

    for (int i = 0; i < keyLength; i++) {
        //Generate a random integer in the printable characters ASCII range
        int randomAscii = rand() % (127 - 33) + 33;
        key[i] = (char)randomAscii;
    }

    key[keyLength - 1] = '\0';

    return key;
}

char* stringToBinary(char* input) {
    size_t inputLength = strlen(input);
    char* binaryResult = (char*)malloc(inputLength * 8 + 1); // +1 for null terminator
    binaryResult[inputLength * 8] = '\0';

    size_t index = 0; // Track the index in the binaryResult array

    while (*input) {
        int asciiCode = (int)(*input++);

        // Convert ASCII code to binary representation
        for (int i = 7; i >= 0; i--) {
            binaryResult[index++] = (asciiCode & (1 << i)) ? '1' : '0';
        }
    }

    return binaryResult;
}


