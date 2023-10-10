#include "s21_decimal.h"
#include "s21_decimal_test.h"

START_TEST(s21_from_int_to_decimal_1) {
  int src = -31325;
  int temp = 0;
  int return_value = 0;
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_from_int_to_decimal(src, &value_1);
  s21_from_decimal_to_int(value_1, &temp);
  return_value = (src == temp);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(s21_from_int_to_decimal_2) {
  int src = -0;
  int temp = 0;
  int return_value = 0;
  s21_decimal value_1 = {{1, 0, 0, 0}};
  s21_from_int_to_decimal(src, &value_1);
  s21_from_decimal_to_int(value_1, &temp);
  return_value = (src == temp);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

START_TEST(s21_from_int_to_decimal_3) {
  int src = 101;
  int temp = 0;
  int return_value = 0;
  s21_decimal value_1 = {{0, 0, 0, 0}};
  s21_from_int_to_decimal(src, &value_1);
  s21_from_decimal_to_int(value_1, &temp);
  return_value = (src == temp);
  ck_assert_int_eq(return_value, 1);
}
END_TEST

Suite *s21_from_int_to_decimal_suite(void) {
  Suite *s = suite_create("s21_from_int_to_decimal_suite");
  TCase *tc = tcase_create("s21_from_int_to_decimal_testcase");

  tcase_add_test(tc, s21_from_int_to_decimal_1);
  tcase_add_test(tc, s21_from_int_to_decimal_2);
  tcase_add_test(tc, s21_from_int_to_decimal_3);

  suite_add_tcase(s, tc);
  return s;
}