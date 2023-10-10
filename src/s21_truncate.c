#include "s21_decimal.h"

int s21_truncate(s21_decimal value, s21_decimal *result) {
  clearbits(result);
  int return_value = OK;
  int scale = get_scale(&value);
  int sign = getsign(value);
  if (result == NULL) {
    return_value = 1;
  } else {
    for (int i = scale; i > 0; i--) {
      div_ten(&value);
    }
    *result = value;
    set_scale(result, 0);
    setsign(result, sign);
  }
  return return_value;
}