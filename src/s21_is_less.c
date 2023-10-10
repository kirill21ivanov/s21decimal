#include "s21_decimal.h"

int s21_is_less(s21_decimal value_1, s21_decimal value_2) {
  int return_value;
  s21_decimal zero = {{0, 0, 0, 0}};
  int sign_1 = getsign(value_1);
  int sign_2 = getsign(value_2);
  if (get_scale(&value_1) != get_scale(&value_2))
    scale_equlization(&value_1, &value_2);
  if (is_equal_without_sign(value_1, zero) == TRUE &&
      is_equal_without_sign(value_2, zero) == TRUE) {
    return_value = FALSE;
  } else if (sign_1 < sign_2) {
    return_value = FALSE;
  } else if (sign_1 > sign_2) {
    return_value = TRUE;
  } else {
    return_value = less_without_mod(value_1, value_2);
    if (sign_1 && sign_2 && return_value == TRUE) {
      return_value = FALSE;
    } else if (sign_1 && sign_2 && return_value == FALSE) {
      return_value = TRUE;
    }
  }
  return return_value;
}