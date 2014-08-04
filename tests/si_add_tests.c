#include "minunit.h"
#include <stack_int.h>
#include <string.h>

#define CHECK_ADD(X,Y,Z) \
  stack_int a, b, c, check; \
  si_from_str("" #X "", strlen("" #X ""), 10, 10, &a); \
  si_from_str("" #Y "", strlen("" #Y ""), 10, 10, &b); \
  si_from_str("" #Z "", strlen("" #Z ""), 10, 10, &check); \
  si_add(&a, &b, &c); \
  mu_assert(si_equals(&c, &check), "" #X " + " #Y " = " #Z ""); \
  char out[128]; \
  si_to_str(&c, out, 128, 1); \
  mu_assert(!strcmp(out, "" #Z ""), "si_to_str(" #X " + " #Y ") = \"" #Z "\""); \
  return NULL;

char *test_si_add_0_plus_0() {
  CHECK_ADD(0, 0, 0)
}

char *test_si_add_255_plus_255() {
  CHECK_ADD(255, 255, 510)
}

char *test_si_add_512_plus_12344() {
  CHECK_ADD(512, 12344, 12856)
}

char *test_si_add_99999999_plus_1() {
  CHECK_ADD(99999999, 1, 100000000)
}


char *test_si_add_1_plus_99999999() {
  CHECK_ADD(1, 99999999, 100000000)
}

char *test_si_add_1_plus_1() {
  CHECK_ADD(1, 1, 2)
}

char *test_si_add_222_plus_222() {
  CHECK_ADD(222, 222, 444)
}


char *all_tests() {
  mu_suite_start();

  mu_run_test(test_si_add_0_plus_0);
  mu_run_test(test_si_add_255_plus_255);
  mu_run_test(test_si_add_512_plus_12344);
  mu_run_test(test_si_add_99999999_plus_1);
  mu_run_test(test_si_add_1_plus_99999999);
  mu_run_test(test_si_add_1_plus_1);
  mu_run_test(test_si_add_222_plus_222);

  return NULL;
}

RUN_TESTS(all_tests);
