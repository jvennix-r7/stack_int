#include "minunit.h"
#include "../src/stack_int.h"

char *test_si_init_width_and_radix() {
  stack_int si;

  si.width = 123;
  si.digits[0] = 123;
  si.radix = 10;

  si_init(&si, 16);

  mu_assert(si.width == 0, "Failed to set width to zero.");
  mu_assert(si.radix == 16, "Failed to set radix to 16.");

  return NULL;
}

char *test_si_init_zero() {
  stack_int si;

  si.width = 123;
  si.digits[0] = 123;
  si.radix = 10;

  si_init(&si, 16);

  mu_assert(si_is_zero(&si), "Failed to set integer to zero.");

  return NULL;
}

char *all_tests() {
  mu_suite_start();

  mu_run_test(test_si_init_width_and_radix);
  mu_run_test(test_si_init_zero);

  return NULL;
}

RUN_TESTS(all_tests);
