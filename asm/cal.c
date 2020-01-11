/*
#include <stdio.h>
#include <stdint.h>

int tc(uint64_t x) {
	return 0;
}

int cnt(uint64_t x) {
    static int s = 0;
	for(int i = 0; i < 16; i ++) {
	  if((x >> i) & 1) s ++;
	}
	return s;
}

int main() {
  unsigned long long a = 0xffffffffffffffff;
  cnt(a);
  return 0;

}
*/
