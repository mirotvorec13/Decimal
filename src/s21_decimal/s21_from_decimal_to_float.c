#include "../s21_decimal.h"

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int res = OK;
  long double res_double = 0;
  int scale = get_scale(src);
  if (!dst) {
    res = CONVERTING_ERROR;
  } else if (s21_is_decimal_correct(src)) {
    res = CONVERTING_ERROR;
    *dst = 0.0;
  } else if ((src.bits[0] == 0) && (src.bits[1] == 0) &&
             (src.bits[2] == 0)) {  // проверка на 0
    res = OK;
    *dst = 0.0;
  } else {
    *dst = 0.0;
    for (int i = 0; i <= 95; i++) {
      if (is_set_bit(src, i)) {
        res_double = res_double + pow(2, i);
      }
    }
    while (scale != 0) {
      res_double = res_double / 10;
      scale -= 1;
    }
    *dst = res_double;

    if (check_sign(src)) {
      *dst = *dst * (-1);
    }
  }

  return res;
}