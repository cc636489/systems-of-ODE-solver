#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "solver.h"
#include "solver_explicit_euler.h"
#include "solver_runga_katta.h"
#include "writeoutput.h"
using namespace std;

void solver(double * initial, double ** p_solution, double ** matrixA, int nsolver, int nvar, double * time)
{
 /* 
 * This function solve the porblem.
 *
 * Inputs:
 *  
 *   initial: initial condition vector.
 *   p_solution: pointer to solution vector.
 *   matrixA: model matrix
 *   nsolver:  the number of method chosen.
 *   nvar: problem dimension.
 *   time: time vector contains Tstart/Tend/dt.
 *   
 * Outputs:
 *   
 *   None
 * 
 */
  
  // initialization local variables.
  int nstep = int( (time[1]-time[0])/time[2] );

  // allocation + initialization of the solution.
  *p_solution = new double [nvar];
  for (int i=0;i<nvar;++i){ *(*p_solution+i) = initial[i]; } 
  
  // start output file IO.
  ofstream myfile ("output.dat", ios_base::out);
  if (myfile.is_open()){

     // write to file initially.
     myfile << "writing solution in this file:\n";
     writeoutput(time[0] , * p_solution, nvar, myfile);
     
     // start time counting for each time stepping iteration.
     const clock_t begin_time = clock();

     // start the solver.
     for (int i=1;i<=nstep;++i){

       // solve within this time step, using explicit euler || rk4 || rk5 || rk45.
       if (nsolver == 1)
       {
          solver_explicit_euler( * p_solution, matrixA, time[2], nvar);

       }else if (nsolver == 2 || nsolver == 3 || nsolver == 4){
          
          solver_runga_katta( * p_solution, matrixA, time, nvar, nsolver, i);

       }else{

          cout << "ERROR: no solver provided, no further solution will be writen into file." << endl;
       
       }

       // check if the solution is as expected.
       cout << "Timestep[" + to_string(i) + "]:" << endl;
       for (int j=0;j<nvar;++j)
         {cout << " Solution[" + to_string(j) + "] is: " << scientific  << setprecision(5) << *(*p_solution + j) << endl;}

       // write the computed solution to file.
       double Tcurr = time[0] + time[2] * i;
       writeoutput(Tcurr, * p_solution, nvar, myfile);
      
       // end time calculating for this iteration,
       cout << "Total time ecalpse(unit: second): " << scientific << setprecision(5) << double( clock () - begin_time ) / double(CLOCKS_PER_SEC) << endl;
       cout << "\n";
     } 
         
  }else cout << "Unable to open file";

  myfile.close();    

}


