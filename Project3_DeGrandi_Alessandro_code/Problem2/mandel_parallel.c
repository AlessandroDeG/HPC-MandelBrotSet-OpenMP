#include <stdio.h>
#include <stdlib.h>

#include <sys/time.h>
#include <time.h>
#include <unistd.h>

#include "consts.h"
#include "pngwriter.h"
#include <math.h>
#include <omp.h>



unsigned long get_time() {
  struct timeval tp;
  gettimeofday(&tp, NULL);
  return tp.tv_sec * 1000000 + tp.tv_usec;
}

int main(int argc, char **argv) {

  png_data *pPng = png_create(IMAGE_WIDTH, IMAGE_HEIGHT);

  //double x, y, x2, y2, 
  double cx, cy; 
  cy = MIN_Y;

  double fDeltaX = (MAX_X - MIN_X) / (double)IMAGE_WIDTH; 
  double fDeltaY = (MAX_Y - MIN_Y) / (double)IMAGE_HEIGHT;

  //printf("%f\n",fDeltaX);
  //printf("%f\n",fDeltaY);

  unsigned long nTotalIterationsCount = 0;
  unsigned long nTimeStart = get_time();

  long i, j;

  
  // do the calculation
  
  for (j = 0; j < IMAGE_HEIGHT; j++) {
      //cx = MIN_X;
      int firstThreadIter=0;
      
       #pragma omp parallel for private(cx,firstThreadIter) reduction(+:nTotalIterationsCount)
    for (i = 0; i < IMAGE_WIDTH; i++) {
       //need to make sure that starting cx of thread is mapped to starting i
       //problem if WIDTH not divisible by NUM_THREADS
       /*
       if(i==((IMAGE_WIDTH/omp_get_num_threads())*omp_get_thread_num())){
              cx=MIN_X+((MAX_X-MIN_X)/omp_get_num_threads())*omp_get_thread_num();
              if(j==0){
                     
                     printf("%d, %lf\n",i,cx);
              }
       }

        *///different way
       /*
       if(firstThreadIter==0){
              firstThreadIter++;
              //got the starting i for the thread, map it to parameters space, get starting cX
              cx= MIN_X+ (i * fDeltaX);
                printf("%d, %lf\n",i,cx);
              
       }

       */ // is it round robin?? oh well, calculate cx for every i using the increment
       cx= MIN_X+(fDeltaX*i);
       //if(j==0){
       //printf("%d, %d, %lf\n",omp_get_thread_num(),cx);
       //}
      
       
              
       
       
      //cx = fDeltaX*i;
      double x = cx;
      double y = cy;
      double x2 = x * x;
      double y2 = y * y;
      // compute the orbit z, f(z), f^2(z), f^3(z), ...
      // count the iterations until the orbit leaves the circle |z|=2.
      // stop if the number of iterations exceeds the bound MAX_ITERS.
      // TODO
      // >>>>>>>> CODE IS MISSING
      long n = 0;
      
      for(n=0;x2+y2<=2 && n<MAX_ITERS;n++){
             //(x+yi)*(x+yi)=x2+2xyi-y2
             //= x2-y2   +   2xyi
             
             y=2*y*x+cy;
             x=x2-y2+cx;

             x2 = x*x;
             y2= y*y; 
      }
      nTotalIterationsCount += n;
      //printf("iter:%ld\n",nTotalIterationsCount);
       
      // <<<<<<<< CODE IS MISSING
      // n indicates if the point belongs to the mandelbrot set
      // plot the number of iterations at point (i, j)
      
      
     
       int c = ((long)n * 255) / MAX_ITERS;
      
      //printf("%d",c);
      //png_plot(pPng, i, j, c/3, c/2, c);
      //#pragma omp critical
      png_plot(pPng, i, j, c, c, c);
      
      //cx += fDeltaX;
    }
    
    cy += fDeltaY;
  }
  unsigned long nTimeEnd = get_time();

  //Test
  printf("MaxIter: %ld\n", MAX_ITERS);
  printf("X: %f->%f\n", MIN_X,MAX_X);
  printf("Y: %f->%f\n", MIN_Y,MAX_Y);

  // print benchmark data
  printf("Total time:                 %g milliseconds\n",
         (nTimeEnd - nTimeStart) / 1000.0);
  printf("Image size:                 %ld x %ld = %ld Pixels\n",
         (long)IMAGE_WIDTH, (long)IMAGE_HEIGHT,
         ((long)IMAGE_WIDTH * (long)IMAGE_HEIGHT));
  printf("Total number of iterations: %ld\n", nTotalIterationsCount);
  printf("Avg. time per pixel:        %g microseconds\n",
         (nTimeEnd - nTimeStart) / (double)((long)IMAGE_WIDTH * (long)IMAGE_HEIGHT));
  printf("Avg. time per iteration:    %g microseconds\n",
         (nTimeEnd - nTimeStart) / (double)nTotalIterationsCount);
  printf("Iterations/second:          %g\n",
         nTotalIterationsCount / (double)(nTimeEnd - nTimeStart) * 1e6);
  // assume there are 8 floating point operations per iteration
  printf("MFlop/s:                    %g\n",
         nTotalIterationsCount * 8.0 / (double)(nTimeEnd - nTimeStart));

  png_write(pPng, "mandel.png");
  return 0;
}
