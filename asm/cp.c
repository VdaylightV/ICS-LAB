#include "stdio.h"
#include "string.h"
void* memcpy(void* out, const void* in, size_t n) {
	
  char* temp_out = (char *)out;
  char* temp_in = (char *)in;

  for(size_t i = 0; i < n; i ++)
      ((char*)temp_out)[i] = ((char*)temp_in)[i];


  return out;
}

void *asm_memcpy(void *dest, const void *src, size_t n) {
    return memcpy(dest,src,n);
}

int main() {

	return 0;

}


