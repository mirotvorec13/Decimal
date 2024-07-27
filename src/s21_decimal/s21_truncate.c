#include "../s21_decimal.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
  int res = OTHER_OK;
  unsigned int ex = 0;
  int sign = check_sign(value);
  if (!result) {
    res = OTHER_ERROR_CALCULATION;
  } else if (s21_is_decimal_correct(value)) {
    res = OTHER_ERROR_CALCULATION;
  } else {
    *result = value;
    int scale = get_scale(value);
    for (int i = 0; i < scale; i++) {
      div_10(result, &ex);
    }
    if (sign) {
      get_sign(result);
    }
  }
  return res;
}
