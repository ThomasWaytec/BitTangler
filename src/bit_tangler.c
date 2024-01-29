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
#include "random.h"

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


void corruptFile(const char *FILE_PATH, size_t sequences, size_t maxSeqLen) {
    const size_t FILE_SIZE = getFileSize(FILE_PATH);

    FILE *file = fopen(FILE_PATH, "r+");


    for (size_t i = 0; i < sequences; i++)
    {

        size_t position = (size_t) randNum(0, FILE_SIZE);
        size_t seqLen = (size_t) randNum(1, maxSeqLen);

        fseek(file, position, SEEK_SET);

        /* write a byte sequence of length seqLen */
        for (size_t i = 0; i < seqLen; i++) {
            char randomByte = (char) randNum(0, CHAR_MAX);
            fwrite(&randomByte, sizeof(char), 1, file);
        }
    }

    fclose(file);

}

void parseArgs(int argc, char* argv[],
               char** pFilePath, size_t* pUnscaledIntensity) {
    /* parse command-line arguments */

    char* filePath = NULL;
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
                fatalError("Intensity level \"%s\" may only contain numbers.", arg);
            }
            
            unscaledIntensity = atoi(arg);

            if (unscaledIntensity < 1 || unscaledIntensity > 100)
            {
                fatalError("Intensity level \"%zu\" has to be between 1 and 100 (including).", unscaledIntensity);
            }
            
            intensityInput = false;
            
        }
        
        /* single letter intensity argument (i.e. -i 15) */
        else if (arg[0] == '-' && argLen == 2)
        {   

            if (arg[1] == 'i') 
            {intensityInput = true;}
            else {unknownArgError(arg);}
            
        }

        /* double dash intensity argument with input (i.e. --intensity 15) */
        else if (arg[0] == '-' && arg[1] == '-'  && argLen >= 2) {
            
            if (strcmp(arg, "--intensity") == 0)
            {intensityInput = true;}

            else {unknownArgError(arg);}
        }


        /* non-switch (file path) argument */
        else if (arg[0] != '-') {
            /* more than one file path arguments given */
            if (filePath != NULL) {fatalError("Too many non-switch (file path) arguments: \"%s\" ...", arg);}

            filePath = arg;
        }

        /* any other argument */
        else {unknownArgError(arg);}
    }

    if (filePath == NULL) {
        printUsage();
        fatalError("No file argument given.");
    }

    /* return values via pointers */
    *pUnscaledIntensity = unscaledIntensity;
    *pFilePath = strdup(filePath);

    
}

int main(int argc, char* argv[]) {


    char* filePath = NULL;
    size_t unscaledIntensity = DEFAULT_INTENSITY;

    parseArgs(argc, argv,
              &filePath, &unscaledIntensity);

 




    if (!fileExists(filePath))
    {fatalError("File not found or doesn't exist: \"%s\"", filePath);}
    
    
    
    const size_t FILE_SIZE = getFileSize(filePath);
    size_t intensity = (size_t)scaleIntensity((double)unscaledIntensity);

    double bytesToCorrupt = (double)FILE_SIZE * ((double)intensity/100);


    size_t maxSeqLen = (size_t) ceil((bytesToCorrupt * 0.003));
    size_t sequences = (size_t) (bytesToCorrupt / ((double)maxSeqLen/2));

    /* seed the RNG */
    seedRand();

    corruptFile(filePath, sequences, maxSeqLen);

    printf("%s corrupted successfully with intensity level of %zu.\n",
    filePath, unscaledIntensity);

    return 0;
}
