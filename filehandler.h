#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void readFileToString(const char* filename, char* buffer, size_t bufferSize) {
    FILE* fp = fopen(filename, "r");
    if (fp == NULL) {
        perror("Unable to open file for reading");
        exit(1);
    }

    size_t bytesRead = fread(buffer, 1, bufferSize - 1, fp); 
    buffer[bytesRead] = '\0';
    fclose(fp);
}

void writeFileFromString(const char* filename, const char* buffer) {
    FILE* fp = fopen(filename, "w");
    if (fp == NULL) {
        perror("Unable to open file for writing");
        exit(1);
    }

    fwrite(buffer, 1, strlen(buffer), fp);  
    fclose(fp);
}