#include "../s21_decimal.h"

int shift_left(s21_decimal *value_1, s21_decimal value_2, int index) {
  bit buf = {0};
  int length = s21_decimal_length(value_2) + index;
  int res = 0;
  if (length > 96) {
    res = 1;
    memset(value_1, 0, sizeof(s21_decimal));
    *value_1 = value_2;
  } else {
    for (int i = 0; i < index; i++) {
      buf.value_x = is_set_bit(value_2, 31);
      buf.value_y = is_set_bit(value_2, 63);
      for (int j = 0; j < 3; j++) {
        value_2.bits[j] <<= 1;
      }
      if (buf.value_x) set_bit(&value_2, 32);
      if (buf.value_y) set_bit(&value_2, 64);
    }
  }
  memset(value_1, 0, sizeof(s21_decimal));
  *value_1 = value_2;
  return res;
}

int shift_left_l(s21_ldecimal *value_1, s21_ldecimal value_2, int index) {
  bit buf = {0};
  bit buf1 = {0};
  bit buf2 = {0};
  int length = s21_ldecimal_length(value_2) + index;
  int res = 0;
  if (length > 224) {
    res = 1;
    memset(value_1, 0, sizeof(s21_decimal));
    *value_1 = value_2;
  } else {
    for (int i = 0; i < index; i++) {
      buf.value_x = is_set_lbit(value_2, 31);
      buf.value_y = is_set_lbit(value_2, 63);
      buf1.value_x = is_set_lbit(value_2, 95);
      buf1.value_y = is_set_lbit(value_2, 127);
      buf2.value_x = is_set_lbit(value_2, 159);
      buf2.value_y = is_set_lbit(value_2, 191);
      for (int j = 0; j < 8; j++) {
        value_2.bits[j] <<= 1;
      }
      if (buf.value_x) set_lbit(&value_2, 32);
      if (buf.value_y) set_lbit(&value_2, 64);
      if (buf1.value_x) set_lbit(&value_2, 96);
      if (buf1.value_y) set_lbit(&value_2, 128);
      if (buf2.value_x) set_lbit(&value_2, 160);
      if (buf2.value_y) set_lbit(&value_2, 192);
    }
  }
  memset(value_1, 0, sizeof(s21_decimal));
  *value_1 = value_2;
  return res;
}
