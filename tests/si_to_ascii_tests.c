#include "minunit.h"
#include <string.h>
#include <stack_int.h>

char *test_si_to_ascii_zero() {
  stack_int si;
  si_init(&si, 10);
  mu_assert(si_is_zero(&si), "initialized stack_int should be zero.");

  si_len_t buflen = 128;
  char buf[buflen];

  si_to_ascii(&si, buf, buflen);
  mu_assert(
    !strcmp(buf, "0"),
    "si_to_ascii() on an initialized stack int should be \"0\"."
  );

  return NULL;
}

char *test_si_to_ascii_twenty() {
  stack_int si;
  si.digits[SI_MAX_PRECISION-2] = 2;
  si.digits[SI_MAX_PRECISION-1] = 0;
  si.width = 2;
  si.radix = 10;

  mu_assert(!si_is_zero(&si), "stack_int set to 20 should not be zero.");

  si_len_t buflen = 128;
  char buf[buflen];

  si_to_ascii(&si, buf, buflen);
  mu_assert(
    !strcmp(buf, "20"),
    "si_to_ascii() on an initialized stack int should be \"20\"."
  );

  return NULL;
}

char *test_si_to_ascii_serialization() {
  stack_int si;
  si_from_ascii("123456789abcdef", 15, 16, 16, &si);

  mu_assert(!si_is_zero(&si), "stack_int set to 123456789abcdef should not be zero.");

  si_len_t buflen = 128;
  char buf[buflen];

  si_to_ascii(&si, buf, buflen);
  mu_assert(
    !strcmp(buf, "123456789abcdef"),
    "si_to_ascii(str_from_str(\"123456789abcdef\")) should be correct."
  );

  return NULL;
}

char *all_tests() {
  mu_suite_start();

  mu_run_test(test_si_to_ascii_zero);
  mu_run_test(test_si_to_ascii_twenty);
  mu_run_test(test_si_to_ascii_serialization);

  return NULL;
}

RUN_TESTS(all_tests);
