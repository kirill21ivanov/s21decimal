#include "s21_decimal.h"

int s21_from_float_to_decimal(float src, s21_decimal *dst) {
  clearbits(dst);
  int result = 0;
  if (isinf(src) == 1 || isnan(src) == 1 || dst == NULL) {
    result = 1;
  } else {
    int sign = getFloatSign(src);
    int float_exp = getFloatExp(&src);
    float tmp = fabs(src);
    int powten = 0;
    while (powten < 28 && (int)tmp / (int)pow(2, 21) == 0) {
      tmp *= 10;
      powten++;
    }
    tmp = round(tmp);
    if (powten <= 28 && (float_exp > -94 && float_exp < 96)) {
      soviet mantissa;
      while (fmod(tmp, 10) == 0 && powten > 0) {
        powten--;
        tmp /= 10;
      }
      mantissa.flo = tmp;
      float_exp = getFloatExp(&mantissa.flo);
      dst->bits[float_exp / 32] |= 1 << float_exp % 32;
      for (int i = float_exp - 1, j = 22; j >= 0; i--, j--) {
        if ((mantissa.uns_int & (1 << j)) != 0) {
          dst->bits[i / 32] |= 1 << i % 32;
        }
      }
      setsign(dst, sign);
      set_scale(dst, powten);
    }
  }
  return result;
}

int s21_from_decimal_to_float(s21_decimal src, float *dst) {
  int res = 0;
  int scale = get_scale(&src);
  if (dst == NULL || scale > 28) {
    res = 1;
  } else {
    *dst = 0.0;
    double tmp = *dst;
    for (int i = 0; i < 96; i++) {
      if (getbit(src, i)) {
        tmp += pow(2, i);
      }
    }
    while (scale > 0) {
      tmp /= 10;
      scale--;
    }
    *dst = tmp;
    if (getsign(src)) {
      *dst *= -1;
    }
  }
  return res;
}