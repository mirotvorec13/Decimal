#include "../s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int code = S21_ARITHMETIC_OK;
  s21_decimal res = {0};
  if (!result) {
    code = S21_ARITHMETIC_ERROR;
  } else if (s21_is_decimal_correct(value_1) ||
             s21_is_decimal_correct(value_2)) {
    code = S21_ARITHMETIC_ERROR;
  } else {
    int sign1 = check_sign(value_1);
    int sign2 = check_sign(value_2);
    if (sign1 == 0 && sign2 == 0) {  //если оба числа положительные

      code = s21_add_head(value_1, value_2, &res);
    } else if (sign1 == 0 && sign2 == 1) {
      code = s21_sub(value_1, s21_abs(value_2), &res);
      if (s21_is_less(value_1, value_2)) {
        s21_negate(res, &res);
      }
    } else if (sign1 == 1 && sign2 == 0) {
      code = s21_sub(s21_abs(value_1), value_2, &res);
      if (s21_is_less(value_1, value_2)) {
        s21_negate(res, &res);
      }
    } else if (sign1 == 1 && sign2 == 1) {  //если оба числа отрицательные
      code = s21_add_head(s21_abs(value_1), s21_abs(value_2), &res);
      if (code == 1) {
        code = S21_ARITHMETIC_SMALL;
        res = (s21_decimal){{0}};
      }
      s21_negate(res, &res);
    }
  }

  *result = res;
  return code;
}

int s21_add_head(s21_decimal value_1, s21_decimal value_2,
                 s21_decimal *result) {
  int code = S21_ARITHMETIC_OK;
  if (checkZero(value_1)) {
    value_1.bits[3] = 0;
  }
  if (checkZero(value_2)) {
    value_2.bits[3] = 0;
  }
  s21_ldecimal result_long = {{0}};
  s21_ldecimal value_11 = from_decimal_to_ldecimal(value_1);
  s21_ldecimal value_22 = from_decimal_to_ldecimal(value_2);
  reduce_the_scale_long(&value_11, &value_22);
  int res_scale = get_scale_l(value_11);
  s21_ladd(value_11, value_22, &result_long);
  code = from_ldecimal_to_decimal(result_long, result, res_scale);
  return code;
}

int s21_ladd(s21_ldecimal value_1, s21_ldecimal value_2, s21_ldecimal *result) {
  s21_ldecimal mask = {0};
  int temp = 0;
  int i = 0;
  if (check_l_Zero(value_1)) {
    *result = value_2;
  } else if (check_l_Zero(value_2)) {
    *result = value_1;
  } else {
    while (!check_l_Zero(value_2)) {
      while (i < 7) {
        mask.bits[i] = (value_1.bits[i] & value_2.bits[i]);
        value_1.bits[i] = (value_1.bits[i] ^ value_2.bits[i]);
        i++;
      }
      value_2 = (s21_ldecimal){0};
      shift_left_l(&value_2, mask, 1);
      memset(result, 0, sizeof(s21_decimal));
      *result = value_1;
      i = 0;
    }
  }
  return temp;
}

void value_plus_one_long(s21_ldecimal *value) {
  int i = 0;
  s21_ldecimal mask = {0};
  s21_ldecimal value_1 = *value;
  s21_ldecimal value_2 = {{1, 0, 0, 0}};
  while (!check_l_Zero(value_2)) {
    while (i < 7) {
      mask.bits[i] = (value_1.bits[i] & value_2.bits[i]);
      value_1.bits[i] = (value_1.bits[i] ^ value_2.bits[i]);
      i++;
    }
    value_2 = (s21_ldecimal){0};
    shift_left_l(&value_2, mask, 1);
    *value = value_1;
    i = 0;
  }
}

void value_plus_one(s21_decimal *value) {
  int i = 0;
  s21_decimal mask = {0};
  s21_decimal value_1 = *value;
  s21_decimal value_2 = {{1, 0, 0, 0}};
  while (!checkZero(value_2)) {
    while (i < 3) {
      mask.bits[i] = (value_1.bits[i] & value_2.bits[i]);
      value_1.bits[i] = (value_1.bits[i] ^ value_2.bits[i]);
      i++;
    }
    value_2 = (s21_decimal){0};
    shift_left(&value_2, mask, 1);
    *value = value_1;
    i = 0;
  }
}
