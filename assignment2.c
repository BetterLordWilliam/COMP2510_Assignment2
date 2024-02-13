#include <stdio.h>
#include <stdlib.h>

// Definitions

// Method headers
Particle** readFile(int *pa);
void simulateFunction();
void writeFile(Particle **p);
void printErrorExit();
Particle* makeParticle(int px, int py, int vx, int vy);
void destroyParticle(Particle *p);

// Constants
FILE *in;
FILE *out;
 
int maxX;
int maxY;
int time;

// Structs
typedef struct {
    int pX;
    int pY;
    int vX;
    int vY;
} Particle;

/*
*   main: main method of program
*/
int main(int argc, char *argv[]) {
    if (argc != 4) {
        return 1;
    }

    // Read command line args
    in = fopen(argv[1], "r");
    out = fopen(argv[2], "w");
    if (in == NULL || out == NULL) printErrorExit(); // exit if problem opening files
    time = atoi(argv[3]);

    // Read input file:
    // update the bor
    // get a pointer to an array of particle objects
    int particleCount = 0;
    readFile(&particleCount);
    
    // create 2d array with a border

    simulateFunction();
}

/*
*   printErrorExit: Print error message to output file and exit
*/
void printErrorExit() {
    FILE *out = fopen("output.txt", "w");
    fputs("error", out);
    fclose(out);
    exit(1);
}

/*
*   makeParticle:   Create a particle with given inputs.
*   params:         integer values for x position, y position, x velocity, y velocity
*   return:         pointer to the particle object
*/
Particle* makeParticle(int px, int py, int vx, int vy) {
    Particle *p = malloc(sizeof(Particle));
    p->pX = px;
    p->pY = py;
    p->vX = vx;
    p->pY = vy;
    return p;
}

/*
*   destroyParticle:    Destroy a particle that has collided.
*   param *p:           pointer to particle that collided with another
*/
void destroyParticle(Particle *p) {
    free(p);
    p = NULL;
}

/* 
*   readFile:   reads the file input, assign maxX and maxY and read particles
*   param *particleCount:   pointer to the variable storing the number of particles
*   returns:    pointer arr
*/
Particle** readFile(int *particleCount) {
    
    // update particle counter, read number of lines in input file
    char check = 0;
    while ((check = fgetc(in)) != 'E') {
        if (check = '\n') *particleCount++;
    }
    // subtract first two lines that indicate border limits to get correct count
    *particleCount = *particleCount - 2;

    // set buffer back to particle position
    char buff[10];
    fseek(in, 0, SEEK_SET);
    fgets(buff, 10, in);
    fgets(buff, 10, in); // pointer should now be at the correct line to read particles
    while(fgets(buff, 10, in) != NULL) {
        int pXtemp = 0;
        int pYtemp = 0;
        int vXtemp = 0;
        int vYtemp = 0;
        sscanf(buff, "%d,%d,%d,%d", &pXtemp, &pYtemp, &vXtemp, &vYtemp); 
        Particle *p = makeParticle(pXtemp, pYtemp, vXtemp, vYtemp);
    }
    
}

/*
*   simulateFunction:   Runs the simulation on the particles for the time
*   param **p:           pointer to memory with particles
*/
void simulateFunction(Particle **p) {
    int cT = 0;
    int pC = sizeof(p) / sizeof(Particle);

    // Iterate cT as specified by input
    while (cT < time) {
        // Increment the particles position by their velocities
        for (int i = 0; i < pC; i++) {
            Particle *pT = p[i];

            // Confirm that the movement is in bounds
            if (pT->pX + pT->vX < maxX && pT->pX + pT->vX > 0 &&
                pT->pY + pT->pY < maxY && pT->pY + pT->vY > 0) {
                
                pT->pX += pT->vX; 
                pT->pY += pT->vY;
           
                // Handle collision

            // Bound cases 
            } else {
                // Changed X is too big
                if (pT->pX + pT->vX >= maxX) {
                    // Y is too big too
                    if (pT->pY + pT->pY >= maxY) {
                        

                    // Y is too small
                    } else if (pT->pY + pT->pY <= 0) {


                    // Y is chill                
                    } else {
                        
                    }

                // Changed X is too small
                } else if (pT->pX + pT->vX <= 0) {
                    // Y is too big too
                    if (pT->pY + pT->pY >= maxY) {


                    // Y is too small
                    } else if (pT->pY + pT->pY <= 0) {


                    // Y is chill
                    } else {
                        
                    }
                }
            }
        }        
    }
}

/*
*   writeFile: Makes array of simulation and writes to output file
*/
void writeFile(Particle **p,){
    
    int rows = maxY + 2;
    int cols = maxX + 2;

    char **array = (char **)malloc(rows * sizeof(char *));
    for (int i = 0; i < rows; i++){
        array[i] = (char *)malloc(cols * sizeof(char));
    }

    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            if (i == 0 || i == rows - 1 || j == 0 || j == cols - 1) {
                array[i][j] = '*';
            }
        }
    }




    
}