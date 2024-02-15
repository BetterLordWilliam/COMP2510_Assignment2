// Will Otterbein       A01372608
// Raymond Xie          A##
// Lucas Laviolette     A##
// Calvin Lee           A00922317

#include <stdio.h>
#include <stdlib.h>

// Structs
typedef struct {
    int pX;
    int pY;
    int vX;
    int vY;
} Particle;

// Method headers
Particle** readFile(int *particleCount);
void simulateFunction(Particle **p, int *particleCount);
void writeFile(Particle **p, int *particleCount);
void printErrorExit();
Particle* makeParticle(int pX, int pY, int vx, int vy);
void destroyParticle(Particle *p);
void freeMemory(Particle **pArr, int *particleCount);

// Constants
FILE *in;
FILE *out;
 
int maxX;
int maxY;
int time;

/*
*   main: main method of program
*/
int main(int argc, char *argv[]) {
    if (argc != 3) {
        return 1;
    }

    printf("Here MM\n");
    
    // Read command line args
    in = fopen(argv[1], "r");
    out = fopen(argv[2], "w");
    if (in == NULL || out == NULL) printErrorExit(); // exit if problem opening files

    // Read input file:
    // update the bor
    // get a pointer to an array of particle objects
    int particleCount = 0;
    Particle **particleArray = readFile(&particleCount);
    
    // create 2d array with a border
    simulateFunction(particleArray, &particleCount);

    // Create output lol
    writeFile(particleArray, &particleCount);

    // free up all particles and arrays
    // freeMemory(particleArray, &particleCount);
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
Particle* makeParticle(int pX, int pY, int vx, int vy) {
    Particle *p = malloc(sizeof(Particle));
    p->pX = pX;
    p->pY = pY;
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
}

/* 
*   readFile:   reads the file input, assign maxX and maxY and read particles
*   param *particleCount:   pointer to the variable storing the number of particles
*   returns:    pointer arr
*/
Particle** readFile(int *particleCount) {
    
    // create 2d array with a border
    // update particle counter
    // read number of lines in input file, subtract first three lines to get correct count
    char check = 0;
    while ((check = fgetc(in)) != 'E') {
       // printf("Here 1 RF --> during number count loop, %d\n", *particleCount);
        if (check == '\n'){
            *particleCount = (*particleCount + 1);
        }
    }
    *particleCount = *particleCount - 3;

    // create array that stores the particles
    Particle **pArr = malloc(*particleCount * sizeof(Particle*));

    // set buffer back to beginning
    char buff[10];
    fseek(in, 0, SEEK_SET);
    fgets(buff, 10, in); // read max x
    sscanf(buff, "%d", &maxX);
    fgets(buff, 10, in); // read max y
    sscanf(buff, "%d", &maxY);
    fgets(buff, 10, in); // read time
    sscanf(buff, "%d", &time);
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

    printf("Here SF\n");
    // create 2d array with a border
    // Iterate cT as specified by input
    while (cT < time) {
        // Increment the particles position by their velocities
        for (int i = 0; i < *particleCount; i++) {
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
                nX = (maxX - (nX - maxX));
                pT->vX = -(pT->vX);
            }
            // check y position, rebound and update velocity if necessary
            if (nY < 0) {
                nY = -nY;
                pT->vY = -(pT->vY);
            }
            else if (nY > maxY - 1) {
                nY = (maxY - (nY - maxY));
                pT->vY = -(pT->vY);
            }

            printf("pX%d, pY%d\n", nX, nY);

            // update the position of the particle
            pT->pX = nX;
            pT->pY = nY;
        }

        // finally check if particles collided or not before running next iteration
        for (int i = 0; i < *particleCount; i++) {
            for (int j = i + 1; j < *particleCount; j++) {
                if (p[i] != NULL && p[j] != NULL && (p[i]->pX == p[j]->pX && p[i]->pY == p[j]->pY)) {
                    //destroyParticle(p[i]);
                    p[i] = NULL;
                    //destroyParticle(p[j]);
                    p[j] = NULL;
                }
            }
        }
        cT++;      
    }
}

/*
*   writefile:              makes array of simulation and writes to output file
*   param **p:              pointer to memory with particles
*   param *particleCount:   amount of particles in p 
*/
void writeFile(Particle **p, int *particleCount){
    
    printf("Here WF\n");
    // create 2d array with a border
    int rows = maxY + 2;
    int cols = maxX + 2;

    // allocating memory for array
    char **array = (char **)malloc(rows * sizeof(char *));
    for (int i = 0; i < rows; i++){
        array[i] = (char *)malloc(cols * sizeof(char));
    }

    // printing border of array
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            if (i == 0 || i == rows - 1 || j == 0 || j == cols - 1) {
                array[i][j] = '*';
            }
            else array[i][j] = ' ';
        }
    }


    // added particles to array
    for (int count = 0; count < *particleCount; count++){
        Particle *pt;
        if (p[count] != NULL) {
            printf("%p\n", p[count]);
            pt = p[count];
            printf("%d, %d\n", pt->pX, pt->pY);
            array[maxY - (pt->pY)][(pt->pX) + 1] = '+';
        } else {
            continue;
        }
    }

    // writing array to output file
    for (int i = 0; i < rows; i++){
        for (int j = 0; j < cols; j++){
            fprintf(out, "%c", array[i][j]);
        }
        if (i != rows - 1)
            fprintf(out, "\n");
    }

    // free array
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
    printf("Here FM\n");
    // create 2d array with a border
    for (int i = 0; i < *particleCount; i++) {
        free(pArr[i]);
        pArr[i] = NULL;
    }
    free(pArr);
    pArr = NULL;
}