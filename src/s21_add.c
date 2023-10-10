#include "s21_decimal.h"

int s21_add(s21_decimal value_1, s21_decimal value_2, s21_decimal *result) {
  clearbits(result);
  int return_value = OK;
  int sign_1 = getsign(value_1);
  int sign_2 = getsign(value_2);
  if (get_scale(&value_1) != get_scale(&value_2)) {
    scale_equlization(&value_1, &value_2);
  }
  if (sign_1 == sign_2) {
    if (sign_1 == 0) {  //                                                a + b
      return_value = bit_add(value_1, value_2, result);
      setsign(result, 0);
    } else if (sign_1 ==
               1) {  //                                         (-a) + (-b)
      if ((return_value = bit_add(value_1, value_2, result)) == INF)
        return_value = N_INF;
      setsign(result, 1);
    }
  } else if (sign_1 <
             sign_2) {  //                                        a + (-b)
    if (less_without_mod(value_1, value_2) == TRUE) {
      return_value = bit_sub(value_2, value_1, result);
      setsign(result, 1);
    } else {
      return_value = bit_sub(value_1, value_2, result);
      setsign(result, 0);
    }
  } else {  //                                         (-a) + b
    if (less_without_mod(value_1, value_2) == TRUE) {
      return_value = bit_sub(value_2, value_1, result);
      setsign(result, 0);
    } else {
      return_value = bit_sub(value_1, value_2, result);
      setsign(result, 1);
    }
  }
  set_scale(result, get_scale(&value_1));
  return return_value;
}