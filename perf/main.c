#include "perf.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <stdint.h>
#include <math.h>

#define DECL(fn) void fn();

PROGRAMS(DECL)

double last = 0;

static int str_to_num(char *str) {
    int result = 0;
	char *temp = str;

	while (*temp != '\0') {
	    result *= 10;
		result += (*temp - '0');
		temp ++;
	}

	return result;
}

/*
static uint64_t gettime_copy() {

  return clock();
}
*/

static void run(void (*func)(), int rounds);
static uint64_t gettime();
static void (*lookup(const char *fn))();

int main(int argc, char **argv) {
//	uint64_t st = gettime_copy();
//	uint64_t ed = clock();
//	double duration = ed - st;
//	last = duration / CLOCKS_PER_SEC;
	//printf("duration:%f\n", last);
	/*
	for(int i = 0; i < argc; i++) {
	    printf("%s\n",argv[i]);
	}
	*/
  // TODO: parse arguments: set @func and @rounds
//  char r[3] = "-r";
  int rounds = 1;

  void (*func)() = lookup(argv[1]);

  if(argc == 2) {
//      printf("--------THE FUNCTION CALLED IS %s------\n",argv[1]);
//      printf("--------TOTAL LOOP TIME IS %d---------\n", rounds);
	  run(func, rounds);
  }
  else {
	  if(argc == 4) {
	      rounds = str_to_num(argv[3]);
	  }
//      printf("--------THE FUNCTION CALLED IS %s------\n",argv[1]);
//      printf("--------TOTAL LOOP TIME IS %d---------\n", rounds);
	  run(func, rounds);
  }

  /*
  void (*func)() = lookup("dummy");
  int rounds = 10;

  run(func, rounds);
  */
}

static uint64_t gettime() {

  // TODO: implement me! 
  //return time(NULL);
  return clock();
}

static void (*lookup(const char *fn))() {
  #define PAIR(fn) { #fn, fn },
  struct pair {
    const char *name;
    void *ptr;
  };
  struct pair lut[] = {
    PROGRAMS(PAIR)
  };

  for (int i = 0; i < LENGTH(lut); i++) {
    struct pair *p = &lut[i];
    if (strcmp(fn, p->name) == 0) return p->ptr;
  }
  return print_error;
}

static void run(void (*func)(), int rounds) {
  //printf("rounds:%d\n", rounds);
  //uint64_t *elapsed = malloc(sizeof(uint64_t) * rounds);
  double *elapsed = malloc(sizeof(double) * rounds);
  if (!elapsed) {
    perror("elapsed");
    return;
  }

  for (int round = 0; round < rounds; round++) {
    uint64_t st = gettime();
    func();
    uint64_t ed = gettime();
    elapsed[round] = (double)(ed - st)/(double)CLOCKS_PER_SEC; //- last;
//	printf("st:%lu\n",st);
//	printf("ed:%lu\n",ed);
  }

  // TODO: display runtime statistics
  double average = 0;
  double average_update = 0;
// double variance = 0;
  double variance_update = 0;
//  printf("--------THE FOLLOWING ARE STATISTICS---------\n");
  for(int i = 0; i < rounds; i ++) {
      average += elapsed[i];
//	  printf("             No.%d Time:%fs\n",i, elapsed[i]);
  }
  average /= rounds;
  
  int counts = 0;
  for(int i = 0; i < rounds; i ++) {
      if(elapsed[i] < average*2) {
		  average_update += elapsed[i];
		  counts ++;
	  } 
  }
  average_update /= counts;

  /*
  for(int i = 0; i < rounds; i ++) {
      variance += (double)pow((elapsed[i] - average)*1000, 2);
  }
  variance /= rounds;
  */
  
  for(int i = 0; i < rounds; i ++) {
      if(elapsed[i] < average*2) {
          variance_update += (double)pow((elapsed[i] - average_update)*10000, 2);
	  } 
  }
  variance_update /= counts;
 

  free(elapsed);
//  printf("--------THE FOLLOWING ARE ANALYSES---------\n");
//  printf("          average time : %fs\n", average);
//  printf("          update average time : %fs\n", average_update);
  printf("%f\n", average_update);
  printf("          update variance : %f×10^(-8)\n", variance_update);
//  printf("          bad points : %d\n", rounds-counts);
}
