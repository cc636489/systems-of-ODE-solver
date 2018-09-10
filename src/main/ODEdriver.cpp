#include "readinput.h"
#include "solver.h"
using namespace std;


int main(int argc, char *argv[])
{

  // read in filename from command line option.
  string filename;

  if (argc == 1){
    cout << " ERROR: No input filename string found! Program will exit shortly..." << endl;
    exit(1);
  }else if (argc == 2){
    cout << " get input filename, Program starts..." << endl;
    filename = argv[1];
  }else{
    cout << " ERROR: too many command line inputs found! Prgram will exit shortly..." << endl;
    exit(1);
  }

  // declaration + allocation + initialization.
  int  nvar = 0;
  int  nsolver = 0;
  double * time = 0;
  double * initial = 0;
  double * solution= 0;
  double ** matrixA= 0;
  
  // read other input parameters from filename.
  readinput( & nvar, & initial, & matrixA, & nsolver, & time, filename);

#ifdef DEBUG
  // make sure I read in file correctly.
  cout << "input filename is:" << filename << endl;
  cout << "nvar is:" << nvar << endl;
  cout << "nsolver is:" << nsolver << endl;
  cout << "startime is:" << time[0] << endl;
  cout << "endtime is:" << time[1] << endl;
  cout << "time stepping is:" << time[2] << endl;
  for (int i=0;i<nvar;++i){
    cout << "initial condition[" + to_string(i) + "] is:" << initial[i] << endl;}
  for (int i=0;i<nvar;++i){
    for (int j=0;j<nvar;++j){
      cout << "matrixA[" + to_string(i) + "][" + to_string(j) + "] is:" << matrixA[i][j] << endl;}}
#endif

  // solve the problem and write into file.
  solver(initial, & solution, matrixA, nsolver, nvar, time);
 
  // deallocation.
  delete [] time;
  delete [] initial;
  delete [] solution;
  for (int i=0;i<nvar;++i){delete [] matrixA[i];}
  delete matrixA;

  return 0;
}



















