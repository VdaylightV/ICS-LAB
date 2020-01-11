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
	char *ret = NULL;
	char* temp_out = (char *)dest; 
	char* temp_in = (char *)src;
	
	asm (
			"loop:\n\t"
			"cmpq %3, %4;"
			"jnb end2;"
            "movq (%2, %4, 1), %%rdx;"			
			"movb %%dl, (%1, %4, 1);"
			"addq $0x1, %4;"
			"jmp loop;"
			"end2:\n\t"
			"movq %1, %%rax;"
			"movq %%rax, %0;"

			:"+r"(ret)
			:"r"(temp_out), "r"(temp_in), "r"(n), "r"(i)
			: "rdx", "rax"
	);
  // TODO: implement
  return ret;
}

int asm_setjmp(asm_jmp_buf env) {
	int ret_val = 0;

	asm (
			"pushq %%rbx;"
			"movl 8(%%esp), %%ebx;"
			"movl %%eax, (%%ebx);"
			"popq %%rax;"
			"movl %%eax, 4(%%ebx);"
			"movl %%ecx, 8(%%ebx);"
			"movl %%edx, 12(%%ebx);"
			"movl %%edx, 16(%%ebx);"
			"movl %%esi, 24(%%ebx);"
			"movl %%ebp, 28(%%ebx);"
			"movl (%%esp), %%eax;"
			"movl %%eax, 32(%%ebx);"
			"movl -4(%%esp), %%ebx;"
			"xorl %%eax, %%eax;"
			"ret;"
			:"+a"(ret_val)
			:
			:
	);
  // TODO: implement
  return ret_val;
}

void asm_longjmp(asm_jmp_buf env, int val) {
	asm (
			"movl 4(%%esp), %%ebx;"
			"movl 8(%%esp), %%eax;"
			"movl 24(%%ebx), %%esp;"
			"movl 32(%%ebx), %%edi;"
			"movl %%edi, 0(%%esp);"
			"movl 8(%%ebx), %%ecx;"
			"movl 12(%%ebx), %%edx;"
			"movl 16(%%ebx), %%esi;"
			"movl 20(%%ebx), %%edi;"
			"movl 28(%%ebx), %%ebp;"
			"movl 4(%%ebx), %%ebx;"
			"testl %%eax, %%eax;"
			"jne bye;"
			"incl %%eax;"
			"bye:\n\t"
			"ret;"
			:
			:
			:
			
	);
  // TODO: implement
}
