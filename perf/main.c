#include "perf.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>
#include <time.h>
#include <stdint.h>

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
  char r[3] = "-r";
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
  return time(NULL);
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
  uint64_t *elapsed = malloc(sizeof(uint64_t) * rounds);
  if (!elapsed) {
    perror("elapsed");
    return;
  }

  for (int round = 0; round < rounds; round++) {
    uint64_t st = gettime();
    func();
    uint64_t ed = gettime();
    elapsed[round] = ed - st;
  }

  // TODO: display runtime statistics

  free(elapsed);
}
