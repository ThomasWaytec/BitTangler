#include <stdio.h>
#include <stdlib.h>
#include <time.h>

size_t getFileSize(const char *filename) {
    FILE *file = fopen(filename, "r");

    if (file == NULL) {
        perror("Error opening file.");
        exit(EXIT_FAILURE);
    }


    /* get file size */
    fseek(file, 0, SEEK_END);
    size_t fileSize = ftell(file);
    fseek(file, 0, SEEK_END);


    fclose(file);

}

void corruptFile(const char *filename, size_t sequences, size_t maxSeqLen) {
    FILE *file = fopen(filename, "r+");
    

    /* seed RNG */
    srand((unsigned int)time(NULL));



    for (size_t i = 0; i < sequences; i++)
    {
        size_t position = rand() % fileSize;
        size_t seqlength = rand() % maxSeqLen + 1;


        fseek(file, position, SEEK_SET);

        for (size_t i = 0; i < seqlength; i++) {
            //char randomByte = rand() % CHAR_MAX;
            char randomByte = 0x00;
            fwrite(&randomByte, sizeof(char), 1, file);
        }
    }

    fclose(file);
}

int main() {
    const char *filename = "test.txt";


    size_t sequences = 1;
    size_t maxSeqLen = 2;

    corruptFile(filename, sequences, maxSeqLen);

    printf("File corrupted successfully.\n");

    return 0;
}
