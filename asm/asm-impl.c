#include "stdio.h"
#include "asm.h"
#include <string.h>

int64_t asm_add(int64_t a, int64_t b) {
  printf("Old a:%ld\n",a);
  printf("Old b:%ld\n",b);
  asm (
		  "addq %[a], %[b]"
		  :[b] "=r"(b)
          :"a"(a)
		  : "b"(b)
		  :
  );
  printf("%ld\n",b);

  // TODO: implement
  return b;
}

int asm_popcnt(uint64_t n) {
  // TODO: implement
  return 0;
}

void *asm_memcpy(void *dest, const void *src, size_t n) {
  // TODO: implement
  return NULL;
}

int asm_setjmp(asm_jmp_buf env) {
  // TODO: implement
  return 0;
}

void asm_longjmp(asm_jmp_buf env, int val) {
  // TODO: implement
}
