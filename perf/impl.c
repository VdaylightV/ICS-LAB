#include "perf.h"
#include <stdio.h>
#include <stdlib.h>

void dummy() {
}


void print_hello() {
  printf("hello\n");
}

void print_error() {
  printf("invalid subject!\n");
  exit(1);
}

void simple_loop() {
  for (volatile int i = 0; i < 1000000; i++) ;
}

extern int64_t multimod_p2(int64_t a, int64_t b, int64_t m); 

extern int64_t multimod_p3(int64_t a, int64_t b, int64_t m); 
