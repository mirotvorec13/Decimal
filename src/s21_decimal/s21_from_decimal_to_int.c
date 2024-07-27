#include "../s21_decimal.h"

int s21_from_decimal_to_int(
    s21_decimal src,
    int *dst) {  // работает если число не целое(нужна функция truncate)
  int res = OK;
  *dst = 0;
  s21_decimal tmp = {{0}};

  if (!dst) {
    res = CONVERTING_ERROR;
  } else if (s21_is_decimal_correct(src)) {
    res = CONVERTING_ERROR;
  } else {  // если все ок, записываем в dst значение инта
    s21_truncate(src, &tmp);
    *dst = tmp.bits[0];
    if (check_sign(src)) {
      *dst = *dst * (-1);
    }
    if (tmp.bits[1] || tmp.bits[2]) {
      res = CONVERTING_ERROR;
      *dst = 0;
    }
  }
  return res;
}
