#include "s21_decimal.h"

int zero(s21_decimal* res) {
  int k = 0;

  if (res->bits[2] == 0 && res->bits[1] == 0 && res->bits[0] == 0) {
    res->bits[3] = 0;
    k = 1;
  }
  return k;
}

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal* result) {
  int check = 0;
  s21_big_decimal value_big_1 = {{0}};
  s21_big_decimal value_big_2 = {{0}};
  s21_big_decimal result_big = {{0}};

  s21_dec_to_big_dec(value_1, &value_big_1);
  s21_dec_to_big_dec(value_2, &value_big_2);
  value_big_2.bits[7] = 0;
  // умножение невъебическое
  if (!zero(&value_1) && !zero(&value_2)) {
    for (int i = 0; i < 96; i++) {
      if (big_get_bit(value_big_1, i)) {
        s21_add_withot_normalize(result_big, value_big_2, &result_big);
      }
      s21_big_left_shift(&value_big_2, 1);
    }
    int scale = (s21_get_scale(value_1) + s21_get_scale(value_2));
    big_set_sign(&result_big,
                 ((s21_get_sign(value_1) + s21_get_sign(value_2)) % 2));

    big_set_scale(&result_big, scale);
    check = s21_from_big_to_dec(result_big, result);
  }
  return check;
}