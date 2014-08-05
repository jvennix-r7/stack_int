#include "minunit.h"
#include "../src/stack_int.h"
#include <string.h>

#define CHECK_LT(X,Y,Z) \
  stack_int a, b; \
  si_from_ascii("" #X "", strlen("" #X ""), 10, 10, &a); \
  si_from_ascii("" #Y "", strlen("" #Y ""), 10, 10, &b); \
  mu_assert(si_lt(&a, &b)==Z, "si_lt(" #X ", " #Y ") = " #Z ""); \
  return NULL;

char *test_si_lt_0_not_lt_0() {
  CHECK_LT(0,0,0)
}

char *test_si_lt_0_lt_1() {
  CHECK_LT(0,1,1)
}

char *test_si_lt_1_not_lt_1() {
  CHECK_LT(1,1,0)
}

char *test_si_lt_1_not_lt_0() {
  CHECK_LT(1,1,0)
}

char *test_si_lt_980128_lt_1000238929() {
  CHECK_LT(980128,1000238929,1)
}

char *test_si_lt_109_not_lt_108() {
  CHECK_LT(109,108,0)
}

char *test_si_lt_105_lt_255() {
  CHECK_LT(105,255,1)
}

char *test_si_lt_1000000000000000000000000_lt_999999() {
  CHECK_LT(1000000000000000000000000,999999,0)
}

char *test_si_lt_555555555511113_not_lt_555555555511113() {
  CHECK_LT(555555555511113,555555555511113,0)
}


char *all_tests() {
  mu_suite_start();

  mu_run_test(test_si_lt_0_not_lt_0);
  mu_run_test(test_si_lt_0_lt_1);
  mu_run_test(test_si_lt_1_not_lt_1);
  mu_run_test(test_si_lt_1_not_lt_0);
  mu_run_test(test_si_lt_980128_lt_1000238929);
  mu_run_test(test_si_lt_109_not_lt_108);
  mu_run_test(test_si_lt_105_lt_255);
  mu_run_test(test_si_lt_1000000000000000000000000_lt_999999);
  mu_run_test(test_si_lt_555555555511113_not_lt_555555555511113);
  return NULL;
}

RUN_TESTS(all_tests);
