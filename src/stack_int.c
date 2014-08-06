#include "stack_int.h"
#include <stdio.h>

void si_init(stack_int* si, si_digit_t radix) {
  si->width = 0;
  si->radix = radix;
}

void si_copy(stack_int* a, stack_int* b) {
  b->width = a->width;
  b->radix = a->radix;
  for (si_len_t i = SI_MAX_PRECISION-a->width-1; i < SI_MAX_PRECISION; i++) {
    b->digits[i] = a->digits[i];
  }
}

void si_from_ascii(char* str,
                   si_len_t len,
                   si_digit_t inradix,
                   si_digit_t outradix,
                   stack_int* si) {

  si_init(si, outradix);
  
  si_len_t width = 0;
  for (si_len_t i = 0; i < len; i++) {
    si_digit_t d = str[len-i-1];
    if (d >= '0' && d <= '9') {
      d -= '0';
    } else if (d >= 'a' && d <= 'z') {
      d = d - 'a' + 10;
    }

    if (d != 0) width = i+1;
    si->digits[SI_MAX_PRECISION-i-1] = d;
  }

  si->width = width;
}

void si_to_ascii(stack_int* si, char* buf, si_len_t buflen) {
  if (si_is_zero(si)) {
    buf[0] = '0';
    buf[1] = 0;
  } else {
    for (si_len_t i = 0; i < buflen && i < si->width; i++) {
      buf[i] = si_digit_at(si, i);    
    }
    buf[si->width] = 0;

    // ascii encode all the things
    for (si_len_t i = 0; i < buflen && i < si->width; i++) {
      if (buf[i] < 10) {
        buf[i] += '0';
      } else {
        buf[i] = buf[i] - 10 + 'a';
      }
    }
  }
}

void si_add(stack_int* a, stack_int* b, stack_int* ret) {
  si_len_t     r      = SI_MAX_PRECISION-1;
  uint8_t  carry      = 0;
  si_len_t width      = (a->width > b->width) ? a->width : b->width;
  si_len_t i          = 0;
  si_len_t new_width  = 0;

  while (r > SI_MAX_PRECISION-width-2 && i < SI_MAX_PRECISION) {
    si_digit_t a_ = (i < a->width) ? a->digits[r] : 0;
    si_digit_t b_ = (i < b->width) ? b->digits[r] : 0;

    si_double_digit_t n = a_ + b_ + carry;
    ret->digits[r]      = n % a->radix;

    carry = (n >= a->radix) ? 1 : 0;
    new_width = (ret->digits[r] != 0) ? i+1 : new_width;

    i++;
    r--;
  }

  ret->radix = a->radix;
  ret->width = new_width;
}

void si_sub(stack_int* a, stack_int* b, stack_int* ret) {
  si_len_t r          = SI_MAX_PRECISION-1;
  uint8_t  carry      = 0;
  si_len_t width      = (a->width > b->width) ? a->width : b->width;
  si_len_t i          = 0;
  si_len_t new_width  = 0;

  while (r > SI_MAX_PRECISION-width-2 && i < SI_MAX_PRECISION) {
    si_digit_t a_ = (i < a->width) ? a->digits[r] : 0;
    si_digit_t b_ = (i < b->width) ? b->digits[r] : 0;
    si_double_digit_t n;

    if (a_ - carry >= b_) {
      n = a_ - b_ - carry;
      carry = 0;
    } else { // we have to borrow from left
      n = ((si_double_digit_t)(a->radix) + a_ - carry) - b_;
      carry = 1;
    }

    ret->digits[r] = n;

    new_width = (ret->digits[r] != 0) ? i+1 : new_width;

    i++;
    r--;
  }

  ret->radix = a->radix;
  ret->width = new_width;
}

void si_mult_naive(stack_int* a, stack_int* b, stack_int* ret) {
  stack_int one, i;

  si_from_ascii("1", 1, 10, a->radix, &one);
  si_init(&i, a->radix);
  si_init(ret, a->radix);

  while (si_lt(&i, b)) {
    si_add(ret, a, ret);
    si_add(&i, &one, &i);
  }
}

void si_mult_long(stack_int* a, stack_int* b, stack_int* ret) {

  // Ensure b always never has more digits than a
  if (a->width < b->width) {
    stack_int* tmp = b;
    b = a;
    a = tmp;
  }

  si_digit_t carry      = 0;
  si_len_t   i          = 0;
  si_len_t   new_width  = 0;

  si_digit_t digits[b->width][a->width+1];

  for (i = 0; i < b->width; i++) {
    for (si_len_t i2 = 0; i2 < a->width+1; i2++) {
      si_digit_t a_ = (i2 < a->width) ? a->digits[SI_MAX_PRECISION-1-i2] : 0;
      si_digit_t b_ = (i < b->width) ? b->digits[SI_MAX_PRECISION-1-i] : 0;
      si_double_digit_t n = a_ * b_ + carry;

      digits[i][a->width-i2] = n % a->radix;
      carry = n / a->radix;
    }
  }

  carry = 0;

  if (a->width > 0) {
    for (i = 0; i < a->width*2-1; i++) {
      si_double_digit_t n = carry;
      for (si_len_t j = 0; j <= i && j < b->width; j++) {
        if (i <= a->width+j) {
          n += digits[j][a->width-i+j];
        }
      }

      carry = n / a->radix;
      ret->digits[SI_MAX_PRECISION-1-i] = n % a->radix;

      if (n > 0) new_width = i+1;
    }
  }

  ret->radix = a->radix;
  ret->width = new_width;
}

void si_mult(stack_int* a, stack_int* b, stack_int* ret) {
  si_mult_naive(a, b, ret);
}

void si_div(stack_int* n, stack_int* d, stack_int* q, stack_int* r) {
  stack_int one;
  si_from_ascii("1", 1, 10, n->radix, &one);
  si_copy(n, r);
  si_init(q, n->radix);

  if (d->width) {
    while (si_lt(d, r) || si_equals(d, r)) {
      si_sub(r, d, r);
      si_add(q, &one, q);
    }
  }
}

si_len_t si_log(stack_int* a, si_digit_t base) {
  if (base == a->radix) {
    return a->width-1;
  } else {
    // convert and return result
    return 0;
  }
}

uint8_t si_lt(stack_int* a, stack_int *b) {
  if (a->width != b-> width)
    return (a->width < b-> width);

  for (si_len_t i = 0; i < a->width; i++) {
    if (si_digit_at(a, i) > si_digit_at(b, i)) {
      return 0;
    } else if (si_digit_at(a, i) < si_digit_at(b, i)) {
      return 1;
    }
  }

  return 0;
}

uint8_t si_equals(stack_int* a, stack_int* b) {
  if (a->width != b->width) return 0;
  for (si_len_t i = 0; i < a->width; i++) {
    if (si_digit_at(a, i) != si_digit_at(b, i)) {
      return 0;
    }
  }
  return 1;
}

void si_print(stack_int* si) {
  char buf[1024];
  si_to_ascii(si, buf, 1024);
  printf("%s\n", buf);
}

si_digit_t si_digit_at(stack_int* si, si_len_t left_offset) {
  return si->digits[SI_MAX_PRECISION-si->width+left_offset];
}

uint8_t si_is_zero(stack_int* si) {
  return (si->width == 0);
}


