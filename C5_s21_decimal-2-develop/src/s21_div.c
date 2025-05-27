#include "s21_decimal.h"

void s21_big_set_bit(s21_big_decimal *value, int bit_position) {
  int index = bit_position / 32;
  int bit_offset = bit_position % 32;
  value->bits[index] |= (1U << bit_offset);
}

void s21_big_subtract(s21_big_decimal value1, s21_big_decimal value2,
                      s21_big_decimal *result) {
  unsigned int borrow = 0;
  for (int i = 0; i < 7; i++) {
    unsigned long long sub =
        (unsigned long long)value1.bits[i] - value2.bits[i] - borrow;
    result->bits[i] = (uint32_t)sub;
    borrow = (sub >> 32) & 1;
  }
}

int big_compare(s21_big_decimal value_1, s21_big_decimal value_2) {
  for (int i = 223; i >= 0; i--) {
    int bit_1 = (value_1.bits[i / 32] & (1 << (i % 32))) ? 1 : 0;
    int bit_2 = (value_2.bits[i / 32] & (1 << (i % 32))) ? 1 : 0;

    if (bit_1 > bit_2) {
      return 1;
    } else if (bit_1 < bit_2) {
      return -1;
    }
  }
  return 0;
}
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int check = 0;
  s21_big_decimal value_big_1 = {{0}};
  s21_big_decimal value_big_2 = {{0}};
  s21_big_decimal result_big = {{0}};

  s21_dec_to_big_dec(value_1, &value_big_1);
  s21_dec_to_big_dec(value_2, &value_big_2);

  if (zero(&value_2)) {
    return 3;
  } else {
    s21_big_decimal remainder = {{0}};

    int scale_1 = s21_get_scale(value_1);
    int scale_2 = s21_get_scale(value_2);
    int result_scale = scale_1 - scale_2;
    if (s21_get_scale(value_1) > s21_get_scale(value_2)) {
      s21_big_normalize(&value_big_1, &value_big_2);
    } else if (s21_get_scale(value_1) < s21_get_scale(value_2))
      s21_big_normalize(&value_big_2, &value_big_1);

    for (int i = 191; i >= 0; i--) {
      s21_big_left_shift(&remainder, 1);
      if (big_get_bit(value_big_1, i)) {
        s21_big_set_bit(&remainder, 0);
      }

      if (big_compare(remainder, value_big_2) >= 0) {
        s21_big_subtract(remainder, value_big_2, &remainder);
        s21_big_set_bit(&result_big, i);
      }
    }

    if (result_scale < 0) result_scale = 0;

    big_set_sign(&result_big,
                 (s21_get_sign(value_1) + s21_get_sign(value_2)) % 2);

    big_set_scale(&result_big, result_scale);

    check = s21_from_big_to_dec(result_big, result);

    if (check == 1) {
      return 1;
    } else if (check == 2) {
      return 2;
    }
  }

  return check;
}
