#include "s21_decimal_test.h"

int main() {
  int number_failed = 0;

  Suite *test[] = {suite_from_int_to_decimal(),    //++
                   suite_from_decimal_to_int(),    //++
                   suite_float_to_decimal(),       //++
                   suite_from_decimal_to_float(),  //++

                   suite_is_equal(),             //++
                   suite_is_less(),              //++
                   suite_is_not_equal(),         //++
                   suite_is_greater(),           //++
                   suite_is_less_or_equal(),     //++
                   suite_is_greater_or_equal(),  //++

                   suite_negate(),    //++m
                   suite_truncate(),  //++
                   suite_floor(),     //++
                   suite_round(),     //++

                   suite_add(),  //++
                   suite_sub(),  //++
                   suite_mul(),  //++
                   suite_div(),  //++

                   NULL};

  for (int i = 0; test[i] != NULL; i++) {
    printf("\n\n");
    SRunner *sr = srunner_create(test[i]);

    srunner_run_all(sr, CK_VERBOSE);

    number_failed += srunner_ntests_failed(sr);
    srunner_free(sr);
  }
  return (number_failed == 0) ? 0 : 1;
}
