#include "multimod.h"

int64_t multimod_p2(int64_t a, int64_t b, int64_t m) {
  int64_t multi_factor = b;
  int64_t left = 0;
  while(a > 0) {
      if(a&1 == 1) {
	      left = (left + multi_factor) % m;
	  }
	  multi_factor = (multi_factor * multi_factor) % m;
	  a >> 1;
  } 
  // TODO: implement
  return left;
}
