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

	uint64_t count = 0;
	uint64_t i = 0;
	//printf("----n:%lx, count:%lx----\n",n ,count);
	//for(; i < 64; i ++) {
	    asm (
			"body:\n\t"
			"cmpq $0x40, %2;"
			"jnb end;"
			"movq %3, %%rbx;"
			"andq $0x1, %%rbx;"
			"testq %%rbx, %%rbx;"
			"je equ;"
			"addq $0x1, %0;"
			"addq $0x1, %2;"
			"shrq $0x1, %3;"
			"jmp body;"
			"equ:\n\t"
			"addq $0x1, %2;"
			"shrq $0x1, %3;"
			"jmp body;"
			"end:\n\t"

			:"+r"(count), "=a"(n), "+r"(i)
			:"a"(n), "r"(i)
			: "rbx"
		);
//		printf("----n:%lx, count:%lx, i:%lx----\n",n ,count,i);
	//}

  // TODO: implement
  
  return count;
}

void *asm_memcpy(void *dest, const void *src, size_t n) {
	size_t i = 0;
	asm (
			"loop:\n\t"
			"cmpq %3, %4;"
			"jnb end2;"
            "leaq (%2, %4, 4), %%rdx;"			
			"movb %%dl, (%1, %4, 4);"
			"addq $0x1, %4;"
			"jmp loop;"
			"end2:\n\t"
			"movq %1, %%rax;"
			"movq %%rax, %0;"

			:"=r"(dest)
			:"r"(dest), "r"(src), "r"(n), "r"(i)
			: "rdx"
	);
  // TODO: implement
  return dest;
}

int asm_setjmp(asm_jmp_buf env) {
  // TODO: implement
  return 0;
}

void asm_longjmp(asm_jmp_buf env, int val) {
  // TODO: implement
}
