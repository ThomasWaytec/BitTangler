#include <stdlib.h>
#include <stdbool.h>
#include <ctype.h>


bool isStringNumeric(char* string) {
    for (size_t i = 0; i < strlen(string); i++)
    {
        if (!isdigit(string[i]))
        {
            return false;
        }
        
    }
    return true;
    
}
