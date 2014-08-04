`stack_int` is a small, stack-based implementation of arbitrary-precision integers written in ANSI C. No dependencies are needed besides <stdint.h>. Negative integers are not supported for the moment.

#### Sample Code

    #include <stack_int.h>
  
    int main() {
      stack_int a, b, c;

      si_from_str("2000000", 7, 10, 10, &a);
      si_from_str("3000000", 7, 10, 10, &b);

      si_add(&a, &b, &c);

      char buf[128];
      si_to_str(&c, buf, 128);

      printf("a = %s\n", buf);

      return 1;
    }

#### Building

The entire implementation is found in the `stack_int.c` file. If you add a new function, make sure you add a matching test file inside of the `tests/` directory. To build a library containing the `si_*` functions, you can run:

    $ make build/libstack_int.a

#### Unit Tests

The simple unit test structure is taken from Zed Shaw's free book [Learn C the Hard Way](http://c.learncodethehardway.org/book/ex28.html). To run the test suite:

    $ make test
