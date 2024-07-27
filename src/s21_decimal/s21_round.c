#include "../s21_decimal.h"

int s21_round(s21_decimal value, s21_decimal *result) {
  int res = OTHER_OK;
  if (!result) {
    res = OTHER_ERROR_CALCULATION;
  } else if (s21_is_decimal_correct(value)) {
    res = OTHER_ERROR_CALCULATION;
    *result = (s21_decimal){{0}};
  } else {
    int scale = get_scale(value);
    *result = (s21_decimal){{0}};
    int sign = check_sign(value);
    unsigned int rem = 0;
    float rem_float = 0;
    if (sign) {
      value.bits[3] |= ((unsigned)1 << 31);
    }

    for (int i = 0; i < scale; i++) {
      div_10(&value, &rem);
      rem_float /= 10;
      rem_float += (float)rem / 10;
    }
    bank_round(rem_float, &value);
    *result = value;
    // Возвращаем знак
    if (sign) {
      result->bits[3] = 0x80000000;
    }
  }

  return res;
}
