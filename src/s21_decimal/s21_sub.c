#include "../s21_decimal.h"

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int code = S21_ARITHMETIC_OK;
  s21_decimal res = {{0}};
  if (!result) {
    code = S21_ARITHMETIC_ERROR;
  } else if (s21_is_decimal_correct(value_1) ||
             s21_is_decimal_correct(value_2)) {
    code = S21_ARITHMETIC_ERROR;
  } else {
    int sign1 = check_sign(value_1);
    int sign2 = check_sign(value_2);

    if (sign1 == 0 && sign2 == 0) {
      if (s21_is_greater_or_equal(value_1, value_2)) {
        code = s21_sub_head(value_1, value_2, &res);
      } else {
        code = s21_sub_head(value_2, value_1, &res);
        s21_negate(res, &res);
      }
    } else if (sign1 == 0 && sign2 == 1) {
      code = s21_add(value_1, s21_abs(value_2), &res);
    } else if (sign1 == 1 && sign2 == 0) {
      code = s21_add(s21_abs(value_1), value_2, &res);
      if (code == 1) {
        code = S21_ARITHMETIC_SMALL;
      }
      s21_negate(res, &res);
    } else if (sign1 == 1 && sign2 == 1) {
      if (s21_is_greater_or_equal(value_1, value_2)) {
        code = s21_sub_head(s21_abs(value_2), s21_abs(value_1), &res);
      } else {
        code = s21_sub_head(s21_abs(value_1), s21_abs(value_2), &res);

        s21_negate(res, &res);
      }
    }
  }
  *result = res;
  return code;
}

int s21_sub_head(s21_decimal value_1, s21_decimal value_2,
                 s21_decimal *result) {
  int code = S21_ARITHMETIC_OK;
  if (checkZero(value_1)) {
    value_1.bits[3] = 0;
  }
  if (checkZero(value_2)) {
    value_2.bits[3] = 0;
  }

  if (s21_is_equal(value_1, value_2)) {
    *result = (s21_decimal){{0}};
  }
  s21_ldecimal result_long = {{0}};
  s21_ldecimal value_11 = from_decimal_to_ldecimal(value_1);
  s21_ldecimal value_22 = from_decimal_to_ldecimal(value_2);
  reduce_the_scale_long(&value_11, &value_22);
  int res_scale = get_scale_l(value_11);
  s21_lsub(value_11, value_22, &result_long);
  code = from_ldecimal_to_decimal(result_long, result, res_scale);
  if (checkZero(*result)) {
    result->bits[3] = 0;
  }
  return code;
}

int s21_lsub(s21_ldecimal value_1, s21_ldecimal value_2, s21_ldecimal *result) {
  int length_v1 = 0;
  length_v1 = s21_ldecimal_length(value_1);
  for (int i = 0; i < length_v1; i++) {
    if (is_set_lbit(value_2, i)) {
      int temp = 0;
      for (int j = i; j < length_v1 && temp == 0; j++) {
        if (!is_set_lbit(value_1, j)) {
          set_lbit(&value_1, j);
        } else {
          temp = 1;
          reset_lbit(&value_1, j);
        }
      }
    }
    *result = value_1;
  }
  return 0;
}

s21_ldecimal sub_two_values(s21_ldecimal value_1, s21_decimal *value_2) {
  int length_v1 = s21_ldecimal_length(value_1);
  for (int i = 0; i < length_v1; i++) {
    if (is_set_bit(*value_2, i)) {
      int temp = 0;
      for (int j = i; j < length_v1 && temp == 0; j++) {
        if (!is_set_lbit(value_1, j)) {
          set_lbit(&value_1, j);
        } else {
          temp = 1;
          reset_lbit(&value_1, j);
        }
      }
    }
  }
  return value_1;
}
