#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "error.h"

#ifdef _WIN32
    #include <io.h>

    bool fileExists(const char* FILEPATH) {
        return _access(FILEPATH, 0) != -1;
    }

#endif

#ifdef linux
    #include <unistd.h>

    bool fileExists(const char* FILEPATH) {
        return access(FILEPATH, F_OK) != -1;
    }
#endif

const size_t getFileSize(const char* FILEPATH) {
    FILE* file = fopen(FILEPATH, "r");

    /* get file size */
    fseek(file, 0, SEEK_END);
    const size_t FILE_SIZE = ftell(file);
    fseek(file, 0, SEEK_END);


    fclose(file);

    return FILE_SIZE;

}
