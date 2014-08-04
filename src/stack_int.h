#ifndef STACK_INT_H
#define STACK_INT_H

#ifndef uint8_t
#include <stdint.h>
#endif

#define SI_MAX_PRECISION 1024

typedef uint8_t  si_digit_t;
typedef uint16_t si_double_digit_t;
typedef uint32_t si_len_t;

typedef struct {
  si_digit_t digits[SI_MAX_PRECISION];
  si_len_t   width;
  si_digit_t radix;
} stack_int;

// Creation and formatting functions
void si_init(stack_int* si, si_digit_t radix);
void si_copy(stack_int* a, stack_int* b);
void si_to_str(stack_int* si, char* buf, si_len_t buflen, uint8_t ascii);
void si_from_str(char* str,
                 si_len_t len,
                 si_digit_t inradix,
                 si_digit_t outradix,
                 stack_int* si);

// Mathematical functions
void si_add(stack_int* a, stack_int* b, stack_int* ret);
void si_sub(stack_int* a, stack_int* b, stack_int* ret);
void si_mult(stack_int* a, stack_int* b, stack_int* ret);


// Utility/helper functions
si_digit_t si_digit_at(stack_int* si, si_len_t left_offset);
uint8_t    si_is_zero(stack_int* si);
uint8_t    si_equals(stack_int* a, stack_int* b);
uint8_t    si_lt(stack_int* a, stack_int *b);

#endif // STACK_INT_H
