#include <stdio.h>
#include <stdlib.h>
#include <sys/time.h>

double get_time()
{
  struct timeval tv;
  gettimeofday(&tv, NULL);
  return tv.tv_sec + tv.tv_usec * 1e-6;
}

int init(int n, double *a, double *b, double *c) {
  // Initialize the matrices to some values.
  int i, j;
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      a[i * n + j] = i * n + j; // A[i][j]
      b[i * n + j] = j * n + i; // B[i][j]
      c[i * n + j] = 0; // C[i][j]
    }
  }
}

int calc_prod(int n, double *a, double *b, double *c) {
  // calculate matrix production
  int i, j, k;
  for (i = 0; i < n; i++) 
    for (j = 0; j < n; j++) 
      for (k = 0; k < n; k++) 
        c[i * n + j] += a[i * n + k] * b[k * n + j];
}

double get_avg_time(double *time, int i) {
  // use the average of the two shortest execution times of the three result
  double t;
  double t1 =  time[i * 3 + 0];
  double t2 =  time[i * 3 + 1];
  double t3 =  time[i * 3 + 2];
  if (t1 > t2 && t1 > t3) {
    t = (t2+t3)/2;
  } else if (t2 > t3) {
    t = (t1+t3)/2;
  } else {
    t = (t1+t2)/2;
  }
  return t;
}

void debug(int n, int*c) {
  // Print C for debugging. Comment out the print before measuring the execution time.
  double sum = 0;
  int i, j;
  for (i = 0; i < n; i++) {
    for (j = 0; j < n; j++) {
      sum += c[i * n + j];
      //printf("c[%d][%d]=%lf\n", i, j, c[i * n + j]);
    }
  }
  // Print out the sum of all values in C.
  // This should be 450 for N=3, 3680 for N=4, and 18250 for N=5.
  printf("sum: %.6lf\n", sum);
}

int main(int argc, char** argv)
{
  if (argc != 2) {
    printf("usage: %s N\n", argv[0]);
    return -1;
  }

  int n = atoi(argv[1]);
  int i, k;
  double* time = (double*)malloc(n * 3 * sizeof(double));
  // measure a time three times to reduce noise
  for (k = 0; k < 3; k++) {
    for (i = 0; i < n; i++) {
      double* a = (double*)malloc(i * i * sizeof(double)); // Matrix A
      double* b = (double*)malloc(i * i * sizeof(double)); // Matrix B
      double* c = (double*)malloc(i * i * sizeof(double)); // Matrix C

      init(i, a, b, c);
      double begin = get_time();
      calc_prod(i, a, b, c);
      double end = get_time();
      time[i * 3 + k] = end - begin;
      free(a);free(b);free(c);
    }
  }
  
  FILE *fp = fopen("time.txt", "w");
  for (i = 0; i < n; i++) {
    double t;
    // use the average of the two shortest execution times of the three result
    t = get_avg_time(time, i);
    fprintf(fp, "%f\n", t);
  }
  fclose(fp);
  return 0;
}