#include "s21_decimal.h"

void s21_dec_to_big_dec(s21_decimal value_1, s21_big_decimal *value_2) {
  value_2->bits[0] = value_1.bits[0];
  value_2->bits[1] = value_1.bits[1];
  value_2->bits[2] = value_1.bits[2];
  value_2->bits[7] = value_1.bits[3];
}

int div_simple_ten(s21_big_decimal *value) {
  unsigned long long int num, max35;
  unsigned long long int x = 8;
  max35 = 34359738368;
  unsigned long long int osthighbit = 0;
  unsigned long long int ostlowbit = 0;  // остаток

  osthighbit = value->bits[6] % 10;
  value->bits[6] =
      value->bits[6] / 10;  // остаток от деления на 10 старшего бита

  for (int i = 6; i > 0; i = i - 1) {  // идем по мантиссе со старших разрядов

    ostlowbit = value->bits[i - 1] % 10;  // остаток от деления на 10 шего бита

    value->bits[i - 1] = value->bits[i - 1] / 10;

    max35 = 4294967296;
    num = 0;
    x = 8;

    while (osthighbit > 0) {
      num = (osthighbit % 2) * max35 + num;
      osthighbit = osthighbit / 2;  //}
      x = x / 2;

      max35 = max35 * 2;
    }
    max35 = 4294967296;

    ostlowbit = ostlowbit + num % 10;
    num = value->bits[i - 1] + num / 10 + ostlowbit / 10;

    if (num >= max35) {
      ++value->bits[i];
      num = num - max35;
    }
    value->bits[i - 1] = num;
    osthighbit = ostlowbit % 10;
  }

  big_set_scale(value, s21_big_get_scale(*value) - 1);
  return osthighbit;
}

int s21_from_big_to_dec(s21_big_decimal number, s21_decimal *result) {
  int res = 0;
  int zero = 0;
  int okrugl = 0;
  int k = 0;

  while (s21_big_get_scale(number) > 28) {
    if (number.bits[0] == 0 && number.bits[1] == 0 && number.bits[2] == 0 &&
        number.bits[3] == 0 && number.bits[4] == 0 && number.bits[5] == 0 &&
        number.bits[6] == 0) {
      res = 2;

      break;
    } else {
      zero = div_simple_ten(&number);
      okrugl = zero + okrugl;
      k++;
    }
  }

  while ((number.bits[3] > 0 || number.bits[4] > 0 || number.bits[5] > 0 ||
          number.bits[6] > 0)) {
    if (s21_big_get_scale(number) > 0) {
      zero = div_simple_ten(&number);
      okrugl = zero + okrugl;
      k++;
    }

    else {
      if (s21_big_get_sign(number) == 1) {
        res = 2;
      } else {
        res = 1;
      }

      break;
    }
  }

  s21_big_decimal bank = {{1, 0, 0, 0, 0, 0, 0, 0}};

  if ((zero > 5 || (zero == 5 && okrugl > zero))) {
    s21_add_withot_normalize(number, bank, &number);
  }
  if (zero == 5 && okrugl == zero && number.bits[0] % 2 == 1 &&
      s21_big_get_sign(number) == 0) {
    s21_add_withot_normalize(number, bank, &number);
  }

  if (number.bits[3] == 0 && number.bits[4] == 0 && number.bits[5] == 0 &&
      number.bits[6] == 0 && res == 0) {
    result->bits[3] = number.bits[7];
    result->bits[0] = number.bits[0];
    result->bits[1] = number.bits[1];
    result->bits[2] = number.bits[2];
    res = 0;
  }
  if ((number.bits[3] > 0 || number.bits[4] > 0 || number.bits[5] > 0 ||
       number.bits[6] > 0) &&
      s21_big_get_scale(number) == 0 && s21_big_get_sign(number) == 0) {
    res = 1;
  }
  if ((number.bits[3] > 0 || number.bits[4] > 0 || number.bits[5] > 0 ||
       number.bits[6] > 0) &&
      s21_big_get_scale(number) == 0 && s21_big_get_sign(number) == 1) {
    res = 2;
  }

  return res;
}
