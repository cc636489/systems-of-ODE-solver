#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <stdio.h>
#include <cmath>
#include <gsl/gsl_errno.h>
#include <gsl/gsl_matrix.h>
#include <gsl/gsl_odeiv.h>
#include "solver_runga_katta.h"
using namespace std;

struct matrixcomb
{
  int nvar;
  double ** matrixA;
};

int func (double t, const double y[], double f[], void *params)
{
  matrixcomb * p_struct = (matrixcomb *)params;
  
  for (int i=0;i<(*p_struct).nvar;++i){
    f[i] = 0.0;
    for (int j=0;j<(*p_struct).nvar;++j){
      f[i] += (*p_struct).matrixA[i][j] * y[j];
    }
  } 
  
  return GSL_SUCCESS;
}

int jac (double t, const double y[], double *dfdy, double dfdt[], void *params)
{
  matrixcomb * p_struct = (matrixcomb *)params;
  gsl_matrix_view dfdy_mat = gsl_matrix_view_array (dfdy, (*p_struct).nvar, (*p_struct).nvar);
  gsl_matrix * m = &dfdy_mat.matrix; 

  for (int i=0;i<(*p_struct).nvar;++i){
    for (int j=0;j<(*p_struct).nvar;++j){
      gsl_matrix_set (m, i, j, (*p_struct).matrixA[i][j]);  } } 
  for (int i=0;i<(*p_struct).nvar;++i){dfdt[i]=0.0;}

  return GSL_SUCCESS;
}


void solver_runga_katta(double * solution, double ** matrixA, double * time, int nvar, int nsolver, int timestep)
{

  double t  = time[0] + ( timestep - 1 ) * time[2];
  double ti = time[0] + timestep * time[2];
  double h  = 1e-6;    
  double eps_abs = 1e-8;
  double eps_rel = 0.0;
  const gsl_odeiv_step_type * T; 

  matrixcomb gslmatrix;
  gslmatrix.nvar = nvar;
  gslmatrix.matrixA = matrixA;

  if (nsolver == 2){
     T = gsl_odeiv_step_rk4;
  }else if(nsolver == 3){
     T = gsl_odeiv_step_rkf45;
  }else if(nsolver == 4){
     T = gsl_odeiv_step_rk8pd;
  }else{
     cout << "ERROR: no solver found!" << endl;
     exit(1);
  }
  gsl_odeiv_step * s    = gsl_odeiv_step_alloc (T, nvar);
  gsl_odeiv_control * c = gsl_odeiv_control_y_new (eps_abs, eps_rel);
  gsl_odeiv_evolve * e  = gsl_odeiv_evolve_alloc (nvar);
  gsl_odeiv_system sys = {func, jac, nvar, &gslmatrix};

  while ( t < ti ){
  
    int status = gsl_odeiv_evolve_apply (e, c, s, &sys, &t, ti, &h, solution);
    
    if (status != GSL_SUCCESS) break;

#ifdef DEBUG
    for (int i=0;i<nvar;++i){
      cout << "In this iteration, solution[" + to_string(i) + "] is:" << solution[i] << " " << endl;}
#endif

  }
  
  gsl_odeiv_evolve_free (e);
  gsl_odeiv_control_free (c);
  gsl_odeiv_step_free (s);


}

