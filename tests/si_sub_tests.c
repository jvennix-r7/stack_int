#include "minunit.h"
#include <stack_int.h>
#include <string.h>

#define CHECK_SUB(X,Y,Z) \
  stack_int a, b, c, check; \
  si_from_str("" #X "", strlen("" #X ""), 10, 10, &a); \
  si_from_str("" #Y "", strlen("" #Y ""), 10, 10, &b); \
  si_from_str("" #Z "", strlen("" #Z ""), 10, 10, &check); \
  si_sub(&a, &b, &c); \
  mu_assert(si_equals(&c, &check), "" #X " - " #Y " = " #Z ""); \
  char out[4096]; \
  si_to_str(&c, out, 4096, 1); \
  mu_assert(!strcmp(out, "" #Z ""), "si_to_str(" #X " - " #Y ") = \"" #Z "\""); \
  return NULL;

char *test_si_sub_0_minus_0() {
  CHECK_SUB(0, 0, 0)
}

char *test_si_sub_255_minus_255() {
  CHECK_SUB(255, 255, 0)
}

char *test_si_sub_12344_minus_512() {
  CHECK_SUB(12344, 512, 11832)  
}

char *test_si_sub_99999999_minus_1() {
  CHECK_SUB(99999999, 1, 99999998)
}


char *test_si_sub_99999999_minus_99999999() {
  CHECK_SUB(99999999, 99999999, 0)
}

char *test_si_sub_1_minus_1() {
  CHECK_SUB(1, 1, 0)
}

char *test_si_sub_222_minus_222() {
  CHECK_SUB(222, 222, 0)
}

char *test_si_sub_large1() {
  CHECK_SUB(
    123172398712893781923891,
         9893280953095902358,
    123162505431940686021533
  )
}

char *test_si_sub_large2() {
  CHECK_SUB(
    103702690922713359741973967818859673961833308784453371570763751110053423423879,
    97508801281153954350327315114225299043631844227323935871416821872753907323803,
    6193889641559405391646652704634374918201464557129435699346929237299516100076
  )
}

char *test_si_sub_large3() {
  CHECK_SUB(
    13357310392908256918229741159946734706192741720215500639464653467921202093674691526075440108345402791061741514957638198489020044583186389313988751327460763,
    12311751785753370394881428189598405054364174485502824922351817579519864845672562310637257672652996340953491243806848625727274230852375488928772352871096419,
    1045558607154886523348312970348329651828567234712675717112835888401337248002129215438182435692406450108250271150789572761745813730810900385216398456364344
  )
}

char *all_tests() {
  mu_suite_start();

  mu_run_test(test_si_sub_0_minus_0);
  mu_run_test(test_si_sub_255_minus_255);
  mu_run_test(test_si_sub_12344_minus_512);
  mu_run_test(test_si_sub_99999999_minus_1);
  mu_run_test(test_si_sub_99999999_minus_99999999);
  mu_run_test(test_si_sub_1_minus_1);
  mu_run_test(test_si_sub_222_minus_222);
  mu_run_test(test_si_sub_large1);
  mu_run_test(test_si_sub_large2);
  mu_run_test(test_si_sub_large3);

  return NULL;
}

RUN_TESTS(all_tests);
