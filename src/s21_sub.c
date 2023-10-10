#include "s21_decimal.h"

int s21_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  clearbits(result);
  int return_value = OK;
  int sign_1 = getsign(value_1);
  int sign_2 = getsign(value_2);
  int sign;
  if (get_scale(&value_1) != get_scale(&value_2)) {
    scale_equlization(&value_1, &value_2);
  }
  if (sign_1 != sign_2) {
    sign = sign_1;
    setsign(&value_1, 0);
    setsign(&value_2, 0);
    return_value = s21_add(value_1, value_2, result);
    if (return_value == INF) {
      return_value = N_INF;
    } else {
      setsign(result, sign);
    }
  } else {
    s21_decimal *big_val, *small_val;
    setsign(&value_1, 0);
    setsign(&value_2, 0);
    if (s21_is_less(value_1, value_2)) {
      small_val = &value_1;
      big_val = &value_2;
      sign = !sign_2;
    } else {
      small_val = &value_2;
      big_val = &value_1;
      sign = sign_1;
    }
    bit_sub(*big_val, *small_val, result);
    set_scale(result, get_scale(&value_1));
    setsign(result, sign);
  }
  return return_value;
}