#ifndef S21_DECIMAL_H
#define S21_DECIMAL_H

#include <ctype.h>
#include <float.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct {
  unsigned int bits[4];
} s21_decimal;

typedef struct {
  unsigned int bits[8];
} s21_big_decimal;
enum enum_error {
  OK = 0,
  FALSE = 0,
  NUMBER_INF = 1,
  TRUE = 1,
  ERROR_CONVERT = 1,
  NUMBER_MIN_INF = 2,
  DEV_BY_ZERO = 3
};
#define MINUS 0x80000000     // 10000000 00000000 00000000 00000000
#define SCALE 0x00ff0000     // 00000000 11111111 00000000 00000000
#define MAX4BITE 0xffffffff  // 11111111 11111111 11111111 11111111
#define MASK 0xf0000000      // 11110000 00000000 00000000 00000000
#define MIN4BITE 0x00000000

#define MAX_INT 2147483647
#define MIN_INT -2147483647
#define DEC_MAX 79228162514264337593543950335.0
#define DEC_MIN 1.0e-28

int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

int s21_get_sign(s21_decimal value);
int s21_big_get_sign(s21_big_decimal value);

int big_set_sign(s21_big_decimal *number, int sign);
int big_set_scale(s21_big_decimal *number, int scale);
int big_get_bit(s21_big_decimal number, int index_bit);
int s21_get_scale(s21_decimal value);
int s21_big_get_scale(s21_big_decimal value);
void s21_big_left_shift(s21_big_decimal *value, int number);
void s21_add_withot_normalize(s21_big_decimal value_big_1,
                              s21_big_decimal value_big_2,
                              s21_big_decimal *result_big);
void s21_big_normalize(s21_big_decimal *value_1, s21_big_decimal *value_2);

void s21_dec_to_big_dec(s21_decimal value_1, s21_big_decimal *value_2);

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);
int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result);

int s21_is_less(s21_decimal value_1, s21_decimal value_2);
int s21_is_less_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater(s21_decimal value_1, s21_decimal value_2);
int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_equal(s21_decimal value_1, s21_decimal value_2);
int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2);
int zero(s21_decimal *res);
int s21_from_int_to_decimal(int src, s21_decimal *dst);
int s21_from_float_to_decimal(float src, s21_decimal *dst);
int s21_from_decimal_to_int(s21_decimal src, int *dst);
int s21_from_decimal_to_float(s21_decimal src, float *dst);

void print_decimal(s21_decimal dst);
void print_big_decimal(s21_big_decimal dst);
int set_sign(s21_decimal *number, int sign);
int s21_from_big_to_dec(s21_big_decimal number, s21_decimal *result);

int div_simple_ten(s21_big_decimal *value);

int s21_negate(s21_decimal value,
               s21_decimal *result);  // Возвращает результат умножения
                                      // указанного Decimal на -1.
int s21_truncate(s21_decimal value,
                 s21_decimal *result);  // Возвращает целые цифры указанного
                                        //  Decimal числа; любые дробные цифры
                                        // отбрасываются, включая конечные нули.
int s21_floor(s21_decimal value,
              s21_decimal *result);  // Округляет указанное Decimal число до
                                     // ближайшего целого числа в сторону
                                     // отрицательной бесконечности.
int s21_round(
    s21_decimal value,
    s21_decimal *result);  // Округляет Decimal до ближайшего целого числа.

#endif