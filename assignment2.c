// Will Otterbein       A##
// Raymond Xie          A##
// Lucas Laviolette     A##
// Calvin Lee           A00922317

#include <stdio.h>
#include <stdlib.h>

// Definitions

// Method headers
Particle** readFile(int *pa);
void simulateFunction(Particle **p, int *particleCount);
void writeFile(Particle **p, int *particleCount);
void printErrorExit();
Particle* makeParticle(int px, int py, int vx, int vy);
void destroyParticle(Particle *p);
void freeMemory(Particle **pArr, int *particleCount);

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
    Particle **particleArray = readFile(&particleCount);
    
    // create 2d array with a border

    simulateFunction(particleArray, &particleCount);

    // free up all particles and arrays
    freeMemory(particleArray, &particleCount);
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
    p->vY = vy;
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
*   param *particlecount:   pointer to the variable storing the number of particles
*   returns:    pointer arr
*/
Particle** readFile(int *particlecount) {
    
    // update particle counter
    // read number of lines in input file, subtract first two lines to get correct count
    char check = 0;
    while ((check = fgetc(in)) != 'E') {
        if (check == '\n') *particlecount++;
    }
    *particlecount = *particlecount - 2;

    // create array that stores the particles
    Particle **pArr = malloc(*particlecount * sizeof(Particle));

    // set buffer back to beginning
    char buff[10];
    fseek(in, 0, SEEK_SET);
    fgets(buff, 10, in); // read max x
    sscanf(buff, "%d", &maxX);
    fgets(buff, 10, in); // read max y
    sscanf(buff, "%d", &maxY);
    int count = 0;
    while(fgets(buff, 10, in) != NULL) {
        int pXtemp = 0;
        int pYtemp = 0;
        int vXtemp = 0;
        int vYtemp = 0;
        if (sscanf(buff, "%d,%d,%d,%d", &pXtemp, &pYtemp, &vXtemp, &vYtemp) != EOF) {
            Particle *p = makeParticle(pXtemp, pYtemp, vXtemp, vYtemp);
            pArr[count++] = p; 
        } 
    }

    return pArr;
}

/*
*   simulateFunction:     Runs the simulation on the particles for the time
*   param **p:            pointer to array with particles
*   param *particleCount: the number of particles in the array
*/
void simulateFunction(Particle **p, int *particleCount) {
    int cT = 0;
    int pC = *particleCount;

    // Iterate cT as specified by input
    while (cT < time) {
        // Increment the particles position by their velocities
        for (int i = 0; i < pC; i++) {
            Particle *pT = p[i];
            // new positions
            int nX = pT->pX + pT->vX;
            int nY = pT->pY + pT->vY;

            // check x position, rebound and update velocity if necessary
            if (nX < 0) {
                nX = -nX;
                pT->vX = -(pT->vX);
            }
            else if (nX > maxX - 1) {
                nX = (maxX - (nX - maxX) - 1);
                pT->vX = -(pT->vX);
            }
            // check y position, rebound and update velocity if necessary
            if (nY < 0) {
                nY = -nY;
                pT->vY = -(pT->vY);
            }
            else if (nY > maxY - 1) {
                nY = (maxY - (nY - maxY) - 1);
                pT->vY = -(pT->vY);
            }

            // update the position of the particle
            pT->pX = nX;
            pT->pY = nY;
        }

        // finally check if particles collided or not before running next iteration
        for (int i = 0; i < pC; i++) {
            for (int j = i + 1; j < pC; j++) {
                if (p[i]->pX == p[j]->pX && p[i]->pY == p[j]->pY) {
                    destroyParticle(p[i]);
                    destroyParticle(p[j]);
                    pC -= 2;
                }
            }
        }
        cT++;      
    }
}

/*
*   writeFile:              Makes array of simulation and writes to output file
*   param **p:              pointer to memory with particles
*   param *particleCount:   Amount of particles in p 
*/
void writeFile(Particle **p, int *particleCount){
    
    int rows = maxY + 2;
    int cols = maxX + 2;
    const int pC = *particleCount; 

    //allocating memory for array
    char **array = (char **)malloc(rows * sizeof(char *));
    for (int i = 0; i < rows; i++){
        array[i] = (char *)malloc(cols * sizeof(char));
    }

    //printing border on array
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            if (i == 0 || i == rows - 1 || j == 0 || j == cols - 1) {
                array[i][j] = '*';
            }
        }
    }

    //added particles to array
    for (int count = 0; count < pC; count++){
        Particle *pT = p[count];
        array[(pT->pY) + 1][(pT->pX) + 1] = '+';
    }

    //writing array to output file
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            fprintf(out, "%c ", array[i][j]);
        }
        fprintf(out, "\n");
    }

    //free array
    for (int i = 0; i < rows; i++){
        free(array[i]);
    }
    free(array);
}

/*
*   freeMemory:     Free up any used memory by remaining particles and its
*                   containing array.
*   param **p:      pointer to the array containing particles
*   param *particleCount:   the number of particles remaining in the array
*/
void freeMemory(Particle **pArr, int *particleCount) {
    for (int i = 0; i < *particleCount; i++) {
        free(pArr[i]);
        pArr[i] = NULL;
    }
    free(pArr);
    pArr = NULL;
}