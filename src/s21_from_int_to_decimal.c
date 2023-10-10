#include "s21_decimal.h"

int s21_from_int_to_decimal(int src, s21_decimal *dst) {
  clearbits(dst);
  int res = OK;
  if (dst == NULL || isinf(src) || isnan(src)) {
    res = 1;
  } else {
    if (src < 0) {
      src *= -1;
      setsign(dst, 1);
    }
    dst->bits[0] = src;
  }
  return res;
}