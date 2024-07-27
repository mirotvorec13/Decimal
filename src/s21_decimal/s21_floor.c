#include "../s21_decimal.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  int res = OTHER_OK;

  if (!result) {
    // Если указатель на decimal является NULL
    res = OTHER_ERROR_CALCULATION;
  } else if (s21_is_decimal_correct(value)) {
    // Проверяем, что value является корректными decimal
    res = OTHER_ERROR_CALCULATION;
    *result = (s21_decimal){{0}};
  } else {
    // В остальных случаях округляем
    *result = (s21_decimal){{0}};
    int sign = check_sign(value);

    s21_decimal value_unsigned = value;
    s21_decimal fractional = {{0}};  //дробная часть
    s21_decimal value_unsigned_truncated = {{0}};
    // Убираем знак
    if (sign) {
      value_unsigned.bits[3] ^= ((unsigned)1 << 31);
    }
    // Убираем дробную часть числа
    s21_truncate(value_unsigned, &value_unsigned_truncated);

    // Считаем убранную дробную часть числа
    s21_sub(value_unsigned, value_unsigned_truncated, &fractional);
    // Если дробная часть была больше нуля и число было отрицательным, то
    // прибавляем 1

    if (sign == 1 && !checkZero(fractional)) {
      value_plus_one(&value_unsigned_truncated);
    }

    *result = value_unsigned_truncated;

    // Возвращаем знак
    if (sign) {
      result->bits[3] = 0x80000000;
    }
  }

  return res;
}
