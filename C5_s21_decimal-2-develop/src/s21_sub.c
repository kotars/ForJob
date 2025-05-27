#include "s21_decimal.h"

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int check = 0, memory = 0, bit_big = 0, bit_small = 0;
  int k1 = s21_get_sign(value_1);
  int k2 = s21_get_sign(value_2);
  if (k1 != k2) {
    set_sign(&value_2, s21_get_sign(value_1));
    check = s21_add(value_1, value_2, result);
  } else {
    s21_big_decimal value_big_1 = {{0}};
    s21_big_decimal value_big_2 = {{0}};
    s21_big_decimal result_big = {{0}};
    set_sign(&value_1, 0);
    set_sign(&value_2, 0);
    if (s21_is_equal(value_1, value_2) == 0) {
      if (s21_is_greater(value_1, value_2)) {
        s21_dec_to_big_dec(value_1, &value_big_1);
        if (k2 == 1) {
          big_set_sign(&result_big, 1);
        }
        s21_dec_to_big_dec(value_2, &value_big_2);

      } else {
        s21_dec_to_big_dec(value_2, &value_big_1);
        if (k2 == 0) {
          big_set_sign(&result_big, 1);
        }
        s21_dec_to_big_dec(value_1, &value_big_2);
      }

      if (s21_get_scale(value_1) > s21_get_scale(value_2))
        s21_big_normalize(&value_big_1, &value_big_2);
      else if (s21_get_scale(value_1) < s21_get_scale(value_2))
        s21_big_normalize(&value_big_2, &value_big_1);

      big_set_scale(&result_big, s21_big_get_scale(value_big_1));

      for (int i = 0; i < 224; i++) {
        bit_big = big_get_bit(value_big_1, i);
        bit_small = big_get_bit(value_big_2, i);
        if (bit_big == 0 && bit_small == 1 && !memory) {
          memory = 1;
          result_big.bits[i / 32] += (int)pow(2, i % 32);
        } else if ((bit_big == 1 && bit_small == 1 && memory) ||
                   (bit_big == 1 && bit_small == 0 && !memory) ||
                   (bit_big == 0 && bit_small == 0 && memory)) {
          result_big.bits[i / 32] += (int)pow(2, i % 32);
        } else if (bit_big == 1 && bit_small == 0 && memory) {
          memory = 0;
        }
      }
    }
    check = s21_from_big_to_dec(result_big, result);
  }
  return check;
}

// какие случаи нужно обработать? (sub)
// 1. a > b && (+ == + || - == - ) => result.bits[3] - нужно заполнить +
// 2. a >=< b && (+, -) => s21_add => result.bits[3] - заполянем - sign = 0
// +
// 3. a >=< b && (-, +) => s21_add => result.bits[3] -заполняем - sign = 1 +
// 4. a == b && (+ == + || - == - ) => result.bits[3] = 0 +
// 5. a < b && (+ == + || - == -) => result.bits[3] - заполняем +