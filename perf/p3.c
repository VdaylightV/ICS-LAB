#include "stdio.h"
#include "stdint.h"
#include "stdlib.h"
#include "sys/time.h" 
#include "time.h" 

int64_t multimod_p3() {
//	struct timeval tv0;
//	gettimeofday(&tv0, NULL);
srand((unsigned int)time(NULL));
//	int64_t a = rand()*4294967296 + 4294967295;
	int64_t a = rand();
	int64_t b = rand();
	int64_t m = rand();
//	printf("a%ld\n", a);
//	int64_t b = rand()*4294967296 + 4294967295;
//	printf("b%ld\n", b);
//	int64_t m = rand()*4294967296 + 4294967295;
//	printf("m%ld\n", m);

//  int64_t a = 89;
//  int64_t b = 23;
//  int64_t m = 34;


  int64_t t = (a * b - (int64_t)((double)a * b / m) * m) % m;
  t = t < 0 ? t + m : t;
//	struct timeval tv1;
//	gettimeofday(&tv1, NULL);
	
//  printf("%ldms\n",tv1.tv_usec-tv0.tv_usec);

  return t;
}
