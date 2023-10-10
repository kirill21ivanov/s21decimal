#include "s21_decimal.h"

int getbit(s21_decimal num, int bit) {
  int res = 0;
  if ((bit / 32) < 4) {
    unsigned int mask = 1u << (bit % 32);
    res = num.bits[bit / 32] & mask;
  }
  return !!res;
}

void setbit(s21_decimal *num, int bit, int value) {
  unsigned int mask = 1u << (bit % 32);
  if ((bit / 32) < 4 && value == TRUE) {
    num->bits[bit / 32] |= mask;
  }
  if ((bit / 32) < 4 && value == FALSE) {
    num->bits[bit / 32] &= ~mask;
  }
}

int last_bit(s21_decimal number) {
  int last_bit = 95;
  for (; last_bit >= 0 && getbit(number, last_bit) == 0; last_bit--) {
  }
  return last_bit;
}

int offset_left(s21_decimal *num, int value_offset) {
  int return_value = OK;
  int lastbit = last_bit(*num);
  if (lastbit + value_offset > 95) {
    return_value = INF;
  } else {
    for (int i = 0; i < value_offset; i++) {
      int value_31bit = getbit(*num, 31);
      int value_63bit = getbit(*num, 63);
      num->bits[0] <<= 1;
      num->bits[1] <<= 1;
      num->bits[2] <<= 1;
      if (value_31bit) setbit(num, 32, 1);
      if (value_63bit) setbit(num, 64, 1);
    }
  }
  return return_value;
}

void setsign(s21_decimal *num, int sign) {
  unsigned int mask = 1u << 31;
  if (sign != 0) {
    num->bits[3] |= mask;
  } else {
    num->bits[3] &= ~mask;
  }
}

int get_scale(const s21_decimal *num) {
  char scale = num->bits[3] >> 16;
  return scale;
}

void set_scale(s21_decimal *num, int scale) {
  int clearMask = ~(0xFF << 16);
  num->bits[3] &= clearMask;
  int mask = scale << 16;
  num->bits[3] |= mask;
}

void clearbits(s21_decimal *num) {
  if (num != NULL) {
    memset(num->bits, 0, sizeof(num->bits));
  }
}

int getsign(s21_decimal num) {
  unsigned int mask = 1u << 31;
  int res = num.bits[3] & mask;
  return !!res;
}
void mul_ten(s21_decimal *num) {
  s21_decimal ten = {{10, 0, 0, 0}};
  bit_mul(*num, ten, num);
}

void div_ten(s21_decimal *num) {
  s21_decimal nothing;
  s21_decimal ten = {{10, 0, 0, 0}};
  bit_div(*num, ten, num, &nothing);
}

int getFloatSign(float src) {
  int res = 0;
  if (src < 0) {
    res = 1;
  }
  return res;
}

int getFloatExp(float *src) {
  int exp = ((*(int *)src & ~SIGN_MASK) >> 23) - 127;
  return exp;
}

int result_sign(s21_decimal value_1, s21_decimal value_2) {
  int sign_1 = getsign(value_1);
  int sign_2 = getsign(value_2);
  int sign;
  if (sign_1 == sign_2) {
    sign = 0;
  } else {
    sign = 1;
  }
  return sign;
}

int is_equal_without_sign(s21_decimal value_1, s21_decimal value_2) {
  int res;
  if (value_1.bits[2] != value_2.bits[2]) {
    res = FALSE;
  } else if (value_1.bits[1] != value_2.bits[1]) {
    res = FALSE;
  } else if (value_1.bits[0] != value_2.bits[0]) {
    res = FALSE;
  } else {
    res = TRUE;
  }
  return res;
}

int less_without_mod(s21_decimal value_1, s21_decimal value_2) {
  int return_value;
  if (value_1.bits[2] < value_2.bits[2]) {
    return_value = TRUE;
  } else if (value_1.bits[2] > value_2.bits[2]) {
    return_value = FALSE;
  } else {
    if (value_1.bits[1] < value_2.bits[1]) {
      return_value = TRUE;
    } else if (value_1.bits[1] > value_2.bits[1]) {
      return_value = FALSE;
    } else {
      if (value_1.bits[0] < value_2.bits[0]) {
        return_value = TRUE;
      } else if (value_1.bits[0] > value_2.bits[0]) {
        return_value = FALSE;
      } else {
        return_value = FALSE;
      }
    }
  }
  return return_value;
}

void scale_equlization(s21_decimal *value_1, s21_decimal *value_2) {
  if (get_scale(value_1) < get_scale(value_2)) {
    int difference = get_scale(value_2) - get_scale(value_1);
    if (getbit(*value_2, 93) == 0 && getbit(*value_2, 94) == 0 &&
        getbit(*value_2, 95) == 0) {
      for (int i = 0; i < difference; i++) {
        mul_ten(value_1);
      }
      set_scale(value_1, get_scale(value_2));
    } else {
      for (int i = 0; i < difference; i++) {
        div_ten(value_2);
      }
      set_scale(value_2, get_scale(value_1));
    }
  } else {
    int difference = get_scale(value_1) - get_scale(value_2);
    if (getbit(*value_1, 93) == 0 && getbit(*value_1, 94) == 0 &&
        getbit(*value_1, 95) == 0) {
      for (int i = 0; i < difference; i++) {
        mul_ten(value_2);
      }
      set_scale(value_2, get_scale(value_1));
    } else {
      for (int i = 0; i < difference; i++) {
        div_ten(value_1);
      }
      set_scale(value_1, get_scale(value_2));
    }
  }
}