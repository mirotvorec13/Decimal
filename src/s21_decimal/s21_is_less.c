#include "../s21_decimal.h"

int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
  int code = 0;
  if ((checkZero(value_1)) && (checkZero(value_2))) {
    code = 0;
  } else if ((check_sign(value_1) == 1) && (check_sign(value_2) == 0)) {
    code = 1;
  } else if ((check_sign(value_1) == 0) && (check_sign(value_2) == 1)) {
    code = 0;
  } else if ((check_sign(value_1) == 1) && (check_sign(value_2) == 1)) {
    code = less_coparis(value_2, value_1);  // сравниваем
  } else {
    code = less_coparis(value_1, value_2);
  }

  return code;
}

int less_coparis(s21_decimal value_1, s21_decimal value_2) {
  int res = 0;
  int flag = 0;
  bit check = {0};
  s21_decimal value_11 = value_1;
  s21_decimal value_22 = value_2;
  int scale1 = get_scale(value_1);
  int scale2 = get_scale(value_2);
  if (scale1 != scale2) {
    scale1 = oneLength(value_1, &value_11);
    scale2 = oneLength(value_2, &value_22);
  }
  if ((scale1 > scale2) && ((!checkZero(value_1)) && !checkZero(value_2))) {
    res = 1;
  } else if ((scale1 < scale2) &&
             ((!checkZero(value_1)) && !checkZero(value_2))) {
    res = 0;
  } else {
    for (int i = 95; i >= 0 && flag == 0; i--) {
      check.value_x = is_set_bit(value_11, i);
      check.value_y = is_set_bit(value_22, i);
      if (check.value_x != check.value_y && check.value_x < check.value_y) {
        res = 1;
        flag = 1;
      } else if (check.value_x != check.value_y &&
                 check.value_x > check.value_y) {
        res = 0;
        flag = 1;
      }
    }
  }
  return res;
}
