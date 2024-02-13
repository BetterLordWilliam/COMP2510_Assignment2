#include <stdio.h>
#include <stdlib.h>

// Definitions

// Method headers
void readFile();
void simulateFunction();
void outputFile();
void printErrorExit();

// Constants
FILE *in;
FILE *out; 

// Structs
struct  {
    int pX;
    int pY;
    int vX;
    int vY;
};

/*
    main: main method of program
*/
int main(int argc, char *argv[]) {
    if (argc != 4) {
        return 1;
    }

    // Setup files
    readFile();

    simulateFunction();
}

/*
le and exit*   printErrorExit: Print error message to output f
*/
void printErrorExit() {
    FILE *out = fopen("output.txt", "w");
    fputs("error", out);
    exit(1);
}

// Print an