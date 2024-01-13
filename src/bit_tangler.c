#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

double scaleIntensity(double n) {


    double scale = 65.0;

    if (n > 90.0) {scale = 15.0;}
    else if (n > 70.0) {scale = 25.0;}
    else if (n > 50.0) {scale = 45.0;}    
    else if (n > 20.0) {scale = 55.0;}    
    
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
        size_t seqLength = rand() % maxSeqLen + 1;


        fseek(file, position, SEEK_SET);

        for (size_t i = 0; i < seqLength; i++) {
            //char randomByte = rand() % CHAR_MAX;
            char randomByte = 0x00;
            fwrite(&randomByte, sizeof(char), 1, file);
        }
    }

    fclose(file);
}

int main() {
    const char *filename = "test.txt";

    size_t fileSize = getFileSize(filename);

    size_t INTENSITY = 0; /* 0 - 100 */


    INTENSITY = (size_t)scaleNumber((double)INTENSITY);
    printf("INTENSITY=%lld\n", INTENSITY);
    //exit(0);


    //INTENSITY = (size_t) ((double)INTENSITY * (double)INTENSITY/20);


    double bytesToCorrupt = (double)fileSize * ((double)INTENSITY/100);
    printf("bytesToCorrupt=%f\n", bytesToCorrupt);

    size_t maxSeqLen = (size_t) ceil((bytesToCorrupt * 0.003));
    printf("maxSeqLen=%lld\n", maxSeqLen);

    size_t sequences = (size_t) (bytesToCorrupt / (double)maxSeqLen);
    printf("sequences=%lld\n", sequences);


    corruptFile(filename, sequences, maxSeqLen);

    printf("File corrupted successfully.\n");

    return 0;
}
