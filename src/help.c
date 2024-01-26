



/* RENAME print_help_message 

and ALL other snake_case variables !!!
*/


#include <stdio.h>

const char *HELP_MESSAGE = "tangler: Corrupt files by overwriting bytes with controlled intensity.\n" 
    "\n"
    "Usage: tangler FILE [OPTIONS]\n"
    "\n"
    "Positional Arguments:\n"
    "  FILE                    The name or path of the file to be corrupted.\n"
    "\n"
    "OPTIONS:\n"
    "  -i, --intensity INT     Set the intensity level (1 to 100) for file corruption.\n"
    "  -h, --help              Display this help message and exit.\n"
    "\n"
    "Example Usage:\n"
    "   tangler file.txt\n"
    "   tangler audio.mp3 -i 97\n"
    "   tangler media/image.jpg --intensity 75\n";


void print_help_message(void) {
    printf("%s\n", HELP_MESSAGE);
}

void print_usage(void) {
    const char* USAGE = "\n\nUsage: tangler FILE [OPTIONS]\nUse -h for help.";
    printf("%s\n", USAGE);
}
