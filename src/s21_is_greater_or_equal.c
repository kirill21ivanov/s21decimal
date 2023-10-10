#include "s21_decimal.h"

int s21_is_greater_or_equal(s21_decimal value_1, s21_decimal value_2) {
  int return_value = FALSE;
  if (s21_is_greater(value_1, value_2) == TRUE ||
      s21_is_equal(value_1, value_2) == TRUE)
    return_value = TRUE;
  return return_value;
}