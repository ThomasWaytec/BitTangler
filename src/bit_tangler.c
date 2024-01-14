#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

double scaleIntensity(double n) {


    double scale = 500.0;

    if (n == 100.0) {scale = 25.0;}
    else if (n > 90.0) {scale = 95.0;}
    else if (n > 70.0) {scale = 155.0;}
    else if (n > 50.0) {scale = 315.0;}    
    
    return n + n * (n / scale);
}   

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

    return fileSize;

}

void corruptFile(const char *filename, size_t sequences, size_t maxSeqLen) {
    size_t fileSize = getFileSize(filename);

    FILE *file = fopen(filename, "r+");
    
    /* seed RNG */
    srand((unsigned int)time(NULL));



    for (size_t i = 0; i < sequences; i++)
    {
        size_t position = rand() % fileSize;
        size_t seqLen = rand() % maxSeqLen + 1;


        fseek(file, position, SEEK_SET);

        /* write a byte sequence of length seqLen */
        for (size_t i = 0; i < seqLen; i++) {
            char randomByte = rand() % CHAR_MAX;
            fwrite(&randomByte, sizeof(char), 1, file);
        }
    }

    fclose(file);
}

int main() {
    const char *filename = "test.txt";


    /* parse command-line arguments here */



    size_t intensity = 15; /* 0 - 100 */    
    intensity = (size_t)scaleIntensity((double)intensity);


    size_t fileSize = getFileSize(filename);

    double bytesToCorrupt = (double)fileSize * ((double)intensity/100);

    size_t maxSeqLen = (size_t) ceil((bytesToCorrupt * 0.003));
    size_t sequences = (size_t) (bytesToCorrupt / ((double)maxSeqLen/2));


    corruptFile(filename, sequences, maxSeqLen);

    printf("File corrupted successfully.\n");

    return 0;
}
