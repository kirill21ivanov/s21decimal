#include "s21_decimal.h"

int s21_from_decimal_to_int(s21_decimal src, int *dst) {
  int res = OK;
  int sign = getsign(src);
  int s = getbit(src, 31);
  if (src.bits[2] != 0 || src.bits[1] != 0 || s == 1 || dst == NULL) {
    res = 1;
  } else {
    *dst = 0;
    for (int i = get_scale(&src); i > 0; i--) {
      div_ten(&src);
    }
    *dst = src.bits[0];
    if (sign == 1) {
      *dst *= -1;
    }
  }
  return res;
}