#include "s21_decimal.h"

int s21_is_equal(s21_decimal value_1, s21_decimal value_2) {
  int return_value;
  if (get_scale(&value_1) != get_scale(&value_2))
    scale_equlization(&value_1, &value_2);
  s21_decimal zero = {{0, 0, 0, 0}};
  if (is_equal_without_sign(zero, value_1) == TRUE &&
      is_equal_without_sign(zero, value_2) == TRUE) {
    return_value = TRUE;
  } else if (getsign(value_1) != getsign(value_2)) {
    return_value = FALSE;
  } else if (value_1.bits[2] != value_2.bits[2]) {
    return_value = FALSE;
  } else if (value_1.bits[1] != value_2.bits[1]) {
    return_value = FALSE;
  } else if (value_1.bits[0] != value_2.bits[0]) {
    return_value = FALSE;
  } else {
    return_value = TRUE;
  }
  return return_value;
}