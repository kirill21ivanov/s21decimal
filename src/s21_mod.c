#include "s21_decimal.h"

int s21_mod(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  int return_value = OK;
  clearbits(result);
  int sign = getsign(value_1);
  int scale_1 = get_scale(&value_1);
  int scale_2 = get_scale(&value_2);
  int scale;
  if (scale_1 > scale_2) {
    scale = scale_1;
  } else {
    scale = scale_2;
  }
  s21_decimal mod = {{0, 0, 0, 0}};
  s21_decimal zero = {{0, 0, 0, 0}};
  if (s21_is_equal(zero, value_2)) {
    return_value = 3;
  } else if (scale > 28) {
    return_value = INF;
    if (sign) return_value = N_INF;
  } else {
    setsign(&value_1, 0);
    setsign(&value_2, 0);
    scale_equlization(&value_1, &value_2);
    set_scale(&value_1, 0);
    set_scale(&value_2, 0);
    bit_div(value_1, value_2, &zero, &mod);
    set_scale(&mod, scale);
    setsign(&mod, sign);
    *result = mod;
  }
  return return_value;
}