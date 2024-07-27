#include "../s21_decimal.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
  int code = OTHER_OK;
  if (!result) {
    code = OTHER_ERROR_CALCULATION;
  } else {
    *result = value;
    if (check_sign(value)) {
      result->bits[3] ^= ((unsigned)1 << 31);
    } else {
      result->bits[3] |= ((unsigned)1 << 31);
    }
  }
  return code;
}
