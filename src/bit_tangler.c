#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#include <limits.h>

#include "error.h"
#include "help.h"
#include "file.h"
#include "string_utils.h"

#define DEFAULT_INTENSITY 10

double scaleIntensity(double n) {
    /* amplify larger numbers while minimally
    affecting smaller ones */


    double scale = 500.0;

    if (n == 100.0) {scale = 25.0;}
    else if (n > 90.0) {scale = 95.0;}
    else if (n > 70.0) {scale = 155.0;}
    else if (n > 50.0) {scale = 315.0;}    
    
    return n + n * (n / scale);
}   


void corruptFile(const char *FILEPATH, size_t sequences, size_t maxSeqLen) {
    const size_t FILESIZE = getFileSize(FILEPATH);

    FILE *file = fopen(FILEPATH, "r+");
    
    /* seed RNG */
    srand((unsigned int)time(NULL));


    for (size_t i = 0; i < sequences; i++)
    {

        size_t position = rand() % FILESIZE;
        size_t seqLen = rand() % maxSeqLen + 1;


        fseek(file, position, SEEK_SET);

        /* write a byte sequence of length seqLen */
        for (size_t i = 0; i < seqLen; i++) {
            char randomByte = rand() % CHAR_MAX;
            fwrite(&randomByte, sizeof(char), 1, file);
        }
    }

    fclose(file);

}

void parseArgs(int argc, char* argv[],
               char** pFilepath, size_t* pUnscaledIntensity) {
    /* parse command-line arguments */

    char* filepath = NULL;
    size_t unscaledIntensity = *pUnscaledIntensity;
    
    bool intensityInput;

    char* arg;
    size_t argLen;
    /* parse coommand-line arguments */
    for (size_t i = 1; i < argc; i++) {   
        
        arg = argv[i];
        argLen = strlen(arg);
        
        /* help message arguments */
        if (strcmp(arg, "-h") == 0 || strcmp(arg, "--help") == 0)
        {printHelpMessage(); exit(EXIT_SUCCESS);}


        if (intensityInput)
        {

            if (!isStringNumeric(arg))
            {
                fatal_error("Intensity level \"%s\" may only contain numbers.", arg);
            }
            
            unscaledIntensity = atoi(arg);

            if (unscaledIntensity < 1 || unscaledIntensity > 100)
            {
                fatal_error("Intensity level \"%zu\" has to be between 1 and 100 (including).", unscaledIntensity);
            }
            
            intensityInput = false;
            
        }
        
        /* single letter intensity argument (i.e. -i 15) */
        else if (arg[0] == '-' && argLen == 2)
        {   

            if (arg[1] == 'i') 
            {intensityInput = true;}
            else {unknown_arg_error(arg);}
            
        }

        /* double dash intensity argument with input (i.e. --intensity 15) */
        else if (arg[0] == '-' && arg[1] == '-'  && argLen >= 2) {
            
            if (strcmp(arg, "--intensity") == 0)
            {intensityInput = true;}

            else {unknown_arg_error(arg);}
        }


        /* non-switch (filepath) argument */
        else if (arg[0] != '-') {
            /* more than one filepath arguments given */
            if (filepath != NULL) {fatal_error("Too many non-switch (filepath) arguments: \"%s\" ...", arg);}

            filepath = arg;
        }

        /* any other argument */
        else {unknown_arg_error(arg);}
    }

    if (filepath == NULL) {
        print_usage();
        fatal_error("No file argument given.");
    }

    /* return values via pointers */
    *pUnscaledIntensity = unscaledIntensity;
    *pFilepath = strdup(filepath);

    
}

int main(int argc, char* argv[]) {


    char* filepath = NULL;
    size_t unscaledIntensity = DEFAULT_INTENSITY;

    parseArgs(argc, argv,
              &filepath, &unscaledIntensity);

 




    if (!fileExists(filepath))
    {fatal_error("File not found or doesn't exist: \"%s\"", filepath);}
    
    
    
    const size_t FILESIZE = getFileSize(filepath);
    size_t intensity = (size_t)scaleIntensity((double)unscaledIntensity);

    double bytesToCorrupt = (double)FILESIZE * ((double)intensity/100);


    size_t maxSeqLen = (size_t) ceil((bytesToCorrupt * 0.003));
    size_t sequences = (size_t) (bytesToCorrupt / ((double)maxSeqLen/2));


    corruptFile(filepath, sequences, maxSeqLen);

    printf("%s corrupted successfully with intensity level of %zu.\n",
    filepath, unscaledIntensity);

    return 0;
}
