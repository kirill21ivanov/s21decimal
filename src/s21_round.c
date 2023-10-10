#include "s21_decimal.h"

int s21_round(s21_decimal value, s21_decimal *result) {
  clearbits(result);
  int res = OK;
  int sign = getsign(value);
  setsign(&value, 0);
  s21_decimal val_without_scale = {{0, 0, 0, 0}};
  s21_decimal five = {{5, 0, 0, 0}};
  set_scale(&five, 1);
  s21_decimal tmp = {{0, 0, 0, 0}};
  s21_decimal one = {{1, 0, 0, 0}};
  if (result == NULL) {
    res = 1;
  } else {
    s21_truncate(value, &val_without_scale);
    s21_sub(value, val_without_scale, &tmp);

    if (s21_is_greater_or_equal(tmp, five)) {
      s21_add(val_without_scale, one, result);
      set_scale(result, 0);
      setsign(result, sign);
    } else {
      *result = val_without_scale;
      set_scale(result, 0);
      setsign(result, sign);
    }
  }
  return res;
}