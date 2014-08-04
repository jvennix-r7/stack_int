#include "minunit.h"
#include <string.h>
#include <stack_int.h>

char *test_si_from_str_zero() {
  stack_int si;

  si_from_str("0", 1, 10, 10, &si);
  mu_assert(si_is_zero(&si), "si_from_str(\"0\") should be zero.");

  si_from_str("0000", 4, 10, 10, &si);
  mu_assert(si_is_zero(&si), "si_from_str(\"0000\") should be zero.");

  return NULL;
}

char *test_si_from_str_nonzero() {
  stack_int si;

  si_from_str("1", 1, 10, 10, &si);
  mu_assert(!si_is_zero(&si), "si_from_str(\"1\") should not be zero.");
  mu_assert(si.width == 1, "si_from_str(\"1\") should have a width of one.");

  si_from_str("3123", 4, 10, 10, &si);
  mu_assert(!si_is_zero(&si), "si_from_str(\"3123\") should not be zero.");
  mu_assert(si.width == 4, "si_from_str(\"3123\") should have a width of four.");

  return NULL;
}

char *test_si_from_str_trim_left_zeroes() {
  stack_int si;

  si_from_str("0001", 4, 10, 10, &si);
  mu_assert(si.width == 1, "si_from_str(\"0001\") should have a width of 1.");

  return NULL;
}

char *test_si_from_str_serialization() {
  stack_int si;
  si_len_t buflen = 128;
  char buf[buflen];

  si_from_str("1", 1, 10, 10, &si);
  mu_assert(si.width == 1, "si_from_str(\"1\") should have a width of 1.");

  si_to_str(&si, buf, buflen, 1);
  mu_assert(
    buf[0] == '1' && buf[1] == 0,
    "si_to_str(si_from_str(\"1\"),buf,buflen) should set buf to ['1',0]."
  );

  si_from_str("1234567890a", 11, 16, 16, &si);
  si_to_str(&si, buf, buflen, 1);
  mu_assert(
    !strcmp(buf, "1234567890a"),
    "si_to_str(si_from_str(\"1234567890a\"),buf,buflen) should be correct."
  );

  return NULL;
}

char *all_tests() {
  mu_suite_start();

  mu_run_test(test_si_from_str_zero);
  mu_run_test(test_si_from_str_nonzero);
  mu_run_test(test_si_from_str_trim_left_zeroes);
  mu_run_test(test_si_from_str_serialization);

  return NULL;
}

RUN_TESTS(all_tests);
