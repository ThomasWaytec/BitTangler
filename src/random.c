#include <stdlib.h>

size_t randSizeT(size_t lower, size_t upper) {

    size_t range = upper + 1 - lower;
    
    size_t prelimitedRandNum = rand() ^ (rand() << 15) ^ ((size_t) rand() << 30); /* to return larger numbers than RAND_MAX */
    size_t randNum = prelimitedRandNum % range + lower;

    return randNum;
}