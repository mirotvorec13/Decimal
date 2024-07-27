#include "../s21_decimal.h"

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int code = S21_ARITHMETIC_OK;
  memset(result, 0, sizeof(s21_decimal));
  if (!result) {
    code = S21_ARITHMETIC_ERROR;
  } else if (s21_is_decimal_correct(value_1) ||
             s21_is_decimal_correct(value_2)) {
    code = S21_ARITHMETIC_ERROR;
    memset(result, 0, sizeof(s21_decimal));
  } else {
    int sign1 = check_sign(value_1);
    int sign2 = check_sign(value_2);
    memset(result, 0, sizeof(s21_decimal));
    code = s21_div_head(value_1, value_2, result);
    if ((sign1 == 1 && sign2 == 0) && (code == 1)) {
      code = S21_ARITHMETIC_SMALL;
    } else if ((sign1 == 0 && sign2 == 1) && (code == 1)) {
      code = S21_ARITHMETIC_SMALL;
    }
  }
  if (checkZero(*result)) {
    result->bits[3] = 0;
  }
  return code;
}

int s21_div_head(s21_decimal value_1, s21_decimal value_2,
                 s21_decimal *result) {
  int err_code = S21_ARITHMETIC_OK;
  if (checkZero(value_2)) {
    *result = (s21_decimal){0};
    err_code = S21_ARITHMETIC_ZERO_DIV;
    return err_code;
  }

  if (checkZero(value_1)) {
    *result = (s21_decimal){0};
    return 0;
  }
  s21_ldecimal temp = {0};
  int scale_v1 = get_scale(value_1);
  int scale_v2 = get_scale(value_2);
  int sign_v1 = check_sign(value_1);
  int sign_v2 = check_sign(value_2);
  int res_sign = sign_v1 ^ sign_v2;

  value_1.bits[3] = value_2.bits[3] = 0;
  s21_ldecimal dividend = from_decimal_to_ldecimal(value_1);
  while (get_scale_l(dividend) < 35) {
    mul_ten_l(&dividend);
  }
  s21_decimal divisor = value_2;
  s21_ldecimal quotient = {0};
  s21_ldecimal remainder = {0};

  for (int i = 6; i >= 0; i--) {
    for (int j = 31; j >= 0; j--) {
      shift_left_l(&temp, remainder, 1);
      remainder = temp;
      temp = (s21_ldecimal){0};
      remainder.bits[0] |= ((dividend.bits[i] >> j) & 1);
      if (is_greater_or_equal(remainder, divisor)) {
        remainder = sub_two_values(remainder, &divisor);
        quotient.bits[i] |= (1 << j);
      }
    }
  }

  int res_scale = 35 + scale_v1 - scale_v2;
  s21_set_scale_l(&quotient, res_scale);
  res_scale = 0;

  err_code = from_ldecimal_to_decimal(quotient, result, res_scale);
  if (divisible_ten(*result)) {
    unsigned int a = 0;
    div_10(result, &a);
  }
  if (!checkZero(*result)) {
    if (res_sign) {
      get_sign(result);
    }
  }
  return err_code;
}

int div_10(s21_decimal *value, unsigned int *rem) {
  int check_exp = (get_scale(*value) < 1);  // 0 == OK
  if (!check_exp) {
    int int_count = 3;  // decimal
    s21_decimal new_decimal = *value;
    s21_decimal res = {0};
    unsigned int remainder = 0;
    unsigned int ten = 10;  // делитель задаем равным 10 (в десятичном формате)
    s21_set_scale(&res, get_scale(new_decimal) - 1);
    if (check_sign(new_decimal)) get_sign(&res);

    for (int i = int_count - 1; i >= 0; i--) {
      for (int j = 31; j >= 0; j--) {
        remainder <<= 1;
        remainder |= ((new_decimal.bits[i] >> j) & 1);

        if (remainder >= ten) {
          remainder -= ten;
          res.bits[i] |= (1 << j);
        }
      }
    }
    *value = res;
    *rem = remainder;
  }
  return check_exp;
}

int div_10_l(s21_ldecimal *value, unsigned int *rem) {
  int check_exp = (get_scale_l(*value) < 1);  // 0 == OK
  if (!check_exp) {
    s21_ldecimal dividend = *value;
    s21_ldecimal res = {0};
    unsigned int remainder = 0;
    unsigned int ten =
        0b1010;  // делитель задаем равным 10 (в десятичном формате)
    s21_set_scale_l(&res, get_scale_l(dividend) - 1);
    if (check_sign_l(dividend)) s21_set_sign_l(&res);
    for (int i = 6; i >= 0; i--) {
      for (int j = 31; j >= 0; j--) {
        remainder <<= 1;
        remainder |= ((dividend.bits[i] >> j) & 1);

        if (remainder >= ten) {
          remainder -= ten;
          res.bits[i] |= (1 << j);
        }
      }
    }
    *value = res;
    *rem = remainder;
  }
  return check_exp;
}

int divisible_ten(s21_decimal value) {
  int res = 0;
  s21_decimal temp = value;
  unsigned int rem = 0;
  div_10(&temp, &rem);
  if (rem == 0 && !checkZero(temp)) {
    res = 1;
  }
  return res;
}

int divisible_ten_l(s21_ldecimal value) {
  int res = 0;
  s21_ldecimal temp = value;
  unsigned int rem = 0;
  div_10_l(&temp, &rem);
  if (rem == 0 && !check_l_Zero(temp)) {
    res = 1;
  }

  return res;
}
