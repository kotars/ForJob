#include <check.h>

#include "../s21_matrix.h"

START_TEST(eq) {
  matrix_t a;
  matrix_t b;
  s21_create_matrix(3, 3, &a);
  s21_create_matrix(3, 3, &b);
  a.matrix[0][0] = 9999.9999999699;
  a.matrix[0][1] = 5;
  a.matrix[0][2] = 7;
  a.matrix[1][0] = 6;
  a.matrix[1][1] = 3;
  a.matrix[1][2] = 4;
  a.matrix[2][0] = 5;
  a.matrix[2][1] = -2;
  a.matrix[2][2] = -3;
  b.matrix[0][0] = 9999.9999999999;
  b.matrix[0][1] = 5;
  b.matrix[0][2] = 7;
  b.matrix[1][0] = 6;
  b.matrix[1][1] = 3;
  b.matrix[1][2] = 4;
  b.matrix[2][0] = 5;
  b.matrix[2][1] = -2;
  b.matrix[2][2] = -3;
  ck_assert_int_eq(s21_eq_matrix(&a, &b), 1);
  a.matrix[0][2] = 0. / 0.;
  ck_assert_int_eq(s21_eq_matrix(&a, &b), 1);
  a.matrix[0][2] = -77;
  ck_assert_int_eq(s21_eq_matrix(&a, &b), 0);
  b.matrix[0][2] = 0. / 0.;
  ck_assert_int_eq(s21_eq_matrix(&a, &b), 1);
  s21_remove_matrix(&a);
  s21_create_matrix(3, 2, &a);
  a.matrix[0][0] = 2;
  a.matrix[0][1] = 5;
  a.matrix[1][0] = 6;
  a.matrix[1][1] = 3;
  a.matrix[2][0] = 5;
  a.matrix[2][1] = -2;
  ck_assert_int_eq(s21_eq_matrix(&a, &b), 0);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
}
END_TEST

START_TEST(sum) {
  int err;
  matrix_t a, b, res;
  s21_create_matrix(2, 2, &res);
  res.matrix[0][0] = 4;
  res.matrix[0][1] = 10;
  res.matrix[1][0] = 12;
  res.matrix[1][1] = 6;
  s21_create_matrix(2, 2, &a);
  s21_create_matrix(2, 2, &b);
  a.matrix[0][0] = 2;
  a.matrix[0][1] = 5;
  a.matrix[1][0] = 6;
  a.matrix[1][1] = 3;
  b.matrix[0][0] = 2;
  b.matrix[0][1] = 5;
  b.matrix[1][0] = 6;
  b.matrix[1][1] = 3;
  matrix_t result;
  err = s21_sum_matrix(&a, &b, &result);
  ck_assert_int_eq(err, 0);
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      ck_assert_float_eq_tol(result.matrix[i][j], res.matrix[i][j], 7);
    }
  }
  s21_remove_matrix(&a);
  s21_create_matrix(3, 2, &a);
  a.matrix[0][0] = 2;
  a.matrix[0][1] = 5;
  a.matrix[1][0] = 6;
  a.matrix[1][1] = 3;
  a.matrix[2][0] = 5;
  a.matrix[2][1] = -2;
  err = s21_sum_matrix(&a, &b, &result);
  ck_assert_int_eq(err, 2);
  s21_remove_matrix(&result);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&res);
}
END_TEST

START_TEST(sub) {
  int err;
  matrix_t a, b, res;
  s21_create_matrix(2, 2, &res);
  res.matrix[0][0] = 0;
  res.matrix[0][1] = 0;
  res.matrix[1][0] = 1;
  res.matrix[1][1] = 0;
  s21_create_matrix(2, 2, &a);
  s21_create_matrix(2, 2, &b);
  a.matrix[0][0] = 2;
  a.matrix[0][1] = 5;
  a.matrix[1][0] = 7;
  a.matrix[1][1] = 3;
  b.matrix[0][0] = 2;
  b.matrix[0][1] = 5;
  b.matrix[1][0] = 6;
  b.matrix[1][1] = 3;
  matrix_t result;
  err = s21_sub_matrix(&a, &b, &result);
  ck_assert_int_eq(err, 0);
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      ck_assert_float_eq_tol(result.matrix[i][j], res.matrix[i][j], 7);
    }
  }
  a.matrix[0][1] = 0. / 0.;
  err = s21_sub_matrix(&a, &b, &result);
  ck_assert_int_eq(err, 2);
  a.matrix[0][1] = 5;
  b.matrix[1][1] = 0. / 0.;
  err = s21_sub_matrix(&a, &b, &result);
  ck_assert_int_eq(err, 2);
  s21_remove_matrix(&a);
  s21_create_matrix(3, 2, &a);
  a.matrix[0][0] = 2;
  a.matrix[0][1] = 5;
  a.matrix[1][0] = 6;
  a.matrix[1][1] = 3;
  a.matrix[2][0] = 5;
  a.matrix[2][1] = -2;
  err = s21_sub_matrix(&a, &b, &result);
  ck_assert_int_eq(err, 2);
  s21_remove_matrix(&result);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&res);
}
END_TEST

START_TEST(mult_mat) {
  int err;
  matrix_t a, b, res;
  s21_create_matrix(2, 2, &res);
  res.matrix[0][0] = 34;
  res.matrix[0][1] = 25;
  res.matrix[1][0] = 32;
  res.matrix[1][1] = 44;
  s21_create_matrix(2, 2, &a);
  s21_create_matrix(2, 2, &b);
  a.matrix[0][0] = 2;
  a.matrix[0][1] = 5;
  a.matrix[1][0] = 7;
  a.matrix[1][1] = 3;
  b.matrix[0][0] = 2;
  b.matrix[0][1] = 5;
  b.matrix[1][0] = 6;
  b.matrix[1][1] = 3;
  matrix_t result;
  err = s21_mult_matrix(&a, &b, &result);
  ck_assert_int_eq(err, 0);
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      ck_assert_float_eq_tol(result.matrix[i][j], res.matrix[i][j], 7);
    }
  }
  s21_remove_matrix(&a);
  s21_create_matrix(1, 1, &a);
  a.matrix[0][0] = 2;
  err = s21_mult_matrix(&a, &b, &result);
  ck_assert_int_eq(err, 2);
  err = s21_mult_matrix(NULL, NULL, &result);
  ck_assert_int_eq(err, 1);
  s21_remove_matrix(&result);
  s21_remove_matrix(&a);
  s21_remove_matrix(&b);
  s21_remove_matrix(&res);
}
END_TEST
START_TEST(mult_num) {
  int err;
  matrix_t a, res;
  s21_create_matrix(2, 2, &res);
  res.matrix[0][0] = 10;
  res.matrix[0][1] = 25;
  res.matrix[1][0] = 35;
  res.matrix[1][1] = 15;
  s21_create_matrix(2, 2, &a);
  a.matrix[0][0] = 2;
  a.matrix[0][1] = 5;
  a.matrix[1][0] = 7;
  a.matrix[1][1] = 3;
  matrix_t result;
  err = s21_mult_number(&a, 5, &result);
  ck_assert_int_eq(err, 0);
  for (int i = 0; i < 2; i++) {
    for (int j = 0; j < 2; j++) {
      ck_assert_float_eq_tol(result.matrix[i][j], res.matrix[i][j], 7);
    }
  }
  a.matrix[0][1] = 0. / 0.;
  ck_assert_int_eq(s21_mult_number(&a, 5, &result), 2);
  ck_assert_int_eq(s21_mult_number(NULL, 5, &result), 1);
  s21_remove_matrix(&result);
  s21_remove_matrix(&a);
  s21_remove_matrix(&res);
}
END_TEST

START_TEST(xz) {
  matrix_t a;
  double result = 0;
  s21_create_matrix(4, 4, &a);
  a.matrix[0][0] = 3.2000000;
  a.matrix[0][1] = -7.8000000;
  a.matrix[0][2] = 3.2000000;
  a.matrix[0][3] = 3.2000000;
  a.matrix[1][0] = 7.8000000;
  a.matrix[1][1] = 4.5000000;
  a.matrix[1][2] = -9.1000000;
  a.matrix[1][3] = 3.2000000;
  a.matrix[2][0] = 27.4000000;
  a.matrix[2][1] = 4.5000000;
  a.matrix[2][2] = 9.1000000;
  a.matrix[2][3] = 3.2000000;
  a.matrix[3][0] = -35.4000000;
  a.matrix[3][1] = 4.5000000;
  a.matrix[3][2] = 9.1000000;
  a.matrix[3][3] = 3.2000000;
  int err = s21_determinant(&a, &result);
  ck_assert_int_eq(err, 0);
  ck_assert_float_eq_tol(result, 44986.9056, 7);
  a.matrix[0][2] = 0. / 0.;
  err = s21_determinant(&a, &result);
  ck_assert_int_eq(err, 2);
  s21_remove_matrix(&a);
  s21_create_matrix(2, 1, &a);
  a.matrix[0][0] = 1;
  a.matrix[1][0] = 2;
  err = s21_determinant(&a, &result);
  ck_assert_int_eq(err, 2);
  err = s21_determinant(NULL, &result);
  ck_assert_int_eq(err, 1);
  s21_remove_matrix(&a);
  s21_create_matrix(3, 3, &a);
  a.matrix[0][0] = 3.2;
  a.matrix[0][1] = 8;
  a.matrix[0][2] = 9;
  a.matrix[1][0] = 4;
  a.matrix[1][1] = 4;
  a.matrix[1][2] = 6;
  a.matrix[2][0] = -7.5;
  a.matrix[2][1] = 5.5;
  a.matrix[2][2] = 2.5;
  matrix_t res;
  s21_create_matrix(3, 3, &res);
  res.matrix[0][0] = 0.504386;
  res.matrix[0][1] = -0.646930;
  res.matrix[0][2] = -0.263158;
  res.matrix[1][0] = 1.206140;
  res.matrix[1][1] = -1.655702;
  res.matrix[1][2] = -0.368421;
  res.matrix[2][0] = -1.140351;
  res.matrix[2][1] = 1.701754;
  res.matrix[2][2] = 0.421053;
  matrix_t resul;
  s21_inverse_matrix(&a, &resul);
  for (int i = 0; i < 3; i++) {
    for (int j = 0; j < 3; j++) {
      ck_assert_float_eq_tol(resul.matrix[i][j], res.matrix[i][j], 6);
    }
  }
  a.matrix[1][2] = 0. / 0.;
  ck_assert_int_eq(s21_inverse_matrix(&a, &resul), 2);
  ck_assert_int_eq(s21_inverse_matrix(NULL, &resul), 1);
  ck_assert_int_eq(s21_calc_complements(NULL, &resul), 1);
  ck_assert_int_eq(s21_calc_complements(&a, &resul), 2);
  ck_assert_int_eq(s21_transpose(NULL, &resul), 1);
  ck_assert_int_eq(s21_transpose(&a, &resul), 2);
  s21_remove_matrix(&a);
  s21_create_matrix(2, 1, &a);
  a.matrix[0][0] = 1;
  a.matrix[1][0] = 2;
  ck_assert_int_eq(s21_calc_complements(&a, &resul), 2);
  s21_remove_matrix(&a);
  s21_remove_matrix(&resul);
  s21_remove_matrix(&res);
}
END_TEST

int main(void) {
  Suite *s = suite_create("Core");
  TCase *tc = tcase_create("Core");
  SRunner *srun = srunner_create(s);
  int sf = 0;
  suite_add_tcase(s, tc);

  tcase_add_test(tc, eq);
  tcase_add_test(tc, sum);
  tcase_add_test(tc, sub);
  tcase_add_test(tc, mult_mat);
  tcase_add_test(tc, mult_num);
  tcase_add_test(tc, xz);

  srunner_run_all(srun, CK_ENV);
  sf = srunner_ntests_failed(srun);
  srunner_free(srun);
  return sf == 0 ? 0 : 1;
}
