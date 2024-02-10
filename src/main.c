#include "encryption.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main() {
    char* filename = "C://Users//timot//Documents//C//file-encryption//output.txt";
    char* key = "neTRIPkvZgnggmajCJmqgiRHFapacdNJfjnCskZCktBZWDZzCUloyafBqlcNDHkYGxZqNNqc";

    decryptFile(filename, key);
    

    return 0;
}