/*
 * MIT License
 *
 * Copyright (c) 2017-2020, Shahzeb Siddiqui
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy
 * of this software and associated documentation files (the "Software"), to deal
 * in the Software without restriction, including without limitation the rights
 * to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
 * copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
 * AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
 * SOFTWARE.
 * */
#include <stdio.h>
#include "timer.h"
#include <omp.h>
#define SIZE 1000 

float a[SIZE][SIZE];
float b[SIZE][SIZE];
float c[SIZE][SIZE];

int main()
{
 
  int threadcnt;
  int i,j,k;
  printf("Computing Matrix Multiplication C = A * B with %dx%d square matrix\n",SIZE,SIZE);
  for (threadcnt = 1; threadcnt <= 16; threadcnt++)
 {
  StartTimer();
  omp_set_num_threads(threadcnt);
  // Initialize matrices.
   #pragma omp parallel for
   for (i = 0; i < SIZE; ++i) {
    for (j = 0; j < SIZE; ++j) {
      a[i][j] = (float)i + j;
      b[i][j] = (float)i - j;
      c[i][j] = 0.0f;
    }
  }
  // Compute matrix multiplication.
  #pragma omp parallel for
  for (i = 0; i < SIZE; ++i) {
    for (j = 0; j < SIZE; ++j) {
      for (k = 0; k < SIZE; ++k) {
	c[i][j] += a[i][k] * b[k][j];
      }
    }
  }

  double runtime = GetTimer();
  #pragma omp parallel
  {
    if(omp_get_thread_num() == 0)
	printf("Execution Time: %f s with %d threads\n", runtime / 1000.f,omp_get_num_threads());
  }
 }
  /*
  for (i = 0; i < SIZE; i++)
  {
    for (j = 0; j < SIZE; j++)
	printf("%0.6f\t",c[i][j]);
	printf("\n");
  }*/
  return 0;
}
