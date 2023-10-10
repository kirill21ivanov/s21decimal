#include "s21_decimal.h"

int bit_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  clearbits(result);
  int return_value = OK;
  int tmp = 0;
  int i = 0;
  for (; i < 96; i++) {
    int cur_bit_val_1 = getbit(value_1, i);
    int cur_bit_val_2 = getbit(value_2, i);
    if (!cur_bit_val_1 && !cur_bit_val_2) {
      if (tmp == 1) {
        setbit(result, i, TRUE);
        tmp = 0;
      } else {
        setbit(result, i, FALSE);
      }
    } else if (cur_bit_val_1 != cur_bit_val_2) {
      if (tmp == 1) {
        setbit(result, i, FALSE);
        tmp = 1;
      } else {
        setbit(result, i, TRUE);
      }
    } else {
      if (tmp == 1) {
        setbit(result, i, TRUE);
        tmp = 1;
      } else {
        setbit(result, i, FALSE);
        tmp = 1;
      }
    }
    if (i == 95 && tmp == 1) return_value = INF;
  }
  if (return_value == INF) clearbits(result);
  return return_value;
}

int bit_sub(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  clearbits(result);
  int tmp = 0;
  int last_b = 1 + last_bit(value_1);
  for (int i = 0; i < last_b; i++) {
    int cur_bit_val_1 = getbit(value_1, i);
    int cur_bit_val_2 = getbit(value_2, i);
    if (!cur_bit_val_1 && !cur_bit_val_2) {
      if (tmp) {
        tmp = 1;
        setbit(result, i, 1);
      } else {
        setbit(result, i, 0);
      }
    } else if (cur_bit_val_1 && !cur_bit_val_2) {
      if (tmp) {
        tmp = 0;
        setbit(result, i, 0);
      } else {
        setbit(result, i, 1);
      }
    } else if (!cur_bit_val_1 && cur_bit_val_2) {
      if (tmp) {
        tmp = 1;
        setbit(result, i, 0);
      } else {
        tmp = 1;
        setbit(result, i, 1);
      }
    } else if (cur_bit_val_1 && cur_bit_val_2) {
      if (tmp) {
        tmp = 1;
        setbit(result, i, 1);
      } else {
        setbit(result, i, 0);
      }
    }
  }
  return 0;
}

int bit_mul(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  clearbits(result);
  int return_value = OK;
  s21_decimal tmp;
  int lastBit = last_bit(value_1);
  for (int i = 0; i <= lastBit; i++) {
    clearbits(&tmp);
    int cur_val_1 = getbit(value_1, i);
    if (cur_val_1) {
      tmp = value_2;
      return_value = offset_left(&tmp, i);
      bit_add(*result, tmp, result);
    }
  }
  return return_value;
}

void bits_copy(s21_decimal src, s21_decimal *dest) {
  dest->bits[0] = src.bits[0];
  dest->bits[1] = src.bits[1];
  dest->bits[2] = src.bits[2];
}

void bit_div(s21_decimal value_1, s21_decimal value_2, s21_decimal *result,
             s21_decimal *tmp) {
  clearbits(result);
  clearbits(tmp);
  for (int i = last_bit(value_1); i >= 0; i--) {
    if (getbit(value_1, i)) setbit(tmp, 0, 1);
    if (s21_is_greater_or_equal(*tmp, value_2) == TRUE) {
      bit_sub(*tmp, value_2, tmp);
      if (i != 0) offset_left(tmp, 1);
      offset_left(result, 1);
      setbit(result, 0, 1);
    } else {
      offset_left(result, 1);
      if (i != 0) offset_left(tmp, 1);
      if ((i - 1) >= 0 && getbit(value_1, i - 1)) setbit(tmp, 0, 1);
    }
  }
}