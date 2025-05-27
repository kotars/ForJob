#include "s21_decimal.h"

void s21_add_withot_normalize(s21_big_decimal value_big_1,
                              s21_big_decimal value_big_2,
                              s21_big_decimal* result_big) {
  result_big->bits[0] = 0;
  result_big->bits[1] = 0;
  result_big->bits[2] = 0;
  result_big->bits[3] = 0;
  result_big->bits[4] = 0;
  result_big->bits[5] = 0;
  result_big->bits[6] = 0;
  int memory = 0, new_bit = 0;
  for (int i = 0; i < 224; i++) {
    int bit_value_big_1 =
        (value_big_1.bits[i / 32] & (1 << (i % 32))) == 0 ? 0 : 1;
    int bit_value_big_2 =
        (value_big_2.bits[i / 32] & (1 << (i % 32))) == 0 ? 0 : 1;
    new_bit = bit_value_big_1 + bit_value_big_2 + memory;
    memory = new_bit / 2;
    if (new_bit != 0) result_big->bits[i / 32] += (new_bit % 2) << (i % 32);
  }
}
void s21_big_normalize(s21_big_decimal* value_1, s21_big_decimal* value_2) {
  while (s21_big_get_scale(*value_1) != s21_big_get_scale(*value_2)) {
    s21_big_decimal a = *value_2, b = *value_2;
    s21_big_left_shift(&a, 3);
    s21_big_left_shift(&b, 1);
    s21_add_withot_normalize(a, b, value_2);
    value_2->bits[7] >>= 16;
    value_2->bits[7]++;
    value_2->bits[7] <<= 16;
  }
}
