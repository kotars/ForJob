#include "s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int check = 0;
  if (s21_get_sign(value_1) == s21_get_sign(value_2)) {
    s21_big_decimal value_big_1 = {{0}};
    s21_big_decimal value_big_2 = {{0}};
    s21_big_decimal result_big = {{0}};
    s21_dec_to_big_dec(value_1, &value_big_1);
    s21_dec_to_big_dec(value_2, &value_big_2);
    if (s21_get_scale(value_1) > s21_get_scale(value_2)) {
      s21_big_normalize(&value_big_1, &value_big_2);
    } else if (s21_get_scale(value_1) < s21_get_scale(value_2))
      s21_big_normalize(&value_big_2, &value_big_1);

    result_big.bits[7] = value_big_1.bits[7];
    int memory = 0, new_bit = 0;
    for (int i = 0; i < 224; i++) {
      int bit_value_big_1 =
          (value_big_1.bits[i / 32] & (1 << (i % 32))) == 0 ? 0 : 1;
      int bit_value_big_2 =
          (value_big_2.bits[i / 32] & (1 << (i % 32))) == 0 ? 0 : 1;
      new_bit = bit_value_big_1 + bit_value_big_2 + memory;
      memory = new_bit / 2;
      if (new_bit != 0) result_big.bits[i / 32] += (new_bit % 2) << (i % 32);
    }

    check = s21_from_big_to_dec(result_big, result);
  } else {
    if (s21_is_less(value_1, value_2)) {
      set_sign(&value_1, s21_get_sign(value_2));
      check = s21_sub(value_1, value_2, result);
    } else {
      set_sign(&value_2, s21_get_sign(value_1));
      check = s21_sub(value_1, value_2, result);
    }
  }
  return check;
}