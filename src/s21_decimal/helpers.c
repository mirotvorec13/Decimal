#include "../s21_decimal.h"

int is_set_bit(s21_decimal number, int index) {
  int res = is_set_bit_func(number.bits[index / 32], index % 32);
  return res;
}

int is_set_bit_func(unsigned int number, int index) {
  int result = number & (1 << index);
  return result ? 1 : 0;
}

int is_set_lbit(s21_ldecimal number, int index) {
  int res = is_set_bit_func(number.bits[index / 32], index % 32);
  return res;
}

void reset_bit_func(unsigned int *number, int index) {
  *number &= (~(1 << index));
}

void reset_bit(s21_decimal *number, int index) {
  reset_bit_func(&number->bits[index / 32], index % 32);
}

void reset_lbit(s21_ldecimal *number, int index) {
  reset_bit_func(&number->bits[index / 32], index % 32);
}

void set_bit_func(unsigned int *number, int index) { *number |= (1 << index); }

void set_bit(s21_decimal *number, int index) {
  set_bit_func(&number->bits[index / 32], index % 32);
}

void set_lbit(s21_ldecimal *number, int index) {
  set_bit_func(&number->bits[index / 32], index % 32);
}

int get_scale(s21_decimal src) { return ((src.bits[3] & SC) >> 16); }

int get_scale_l(s21_ldecimal src) { return ((src.bits[7] & SC) >> 16); }

int oneLength(s21_decimal value, s21_decimal *result) {  // приводик к 1 длине
  int scale = get_scale(value);
  int NumCount = CuntAllNum(value);
  for (; NumCount < 29; NumCount++) {
    mul_ten(&value);
    scale++;
  }

  *result = value;
  return scale;
}

int CuntAllNum(s21_decimal value) {
  long double res_double = 0;
  int count = 0;
  char numberStr[50];
  for (int i = 0; i <= 95; i++) {
    if (is_set_bit(value, i)) {
      res_double = res_double + pow(2, i);
    }
  }
  sprintf(numberStr, "%.0Lf", res_double);
  int strLength = strlen(numberStr);
  for (int i = 0; i < strLength; i++) {
    if (numberStr[i] >= '0' && numberStr[i] <= '9') {
      count++;
    }
  }
  return count;
}

int checkZero(s21_decimal value) {  // проверка на 0
  int code = 0;
  s21_decimal zero = {0};
  if ((value.bits[0] == zero.bits[0]) && (value.bits[1] == zero.bits[1]) &&
      (value.bits[2] == zero.bits[2])) {
    code = 1;
  }

  return code;
}

int check_l_Zero(s21_ldecimal value) {  // проверка на 0
  int code = 0;
  if (value.bits[0] == 0 && value.bits[1] == 0 && value.bits[2] == 0 &&
      value.bits[3] == 0 && value.bits[4] == 0 && value.bits[5] == 0 &&
      value.bits[6] == 0)
    code = 1;

  return code;
}

// возвращение длины числа
int s21_decimal_length(s21_decimal value_1) {
  int x = 0;
  for (int j = 0; j <= 95; j++) {
    if (is_set_bit(value_1, j)) {
      x = j + 1;
    }
  }
  return x;
}

int s21_ldecimal_length(s21_ldecimal value_1) {
  int x = 0;
  for (int j = 0; j < 224; j++) {
    if (is_set_lbit(value_1, j)) {
      x = j + 1;
    }
  }
  return x;
}

void get_sign(s21_decimal *dst) {  // устанавливаем последний бит в позицию 1
  set_bit(dst, 127);
}

int check_sign_l(s21_ldecimal src) { return is_set_lbit(src, 255); }

int check_sign(s21_decimal src) { return is_set_bit(src, 127); }

void s21_set_scale(s21_decimal *dst, int scale) {
  dst->bits[3] = 0;
  scale <<= 16;
  dst->bits[3] = scale | dst->bits[3];
}

void s21_set_scale_l(s21_ldecimal *dst, int scale) {
  dst->bits[7] = 0;
  scale <<= 16;
  dst->bits[7] |= scale;
}

int s21_is_decimal_correct(
    s21_decimal decimal) {  //  проверка децимал на корректность
  int status = 0;
  if (s21_decimal_get_empty1(decimal) != 0 ||
      s21_decimal_get_empty2(decimal) != 0) {
    status = 1;
  } else {
    int scale = get_scale(decimal);
    if ((scale < 0) || (scale > 28)) {
      status = 1;
    }
  }
  return status;
}

int s21_decimal_get_empty1(
    s21_decimal decimal) {  // возвращает значение битов с 24 по 30 в bits[3]
  decimal_bit3 bits3;
  bits3.i = decimal.bits[3];

  return bits3.parts.empty1;
}

int s21_decimal_get_empty2(
    s21_decimal decimal) {  //возвращает значение битов с 0 до 15 в bits[3]
  decimal_bit3 bits3;
  bits3.i = decimal.bits[3];

  return bits3.parts.empty2;
}

s21_decimal s21_abs(s21_decimal value) {  // устанавливает число по модулю
  s21_decimal result = value;
  reset_bit(&result, 127);
  return result;
}

void reduce_the_scale_long(s21_ldecimal *value_1, s21_ldecimal *value_2) {
  int scale_v1 = get_scale_l(*value_1);
  int scale_v2 = get_scale_l(*value_2);
  if (scale_v1 > scale_v2) {
    for (; scale_v1 != scale_v2; scale_v2++) {
      mul_ten_l(value_2);
    }
  } else if (scale_v1 < scale_v2) {
    for (; scale_v1 != scale_v2; scale_v1++) {
      mul_ten_l(value_1);
    }
  }
}

void s21_set_sign_l(
    s21_ldecimal *dst) {  // устанавливаем последний бит в позицию 1
  set_lbit(dst, 255);
}
