#include "minunit.h"
#include <stack_int.h>
#include <string.h>

#define CHECK_TIMES_NAIVE(X,Y,Z) \
  stack_int a, b, c, check; \
  si_from_ascii("" #X "", strlen("" #X ""), 10, 10, &a); \
  si_from_ascii("" #Y "", strlen("" #Y ""), 10, 10, &b); \
  si_from_ascii("" #Z "", strlen("" #Z ""), 10, 10, &check); \
  si_mult_naive(&a, &b, &c); \
  mu_assert(si_equals(&c, &check), "" #X " * " #Y " = " #Z ""); \
  char out[1024]; \
  si_to_ascii(&c, out, 1024); \
  mu_assert(!strcmp(out, "" #Z ""), "si_to_ascii(" #X " * " #Y ") = \"" #Z "\""); \
  return NULL;

char *test_si_mult_naive_0_times_0() {
  CHECK_TIMES_NAIVE(0, 0, 0)
}

char *test_si_mult_naive_1_times_1() {
  CHECK_TIMES_NAIVE(1, 1, 1)
}

char *test_si_mult_naive_255_times_255() {
  CHECK_TIMES_NAIVE(255, 255, 65025)
}

char *test_si_mult_naive_512_times_12344() {
  CHECK_TIMES_NAIVE(512, 12344, 6320128)
}

char *test_si_mult_naive_99999999_times_1() {
  CHECK_TIMES_NAIVE(99999999, 1, 99999999)
}


char *test_si_mult_naive_1_times_99999999() {
  CHECK_TIMES_NAIVE(1, 99999999, 99999999)
}


char *test_si_mult_naive_99999999_times_1208() {
  CHECK_TIMES_NAIVE(99999999, 1208, 120799998792)
}

char *test_si_mult_naive_222_times_24() {
  CHECK_TIMES_NAIVE(222, 24, 5328)
}

char *test_si_mult_naive_large1() {
  CHECK_TIMES_NAIVE(
    91641010368693957408856288170131471810730481143635276980714674373405563460307,
    24,
    2199384248848654977812550916083155323457531547447246647537152184961733523047368
  )
}

char *test_si_mult_naive_large2() {
  CHECK_TIMES_NAIVE(
    96838929382350179139486535156657652208043818386922685891032442906872130676807,
    42,
    4067235034058707523858434476579621392737840372250752807423362602088629488425894
  )
}

char *test_si_mult_naive_large3() {
  CHECK_TIMES_NAIVE(
    101335708838626427552284269995820006930409162724941669254518011861861689490703,
    55,
    5573463986124453515375634849770100381172503949871791808998490652402392921988665
  )
}

char *all_tests() {
  mu_suite_start();

  mu_run_test(test_si_mult_naive_0_times_0);
  mu_run_test(test_si_mult_naive_1_times_1);
  mu_run_test(test_si_mult_naive_255_times_255);
  mu_run_test(test_si_mult_naive_512_times_12344);
  mu_run_test(test_si_mult_naive_99999999_times_1208);
  mu_run_test(test_si_mult_naive_222_times_24);
  mu_run_test(test_si_mult_naive_large1);
  mu_run_test(test_si_mult_naive_large2);
  mu_run_test(test_si_mult_naive_large3);

  return NULL;
}

RUN_TESTS(all_tests);
