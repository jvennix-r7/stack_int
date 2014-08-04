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

void si_from_str(char* str,
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

void si_to_str(stack_int* si, char* buf, si_len_t buflen, uint8_t ascii) {
  if (si_is_zero(si)) {
    buf[0] = (ascii) ? '0' : 0;
    buf[1] = 0;
  } else {
    for (si_len_t i = 0; i < buflen && i < si->width; i++) {
      buf[i] = si_digit_at(si, i);    
    }
    buf[si->width] = 0;
  }

  // do an ascii encoding if we fit in printable range
  if (ascii) {
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
  si_init(ret, a->radix);

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

  ret->width = new_width;
}

void si_sub(stack_int* a, stack_int* b, stack_int* ret) {
  si_init(ret, a->radix);

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

  ret->width = new_width;
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

si_digit_t si_digit_at(stack_int* si, si_len_t left_offset) {
  return si->digits[SI_MAX_PRECISION-si->width+left_offset];
}

uint8_t si_is_zero(stack_int* si) {
  return (si->width == 0);
}


