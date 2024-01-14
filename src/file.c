#include <stdio.h>
#include <stdlib.h>

#include "error.h"

const size_t getFileSize(const char *FILEPATH) {
    FILE *file = fopen(FILEPATH, "r");

    if (file == NULL) {
        fatal_error("File not found or doesn't exist: \"%s\"", FILEPATH);
    }


    /* get file size */
    fseek(file, 0, SEEK_END);
    const size_t FILESIZE = ftell(file);
    fseek(file, 0, SEEK_END);


    fclose(file);

    return FILESIZE;

}
