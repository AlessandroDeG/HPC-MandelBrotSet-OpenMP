#include "walltime.h"
#include <math.h>
#include <stdlib.h>
#include <omp.h>

int main(int argc, char *argv[]) {
  
  double up = 1.00000001;
  double Sn = 1.00000001;

  // int N = 2000000000;
   int N = 20000000;
   //int N = 200000;
   //int N = 2000;
   //int N = 20;

     printf(" %d " ,N);
   
   //int N = 3;
  //double up = 3;
  //double Sn = 2;
  int n;
  /* allocate memory for the recursion */
  double *opt = (double *)malloc((N + 1) * sizeof(double));

  if (opt == NULL)
    die("failed to allocate problem size");

  double time_start = wall_time();
  // TODO: YOU NEED TO PARALLELIZE THIS LOOP
  
  double num=Sn;
#pragma omp parallel for firstprivate(Sn, up,num) lastprivate(Sn)
  for (n = 0; n <= N; ++n) {
    
    Sn =num * pow(up,(n));
    opt[n] = Sn;
    //printf(" %d  %lf\n" ,n,Sn);
    
  }

  //for (int n = 0; n <= N; ++n) {
  //    printf(" %f " ,opt[n]);
  //}

  printf("\nParallel RunTime   :  %f seconds\n", wall_time() - time_start);
  printf("Final Result Sn    :  %.17g \n", Sn);

  double temp = 0.0;
  for (n = 0; n <= N; ++n) {
    temp += opt[n] * opt[n];
  }
  printf("Result ||opt||^2_2 :  %f\n", temp / (double)N);
  printf("\n");

  return 0;
}
