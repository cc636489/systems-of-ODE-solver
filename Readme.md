
# Program for solving system of ODEs.

This is a C++ solution to solve system of ODEs.

## Dependency:

This program requires **C++ 11** and the following C library installed:

- [GSL](https://www.gnu.org/software/gsl/) : Scientific GNU library.


## Inputs.

* line1: int `nvar`. ==> the number of unknowns.
* line2: double `vector(nvar)`. ==> initial condition. 
* line3: double `matrix[nvar][nvar]`. ==> matrix entry enter.
* line4: int `nsolver`. ==> option of solvers.

        1==explicit euler.
        2==rk4.
        3==rk45.
        4==rk8.

* line5: double `time[3]` ==> time horizon[Tstart, Tend, deltaT].

Two input files `input1.dat` & `input2.dat` are given in root directory.

## Outputs.

* column1: time stamp.
* column2~column(nvar+1): time series of unknown[i] (i = 1 to nvar).

One output file `output.dat` is given in root directory.


## Execution.

- `make` or `make all` will compile the code and produce an executable `ODEdriver`

* Makefile_v1: initial tedious version with all the source and header files at current directory.
* Makefile_v2: final neat version with subdirectory been built. Mark the use of GNU make macro `vpath`.
* Makefile: copy of Makefile_v2.
  
- when running the executable, user is supposed to enter input filename(or fullpath+filename) as a command line option. 

        ./ODEdriver input1.dat


- when program finished running, it will produce an output containing the time series of each unknowns.

        output.dat


## Tests and Analysis.

### Test1:

Given a simple ODE: 
        
        dy/dt=2y, with y(0)=1. 
        
        
- Utilized different implemented method: forward euler and runge katta(rk4, rkf45, rk8pd). 
- Verification based on error bounds with true analytical solution.
- Convergence rate for all methods: 1st order convergence for forward euler. And fast convergence(error within machine precision) for 3 runge katta methods.

<p align="center">
<img width="440" height="300" src="/doc/convergence_euler.png"> <img width="440" height="300" src="/doc/convergence_rk.png">
</p>


### Test2:

If you want to know the trajectory x(t) of the particle shown below, which is governed by a set of three second order differ-ential equations:

<p align="center">
<img src="/doc/ode_1.png">
</p>


where ω and τ are constants. An initial value problem of this type needs 3×2 = 6 initial conditions. These are given as the initial position x0= (x0,y0,z0) and the initial velocity V0 = (u0,v0,w0) of the particle.

In order to solve the equations above numerically, they have to be rewritten as a set of six first order differential equations:

<p align="center">
<img src="/doc/ode_2.png">
</p>


Here is the final trajectory of x(t) given by this program:
<p align="center">
<img src="/doc/ODE_trajectory.png">
</p>

### Run tests:

The following commands will both run the simple test case. 

        make check
        make test



