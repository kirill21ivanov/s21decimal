#include "s21_decimal.h"

int s21_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  clearbits(result);
  s21_decimal zero = {{0, 0, 0, 0}};
  s21_decimal tmp = {{0, 0, 0, 0}};
  s21_decimal remember = {{0, 0, 0, 0}};
  int sign = result_sign(value_1, value_2);
  int return_value = OK;
  if (s21_is_equal(value_2, zero) == FALSE) {
    int scale = get_scale(&value_1) - get_scale(&value_2);
    set_scale(&value_1, 0);
    set_scale(&value_2, 0);
    setsign(&value_1, 0);
    setsign(&value_2, 0);
    bit_div(value_1, value_2, &tmp, &remember);
    bits_copy(tmp, result);
    s21_decimal max_value = {{4294967295u, 4294967295u, 4294967295u, 0}};
    set_scale(&max_value, 1);
    int iscale = 0;
    while (iscale < 28 && s21_is_equal(remember, zero) != TRUE) {
      if (s21_is_less(*result, max_value) != TRUE) break;
      mul_ten(&remember);
      bit_div(remember, value_2, &tmp, &remember);
      mul_ten(result);
      bit_add(*result, tmp, result);
      iscale++;
    }
    int new_scale = scale + iscale;
    while (new_scale > 28) {
      div_ten(result);
      new_scale--;
    }
    while (new_scale < 0) {
      mul_ten(result);
      new_scale++;
    }
    setsign(result, sign);
    set_scale(result, new_scale);
  } else {
    return_value = N_NAN;
    clearbits(result);
  }
  return return_value;
}