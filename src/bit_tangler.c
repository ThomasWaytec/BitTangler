#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

double scaleIntensity(double n) {


    double scale = 500.0;

    if (n == 100.0) {scale = 25.0;}
    else if (n > 90.0) {scale = 95.0;}
    else if (n > 70.0) {scale = 155.0;}
    else if (n > 50.0) {scale = 315.0;}    
    
    return n + n * (n / scale);
}   

size_t getFileSize(const char *FILEPATH) {
    FILE *file = fopen(FILEPATH, "r");

    if (file == NULL) {
        perror("Error opening file.");
        exit(EXIT_FAILURE);
    }


    /* get file size */
    fseek(file, 0, SEEK_END);
    size_t fileSize = ftell(file);
    fseek(file, 0, SEEK_END);


    fclose(file);

    return fileSize;

}

void corruptFile(const char *FILEPATH, size_t sequences, size_t maxSeqLen) {
    size_t fileSize = getFileSize(FILEPATH);

    FILE *file = fopen(FILEPATH, "r+");
    
    /* seed RNG */
    srand((unsigned int)time(NULL));



    for (size_t i = 0; i < sequences; i++)
    {
        size_t position = rand() % fileSize;
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

int main(int argc, char* argv[]) {

     char* FILEPATH = NULL;
    /* parse coommand-line arguments */
    for (size_t i = 1; i < argc; i++) {   
        arg = argv[i];
        arg_len = strlen(arg);
        
        /* help message arguments */
        if (strcmp(arg, "-h") == 0 || strcmp(arg, "--help") == 0)
        {print_help_message(); exit(EXIT_SUCCESS);}



        /* standalone data format arguments with input (i.e. -i 15) */        
        if (arg[0] == '-' && arg_len == 2)
        {   

            /* if not found among the data formats */
            if (!DATA_FORMATS_MAP[arg[1]].exist) {unknown_arg_error(arg);}
            
            chosen_data_formats_len += 1;
            chosen_data_formats = realloc(chosen_data_formats, chosen_data_formats_len*sizeof(data_format_t));

            chosen_data_formats[chosen_data_formats_len - 1] = DATA_FORMATS_MAP[arg[1]];    
                
        }

        /* double dash arguments with input (i.e. --intensity 15) */
        if (arg[0] == '-' && arg[1] == '-'  && arg_len >= 2) {
            
            if (strcmp(arg, "--buffer") == 0)
            {
                buffering = true;
            }

            else {unknown_arg_error(arg);}
        }


        /* non-switch (filepath) argument */
        else if (arg[0] != '-') {
            /* more than one filepath arguments given */
            if (FILEPATH != NULL) {fatal_error("Too many non-switch (filepath) arguments: \"%s\" ...", arg);}

            FILEPATH = arg;
        }

        /* any other argument */
        else {unknown_arg_error(arg);}
    }

    if (FILEPATH == NULL) {
        print_usage();
        fatal_error("No file argument given.");
    }




    size_t intensity = 15; /* 0 - 100 */    
    intensity = (size_t)scaleIntensity((double)intensity);


    size_t fileSize = getFileSize(FILEPATH);

    double bytesToCorrupt = (double)fileSize * ((double)intensity/100);

    size_t maxSeqLen = (size_t) ceil((bytesToCorrupt * 0.003));
    size_t sequences = (size_t) (bytesToCorrupt / ((double)maxSeqLen/2));


    corruptFile(FILEPATH, sequences, maxSeqLen);

    printf("File corrupted successfully.\n");

    return 0;
}
