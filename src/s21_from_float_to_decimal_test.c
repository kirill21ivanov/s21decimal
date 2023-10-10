#include "s21_decimal.h"
#include "s21_decimal_test.h"

START_TEST(s21_from_float_to_decimal_1) {
  float src = 0.0000000;
  s21_decimal value_1 = {{0xffffff, 0xffffff, 0xffffff, 0xffffff}};
  s21_decimal value_2 = {{0, 0, 0, 0}};
  s21_from_float_to_decimal(src, &value_1);
  int return_value = s21_is_equal(value_1, value_2);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(s21_from_float_to_decimal_2) {
  float src = 1.23456789999;
  float temp = 0;
  int return_value = 0;
  s21_decimal value_1 = {0};
  s21_from_float_to_decimal(src, &value_1);
  s21_from_decimal_to_float(value_1, &temp);
  if (fabs((src - temp) / src) < pow(10, -7)) {
    return_value = 1;
  }
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(s21_from_float_to_decimal_3) {
  float src = 7.92281625143e+27;
  float temp = 0;
  int return_value = 0;
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_from_float_to_decimal(src, &value_1);
  s21_from_decimal_to_float(value_1, &temp);
  if (fabs((src - temp) / src) < pow(10, -7)) {
    return_value = 1;
  }
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(s21_from_float_to_decimal_4) {
  float src = 7.92281577919e+28;
  float temp = 0;
  int return_value = 0;
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_from_float_to_decimal(src, &value_1);
  s21_from_decimal_to_float(value_1, &temp);
  if (fabs((src - temp) / src) < pow(10, -7)) {
    return_value = 1;
  }
  ck_assert_int_eq(return_value, 1);
}
END_TEST

Suite *s21_from_float_to_decimal_suite(void) {
  Suite *s = suite_create("s21_from_float_to_decimal_suite");
  TCase *tc = tcase_create("s21_from_float_to_decimal_testcase");

  tcase_add_test(tc, s21_from_float_to_decimal_1);
  tcase_add_test(tc, s21_from_float_to_decimal_2);
  tcase_add_test(tc, s21_from_float_to_decimal_3);
  tcase_add_test(tc, s21_from_float_to_decimal_4);

  suite_add_tcase(s, tc);
  return s;
}