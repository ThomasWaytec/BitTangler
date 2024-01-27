#include <stdlib.h>

size_t randSizeT(size_t lower, size_t upper) {

    /* seed the RNG */
    srand((unsigned int)time(NULL));

    size_t range = upper - lower + 1;
    
    size_t prelimitedRandNum = rand() ^ (rand() << 15) ^ ((size_t) rand() << 30); /* to return larger numbers than RAND_MAX */
    int randNum = prelimitedRandNum % range + lower;

    return randNum;
}