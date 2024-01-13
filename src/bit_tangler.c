#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void corruptFile(const char *filename, size_t numBytesToCorrupt) {
    FILE *file = fopen(filename, "r+");

    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // get file size
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_END);

    srand((unsigned int)time(NULL));

    for (size_t i = 0; i < numBytesToCorrupt; ++i) {
        long position = rand() % fileSize;

        fseek(file, position, SEEK_SET);

        //char randomByte = rand() % 256;
        char randomByte = 0x00;
        fwrite(&randomByte, sizeof(char), 1, file);
    }

    fclose(file);
}

int main() {
    const char *filename = "test.txt";
    size_t numBytesToCorrupt = 10;

    corruptFile(filename, numBytesToCorrupt);

    printf("File corrupted successfully.\n");

    return 0;
}
