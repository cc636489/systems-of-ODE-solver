#######################################################

This is an Introduction on how to use the ODEsolver

#######################################################

1. input file introduction.

 line1: int nvar. ==> the number of unknowns.
 line2: double vector(nvar). ==> initial condition. 
 line3: double matrix[nvar][nvar]. ==> matrix entry enter.
 line4: int nsolver. ==> option of solvers.
    
    1==explicit euler.
    2==rk4.
    3==rk45.
    4==rk8.

 line5: double time[3] ==> time horizon[Tstart, Tend, deltaT].

 There are two sample input files provided in this directory.

2. compile the code and run it.

 "make" or "make all" will compile the code and produce an executable "ODEdriver"

 Makefile_v1: is an initial tedious version with all the source and header files at current directory.
 Makefile_v2: is an final neat version with subdirectory been built. Mark the use of GNU make macro "vpath".
 Makefile: is an copy of Makefile_v2.
  
 when running the program, user is surposed to enter input filename(or fullpath+filename) as a command line option. 
     ./ODEdriver input1.dat

 when program finished running, it will produce an output containing the time series of each unknowns.
      output.dat

3. output file introduction.

 column1: time stamp.
 column2~column(nvar+1): time series of unknown[i] (i = 1 to nvar).

4. verification of the solver. 

 "make check" or "make test" will run an test case of the 4 underlying solvers.
 In verification/ folder, gives the convergence analysis for the 4 solvers. 
 And a result for the particle test case.

#########################################################

                    Enjoy!

#########################################################
