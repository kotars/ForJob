#include "s21_decimal.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
  int k = 0;
  if (s21_get_scale(value) > 28) {
    k = 1;
  } else {
    int sign = s21_get_sign(value);
    if (sign == 0) {
      set_sign(&value, 1);
    } else if (sign == 1) {
      set_sign(&value, 0);
    }
    *result = value;
  }
  return k;
}

int s21_truncate(s21_decimal value, s21_decimal *result) {
  int check = 0;
  if (s21_get_scale(value) > 28) {
    check = 1;
  } else {
    s21_big_decimal big = {{0}};
    int scale = s21_get_scale(value);
    s21_dec_to_big_dec(value, &big);
    while (scale > 0) {
      div_simple_ten(&big);
      *result = value;
      scale--;
    }
    s21_from_big_to_dec(big, result);
  }
  return check;
}
int s21_floor(s21_decimal value, s21_decimal *result) {
  int check = 0;
  if (s21_get_scale(value) > 28) {
    check = 1;
  } else {
    int sign = s21_get_sign(value);
    if (sign == 0) {
      s21_truncate(value, result);
    } else {
      s21_truncate(value, result);
      result->bits[0] += 1;
    }
    set_sign(result, sign);
  }
  return check;
}

int s21_round(s21_decimal value, s21_decimal *result) {
  int k = 0;
  if (s21_get_scale(value) > 28) {
    k = 1;
  } else {
    int scale = s21_get_scale(value);
    s21_big_decimal big = {0};
    s21_dec_to_big_dec(value, &big);
    int zero = 0;
    int okrugl = 0;
    while (scale > 0) {
      scale--;
      zero = div_simple_ten(&big);
      okrugl = zero + okrugl;
    }
    s21_big_decimal bank = {{1, 0, 0, 0, 0, 0, 0, 0}};

    if ((zero > 5 || (zero == 5 && okrugl > zero))) {
      s21_add_withot_normalize(big, bank, &big);
    }
    if (zero == 5 && okrugl == zero && big.bits[0] % 2 == 1 &&
        s21_big_get_sign(big) == 0) {
      s21_add_withot_normalize(big, bank, &big);
    }

    s21_from_big_to_dec(big, result);
  }
  return k;
}