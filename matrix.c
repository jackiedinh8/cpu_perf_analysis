#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define N 2048
int main(int argc, char **argv)
{
  clock_t start, end;
  int *A, *B, *C;

  A = (int*)malloc(N*N*sizeof(int));
  B = (int*)malloc(N*N*sizeof(int));
  C = (int*)malloc(N*N*sizeof(int));

  srand(19);
  for (int i=0; i<N; i++) {
    for (int j=0; j<N; j++) {
      A[i*N + j] = rand();
      B[i*N + j] = rand();
      C[i*N + j] = 0;
    }
  }
  start = clock();
#ifdef CACHE_FRIENDLY
  for (int i=0; i<N; i++) {
      for (int k=0; k<N; k++) {
    for (int j=0; j<N; j++) {
        C[i*N + j] = A[i*N + k] * B[k*N + j];
      }
    }
  }
#else
  for (int i=0; i<N; i++) {
    for (int j=0; j<N; j++) {
      for (int k=0; k<N; k++) {
        C[i*N + j] = A[i*N + k] * B[k*N + j];
      }
    }
  }
#endif
  end = clock();

#ifdef CACHE_FRIENDLY
  printf("(cache-friendly) time taken: %f\n", ((double)(end - start))/CLOCKS_PER_SEC);
#else
  printf("(no-cache-friendly) time taken: %f\n", ((double)(end - start))/CLOCKS_PER_SEC);
#endif

  return 0;
}
