#include "../s21_decimal.h"

// сравнение чисел больше
int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  int res = 1;
  bit check = {0};
  s21_decimal value_11 = value_1;
  s21_decimal value_22 = value_2;
  int scale1 = get_scale(value_1);
  int scale2 = get_scale(value_2);
  if (scale1 != scale2) {
    scale1 = oneLength(value_1, &value_11);
    scale2 = oneLength(value_2, &value_22);
  }
  if (((scale1 != scale2) || (check_sign(value_1) != check_sign(value_2))) &&
      ((!checkZero(value_1)) && (!checkZero(value_2)))) {
    res = 0;
  } else {
    int flag = 0;
    for (int i = 95; i >= 0 && flag == 0; i--) {
      check.value_x = is_set_bit(value_11, i);
      check.value_y = is_set_bit(value_22, i);
      if (check.value_x != check.value_y) {
        res = 0;
        flag = 1;
      }
    }
  }

  return res;
}
