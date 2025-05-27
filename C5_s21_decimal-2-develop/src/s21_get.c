#include "s21_decimal.h"

int s21_get_sign(s21_decimal value) { return value.bits[3] >> 31; }

int s21_big_get_sign(s21_big_decimal value) { return value.bits[7] >> 31; }

int s21_get_scale(s21_decimal value) {
  int scale = 0;
  for (int i = 0; i < 8; i++) {
    scale += pow(2, i) * ((value.bits[3] & (1 << (i + 16))) == 0 ? 0 : 1);
  }
  return scale;
}
int s21_big_get_scale(s21_big_decimal value) {
  int scale = 0;
  for (int i = 0; i < 8; i++) {
    scale += pow(2, i) * ((value.bits[7] & (1 << (i + 16))) == 0 ? 0 : 1);
  }
  return scale;
}
int set_sign(s21_decimal *number, int sign) {
  if (sign == 1) {
    number->bits[3] = number->bits[3] | (1 << 31);
  } else {
    number->bits[3] = number->bits[3] & ~(1 << 31);
  }
  return 0;
}
int big_set_sign(s21_big_decimal *number, int sign) {
  if (sign == 1) {
    number->bits[7] = number->bits[7] | (1 << 31);
  } else {
    number->bits[7] = number->bits[7] & ~(1 << 31);
  }
  return 0;
}
int big_set_scale(s21_big_decimal *number, int scale) {
  int sign = s21_big_get_sign(*number);
  number->bits[7] = 0;
  scale = scale << 16;

  number->bits[7] = scale | number->bits[7];
  if (sign != 0) {
    big_set_sign(number, sign);
  }
  return 0;
}
// void notation_2(unsigned int x) {
//   char str[32];
//   for (int i = 0; i < 32; i++) {
//     str[i] = x % 2 + '0';
//     x /= 2;
//   }
//   printf("[ ");
//   for (int i = 0; i < 32; i++) printf("%c", str[31 - i]);
//   printf(" ]\n");
// }
// void print_decimal(s21_decimal dst) {
//   printf("bits\t%5d%25d\n", 10, 2);
//   for (int i = 0; i < 4; i++) {
//     printf("[%d] = [%10u]", i, dst.bits[i]);
//     notation_2(dst.bits[i]);
//   }
// }
// void print_big_decimal(s21_big_decimal dst) {
//   printf("bits\t%5d%25d\n", 10, 2);
//   for (int i = 0; i < 8; i++) {
//     printf("[%d] = [%10u]", i, dst.bits[i]);
//     notation_2(dst.bits[i]);
//   }
// }
int big_get_bit(s21_big_decimal number, int index_bit) {
  int bit;
  if ((number.bits[index_bit / 32] & (1 << index_bit % 32)) == 0) {
    bit = 0;
  } else {
    bit = 1;
  }
  return bit;
}