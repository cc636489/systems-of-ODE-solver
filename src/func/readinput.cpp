#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include "readinput.h"
using namespace std;

void readinput(int * p_nvar, double ** p_initial, double *** p_matrixA, int * p_nsolver, double ** p_time, const string & filename)
{
 /* 
 * This function read input.dat file for problem declaration.
 *
 * Inputs:
 *  
 *   p_nvar: point to nvar, which is the number of unknowns in this problem.
 *   p_initial: point to a vector initial[nvar], which defines the initial condition for this problem.
 *   p_matrixA: point to a matrix matrixA[nvar][nvar], which defines the characteristic matrix of the problem dot(y)=Ay.
 *   p_nsolver: point to the option number of solvers, which contains the solution of this problem.
 *   
 * Outputs:
 *   
 *   None
 * 
 */
   // start reading from input file.
   string line;
   ifstream myfile (filename,ios_base::in);
   if (myfile.is_open())
     {
        // read the first line ==> number of variables/unknowns.
        getline(myfile,line); 
        istringstream iss_1(line);
        iss_1 >> *p_nvar;
#ifdef DEBUG
        cout << *p_nvar << endl;
#endif

        // read the second line ==> number of initial conditions.
        *p_initial = new double[*p_nvar];
        getline(myfile,line);
        istringstream iss_2(line);
        for (int i=0;i<*p_nvar;++i)
        { 
           iss_2 >> * (*p_initial + i);
#ifdef DEBUG
           cout << * (*p_initial + i) << endl;
#endif
        }

        // read the third bunch of lines ==> entry of matrix A 
        *p_matrixA = new double*[*p_nvar];
        for (int i=0;i<*p_nvar;++i) 
        { *(*p_matrixA + i) = new double[*p_nvar];}
        
        for (int i=0; (i<*p_nvar && getline(myfile,line)); ++i)
        {
          istringstream iss(line);
          for (int j=0;j<*p_nvar;++j)
          {
            iss >> *(*(*p_matrixA + i) + j);
#ifdef DEBUG
            cout << *(*(*p_matrixA + i) + j) << endl;
#endif
          }
#ifdef DEBUG
          cout << line << '\n';
#endif
        }
        
        // read the fourth bunch of lines ==> option of solvers
        getline(myfile,line);
        istringstream iss_4(line);
        iss_4 >> *p_nsolver;
#ifdef DEBUG
        cout << *p_nsolver << endl;
#endif
       
        // read the fifth line ==> about the time scale of the problem.[startime, endtime, timestepping]
        *p_time = new double[3];
        getline(myfile,line);
        istringstream iss_5(line);
        for (int i=0;i<3;++i)
        {
           iss_5 >> * (*p_time + i);
#ifdef DEBUG
           cout << * (*p_time + i) << endl;
#endif
        }

        // finish reading the file, close the file.
        myfile.close();
        
     }
   else cout << "Unable to open file";

}

