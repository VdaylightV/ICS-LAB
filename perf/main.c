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

static int str_to_num(char *str) {
    int result = 0;
	char *temp = str;

	while (*temp != '\0') {
	    result *= 10;
		result += *temp;
		temp ++;
	}

	return result;
}

static void run(void (*func)(), int rounds);
static uint64_t gettime();
static void (*lookup(const char *fn))();

int main(int argc, char **argv) {
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
	  run(func, rounds);
  }
  else {
	  if(argc == 4) {
	      rounds = str_to_num(argv[3]);
	  }
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
  printf("rounds:%d\n", rounds);
  uint64_t *elapsed = malloc(sizeof(uint64_t) * rounds);
  if (!elapsed) {
    perror("elapsed");
    return;
  }

  for (int round = 0; round < rounds; round++) {
    uint64_t st = gettime();
    func();
    uint64_t ed = gettime();
    elapsed[round] = (ed - st)/CLOCKS_PER_SEC;
  }

  // TODO: display runtime statistics
  uint64_t average = 0;
  uint64_t variance = 0;
  for(int i = 0; i < rounds; i ++) {
      average += elapsed[i];
	  printf("----Index:%d Time:%lu\n",i, elapsed[i]);
  }
  average /= rounds;

  for(int i = 0; i < rounds; i ++) {
      variance += (uint64_t)pow((elapsed[i] - average), 2);
  }
  variance /= rounds;

  free(elapsed);
  printf("average time : %lus\n", average);
  printf("variance : %lus\n", variance);
}
