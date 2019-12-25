#include "multimod.h"
#include "stdio.h"
#include "sys/time.h"

int64_t multimod_p2(int64_t a, int64_t b, int64_t m) {

  int64_t multi_factor = b;
  int64_t left = 0;

  struct timeval tv0;
  gettimeofday(&tv0, NULL);

  while(a) {
      if(a&1) {
	      left += multi_factor;
		  left %= m;
	  }
	  multi_factor = (multi_factor + multi_factor) % m;
	  a >>= 1;
  } 
  // TODO: implement
  
  struct timeval tv1;
  gettimeofday(&tv1, NULL);
  printf("%lds\n",tv1.tv_usec-tv0.tv_usec);
  
  return left;
}
