#include "s21_decimal.h"

void s21_big_left_shift(s21_big_decimal* value, int number) {
  unsigned int mem = 0;
  for (int i = 0; i < 7; i++) {
    unsigned int temp = value->bits[i];
    value->bits[i] <<= number;
    value->bits[i] |= mem;
    mem = temp >> (32 - number);
  }
}