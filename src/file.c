#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "error.h"

#ifdef _WIN32
    #include <io.h>

    bool fileExists(const char* FILE_PATH) {
        return _access(FILE_PATH, 0) != -1;
    }

#endif

#ifdef linux
    #include <unistd.h>

    bool fileExists(const char* FILE_PATH) {
        return access(FILE_PATH, F_OK) != -1;
    }
#endif

const size_t getFileSize(const char* FILE_PATH) {
    FILE* file = fopen(FILE_PATH, "r");

    /* get file size */
    fseek(file, 0, SEEK_END);
    const size_t FILE_SIZE = ftell(file);
    fseek(file, 0, SEEK_END);


    fclose(file);

    return FILE_SIZE;

}
