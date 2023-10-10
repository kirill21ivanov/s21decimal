#include "s21_decimal.h"
#include "s21_decimal_test.h"

START_TEST(s21_mod_1) {
  s21_decimal value_2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal value_1 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal result = {0};
  int return_value = s21_mod(value_2, value_1, &result), result_int = 0;
  s21_from_decimal_to_int(result, &result_int);
  ck_assert_int_eq(result_int, 0);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_mod_2) {
  s21_decimal value_2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal value_1 = {0};
  s21_decimal result = {0};
  int return_value = s21_mod(value_2, value_1, &result);
  ck_assert_int_eq(return_value, 3);
}
END_TEST

START_TEST(s21_mod_3) {
  s21_decimal value_2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal value_1 = {0};
  s21_decimal result = {0};
  s21_from_float_to_decimal(0.1, &value_1);
  int return_value = s21_mod(value_2, value_1, &result), result_int = 0;
  s21_from_decimal_to_int(result, &result_int);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_mod_4) {
  s21_decimal value_2 = {{0xFFFFFFFF, 0xFFFFFFFF, 0xFFFFFFFF, 0}};
  s21_decimal value_1 = {0};
  s21_decimal result = {0};
  s21_from_float_to_decimal(-0.1, &value_1);
  int return_value = s21_mod(value_1, value_2, &result), result_int = 0;
  s21_from_decimal_to_int(result, &result_int);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

Suite *s21_mod_suite(void) {
  Suite *s = suite_create("s21_mod_suite");
  TCase *tc = tcase_create("s21_mod_testcase");

  tcase_add_test(tc, s21_mod_1);
  tcase_add_test(tc, s21_mod_2);
  tcase_add_test(tc, s21_mod_3);
  tcase_add_test(tc, s21_mod_4);

  suite_add_tcase(s, tc);
  return s;
}