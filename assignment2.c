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

// Main Method
int main(int argc, char *argv[]) {
    if (argc != 4) {
        return 1;
    }

    // Setup files
    readFile();

    simulateFunction();

    return 0;
}
