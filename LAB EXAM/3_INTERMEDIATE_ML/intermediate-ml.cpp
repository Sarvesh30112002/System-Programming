#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_LINE_LENGTH 100


// Function to convert intermediate code to machine language
void translateToMachineLanguage(FILE *inputFile, FILE *outputFile) {
    char line[MAX_LINE_LENGTH];
    int instructionCounter = 0;


    while (fgets(line, sizeof(line), inputFile)) {
        char *token = strtok(line, " \n");
       
        // Skip empty lines
        if (token == NULL) continue;


        // Translate instructions to machine language
        if (strcmp(token, "MOV") == 0) {
            fprintf(outputFile, "1000\n");
        } else if (strcmp(token, "ADD") == 0) {
            fprintf(outputFile, "2000\n");
        } else if (strcmp(token, "SUB") == 0) {
            fprintf(outputFile, "3000\n");
        } else if (strcmp(token, "HLT") == 0) {
            fprintf(outputFile, "4000\n");
        } else if (strcmp(token, "JNZ") == 0) {
            fprintf(outputFile, "5000\n");
        } else {
            printf("Error: Unknown instruction '%s'\n", token);
            exit(1);
        }


        instructionCounter++;
    }
}


int main() {
    FILE *inputFile, *outputFile;


    // Open input file
    inputFile = fopen("input_icg.txt", "r");
    if (inputFile == NULL) {
        perror("Error opening input file");
        return 1;
    }


    // Open output file
    outputFile = fopen("output_icg.txt", "w");
    if (outputFile == NULL) {
        perror("Error creating output file");
        fclose(inputFile);
        return 1;
    }


    // Translate intermediate code to machine language
    translateToMachineLanguage(inputFile, outputFile);


    // Close files
    fclose(inputFile);
    fclose(outputFile);


    printf("Translation complete. Output written to output.txt.\n");


    return 0;
}
