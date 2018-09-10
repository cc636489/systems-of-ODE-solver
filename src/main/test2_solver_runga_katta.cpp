#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <stdio.h>
#include <cmath>
#include "solver_runga_katta.h"
#define DT 0.1
using namespace std;



int test_solver_runga_katta_rk4()
{
  double time[3] = {0.0,1.0,DT}; // {currT,endT,deltaT} for explicit euler method to get a relatively small bounded global error.
  double currT = time[0];
  double currsolution = 1.0;
  double truesolution = 1.0;
  double ** matrixA = new double*[1]; * matrixA = new double[1]; ** matrixA = 2.0;
  double sumerror = 0.0;
  double TOL = 1e-3;
  double error2norm;
  double currerror;

  int nstep = int((time[1]-time[0])/time[2]);

  cout << "solver_runga_katta_rk4():" << endl;
  cout << setprecision(16) << scientific;

  for (int i=1;i<=nstep;++i)
  {

    currT += time[2];
    truesolution = exp(2 * currT);
    solver_runga_katta( & currsolution, matrixA, time, 1, 2, i);
    currerror = abs(truesolution - currsolution)/truesolution;
#ifdef DEBUG
    cout << "-- computed: " << currsolution << endl;
    cout << "-- expected: " << truesolution << endl;
    cout << "-- relerror: " << currerror << endl;
#endif

    cout << "timestep[" + to_string(i) + "] error is: " << currerror << endl;

#ifdef DEBUG
    cout << "\n";
#endif

    sumerror += pow( (truesolution-currsolution)/truesolution , 2);
  }

  error2norm = sqrt(sumerror);
  cout << "Last time step Golbal Error is: " << currerror << endl;
  cout << "Cumulate-in-time Golbal Error is: " << error2norm << endl;
  cout << "\n";

  if (currerror <= TOL) {
    cout << "\033[32;1mPASS \033[0m\n" << endl;
    return 0;
  }
  else {
    cout << "\033[31;1mFAIL \033[0m\n" << endl;
    return 1;
  }

}

int test_solver_runga_katta_rkf45()
{
  double time[3] = {0.0,1.0,DT}; // {currT,endT,deltaT} for explicit euler method to get a relatively small bounded global error.
  double currT = time[0];
  double currsolution = 1.0;
  double truesolution = 1.0;
  double ** matrixA = new double*[1]; * matrixA = new double[1]; ** matrixA = 2.0;
  double sumerror = 0.0;
  double TOL = 1e-3;
  double error2norm;
  double currerror; 

  int nstep = int((time[1]-time[0])/time[2]);

  cout << "solver_runga_katta_rkf45():" << endl;
  cout << setprecision(16) << scientific;


  for (int i=1;i<=nstep;++i)
  {

    currT += time[2];
    truesolution = exp(2 * currT);
    solver_runga_katta( & currsolution, matrixA, time, 1, 3, i);
    currerror = abs(truesolution - currsolution)/truesolution;
#ifdef DEBUG
    cout << "-- computed: " << currsolution << endl;
    cout << "-- expected: " << truesolution << endl;
    cout << "-- relerror: " << truesolution << endl;
#endif

    cout << "timestep[" + to_string(i) + "] error is: " << currerror << endl;

#ifdef DEBUG
    cout << "\n";
#endif

    sumerror += pow( (truesolution-currsolution)/truesolution , 2);
  }

  error2norm = sqrt(sumerror);
  cout << "Last time step Golbal Error is: " << currerror << endl;
  cout << "Cumulate-in-time Golbal Error is: " << error2norm << endl;
  cout << "\n";

  if (currerror <= TOL) {
    cout << "\033[32;1mPASS \033[0m\n" << endl;
    return 0;
  }
  else {
    cout << "\033[31;1mFAIL \033[0m\n" << endl;
    return 1;
  }


}

int test_solver_runga_katta_rk8pd()
{
  double time[3] = {0.0,1.0,DT}; // {currT,endT,deltaT} for explicit euler method to get a relatively small bounded global error.
  double currT = time[0];
  double currsolution = 1.0;
  double truesolution = 1.0;
  double ** matrixA = new double*[1]; * matrixA = new double[1]; ** matrixA = 2.0;
  double sumerror = 0.0;
  double TOL = 1e-3;
  double error2norm;
  double currerror;

  int nstep = int((time[1]-time[0])/time[2]);

  cout << "solver_runga_katta_rk8pd():" << endl;
  cout << setprecision(16) << scientific;

  for (int i=1;i<=nstep;++i)
  {

    currT += time[2];
    truesolution = exp(2 * currT);
    solver_runga_katta( & currsolution, matrixA, time, 1, 4, i);
    currerror = abs(truesolution - currsolution)/truesolution;
#ifdef DEBUG
    cout << "-- computed: " << currsolution << endl;
    cout << "-- expected: " << truesolution << endl;
    cout << "-- relerror: " << currerror << endl;
#endif

    cout << "timestep[" + to_string(i) + "] error is: " << currerror << endl;

#ifdef DEBUG
    cout << "\n";
#endif

    sumerror += pow( (truesolution-currsolution)/truesolution , 2);
  }

  error2norm = sqrt(sumerror);
  cout << "Last time step Golbal Error is: " << currerror << endl;
  cout << "Cumulative-in-time Golbal Error is: " << error2norm << endl;
  cout << "\n";

  if (currerror <= TOL) {
    cout << "\033[32;1mPASS \033[0m\n" << endl;
    return 0;
  }
  else {
    cout << "\033[31;1mFAIL \033[0m\n" << endl;
    return 1;
  }

}

int main(void)
{
  int ret = 0;
  ret |= test_solver_runga_katta_rk4();
  ret |= test_solver_runga_katta_rkf45();
  ret |= test_solver_runga_katta_rk8pd();
  return ret;
}



