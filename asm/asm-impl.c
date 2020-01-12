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
            "mov (%1), %0;"
			"movq %%rax, 8(%1);"
			"movq %%rbx, 16(%1);"
			"movq %%rcx, 24(%1);"
			"movq %%rdx, 32(%1);"
			"movq %%rsi, 40(%1);"
			"movq %%rdi, 48(%1);"
			"movq %%rbp, 56(%1);"
			"movq %%rsp, 64(%1);"
			"movq %%r8, 72(%1);"
			"movq %%r9, 80(%1);"
			"movq %%r10, 88(%1);"
			"movq %%r11, 96(%1);"
			"movq %%r12, 104(%1);"
			"movq %%r13, 112(%1);"
			"movq %%r14, 120(%1);"
			"movq %%r15, 128(%1);"
			"pushfq;"
			"movq (%%rsp), %%rax;"
			"movq %%rax, 136(%1);"
			"popfq;"
			"movq (%%rsp), %%rax;"
			"movq %%rax, 144(%1);"
			"movq 8(%1), %%rax;"
			"retq;"
            
		    :"+r"(ret_val)
			:"r"(env)
			:"memory"//"rax", "rbx", "rcx", "rdx", "rsi", "rdi", "rbp", "rsp", "r8", "r9", "r10", "r11", "r12", "r13", "r14", "r15"
	);
  // TODO: implement
  return ret_val;
}

void asm_longjmp(asm_jmp_buf env, int val) {
	asm (
			"mov (%0), %1;"
			"movq 16(%0), %%rbx;"
			"movq 24(%0), %%rcx;"
			"movq 32(%0), %%rdx;"
			"movq 40(%0), %%rsi;"
			"movq 48(%0), %%rdi;"
			"movq 56(%0), %%rbp;"
			"movq 64(%0), %%rsp;"
			"movq 72(%0), %%r8;"
			"movq 80(%0), %%r9;"
			"movq 88(%0), %%r10;"
			"movq 96(%0), %%r11;"
			"movq 104(%0), %%r12;"
			"movq 112(%0), %%r13;"
			"movq 120(%0), %%r14;"
			"movq 128(%0), %%r15;"
			"movq 136(%0), %%rax;"
			"pushq %%rax;"
			"popfq;"
			"movq 144(%0), %%rax;"
			"movq %%rax, 0(%%rsp);"
			"mov %1, %%rax;"
			:
			:"r"(env), "r"(val)
			:
			/*
			"movl 4(%%esp), %%ebx;"
			"movl 8(%%esp), %%eax;"
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
			:"+r"(val)
			:"r"(env), "r"(val)
			:
			*/
	);
  // TODO: implement
}
