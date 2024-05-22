#include <stdio.h>
#include <stdlib.h>  //memory allocation
#include <string.h>

int main() {
    FILE *file;    
    char *line = NULL;  //storing lines from input file
    size_t len = 0;     //store length of line
    size_t read; //store no. of character read by getline()

    char intTarget[] = "int";   //Array containing keyword int
    char floatTarget[] = "float";//Array containing keyword float
    int intLength = 4;
    int floatLength = 4;
    int address = 1000;

    file = fopen("code.txt", "r");

    if (file == NULL) {
        fprintf(stderr, "Error opening file for reading!\n");
        return 1;
    }

    printf("Symbol   DataType  Size  address\n");

    while ((read = getline(&line, &len, file)) != -1) {         //while loop that continues until the getline function reaches the end of the file. Inside the loop, each line from the file is read into the line buffer.
        if (strstr(line, "main") == NULL) {      //strstr stands for "string search"
            if (strstr(line, intTarget) != NULL) {    //Checking if the line contains the keyword "int." If true, it enters a block of code to process "int" variable declarations.
                int i = 4;
                char symbol[100]; //Initializing a loop counter (i), and an array (symbol) to store variable names
                memset(symbol, 0, sizeof(symbol)); //ensures that symbol is an empty string before characters are appended to it within the subsequent loop.

                while (line[i] != ';') {    //Starting a loop that processes characters in the line until a semicolon is encountered (end of the variable declaration).
                    if (line[i] == ',') {
                        printf("%s\t%s\t%d\t%d\n", symbol, intTarget, intLength, address);
                        address = address + intLength;
                        memset(symbol, 0, sizeof(symbol));
                    } else {
                        strncat(symbol, &line[i], 1);
                    }
                    i++;
                }   //Inside the loop, if a comma is found, it prints the variable information, increments the address, and resets the symbol array. Otherwise, it appends the current character to the symbol array.


                if (symbol[0] != '\0') {
                    printf("%s\t%s\t%d\t%d\n", symbol, intTarget, intLength, address);
                    address = address + intLength;
                }    //After the loop, if the symbol array is not empty, it prints the information for the last "int" variable.

            }
            else if (strstr(line, floatTarget) != NULL) {          //Checking if the line contains the keyword "float." If true, it enters a block of code to process "float" variable declarations.
                int i = 6; 
                char symbol[256];
                memset(symbol, 0, sizeof(symbol));    //Initializing a loop counter (i), and an array (symbol) to store variable names. The array is initialized to empty using memset. The value 6 is used as the starting index for processing "float" declarations, assuming "float" is declared at index 6.

                while (line[i] != ';') {   // till (end of the variable declaration).
                    if (line[i] == ',') {
                        printf("%s\t%s\t%d\t%d\n", symbol, floatTarget, floatLength, address);
                        address = address + floatLength;
                        memset(symbol, 0, sizeof(symbol));
                    } else {
                        strncat(symbol, &line[i], 1);
                    }
                    i++;
                }     //Inside the loop, if a comma is found, it prints the variable information, increments the address, and resets the symbol array. Otherwise, it appends the current character to the symbol array.

                if (symbol[0] != '\0') {
                    printf("%s\t%s\t%d\t%d\n", symbol, floatTarget, floatLength, address);
                    address = address + floatLength;
                }
            }
        }
    }   //The end of the while loop. The code inside the loop processes each line from the file based on the conditions for "int" and "float" variable declarations.

    fclose(file);
    if (line) {
        free(line);
    }  //Closing the file using fclose. If the line buffer was allocated dynamically (using getline), freeing the allocated memory.

    return 0;
}
