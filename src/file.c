#include <stdio.h>
#include <stdlib.h>

size_t getFileSize(const char *FILEPATH) {
    FILE *file = fopen(FILEPATH, "r");

    if (file == NULL) {
        perror("Error opening file.");
        exit(EXIT_FAILURE);
    }


    /* get file size */
    fseek(file, 0, SEEK_END);
    const size_t FILESIZE = ftell(file);
    fseek(file, 0, SEEK_END);


    fclose(file);

    return FILESIZE;

}
