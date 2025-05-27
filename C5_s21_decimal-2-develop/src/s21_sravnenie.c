#include "s21_decimal.h"

int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
  int flag = 0;
  if (s21_get_sign(value_1) > s21_get_sign(value_2)) {
    flag = 1;
  } else if (s21_get_sign(value_1) < s21_get_sign(value_2)) {
    flag = 0;
  } else {
    s21_big_decimal value_big_1 = {{0}};
    s21_big_decimal value_big_2 = {{0}};
    s21_dec_to_big_dec(value_1, &value_big_1);
    s21_dec_to_big_dec(value_2, &value_big_2);

    if (s21_get_scale(value_1) > s21_get_scale(value_2))
      s21_big_normalize(&value_big_1, &value_big_2);
    else if (s21_get_scale(value_1) < s21_get_scale(value_2))
      s21_big_normalize(&value_big_2, &value_big_1);

    for (int i = 223; i > -1; i--) {
      int bit_1 = (value_big_1.bits[i / 32] & (1 << (i % 32))) == 0 ? 0 : 1;
      int bit_2 = (value_big_2.bits[i / 32] & (1 << (i % 32))) == 0 ? 0 : 1;
      if (bit_1 < bit_2) {
        flag = s21_big_get_sign(value_big_1) > 0 ? 0 : 1;
        break;
      } else if (bit_1 > bit_2) {
        flag = s21_big_get_sign(value_big_1) > 0 ? 1 : 0;
        break;
      }
    }
  }
  return flag;
}
int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  int flag = 1;
  s21_big_decimal value_big_1 = {{0}};
  s21_big_decimal value_big_2 = {{0}};
  s21_dec_to_big_dec(value_1, &value_big_1);
  s21_dec_to_big_dec(value_2, &value_big_2);
  if (s21_get_scale(value_1) > s21_get_scale(value_2))
    s21_big_normalize(&value_big_1, &value_big_2);
  else if (s21_get_scale(value_1) < s21_get_scale(value_2))
    s21_big_normalize(&value_big_2, &value_big_1);

  for (int i = 223; i > -1; i--) {
    int bit_1 = (value_big_1.bits[i / 32] & (1 << (i % 32))) == 0 ? 0 : 1;
    int bit_2 = (value_big_2.bits[i / 32] & (1 << (i % 32))) == 0 ? 0 : 1;
    if (bit_1 != bit_2) {
      flag = 0;
      break;
    }
  }
  if (s21_big_get_sign(value_big_1) != s21_big_get_sign(value_big_2) &&
      value_big_1.bits[0] == 0 && value_big_2.bits[0] == 0 &&
      value_big_1.bits[1] == 0 && value_big_2.bits[1] == 0 &&
      value_big_1.bits[2] == 0 && value_big_2.bits[2] == 0 &&
      value_big_1.bits[3] == 0 && value_big_2.bits[3] == 0 &&
      value_big_1.bits[4] == 0 && value_big_2.bits[4] == 0 &&
      value_big_1.bits[5] == 0 && value_big_2.bits[5] == 0 &&
      value_big_1.bits[6] == 0 && value_big_2.bits[6] == 0)
    flag = 1;
  else if (s21_big_get_sign(value_big_1) != s21_big_get_sign(value_big_2))
    flag = 0;
  return flag;
}
int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2) {
  return s21_is_less(value_1, value_2) || s21_is_equal(value_1, value_2);
}
int s21_is_greater(s21_decimal value_1, s21_decimal value_2) {
  return !s21_is_less_or_equal(value_1, value_2);
}
int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2) {
  return !s21_is_less(value_1, value_2);
}
int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2) {
  return !s21_is_equal(value_1, value_2);
}