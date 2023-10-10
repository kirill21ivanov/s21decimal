#include "s21_decimal.h"

int s21_negate(s21_decimal value, s21_decimal *result) {
  clearbits(result);
  int return_value = OK;
  int sign = getsign(value);
  if (result == NULL) {
    return_value = 1;
  } else {
    if (!sign) {
      sign = 1;
    } else {
      sign = 0;
    }
    *result = value;
    setsign(result, sign);
  }
  return return_value;
}