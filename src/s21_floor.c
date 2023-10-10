#include "s21_decimal.h"

int s21_floor(s21_decimal value, s21_decimal *result) {
  clearbits(result);
  int res = OK;
  int sign = getsign(value);
  s21_decimal tmp = {{1, 0, 0, 0}};
  int scale = get_scale(&value);
  if (result == NULL) {
    res = 1;
  } else {
    if (scale == 0) {
      *result = value;
    } else {
      s21_truncate(value, result);
      if (sign) {
        bit_add(*result, tmp, result);
        setsign(result, sign);
      }
    }
  }
  return res;
}
