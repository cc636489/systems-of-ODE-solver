#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <cmath>
#include "solver_explicit_euler.h"
#define DT 0.0001
using namespace std;

int test_solver_explicit_euler()
{
 /*
 * This function is a unit test function, to test the local truncation error within one time step. 
 * The problem used here for this test is an simple exponential ODE y'=2y, with y(0)=1.
 * Now given time horizon [0,1], using time step = 0.001, Theorem guarantees one-step method will converge.
 * The analytical solution for this problem is: y=e_2t.
 */

  double currT = 0.0;
  double endT   = 1.0;
  double deltaT = DT; // for explicit euler method to get a relatively small bounded global error.
  double currsolution = 1.0;
  double truesolution = 1.0;
  double ** matrixA = new double*[1]; * matrixA = new double[1]; ** matrixA = 2.0;
  double sumerror = 0.0;
  double TOL = 1e-3;
  double error2norm;
  double currerror;

  int nstep = int((endT-currT)/deltaT);

  cout << "solver_explicit_euler():" << endl;
  cout << setprecision(16) << scientific;

  for (int i=1;i<=nstep;++i)
  {
    currT += deltaT;
    truesolution = exp(2 * currT);
    solver_explicit_euler( & currsolution, matrixA, deltaT, 1);
    currerror = abs(truesolution - currsolution)/truesolution;
#ifdef DEBUG
    cout << "-- currT:    " << currT << endl;
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
  cout << "Last timestep Golbal Error is: " << currerror << endl;
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

int main(void)
{
  int ret = 0;
  ret |= test_solver_explicit_euler();
  return ret;
}

