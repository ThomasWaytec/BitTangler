#include <stdio.h>

const char *help_message = "\n";

void print_help_message(void) {

    printf("%s\n", help_message);
}

void print_usage(void) {
    
    const char* USAGE = "\n\nUsage: \nUse -h for help.";
    printf("%s\n", USAGE);
}