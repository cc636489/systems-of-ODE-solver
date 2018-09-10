#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "writeoutput.h"
using namespace std;

void writeoutput(double Tcurr, double * solution, int size , ofstream & myfile)
{
 /* 
 * This function write output.dat file of the porblem.
 *
 * Inputs:
 *  
 *   p_solution: pointer to array of solution.
 *   size: the number of unknowns in this problem.
 *   
 * Outputs:
 *   
 *   None
 * 
 */
      myfile << scientific << setprecision(5) << Tcurr << " ";
      for (int i=0;i<size;++i)
      {
        myfile << setprecision(5) << scientific << solution[i] << " ";
      }
      myfile << "\n";
}
