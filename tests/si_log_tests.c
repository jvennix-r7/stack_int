#include "minunit.h"
#include <stack_int.h>
#include <string.h>

#define CHECK_LOG(X,Y,Z) \
  stack_int a; \
  si_from_ascii("" #X "", strlen("" #X ""), 10, 10, &a); \
  mu_assert(si_log(&a, Y) == Z, "" #X " log base " #Y " = " #Z ""); \
  char out[4096]; \
  si_to_ascii(&a, out, 4096); \
  mu_assert(si_log(&a, Y) == Z, "si_log(" #X ", " #Y ") = \"" #Z "\""); \
  return NULL;

char *test_si_log_5_b10() {
  CHECK_LOG(5, 10, 0);
}

char *test_si_log_1_b10() {
  CHECK_LOG(1, 10, 0);
}

char *test_si_log_25_b10() {
  CHECK_LOG(25, 10, 1);
}

char *test_si_log_25124124124_b10() {
  CHECK_LOG(25124124124, 10, 10);
}

char *all_tests() {
  mu_suite_start();

  mu_run_test(test_si_log_5_b10);
  mu_run_test(test_si_log_1_b10);
  mu_run_test(test_si_log_25_b10);
  mu_run_test(test_si_log_25124124124_b10);

  return NULL;
}

RUN_TESTS(all_tests);
