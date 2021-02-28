#include <stdio.h>
#include <stdlib.h>
#include <time.h>

static double getuptime_nsec(void)
{
    struct timespec ts;
    clock_gettime(CLOCK_REALTIME, &ts);
    return (double)ts.tv_sec*1e9 + (double)ts.tv_nsec;
}

int main()
{
  int n = 1<<25;
  int m = 8;
  int niters = n * m;
  double *data;
  double st, et;
  double sum=0.0;
  data = malloc(n*sizeof(double));

  // intialize data
  for (int i=0; i<n; i++) data[i] = (double)((i+1)%n);

  // main loop
  sum = 0.0;
  int idx = 0;
  st = getuptime_nsec();
  for (int i=0; i< niters; i++) {
    idx = data[(int)data[(int)data[idx]]];
    sum += idx;
  }
  et = getuptime_nsec() - st;

  // stats
  printf("Elapsed[msec]: %lf\n", et*1e-6);
  printf("Per iteration [nsec]: %lf\n", et/(double)niters);
  printf("sum=%lf\n", sum);

  double ref = (double)m*(double)n*(double)(n-1)/2.0;
  if((sum-ref) != 0.0) // rounding?
    printf("Failed to validate: sum should be %lf\n", ref);
  else
    printf("Validation passed!\n");

  return 0;
}
