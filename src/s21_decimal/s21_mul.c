#include "../s21_decimal.h"

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int code = S21_ARITHMETIC_OK;
  s21_decimal res = {{0}};
  if (!result) {
    code = S21_ARITHMETIC_ERROR;
  } else if (s21_is_decimal_correct(value_1) ||
             s21_is_decimal_correct(value_2)) {
    code = S21_ARITHMETIC_ERROR;
    memset(result, 0, sizeof(s21_decimal));
  } else {
    memset(result, 0, sizeof(s21_decimal));

    int sign1 = check_sign(value_1);
    int sign2 = check_sign(value_2);

    if (sign1 == 0 && sign2 == 0) {
      code = s21_mul_head(value_1, value_2, &res);
    } else if (sign1 == 0 && sign2 == 1) {
      code = s21_mul_head(value_1, s21_abs(value_2), &res);
      if (code == 1) {
        code = S21_ARITHMETIC_SMALL;
      }
      s21_negate(res, &res);
    } else if (sign1 == 1 && sign2 == 0) {
      code = s21_mul_head(s21_abs(value_1), value_2, &res);
      if (code == 1) {
        code = S21_ARITHMETIC_SMALL;
      }
      s21_negate(res, &res);
    } else if (sign1 == 1 && sign2 == 1) {
      code = s21_mul_head(s21_abs(value_1), s21_abs(value_2), &res);
    }
  }
  *result = res;
  if (checkZero(res)) {
    result->bits[3] = 0;
  }
  return code;
}

int s21_mul_head(s21_decimal value_1, s21_decimal value_2,
                 s21_decimal *result) {
  int code = S21_ARITHMETIC_OK;
  s21_ldecimal result_long = {{0}};
  s21_ldecimal value_11 = from_decimal_to_ldecimal(value_1);
  s21_ldecimal value_22 = from_decimal_to_ldecimal(value_2);
  int res_scale = get_scale_l(value_11);
  s21_lmul(value_11, value_22, &result_long);
  code = from_ldecimal_to_decimal(result_long, result, res_scale);
  return code;
}

int s21_lmul(s21_ldecimal value_1, s21_ldecimal value_2, s21_ldecimal *result) {
  s21_ldecimal res = {0};
  int min_length = 0;
  int scale_v1 = get_scale_l(value_1);
  int scale_v2 = get_scale_l(value_2);
  int scale_v1_v2 = scale_v1 + scale_v2;
  min_length = s21_ldecimal_length(value_1);
  for (int i = 0; i < min_length; i++) {
    s21_ldecimal temp = {0};
    if (is_set_lbit(value_1, i)) {
      shift_left_l(&temp, value_2, i);
      s21_ladd(res, temp, result);
      res = *result;
    }
  }
  s21_set_scale_l(result, scale_v1_v2);
  return 0;
}

void mul_ten(s21_decimal *value) {
  s21_decimal temp = *value;
  s21_decimal summand = {0};
  s21_decimal addend = {0};
  s21_decimal mask = {0};
  int scale = get_scale(*value);
  shift_left(&summand, temp, 3);
  shift_left(&addend, temp, 1);
  int i = 0;
  while (!checkZero(addend)) {
    while (i < 3) {
      mask.bits[i] = (summand.bits[i] & addend.bits[i]);
      summand.bits[i] = (summand.bits[i] ^ addend.bits[i]);
      i++;
    }
    addend = (s21_decimal){0};
    shift_left(&addend, mask, 1);
    memset(value, 0, sizeof(s21_decimal));
    *value = summand;
    i = 0;
  }
  s21_set_scale(value, scale + 1);
}

void mul_ten_l(s21_ldecimal *value) {
  s21_ldecimal temp = *value;
  s21_ldecimal summand = {0};
  s21_ldecimal addend = {0};
  s21_ldecimal mask = {0};
  int scale = get_scale_l(*value);
  shift_left_l(&summand, temp, 3);
  shift_left_l(&addend, temp, 1);
  int i = 0;
  while (!check_l_Zero(addend)) {
    while (i < 7) {
      mask.bits[i] = (summand.bits[i] & addend.bits[i]);
      summand.bits[i] = (summand.bits[i] ^ addend.bits[i]);
      i++;
    }
    addend = (s21_ldecimal){0};

    shift_left_l(&addend, mask, 1);
    memset(value, 0, sizeof(s21_ldecimal));
    *value = summand;
    i = 0;
  }
  s21_set_scale_l(value, scale + 1);
}
