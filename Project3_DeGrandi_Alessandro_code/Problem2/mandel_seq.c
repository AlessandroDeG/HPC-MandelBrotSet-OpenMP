#include <stdio.h>
#include <stdlib.h>

#include <sys/time.h>
#include <time.h>
#include <unistd.h>

#include "consts.h"
#include "pngwriter.h"

//#define IMAGE_HEIGHT 100
//#define IMAGE_WIDTH 100
//#define MAX_ITERS 100

//#define MIN_X -2.0f
//#define MAX_X 1.0f
//#define MIN_Y -1.0f
//#define MAX_Y 1.0f

unsigned long get_time() {
  struct timeval tp;
  gettimeofday(&tp, NULL);
  return tp.tv_sec * 1000000 + tp.tv_usec;
}

int main(int argc, char **argv) {
  png_data *pPng = png_create(IMAGE_WIDTH, IMAGE_HEIGHT);

  double x, y, x2, y2, cx, cy; //c is current
  cy = MIN_Y;

  double fDeltaX = (MAX_X - MIN_X) / (double)IMAGE_WIDTH;
  double fDeltaY = (MAX_Y - MIN_Y) / (double)IMAGE_HEIGHT;

  unsigned long nTotalIterationsCount = 0;
  unsigned long nTimeStart = get_time();

  long i, j, n;

  n = 0;
  // do the calculation
  for (j = 0; j < IMAGE_HEIGHT; j++) {
    cx = MIN_X;
    for (i = 0; i < IMAGE_WIDTH; i++) {
      x = cx;
      y = cy;
      x2 = x * x;
      y2 = y * y;
      // compute the orbit z, f(z), f^2(z), f^3(z), ...
      // count the iterations until the orbit leaves the circle |z|=2.
      // stop if the number of iterations exceeds the bound MAX_ITERS.
      // TODO
      // >>>>>>>> CODE IS MISSING
      for(n=0;x2+y2<2 && n<MAX_ITERS;n++){
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
      png_plot(pPng, i, j, c, c, c);
      cx += fDeltaX;
    }
    cy += fDeltaY;
  }
  unsigned long nTimeEnd = get_time();

  // print benchmark data
  printf("Total time:                 %g milliseconds\n",
         (nTimeEnd - nTimeStart) / 1000.0);
  printf("Image size:                 %ld x %ld = %ld Pixels\n",
         (long)IMAGE_WIDTH, (long)IMAGE_HEIGHT,
         (long)(IMAGE_WIDTH * IMAGE_HEIGHT));
  printf("Total number of iterations: %ld\n", nTotalIterationsCount);
  printf("Avg. time per pixel:        %g microseconds\n",
         (nTimeEnd - nTimeStart) / (double)(IMAGE_WIDTH * IMAGE_HEIGHT));
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
