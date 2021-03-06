#include "asm.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <assert.h>

static void setjmp_test0();
static void setjmp_test1();

int main() {
  // TODO: add more tests here!
  assert(asm_add(1, 2) == 3);
  assert(asm_add(99, 123) == 222);
  assert(asm_add(-99, 100) == 1);
  assert(asm_popcnt(0xffffffffffffffffull) == 64);
  assert(asm_popcnt(0xff0f00f0f7ff0fffull) == 43);
  assert(asm_popcnt(0xffffffff00000000ull) == 32);

  // TODO: add memcpy tests here!
  char a[5] = "abcd";
  char b[3] = "12";
  char c[27] = "abcdefghijklmnopqrstuvwxyz";
  char d[11] = "0123456789";
  
  assert(asm_memcpy(&a[0], &b[0], 2) == &a[0]);
//  printf("------result:%s--------\n",&a[0]);
  assert(asm_memcpy(&c[0], &d[0], 10) == &c[0]);
//  printf("------result:%s--------\n",&c[0]);

  // setjmp test starts here
  setjmp_test0();
  setjmp_test1();
//  printf("ALL TESTS PASS!\n");
}

struct log_entry {
  const char *str;
  int value;
};
static asm_jmp_buf bufferA, bufferB;
static struct log_entry expected[] = {
  // expected output sequence for setjmp tests
  { "A", 0 },
  { "B", 999 },
  { "A1", 0 },
  { "B1", 0 },
  { "A2", 10001 },
  { "B2", 20001 },
  { "A3", 10002 },
  { "B3", 20002 },
  { "A4", 10003 },
  { NULL, 0 },
};
static struct log_entry *head = expected;

static void setjmp_log(const char *str, int value) {
  assert(head->str != NULL);
//  printf("----head-str:%s\n", head->str);
//  printf("----str:%s\n", str);
  assert(strcmp(head->str, str) == 0);
//  printf("----head-value:%d\n", head->value);
//  printf("----value:%d\n", value);
  assert(head->value == value);
  head++;
}

static void setjmp_test2();
static void setjmp_test1() {
  int r = 0;
  setjmp_log("A1", r);
  if ((r = asm_setjmp(bufferA)) == 0) {
    setjmp_test2();
  }
  setjmp_log("A2", r);
  if ((r = asm_setjmp(bufferA)) == 0) {
    asm_longjmp(bufferB, 20001);
  }
  setjmp_log("A3", r);
  if ((r = asm_setjmp(bufferA)) == 0) {
    asm_longjmp(bufferB, 20002);
  }
  setjmp_log("A4", r);
  assert(head->str == NULL);
}

static void setjmp_test2() {
  int r = 0;
  setjmp_log("B1", r);
  if ((r = asm_setjmp(bufferB)) == 0) {
    asm_longjmp(bufferA, 10001);
  }
  setjmp_log("B2", r);
  if ((r = asm_setjmp(bufferB)) == 0) {
    asm_longjmp(bufferA, 10002);
  }
  setjmp_log("B3", r);
  if ((r = asm_setjmp(bufferB)) == 0) {
    asm_longjmp(bufferA, 10003);
  }
}

static asm_jmp_buf buf;

static void setjmp_test_simple() {
  asm_longjmp(buf, 999);
}

static void setjmp_test0() {
  int r;
  if ((r = asm_setjmp(buf)) == 0) {
    setjmp_log("A", r);
    setjmp_test_simple();
  }
  setjmp_log("B", r);
}
