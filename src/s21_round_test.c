#include "s21_decimal.h"
#include "s21_decimal_test.h"

START_TEST(s21_round_1) {
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  s21_from_float_to_decimal(1.7111000, &value_2);
  int return_value = s21_round(value_2, &result), result_int = 0;
  s21_from_decimal_to_int(result, &result_int);
  ck_assert_int_eq(return_value, 0);
  ck_assert_int_eq(result_int, 2);
}
END_TEST

START_TEST(s21_round_2) {
  s21_decimal value_2 = {{15, 0, 0, 0x80010000}};
  s21_decimal result = {0};
  int return_value = s21_round(value_2, &result);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_round_3) {
  s21_decimal value_2 = {{0xFFFFFFFF, 0, 0xFFFFFFFF, 0x80020000}};
  s21_decimal result = {0};
  int return_value = s21_round(value_2, &result);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

START_TEST(s21_round_4) {
  s21_decimal value_2 = {0};
  s21_decimal result = {0};
  s21_from_float_to_decimal(2.2, &value_2);
  int return_value = s21_round(value_2, &result), result_int = 0;
  s21_from_decimal_to_int(result, &result_int);
  ck_assert_int_eq(return_value, 0);
  ck_assert_int_eq(result_int, 2);
}
END_TEST

START_TEST(s21_round_5) {
  s21_decimal value_2 = {{15, 0, 0, pow(2, 16)}};
  s21_decimal result = {0};
  int return_value = s21_round(value_2, &result);
  ck_assert_int_eq(return_value, 0);
}
END_TEST

Suite *s21_round_suite(void) {
  Suite *s = suite_create("s21_round_suite");
  TCase *tc = tcase_create("s21_round_testcase");

  tcase_add_test(tc, s21_round_1);
  tcase_add_test(tc, s21_round_2);
  tcase_add_test(tc, s21_round_3);
  tcase_add_test(tc, s21_round_4);
  tcase_add_test(tc, s21_round_5);

  suite_add_tcase(s, tc);
  return s;
}