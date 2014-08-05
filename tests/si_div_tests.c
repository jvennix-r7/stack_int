#include "minunit.h"
#include <stack_int.h>
#include <string.h>

#define CHECK_DIV(X,Y,Z) \
  stack_int a, b, c, r, check; \
  si_from_ascii("" #X "", strlen("" #X ""), 10, 10, &a); \
  si_from_ascii("" #Y "", strlen("" #Y ""), 10, 10, &b); \
  si_from_ascii("" #Z "", strlen("" #Z ""), 10, 10, &check); \
  si_div(&a, &b, &c, &r); \
  mu_assert(si_equals(&c, &check), "" #X " * " #Y " = " #Z ""); \
  char out[1024]; \
  si_to_ascii(&c, out, 1024); \
  mu_assert(!strcmp(out, "" #Z ""), "si_to_ascii(" #X " * " #Y ") = \"" #Z "\""); \
  return NULL;

char *test_si_div_0_div_0() {
  CHECK_DIV(0, 0, 0)
}

char *test_si_div_1_div_1() {
  CHECK_DIV(1, 1, 1)
}

char *all_tests() {
  mu_suite_start();

  // mu_run_test(test_si_div_0_div_0);
  // mu_run_test(test_si_div_1_div_1);

  return NULL;
}

RUN_TESTS(all_tests);
