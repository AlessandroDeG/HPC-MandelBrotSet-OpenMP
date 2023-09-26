#include "walltime.h"
#include <iostream>
#include <random>
#include <omp.h>
#include <fstream>

#define VEC_SIZE 1000000000
#define BINS 16

using namespace std;

int main() {
  double time_start, time_end;

  // Initialize random number generator
  unsigned int seed = 123;
  float mean = BINS / 2.0;
  float sigma = BINS / 12.0;
  std::default_random_engine generator(seed);
  std::normal_distribution<float> distribution(mean, sigma);

  // Generate random sequence
  // Note: normal distribution is on interval [-inf; inf]
  //       we want [0; BINS-1]
  int *vec = new int[VEC_SIZE];
  for (long i = 0; i < VEC_SIZE; ++i) {
    vec[i] = int(distribution(generator));
    if (vec[i] < 0)
      vec[i] = 0;
    if (vec[i] > BINS - 1)
      vec[i] = BINS - 1;
  }
  // TODO Parallelize the histogram computation

  

  /* Initialize the lock on shared dist */
omp_set_dynamic(0);
//cout<<"maxt"<<omp_get_max_threads()<<endl;
for(int nThreads=1;nThreads<16385;nThreads*=2) {
  //for(int nThreads=1;nThreads<101;nThreads+=2) {
      omp_set_num_threads(nThreads);

      // Initialize histogram
      // Set all bins to zero
      long dist[BINS];
      omp_lock_t lockdist[BINS];
      for (int i = 0; i < BINS; ++i) {
        dist[i] = 0;
        
        omp_init_lock(&(lockdist[i]));
      }


        time_start = wall_time();
        
        
        #pragma omp parallel shared(vec,dist,lockdist)
        {
          int ID=omp_get_thread_num();
          if(ID==0){
            cout<<"nt: "<<omp_get_num_threads()<< endl;
          }
          long distPrivate[BINS];
          for (int i = 0; i < BINS; ++i) {
            distPrivate[i] = 0;
          }
          #pragma omp for
          for (long i = 0; i < VEC_SIZE; ++i) {
            distPrivate[vec[i]]++;
          }

          /*
          BOTTLENECK SOLUTION
          omp_set_lock(&lockdist);
          #pragma omp critical
            for (long i = 0; i < BINS; ++i) {
              dist[i]+=distPrivate[i];
            }
          #omp_unset_lock(&lockdist);
          */

          // SOLUTION 2
            for (long i = 0; i < BINS; ++i) {
             omp_set_lock(&(lockdist[i]));
              dist[i]+=distPrivate[i];
              omp_unset_lock(&(lockdist[i]));
            }



        }
        













        time_end = wall_time();

        // Write results
        for (int i = 0; i < BINS; ++i) {
          cout << "dist[" << i << "]=" << dist[i] << endl;
        }
        cout << "Time: " << time_end - time_start << " sec" << endl;

          std::ofstream myfile;
              myfile.open ("resultsHistParallel.csv", std::ios::app);
              myfile << nThreads<<";";
              myfile << time_end - time_start<<";";
              myfile << "\n";
              myfile.close();
              

        
 }
 delete[] vec;

  return 0;
}
