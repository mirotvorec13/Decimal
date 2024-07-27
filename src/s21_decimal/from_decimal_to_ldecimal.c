#include "../s21_decimal.h"

int from_ldecimal_to_decimal(s21_ldecimal value_1, s21_decimal *value_2,
                             int res_scale) {
  int err_code = 0;
  unsigned int rem = 0;
  float rem_float = 0;
  int check_exp = 0;
  int sign = check_sign_l(value_1);
  while ((get_scale_l(value_1) > 28 || s21_ldecimal_length(value_1) > 96 ||
          ((divisible_ten_l(value_1)) && (get_scale_l(value_1)) > res_scale)) &&
         (check_exp == 0)) {
    check_exp = div_10_l(&value_1, &rem);
    rem_float /= 10;
    rem_float += (float)rem / 10;
  }

  bank_round_for_long(rem_float, &value_1);

  if ((s21_ldecimal_length(value_1) > 96) && (sign)) {
    err_code = S21_ARITHMETIC_SMALL;
  } else if ((s21_ldecimal_length(value_1) > 96) && (!sign)) {
    err_code = S21_ARITHMETIC_BIG;
  }

  if (err_code == 0) {
    value_2->bits[3] = value_1.bits[7];
    for (int j = 0; j < 3; j++) value_2->bits[j] = value_1.bits[j];
  }
  return err_code;
}

s21_ldecimal from_decimal_to_ldecimal(s21_decimal value) {
  s21_ldecimal result = {0};
  int i = 0;
  while (i < 3) {
    result.bits[i] = value.bits[i];
    i++;
  }
  result.bits[7] = value.bits[3];
  return result;
}
