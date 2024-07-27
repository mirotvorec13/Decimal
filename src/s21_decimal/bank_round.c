#include "../s21_decimal.h"

int bank_round_for_long(float rem, s21_ldecimal *value) {
  if (rem == 0) return 0;

  int check = 0;
  if (rem > 0.5 || (rem == 0.5 && (value->bits[0] & 1) == 1)) {
    value_plus_one_long(value);
  }

  return check;
}

int bank_round(float rem, s21_decimal *value) {
  if (rem == 0) return 0;

  int check = 0;
  if (rem > 0.5 || (rem == 0.5 && (value->bits[0] & 1) == 1)) {
    value_plus_one(value);
  }

  return check;
}
