#include "minunit.h"
#include <stack_int.h>
#include <string.h>

#define CHECK_MOD(X,Y,R) \
  stack_int a, b, r, rcheck; \
  si_from_ascii("" #X "", strlen("" #X ""), 10, 10, &a); \
  si_from_ascii("" #Y "", strlen("" #Y ""), 10, 10, &b); \
  si_from_ascii("" #R "", strlen("" #R ""), 10, 10, &rcheck); \
  si_mod(&a, &b, &r); \
  mu_assert(si_equals(&r, &rcheck), "" #X " mod " #Y " = " #R ""); \
  char out[1024]; \
  si_to_ascii(&r, out, 1024); \
  mu_assert(!strcmp(out, "" #R ""), "si_mod(" #X " mod " #Y ") = \"" #R "\""); \
  return NULL;

char *test_si_mod_0_mod_0() {
  CHECK_MOD(0, 0, 0)
}

char *test_si_mod_1_mod_1() {
  CHECK_MOD(1, 1, 0)
}

char *test_si_mod_2_mod_3() {
  CHECK_MOD(2, 3, 2)
}

char *test_si_mod_10_mod_5() {
  CHECK_MOD(10, 5, 0)
}

char *test_si_mod_1_mod_555555() {
  CHECK_MOD(1, 555555, 1)
}

char *test_si_mod_999999_mod_3() {
  CHECK_MOD(999999, 3, 0)
}

char *test_si_mod_large1() {
  CHECK_MOD(
    106049263636041958604145652070598535526633546516535098317625241745988446838483,
    89546152982728876178118028935422314934181625998417448340141872917759434384267,
    16503110653313082426027623135176220592451920518117649977483368828229012454216
  )
}

char *test_si_mod_large2() {
  CHECK_MOD(
    86075495160336522177662134916461033466141016476468295188677410126,
    89546152982728876178118028935422314934181625998417448340141872917759434384267,
    86075495160336522177662134916461033466141016476468295188677410126
  )
}

char *test_si_mod_large3() {
  CHECK_MOD(
    157518134881843, 81328307514, 66531534739
  )
}

char *all_tests() {
  mu_suite_start();

  // mu_run_test(test_si_mod_0_mod_0); // div by 0 is undefined.
  mu_run_test(test_si_mod_1_mod_1);
  mu_run_test(test_si_mod_2_mod_3);
  mu_run_test(test_si_mod_10_mod_5);
  mu_run_test(test_si_mod_1_mod_555555);
  mu_run_test(test_si_mod_999999_mod_3);
  mu_run_test(test_si_mod_large1);
  mu_run_test(test_si_mod_large2);
  mu_run_test(test_si_mod_large3);

  return NULL;
}

RUN_TESTS(all_tests);
