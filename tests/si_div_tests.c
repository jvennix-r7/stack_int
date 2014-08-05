#include "minunit.h"
#include <stack_int.h>
#include <string.h>

#define CHECK_DIV(X,Y,Z) \
  stack_int a, b, c, r, check; \
  si_from_ascii("" #X "", strlen("" #X ""), 10, 10, &a); \
  si_from_ascii("" #Y "", strlen("" #Y ""), 10, 10, &b); \
  si_from_ascii("" #Z "", strlen("" #Z ""), 10, 10, &check); \
  si_div(&a, &b, &c, &r); \
  mu_assert(si_equals(&c, &check), "" #X " / " #Y " = " #Z ""); \
  char out[1024]; \
  si_to_ascii(&c, out, 1024); \
  mu_assert(!strcmp(out, "" #Z ""), "si_div(" #X " * " #Y ") = \"" #Z "\""); \
  return NULL;

char *test_si_div_0_div_0() {
  CHECK_DIV(0, 0, 0)
}

char *test_si_div_1_div_1() {
  CHECK_DIV(1, 1, 1)
}

char *test_si_div_2_div_3() {
  CHECK_DIV(2, 3, 0)
}

char *test_si_div_10_div_5() {
  CHECK_DIV(10, 5, 2)
}

char *test_si_div_1_div_555555() {
  CHECK_DIV(1, 555555, 0)
}

char *test_si_div_999999_div_3() {
  CHECK_DIV(999999, 3, 333333)
}

char *test_si_div_large1() {
  CHECK_DIV(
    106049263636041958604145652070598535526633546516535098317625241745988446838483,
    89546152982728876178118028935422314934181625998417448340141872917759434384267,
    1
  )
}

char *test_si_div_large2() {
  CHECK_DIV(
    86075495160336522177662134916461033466141016476468295188677410126,
    89546152982728876178118028935422314934181625998417448340141872917759434384267,
    1
  )
}

char *test_si_div_large3() {
  CHECK_DIV(
    86075495160336522177662134916461033466141016476468295188677410126,
    99084692096400397499088821507191675818088,
    868706288924962199159255
  )
}



char *all_tests() {
  mu_suite_start();

  mu_run_test(test_si_div_0_div_0);
  mu_run_test(test_si_div_1_div_1);
  mu_run_test(test_si_div_2_div_3);
  mu_run_test(test_si_div_10_div_5);
  mu_run_test(test_si_div_1_div_555555);
  mu_run_test(test_si_div_999999_div_3);
  mu_run_test(test_si_div_large1);
  mu_run_test(test_si_div_large2);
  mu_run_test(test_si_div_large3);

  return NULL;
}

RUN_TESTS(all_tests);
