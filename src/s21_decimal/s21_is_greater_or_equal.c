#include "../s21_decimal.h"

// сравнение чисел меньше
int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2) {
  return s21_is_greater(value_1, value_2) || s21_is_equal(value_1, value_2);
}

int is_greater_or_equal(s21_ldecimal value_1, s21_decimal value_2) {
  s21_ldecimal long_decimal_1 = value_1;
  s21_ldecimal long_decimal_2 = {0};
  for (int i = 0; i < 3; i++) {
    long_decimal_2.bits[i] = value_2.bits[i];
  }
  int check = 1;

  for (int i = 6; i >= 0 && check; i--) {
    if (long_decimal_1.bits[i] == long_decimal_2.bits[i]) continue;
    if (long_decimal_1.bits[i] < long_decimal_2.bits[i]) {
      check = 0;
    } else
      i = 0;
  }
  return check;
}
