#include "s21_decimal.h"

int s21_is_not_equal(s21_decimal value_1, s21_decimal value_2) {
  int return_value = FALSE;
  if (s21_is_equal(value_1, value_2) == 0) {
    return_value = TRUE;
  }
  return return_value;
}