#ifndef S21_DECIMAL_H
#define S21_DECIMAL_H
#define SC 0x00ff0000
#include <limits.h>
#include <math.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define S21_ARITHMETIC_OK 0;
#define S21_ARITHMETIC_BIG 1;
#define S21_ARITHMETIC_SMALL 2;
#define S21_ARITHMETIC_ZERO_DIV 3;
#define S21_ARITHMETIC_ERROR 4;

#define CONVERTING_ERROR 1;
#define OK 0;

#define OTHER_ERROR_CALCULATION 1;
#define OTHER_OK 0;

#define MAX_FLOAT_TO_CONVERT 79228157791897854723898736640.0f
#define MIN_FLOAT_TO_CONVERT \
  0.00000000000000000000000000010000000031710768509710513471352647538147514756461109f

typedef union decimal_bit_float {
  float f;
  struct {
    uint32_t mantissa : 23;
    uint32_t exp : 8;
    uint32_t sign : 1;
  } parts;

} decimal_bit_float;

typedef union decimal_bit3 {  // разбивка 3-го инта на составляющие по заданию,
                              // чтобы легче было обращаться
  int i;
  struct {
    uint32_t empty2 : 16;
    uint32_t power : 8;
    uint32_t empty1 : 7;
    uint32_t sign : 1;
  } parts;
} decimal_bit3;

typedef struct {
  unsigned int bits[4];
} s21_decimal;

typedef struct {
  unsigned int bits[8];
} s21_ldecimal;

typedef struct bits {
  unsigned int value_x : 1;
  unsigned int value_y : 1;
} bit;

// сложение
int s21_add(s21_decimal, s21_decimal, s21_decimal *);
int s21_add_head(s21_decimal, s21_decimal, s21_decimal *);
int s21_ladd(s21_ldecimal, s21_ldecimal, s21_ldecimal *);
void value_plus_one_long(s21_ldecimal *);
void value_plus_one(s21_decimal *);

// вычитание
int s21_sub(s21_decimal, s21_decimal, s21_decimal *);
int s21_sub_head(s21_decimal, s21_decimal, s21_decimal *);
int s21_lsub(s21_ldecimal, s21_ldecimal, s21_ldecimal *);
s21_ldecimal sub_two_values(s21_ldecimal, s21_decimal *);

// умножение
int s21_mul(s21_decimal, s21_decimal, s21_decimal *);
int s21_mul_head(s21_decimal, s21_decimal, s21_decimal *);
int s21_lmul(s21_ldecimal, s21_ldecimal, s21_ldecimal *);
void mul_ten(s21_decimal *);
void mul_ten_l(s21_ldecimal *);

// деление
int s21_div(s21_decimal, s21_decimal, s21_decimal *);
int s21_div_head(s21_decimal, s21_decimal, s21_decimal *);
int div_10(s21_decimal *, unsigned int *);
int div_10_l(s21_ldecimal *, unsigned int *);
int divisible_ten(s21_decimal);
int divisible_ten_l(s21_ldecimal);

// конверты
int s21_from_int_to_decimal(int, s21_decimal *);
int s21_from_decimal_to_int(s21_decimal, int *);
int s21_from_decimal_to_float(s21_decimal, float *);
s21_ldecimal from_decimal_to_ldecimal(s21_decimal);
int from_ldecimal_to_decimal(s21_ldecimal, s21_decimal *, int);
int s21_from_float_to_decimal(float, s21_decimal *);
int CountNumberBeforePoint(float);

// округление
int s21_negate(s21_decimal, s21_decimal *);
int s21_truncate(s21_decimal, s21_decimal *);
int s21_round(s21_decimal, s21_decimal *);
int s21_floor(s21_decimal, s21_decimal *);
int bank_round_for_long(float, s21_ldecimal *);
int bank_round(float, s21_decimal *);

// сравнение
int s21_is_less(s21_decimal, s21_decimal);
int less_coparis(s21_decimal, s21_decimal);
int s21_is_less_or_equal(s21_decimal, s21_decimal);
int s21_is_greater(s21_decimal, s21_decimal);
int s21_is_greater_or_equal(s21_decimal, s21_decimal);
int is_greater_or_equal(s21_ldecimal, s21_decimal);
int s21_is_equal(s21_decimal, s21_decimal);
int s21_is_not_equal(s21_decimal, s21_decimal);

// операции с битами
int is_set_bit(s21_decimal, int);
int is_set_bit_func(unsigned int num, int);
int is_set_lbit(s21_ldecimal, int);
int shift_left(s21_decimal *, s21_decimal, int);
int shift_left_l(s21_ldecimal *, s21_ldecimal, int);
void set_bit_func(unsigned int *, int);
void set_bit(s21_decimal *, int);
void set_lbit(s21_ldecimal *, int);
void reset_bit_func(unsigned int *, int);
void reset_bit(s21_decimal *, int);
void reset_lbit(s21_ldecimal *, int);
int s21_ldecimal_length(s21_ldecimal);
int s21_decimal_length(s21_decimal);

// степень
int get_scale(s21_decimal);
int get_scale_l(s21_ldecimal);
void s21_set_scale(s21_decimal *, int);
void s21_set_scale_l(s21_ldecimal *, int);
void reduce_the_scale_long(s21_ldecimal *, s21_ldecimal *);

// sign
int check_sign(s21_decimal);
void get_sign(s21_decimal *);
int check_sign_l(s21_ldecimal);
void s21_set_sign(s21_decimal *);
void s21_set_sign_l(s21_ldecimal *);
s21_decimal s21_abs(s21_decimal);

// разные проверки
int CuntAllNum(s21_decimal);
int oneLength(s21_decimal, s21_decimal *);
int checkZero(s21_decimal);
int check_l_Zero(s21_ldecimal);
int s21_is_decimal_correct(s21_decimal);
int s21_decimal_get_empty1(s21_decimal);
int s21_decimal_get_empty2(s21_decimal);

#endif
