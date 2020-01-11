#include "stdio.h"
#include "asm.h"
#include <string.h>

int64_t asm_add(int64_t a, int64_t b) {
  /*
  int64_t m = a;
  int64_t n = b;
  printf("m:%ld\n",m);
  printf("n:%ld\n",n);
  */
  asm (
		  "leaq (%1, %2, 1), %0"
		  : "=r"(b)
          : "r"(a), "r"(b)
		  : 
  );

//  printf("res:%ld\n",b);

  // TODO: implement
  return b;
}

int asm_popcnt(uint64_t n) {
	int count = 0, i = 0;
	for(; i < n; i ++) {
	    asm (
			"movl %1, %%ebx\n\t"
			"andl $0x1, %%ebx\n\t"
			"testl %%ebx, %%ebx\n\t"
			"je equ\n\t"
			"addl $1, %0\n\t"
			"shrl %%eax, %%eax"
			"equ:\n\t"
			"shrl %%eax, %%eax"
			:"=r"(count)
			:"a"(n), "D"(i)
			: "ebx"
		);
	}

  // TODO: implement
  
  return count;
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
