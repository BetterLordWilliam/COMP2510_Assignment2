# C Assignment 2 #

Check stuff of (X) or if a new task is discovered, add it.

<br></br>

## Thoughts ##
* Create structs for particles and velocities.
* Collect the input / output file names.
* Collect the number of seconds that the simulation will run for.
* Create function to open the files and assign them to FILE pointers.
* Create function to return a pointer to memory that contains all the particles on the board. Initialize structs for the particles scanned from the input file.
	- Initialize constants to represent the X and Y dimensions of the board.
	- Pass the pointer to the particles array as well as the simulation duration to a simulate function that will run the simulation with the parameters described in the assignment file.
	- Do so without creating an array? Could be *easier.*
* May need to create a search function, return pointer to particle structs that exist around a position?
* Maybe a check function, which is called before a particle continues on its path. Check function sees if another particle is present (loops through the particle array and returns the pointer to the particle if it exists).
* After completion of the simulate function, pass the particle array (which will contain the updated positions of the particles) to a printSimulation function. This will be output the game to the file.

If you have any thoughts, please add them to the readme.

<br></br>

## Tasks ##

* Agree on approach.
* Implement reading.
* Implement simulating.
* Implement writing.
