#include <stdlib.h>
#include <string.h>

#include "s21_decimal.h"
#define MAX_INT 2147483647
#define MIN_INT -2147483647
#define DEC_MAX 79228162514264337593543950335.0
#define DEC_MIN 1.0e-28

void s21_set_string_for_float(char src_string[1024]);
void s21_set_string_int(char src_string[1024], char src_string_int[1024],
                        s21_decimal *dst);
int get_bit(s21_decimal src, int index);
int make_zero_decimal(s21_decimal *src);

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int res = 1;
  make_zero_decimal(dst);
  if (MIN_INT <= src && src <= MAX_INT) {
    if (src < 0) {
      src = -src;
      dst->bits[3] = 0x80000000;
    } else {
      dst->bits[3] = 0x00000000;
    }
    dst->bits[0] = src;
    res = 0;
  }
  return res;
}

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int res = 0;

  *dst = (float)src.bits[2] * powf(2., 64.) +
         (float)src.bits[1] * powf(2., 32.) + (float)src.bits[0];

  int scale = s21_get_scale(src);

  *dst /= powf(10., scale);

  if (s21_get_sign(src)) {
    *dst = *dst * (-1);
  }

  return res;
}

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int flag = 0;
  if (src.bits[1] == 0 && src.bits[2] == 0) {
    *dst = src.bits[0];
  }
  int scale = s21_get_scale(src);
  *dst /= pow(10, scale);
  if (s21_get_sign(src)) {
    *dst = *dst * -1;
  }
  return flag;
}

int make_zero_decimal(s21_decimal *src) {
  src->bits[0] = 0;
  src->bits[1] = 0;
  src->bits[2] = 0;
  src->bits[3] = 0;
  return 0;
}

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int result = 0;
  if (dst == NULL || isnan(src) || isinf(src) ||
      (fabsf(src) < 1e-28 && fabsf(src) > 0) ||
      src > 79228162514264337593543950335.0) {
    result = 1;
  } else {
    dst->bits[0] = 0;
    dst->bits[1] = 0;
    dst->bits[2] = 0;
    dst->bits[3] = 0;
    if (src != 0.0f) {
      if (src < 0) {
        dst->bits[3] = dst->bits[3] | 1 << 31;
        src = src * (-1);
      }

      double temp_src = (double)src;
      int scale = 0;
      for (; scale < 28 && (int)temp_src / (int)pow(2, 21) == 0;
           temp_src *= 10, scale++) {
      }
      temp_src = round(temp_src);
      if (temp_src > 79228162514264337593543950335.0) {
        result = 1;
      }

      dst->bits[0] = (unsigned int)fmod(temp_src, pow(2, 32));
      temp_src /= pow(2, 32);
      dst->bits[1] = (unsigned int)fmod(temp_src, pow(2, 32));
      temp_src /= pow(2, 32);
      dst->bits[2] = (unsigned int)fmod(temp_src, pow(2, 32));

      dst->bits[3] |= (unsigned int)(scale << 16);
    }
  }
  return result;
}