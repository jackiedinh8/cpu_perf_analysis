#include <stdlib.h>

static int vec_cmp(const void *p1, const void *p2)
{
  const int *s1 = p1, *s2 = p2;
  return *s1 < *s2;
}

int compute(int n)
{
  int i,k;
  long sum = 0;
  int *vec = malloc(n * sizeof(int));

  for (i = 0; i < n; i++)
    vec[i] = rand()%n;

#ifdef ENABLE_SORT
  qsort(vec, n, sizeof(n), vec_cmp);
#endif

  for (k = 0; k < 100000; k++)
    for (i = 0; i < n; i++)
      if (vec[i] > n/2)
        sum += vec[i];

  return sum;
}

int main()
{
  volatile int sum;
  sum = compute(32768);
  (void)sum;
  return 0;
}

