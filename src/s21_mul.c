#include "s21_decimal.h"

int s21_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  clearbits(result);
  int return_value = OK;
  s21_decimal zero = {{0, 0, 0, 0}};
  int sign = result_sign(value_1, value_2);
  if (is_equal_without_sign(zero, value_2) == FALSE) {
    return_value = bit_mul(value_1, value_2, result);
    if (return_value != INF) {
      setsign(result, sign);
      int scale = get_scale(&value_1) + get_scale(&value_2);
      if (scale > 28) {
        return_value = INF;
        if (sign) return_value = N_INF;
      } else {
        set_scale(result, scale);
      }
    }
  }
  if (return_value == INF && sign == 1) return_value = N_INF;
  return return_value;
}