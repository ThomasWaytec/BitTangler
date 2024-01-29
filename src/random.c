#include <stdlib.h>



long long int randNum(long long int lower, long long int upper) {

    long long int range = upper + 1 - lower;
    
    long long int prelimitedRandNum = rand() ^ (rand() << 15) ^ ((long long int) rand() << 30); /* to return larger numbers than RAND_MAX */
    long long int randNum = prelimitedRandNum % range + lower;

    return randNum;
}