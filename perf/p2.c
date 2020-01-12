#include "stdio.h"
#include "stdint.h"
#include "sys/time.h"

int64_t multimod_p2() {

  uint64_t multi_factor = a;
  uint64_t left = 0;

//  struct timeval tv0;
//  gettimeofday(&tv0, NULL);

  while(b) {
      if(b&1) {
	      left = (uint64_t)(left+multi_factor)%m;
	  }
	  multi_factor = (uint64_t)(multi_factor + multi_factor) % m;
	  b >>= 1;
  } 
  // TODO: implement
  
//  struct timeval tv1;
//  gettimeofday(&tv1, NULL);
//  printf("%ldms\n",tv1.tv_usec-tv0.tv_usec);
//  printf("JJJJJJJJJJ\n");  
  return (int64_t)left;
}
