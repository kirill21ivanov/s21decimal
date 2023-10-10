#include "s21_decimal.h"

#include "s21_decimal_test.h"

int run_suite(Suite *suite) {
  int failed;
  SRunner *sr = srunner_create(suite);

  srunner_set_fork_status(sr, CK_NOFORK);
  srunner_run_all(sr, CK_NORMAL);
  failed = srunner_ntests_failed(sr);

  srunner_free(sr);
  return failed;
}

int main(void) {
  Suite *suites[] = {
      s21_add_suite(),
      s21_sub_suite(),
      s21_mul_suite(),
      s21_div_suite(),
      s21_mod_suite(),

      s21_is_less_suite(),
      s21_is_less_or_equal_suite(),
      s21_is_greater_suite(),
      s21_is_greater_or_equal_suite(),
      s21_is_equal_suite(),
      s21_is_not_equal_suite(),

      s21_from_int_to_decimal_suite(),
      s21_from_float_to_decimal_suite(),
      s21_from_decimal_to_int_suite(),
      s21_from_decimal_to_float_suite(),

      s21_floor_suite(),
      s21_round_suite(),
      s21_truncate_suite(),
      s21_negate_suite(),
  };
  int failed = 0, length = sizeof(suites) / sizeof(suites[0]);

  for (int i = 0; i < length; i++) {
    fprintf(stdout, "RUN TEST: %d\n", i + 1);
    failed += run_suite(suites[i]);
  }

  return failed != 0;
}
