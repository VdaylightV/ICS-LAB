#include "stdio.h"
#include "stdint.h"
#include "sys/time.h" 

int64_t multimod_p3() {
//	struct timeval tv0;
//	gettimeofday(&tv0, NULL);
  int64_t a = 89;
  int64_t b = 23;
  int64_t m = 34;


  int64_t t = (a * b - (int64_t)((double)a * b / m) * m) % m;
  t = t < 0 ? t + m : t;
//	struct timeval tv1;
//	gettimeofday(&tv1, NULL);
	
//  printf("%ldms\n",tv1.tv_usec-tv0.tv_usec);

  return t;
}
