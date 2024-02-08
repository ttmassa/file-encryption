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

void encryptFile(char *file) {
    /*
        - Read the file
        - Generate a key
        - Convert into binary forms
        - Make XOR encryption
        - Create new file and add content
    */

    char *fileContent = readFile(file);
    char *key = generateKey(strlen(fileContent));

    if (fileContent == NULL || key == NULL || strlen(fileContent) == 0) {
        printf("Error generating key or fileContent.");
        exit(-1);
    }
    

    char *binaryKey = stringToBinary(key);
    char *binaryText = stringToBinary(fileContent);

    // Proceed to the XOR comparaison
    char *encryptedFileContent = (char*)malloc(strlen(fileContent) + 1 * sizeof(char));

    if (encryptedFileContent == NULL) {
        printf("Error reallocating memory for the key.\n");
        exit(-1);
    }

    // if (strlen(binaryKey) < strlen(binaryText)) {
    //     // If the key is shorter than the text, fill it with '0' characters
    //     int diff = strlen(binaryText) - strlen(binaryKey);
    //     char *temp = (char *)realloc(binaryKey, (strlen(binaryKey) + diff + 1) * sizeof(char));

    //     if (temp == NULL) {
    //         printf("Error reallocating memory for the key.\n");
    //         exit(-1);
    //     }

    //     binaryKey = temp;
    //     for (int i = strlen(binaryKey); i < strlen(binaryText); i++) {
    //         binaryKey[i] = '0';
    //     }

    //     // Add null terminator at the end
    //     binaryKey[strlen(binaryKey) + diff] = '\0';

    // }

    // if (strlen(binaryKey) != strlen(binaryText)) {
    //     printf("Error of key generation.");
    //     exit(-1);
    // }

    for (int i = 0; i < strlen(binaryKey); i++) {
        if (binaryKey[i] == binaryText[i]) {
            encryptedFileContent[i] = '0';
        } else if (binaryKey[i] != binaryText[i]) {
            encryptedFileContent[i] = '1';
        } else {
            encryptedFileContent[i] = '0';
        }
    }

    FILE *encryptedFile = fopen("C:\\Users\\timot\\Documents\\C\\file-encryption\\build\\output.txt", "w");

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
    free(encryptedFileContent);
}
