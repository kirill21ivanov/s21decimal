#include "s21_decimal.h"
#include "s21_decimal_test.h"

START_TEST(s21_negate_1) {
  s21_decimal value_2 = {{0, 0, 1, 0x80000000}};
  s21_decimal value_1 = {{0, 0, 1, 0}};
  s21_decimal result = {0};
  int return_value = s21_negate(value_2, &result);
  ck_assert_int_eq(return_value, 0);
  ck_assert_int_eq(s21_is_equal(value_1, result), 1);
}
END_TEST

START_TEST(s21_negate_2) {
  s21_decimal value_2 = {{0, 0, 1, 0x80000000}};
  s21_decimal value_1 = {{0, 0, 1, 0}};
  s21_decimal result = {0};
  int return_value = s21_negate(value_1, &result);
  ck_assert_int_eq(return_value, 0);
  ck_assert_int_eq(s21_is_equal(result, value_2), 1);
}
END_TEST

Suite *s21_negate_suite(void) {
  Suite *s = suite_create("s21_negate_suite");
  TCase *tc = tcase_create("s21_negate_testcase");

  tcase_add_test(tc, s21_negate_1);
  tcase_add_test(tc, s21_negate_2);

  suite_add_tcase(s, tc);
  return s;
}