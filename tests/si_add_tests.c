#include "minunit.h"
#include <stack_int.h>
#include <string.h>

#define CHECK_ADD(X,Y,Z) \
  stack_int a, b, c, check; \
  si_from_ascii("" #X "", strlen("" #X ""), 10, 10, &a); \
  si_from_ascii("" #Y "", strlen("" #Y ""), 10, 10, &b); \
  si_from_ascii("" #Z "", strlen("" #Z ""), 10, 10, &check); \
  si_add(&a, &b, &c); \
  mu_assert(si_equals(&c, &check), "" #X " + " #Y " = " #Z ""); \
  char out[1024]; \
  si_to_ascii(&c, out, 1024); \
  mu_assert(!strcmp(out, "" #Z ""), "si_to_ascii(" #X " + " #Y ") = \"" #Z "\""); \
  return NULL;

char *test_si_add_0_plus_0() {
  CHECK_ADD(0, 0, 0)
}

char *test_si_add_0_plus_1() {
  CHECK_ADD(0, 1, 1)
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

char *test_si_add_large1() {
  CHECK_ADD(
    106591340561659747704384945938893446180047823176608288858409342163541877798879,
    108076170506751153170470268355992644045301262561025180707909167837797258633403,
    214667511068410900874855214294886090225349085737633469566318510001339136432282
  )
}

char *test_si_add_large2() {
  CHECK_ADD(
     93979385568437385358539373478430828371480064913606997252805093579541430876543,
    100113832380620469216584126907172361337347976228378722847361382912647112324303,
    194093217949057854575123500385603189708828041141985720100166476492188543200846
  )
}

char *test_si_add_large3() {
  CHECK_ADD(
    102959339582582135197285538833603264376545762016509980390528153732131718496007,
    115384991694053998992306102431787426451179805270776350823866851517182932326207,
    218344331276636134189591641265390690827725567287286331214395005249314650822214
  )
}

char *test_si_add_and_replace() {
  stack_int a, b;
  si_from_ascii("12", 2, 10, 10, &a);
  si_from_ascii("99", 2, 10, 10, &b);

  si_add(&a, &b, &a);

  stack_int check;
  si_from_ascii("111", 3, 10, 10, &check);
  mu_assert(si_equals(&a, &check), "Specifying an operand as +dest+ pointer should work");
  return NULL;
}

char *test_si_add_and_replace2() {
  stack_int a, b;
  si_from_ascii("1", 1, 10, 10, &a);
  si_from_ascii("92183781293719", 14, 10, 10, &b);

  si_add(&a, &b, &a);

  stack_int check;
  si_from_ascii("92183781293720", 14, 10, 10, &check);
  mu_assert(si_equals(&a, &check), "Specifying an operand as +dest+ pointer should work");
  return NULL;
}

char *test_si_add_and_replace3() {
  stack_int a, b;
  si_from_ascii("1", 1, 10, 10, &b);
  si_from_ascii("92183781293719", 14, 10, 10, &a);

  si_add(&a, &b, &a);

  stack_int check;
  si_from_ascii("92183781293720", 14, 10, 10, &check);
  mu_assert(si_equals(&a, &check), "Specifying an operand as +dest+ pointer should work");
  return NULL;
}


char *all_tests() {
  mu_suite_start();

  mu_run_test(test_si_add_0_plus_0);
  mu_run_test(test_si_add_0_plus_1);
  mu_run_test(test_si_add_255_plus_255);
  mu_run_test(test_si_add_512_plus_12344);
  mu_run_test(test_si_add_99999999_plus_1);
  mu_run_test(test_si_add_1_plus_99999999);
  mu_run_test(test_si_add_1_plus_1);
  mu_run_test(test_si_add_222_plus_222);
  mu_run_test(test_si_add_large1);
  mu_run_test(test_si_add_large2);
  mu_run_test(test_si_add_large3);
  mu_run_test(test_si_add_and_replace);
  mu_run_test(test_si_add_and_replace2);
  mu_run_test(test_si_add_and_replace3);

  return NULL;
}

RUN_TESTS(all_tests);
