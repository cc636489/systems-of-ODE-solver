#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "solver_explicit_euler.h"
using namespace std;

void solver_explicit_euler( double * solution, double ** matrixA, double dt, int nvar)
{
   // declaration + allocation.
   double tempforward[nvar];

   // initialization.
   for (int i=0;i<nvar;++i){tempforward[i]=0.0;}

   // doing tempforward = (1+A*dt) * previous_solution.
   for (int i=0;i<nvar;++i)
   {
     for (int j=0;j<nvar;++j)
     {
#ifdef DEBUG
       cout << scientific << "matrixA[i][j] is:" << matrixA[i][j] << ", dt is:" << dt  << ",solution[j] is:" << solution[j] << endl;
#endif
       tempforward[i] += (dt * matrixA[i][j]) * solution[j] ; 
     }
     tempforward[i] += solution[i];
#ifdef DEBUG
     cout << "solution for this variable i at this time step is:" << scientific << tempforward[i] << endl;
#endif
   }
   
   // update the solution.
   for(int i=0;i<nvar;++i){solution[i] = tempforward[i];}

}

