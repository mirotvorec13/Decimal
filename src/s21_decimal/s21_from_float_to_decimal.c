#include "../s21_decimal.h"

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  int res = OK;
  long long int_src = 0;
  int count = 0;
  int count_num;
  long double double_src;
  double integerPart;  //десятичная часть числа
  int scale = 0;
  s21_decimal temp = {{0}};
  decimal_bit_float float_bits;
  float_bits.f = src;

  if (!dst) {
    res = CONVERTING_ERROR;
  } else if (src == 0.0) {
    res = OK;
    memset(dst, 0, sizeof(s21_decimal));
  } else if ((fabsf(src) > MAX_FLOAT_TO_CONVERT) ||
             ((fabsf(src) < MIN_FLOAT_TO_CONVERT))) {
    res = CONVERTING_ERROR;
  } else {
    int binexp = float_bits.parts.exp - 127;
    if (binexp > 95) {
      res = CONVERTING_ERROR;
    } else if (binexp <= 95) {
      double_src = fabsf(src);
      while ((int)double_src == 0) {  // если число 0.00031 то умножаем на 10 да
                                      // тех пока пока не будет 3.1
        double_src *= 10;
        scale++;
      }
      count_num = CountNumberBeforePoint(
          double_src);  // считаем количество цифр до запятой
      integerPart = modf(src, &integerPart);  // выделяет десятичную часть числа
      if (count_num >= 7) {  // если число больше 7 цифр до запятой, то
                             // уменьшаем наше число до 7 цифр
        for (int i = 0; i < (count_num - 7); i++) {
          double_src /= 10;
        }
        double_src = round(double_src);  // округляем
        int_src = (int)double_src;
      } else if ((count_num < 7) & (scale < 28)) {
        for (int i = 0; (i < (7 - count_num)) & (scale < 28);
             i++) {  // умножаем на 10 до тех пока не будет 7 значимых цифр
          scale++;
          double_src *= 10;
        }
        int_src = round(double_src);
      } else if (((count_num < 7) & (scale >= 28))) {
        int_src = round(double_src);
      }
      int binexp = float_bits.parts.exp - 127;

      if ((binexp < -94) || (scale > 28)) {
        res = CONVERTING_ERROR;
      }

      float_bits.f = src;
      while (int_src > 0)  // переводим получившийся инт в 2 число
      {
        if (int_src % 2) {
          set_bit(&temp, count);
        }
        int_src = int_src / 2;
        count++;
      }

      *dst = temp;
      if (count_num > 7) {
        for (int i = 0; i < (count_num - 7); i++) {
          mul_ten(&temp);
        }
      }
      *dst = temp;
      s21_set_scale(dst, scale);
      if (src < 0) {  // если число отрицательное то устанавливаем 1
        dst->bits[3] |= ((unsigned)1 << 31);
      }
    }
  }
  return res;
}

int CountNumberBeforePoint(float num)  // подсчет количества цифр до запятой
{
  int res = 0;
  while ((int)num != 0) {
    num /= 10;
    res++;
  }
  return res;
}
