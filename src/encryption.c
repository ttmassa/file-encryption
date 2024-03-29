#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include "db_manager.h"

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
    char* key = (char*)malloc((keyLength + 1) * sizeof(char));

    srand(time(NULL));

    for (int i = 0; i < keyLength; i++) {
        // Generate a random integer in the a-z or A-Z ASCII range
        int randomAscii;
        if (rand() % 2 == 0) {
            // Generate a random lowercase letter
            randomAscii = rand() % (122 - 97 + 1) + 97;
        } else {
            // Generate a random uppercase letter
            randomAscii = rand() % (90 - 65 + 1) + 65;
        }
        key[i] = (char)randomAscii;
    }

    key[keyLength] = '\0';

    return key;
}

char* stringToBinary(char* input) {
    size_t inputLength = strlen(input);
    char* binaryResult = (char*)malloc(inputLength * 8 + 1);
    binaryResult[inputLength * 8] = '\0';  // Null terminator

    size_t index = 0; 

    while (*input) {
        int asciiCode = (int)(*input++);

        // Convert ASCII code to binary representation
        for (int i = 7; i >= 0; i--) {
            binaryResult[index++] = (asciiCode & (1 << i)) ? '1' : '0';
        }
    }

    return binaryResult;
}

char binaryToChar(char* octet) {
    int asciiCode = 0;

    for (int i = 0; i < 8; i++) {
        asciiCode <<= 1;
        if (octet[i] == '1') {
            asciiCode += 1;
        }
    }

    return (char)asciiCode;
}

char* xorComparaison(char* input, char* key) {
    char *res = (char*)malloc(strlen(input) * sizeof(char));

    if (res == NULL) {
        printf("Error reallocating memory for the key.\n");
        exit(-1);
    }

    for (int i = 0; i < strlen(input); i++) {
        res[i] = key[i % strlen(key)] ^ input[i] ? '1' : '0';
    }

    for(int i = 0; i < strlen(res); i++) {
        if (res[i] != '0' && res[i] != '1') {
            res[i] = '0';
        }
    }

    return res;
}

void encryptFile(char *file, char* key) {
    /*
        - Read the file
        - Convert into binary forms the text and the key
        - XORed the two of them
        - Write the result into an new file
    */
    char *fileContent = readFile(file);
    printf("%s\n", key);

    if (fileContent == NULL || key == NULL || strlen(fileContent) == 0) {
        printf("Error generating key or fileContent.");
        exit(-1);
    }
    


    char *binaryKey = stringToBinary(key);
    char *binaryText = stringToBinary(fileContent);

    // Proceed to the XOR comparaison
    char *encryptedFileContent = xorComparaison(binaryText, binaryKey);
    printf("%s", encryptedFileContent);

    FILE *encryptedFile = fopen("output.txt", "w");

    if (encryptedFile == NULL) {
        perror("Error opening file");
        exit(-1);
    }

    fprintf(encryptedFile, "%s", encryptedFileContent);

    fprintf(encryptedFile, "\n");

    fclose(encryptedFile);

    // Free allocated memory
    free(fileContent);
    free(key);
    free(binaryKey);
    free(binaryText);
}

void encryptFileWithoutKey(char *file, char* name) {
    /*
        - Read the file
        - Convert into binary forms the text and the key
        - XORed the two of them
        - Write the result into an new file
    */
    char *fileContent = readFile(file);

    if (fileContent == NULL) {
        printf("Error reading file.");
        exit(-1);
    }
    
    char *key = generateKey(strlen(fileContent));

    if (fileContent == NULL || key == NULL || strlen(fileContent) == 0) {
        printf("Error generating key or fileContent.");
        exit(-1);
    }
    
    storeFile(name, key);

    char *binaryKey = stringToBinary(key);
    char *binaryText = stringToBinary(fileContent);

    // Proceed to the XOR comparaison
    char *encryptedFileContent = xorComparaison(binaryText, binaryKey);

    FILE *encryptedFile = fopen("output.txt", "w");

    if (encryptedFile == NULL) {
        perror("Error opening file");
        exit(-1);
    }

    fprintf(encryptedFile, "%s", encryptedFileContent);

    fprintf(encryptedFile, "\n");

    fclose(encryptedFile);

    // Free allocated memory
    free(fileContent);
    free(key);
    free(binaryKey);
    free(binaryText);
}

void removeLastTwoChars(char* str) {
    int length = strlen(str);
    if (length >= 2) {
        str[length - 2] = '\0';
    }
}

void decryptFile(char* file, char* key) {
    /*
        - Read the file
        - XOR it with the key to get thr original binary form back
        - Convert each octet into its corresponding character
        - Write the result into a file
    */

    char* fileContent = readFile(file);

    if (fileContent == NULL) {
        printf("Error reading file.");
        exit(-1);
    }

    int fileLength = strlen(fileContent);

    char* binaryKey = stringToBinary(key);

    if (binaryKey == NULL) {
        printf("Error converting key");
        exit(-1);
    }


    // Proceed to the XOR comparison
    char *originalContent = xorComparaison(fileContent, binaryKey);

    // Allocate memory for the decrypted content
    char* decryptedContent = malloc(fileLength / 8 + 1);

    // Process each octet
    for (int i = 0; i < fileLength; i += 8) {
        char octet[9];
        strncpy(octet, &originalContent[i], 8);

        // Convert the octet to a char and add it to the decrypted content
        decryptedContent[i / 8] = binaryToChar(octet);
    } 

    decryptedContent[fileLength / 8] = '\0';  // Null-terminate the decrypted content
    
    // Remove the last 2 chars
    removeLastTwoChars(decryptedContent);

    FILE *decryptedFile = fopen("input.txt", "w");

    if (decryptedFile == NULL) {
        perror("Error opening file");
        exit(-1);
    }

    fprintf(decryptedFile, "%s", decryptedContent);

    fclose(decryptedFile);

    // Free the allocated memory
    free(fileContent);
    free(decryptedContent);
}
