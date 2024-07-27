#include "../s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  int res;
  if ((src <= INT_MAX) && (src >= INT_MIN)) {
    res = OK;
  } else {
    res = CONVERTING_ERROR;
  }

  if (dst) {
    memset(dst, 0, sizeof(s21_decimal));  // обнуляем все биты массива dst
    if (src < 0) {  // если число отрицательное то устанавливаем 1
      src *= -1;
      get_sign(dst);
    }
    dst->bits[0] = src;  // записываем число в структуру
  } else {
    res = CONVERTING_ERROR;
  }
  return res;
}
