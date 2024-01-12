#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void corruptFile(const char *filename, size_t numBytesToCorrupt) {
    FILE *file = fopen(filename, "r+");

    if (file == NULL) {
        perror("Error opening file");
        exit(EXIT_FAILURE);
    }

    // Get the file size
    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    rewind(file);

    // Seed for random number generation
    srand((unsigned int)time(NULL));

    // Overwrite random parts of the file
    for (size_t i = 0; i < numBytesToCorrupt; ++i) {
        // Generate a random position within the file
        long position = rand() % fileSize;

        // Move the file pointer to the random position
        fseek(file, position, SEEK_SET);

        // Overwrite one byte with a random value
        char randomByte = rand() % 256;
        fwrite(&randomByte, sizeof(char), 1, file);
    }

    fclose(file);
}

int main() {
    const char *filename = "example.txt";
    size_t numBytesToCorrupt = 10;

    // Create a backup of the original file before corrupting it
    system("cp example.txt example_backup.txt");

    corruptFile(filename, numBytesToCorrupt);

    printf("File corrupted successfully.\n");

    return 0;
}
