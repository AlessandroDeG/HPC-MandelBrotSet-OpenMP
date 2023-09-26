// #include <omp.h>
#include "walltime.h"
#include <iostream>
#include <math.h>
#include <stdio.h>
#include <unistd.h>
#include <omp.h>
#include <fstream>

#define NUM_ITERATIONS 100

// Example benchmarks
// 0.008s ~0.8MB
//#define N 100000
// 0.1s ~8MB
// #define N 1000000
// 1.1s ~80MB
// #define N 10000000
// 13s ~800MB
// #define N 100000000
// 127s 16GB
//#define N 1000000000
#define EPSILON 0.1

using namespace std;

int main() {
  double time_serial, time_start = 0.0;
  double *a, *b;
  //int nThreads=16;
  int Ni=100000;
  int maxN=1000000000;
  //int maxN=100000;
  int stepN=10;
  long double alpha=0;

  omp_set_dynamic(0);
  for(int N=Ni;N<=maxN;N*=stepN){

      // Allocate memory for the vectors as 1-D arrays
      a = new double[N];
      b = new double[N];

      // Initialize the vectors with some values
      for (int i = 0; i < N; i++) {
        a[i] = i;
        b[i] = i / 10.0;
      }


      // serial execution
      // Note that we do extra iterations to reduce relative timing overhead
      time_start = wall_time();
      
      
      for (int iterations = 0; iterations < NUM_ITERATIONS; iterations++) {
        alpha = 0.0;
        for (int i = 0; i < N; i++) {
          alpha += a[i] * b[i];
        }
      }
      
      time_serial = wall_time() - time_start;
      cout << "Serial execution time = " << time_serial << " sec" << endl;
      



    for(int nThreads=1;nThreads<=24;nThreads++){
    
   

  

      long double alpha_parallel1 = 0;
      long double alpha_parallel2 = 0;
      double time_red = 0;
      double time_critical = 0;

      //   TODO: Write parallel version (2 ways!)
      //   i.  Using reduction pragma
      //   ii. Using  critical pragma

      
      omp_set_num_threads(nThreads);

      time_start = wall_time();
      for (int iterations = 0; iterations < NUM_ITERATIONS; iterations++) {
        alpha_parallel1 = 0.0;
        int i=0;
        #pragma omp parallel for default(shared) private(i) reduction(+:alpha_parallel1)  
          for (i = 0; i < N; i++) {
            alpha_parallel1 += a[i] * b[i];
          }
      
      }
      time_red = wall_time() - time_start;

      time_start = wall_time();
      for (int iterations = 0; iterations < NUM_ITERATIONS; iterations++)
      {
        alpha_parallel2 = 0.0;
        #pragma omp parallel
        {
          long double sum=0; 
          #pragma omp for 
          for (int i = 0; i < N; i++) {
              sum+= a[i] * b[i];
          } 

          #pragma omp critical
          alpha_parallel2+=sum;
      }
      }
      time_critical = wall_time() - time_start;
      
      if ((fabs(alpha_parallel1 - alpha) / fabs(alpha_parallel1)) > EPSILON) {
        cout << "parallel reduction: " << alpha_parallel1 << ", serial: " << alpha
            << "\n";
        cerr << "Alpha reduction not yet implemented correctly!\n";
        exit(1);
      }
      if ((fabs(alpha_parallel2 - alpha) / fabs(alpha_parallel2)) > EPSILON) {
        cout << "parallel critical: " << alpha_parallel2 << ", serial: " << alpha
            << "\n";
        cerr << "Alpha critical not yet implemented correctly!\n";
        exit(1);
      }
      

      //cout << "Parallel dot product= " << alpha
          //<< "\n Parallel dot product reduction= " << alpha_parallel1
          //<< "\n Parallel dot product critical= " << alpha_parallel2
      cout << "time using reduction method " <<  time_red << " sec"
          << "\n time using critical method " << time_critical << " sec"
          << endl;


        std::ofstream myfile;
        myfile.open ("results.csv", std::ios::app);
        myfile << nThreads<<";";
        myfile << N <<";";
        myfile << time_serial <<";";
        myfile << time_red<<";";
        myfile << time_critical<<";";
        myfile << "\n";
        myfile.close();
        
        
        
       
        
    }
     // De-allocate memory
        delete[] a;
        delete[] b;
  }
    




  return 0;
}
