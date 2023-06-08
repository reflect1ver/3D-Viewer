#include <check.h>

#include "3D_Viewer.h"

data_t data;
char str[200] = "./obj_files/pyramid.obj";

START_TEST(parser_test) {
  int res = 0;
  res = Parser(&data, str);
  ck_assert_int_eq(0, res);
  ck_assert_int_eq(data.count_of_vertex, 5);
  ck_assert_int_eq(data.count_of_facets, 6);
  FreeMemory(&data);
}
END_TEST

START_TEST(test_move_x) {
  Parser(&data, str);
  Move_X(&data.matrix_3d, 5.0);
  matrix_t expected = {0};
  s21_create_matrix(6, 3, &expected);
  expected.matrix[0][0] = 5;
  expected.matrix[0][1] = 0;
  expected.matrix[0][2] = 0;

  expected.matrix[1][0] = 5;
  expected.matrix[1][1] = 1;
  expected.matrix[1][2] = 0;

  expected.matrix[2][0] = 4;
  expected.matrix[2][1] = 0;
  expected.matrix[2][2] = -1;

  expected.matrix[3][0] = 6;
  expected.matrix[3][1] = 0;
  expected.matrix[3][2] = -1;

  expected.matrix[4][0] = 6;
  expected.matrix[4][1] = 0;
  expected.matrix[4][2] = 1;

  expected.matrix[5][0] = 4;
  expected.matrix[5][1] = 0;
  expected.matrix[5][2] = 1;

  int res = s21_eq_matrix(&data.matrix_3d, &expected);
  ck_assert_int_eq(1, res);
  s21_remove_matrix(&expected);
  FreeMemory(&data);
}
END_TEST

START_TEST(test_move_y) {
  Parser(&data, str);
  Move_Y(&data.matrix_3d, 5.0);
  matrix_t expected = {0};
  s21_create_matrix(6, 3, &expected);
  expected.matrix[0][0] = 0;
  expected.matrix[0][1] = 5;
  expected.matrix[0][2] = 0;

  expected.matrix[1][0] = 0;
  expected.matrix[1][1] = 6;
  expected.matrix[1][2] = 0;

  expected.matrix[2][0] = -1;
  expected.matrix[2][1] = 5;
  expected.matrix[2][2] = -1;

  expected.matrix[3][0] = 1;
  expected.matrix[3][1] = 5;
  expected.matrix[3][2] = -1;

  expected.matrix[4][0] = 1;
  expected.matrix[4][1] = 5;
  expected.matrix[4][2] = 1;

  expected.matrix[5][0] = -1;
  expected.matrix[5][1] = 5;
  expected.matrix[5][2] = 1;

  int res = s21_eq_matrix(&data.matrix_3d, &expected);
  ck_assert_int_eq(1, res);
  s21_remove_matrix(&expected);
  FreeMemory(&data);
}
END_TEST

START_TEST(test_move_z) {
  Parser(&data, str);
  Move_Z(&data.matrix_3d, 5.0);
  matrix_t expected = {0};
  s21_create_matrix(6, 3, &expected);
  expected.matrix[0][0] = 0;
  expected.matrix[0][1] = 0;
  expected.matrix[0][2] = 5;

  expected.matrix[1][0] = 0;
  expected.matrix[1][1] = 1;
  expected.matrix[1][2] = 5;

  expected.matrix[2][0] = -1;
  expected.matrix[2][1] = 0;
  expected.matrix[2][2] = 4;

  expected.matrix[3][0] = 1;
  expected.matrix[3][1] = 0;
  expected.matrix[3][2] = 4;

  expected.matrix[4][0] = 1;
  expected.matrix[4][1] = 0;
  expected.matrix[4][2] = 6;

  expected.matrix[5][0] = -1;
  expected.matrix[5][1] = 0;
  expected.matrix[5][2] = 6;

  int res = s21_eq_matrix(&data.matrix_3d, &expected);
  ck_assert_int_eq(1, res);
  s21_remove_matrix(&expected);
  FreeMemory(&data);
}
END_TEST

START_TEST(test_rotate_x) {
  Parser(&data, str);
  Rotate_By_Ox(&data.matrix_3d, 18.0);
  matrix_t expected = {0};
  s21_create_matrix(6, 3, &expected);
  double a = 18.0 * M_PI / 180.0;

  expected.matrix[0][0] = 0;
  expected.matrix[0][1] = cos(a) * 0.0 + sin(a) * 0.0;
  expected.matrix[0][2] = -0.0 * sin(a) + 0.0 * cos(a);

  expected.matrix[1][0] = 0;
  expected.matrix[1][1] = cos(a) * 1.0 + sin(a) * 0.0;
  expected.matrix[1][2] = -1.0 * sin(a) + 0.0 * cos(a);

  expected.matrix[2][0] = -1;
  expected.matrix[2][1] = cos(a) * 0.0 + sin(a) * (-1.0);
  expected.matrix[2][2] = -0.0 * sin(a) + (-1.0) * cos(a);

  expected.matrix[3][0] = 1;
  expected.matrix[3][1] = cos(a) * 0.0 + sin(a) * (-1.0);
  expected.matrix[3][2] = -0.0 * sin(a) + (-1.0) * cos(a);

  expected.matrix[4][0] = 1;
  expected.matrix[4][1] = cos(a) * 0.0 + sin(a) * 1.0;
  expected.matrix[4][2] = -0.0 * sin(a) + 1.0 * cos(a);

  expected.matrix[5][0] = -1;
  expected.matrix[5][1] = cos(a) * 0.0 + sin(a) * 1.0;
  expected.matrix[5][2] = -0.0 * sin(a) + 1.0 * cos(a);

  int res = s21_eq_matrix(&data.matrix_3d, &expected);
  ck_assert_int_eq(1, res);
  s21_remove_matrix(&expected);
  FreeMemory(&data);
}
END_TEST

START_TEST(test_rotate_y) {
  Parser(&data, str);
  Rotate_By_Oy(&data.matrix_3d, 18.0);
  matrix_t expected = {0};
  s21_create_matrix(6, 3, &expected);
  double a = 18.0 * M_PI / 180.0;

  expected.matrix[0][0] = cos(a) * 0.0 + sin(a) * 0.0;
  expected.matrix[0][1] = 0;
  expected.matrix[0][2] = -0.0 * sin(a) + 0.0 * cos(a);

  expected.matrix[1][0] = cos(a) * 0.0 + sin(a) * 0.0;
  expected.matrix[1][1] = 1;
  expected.matrix[1][2] = -0.0 * sin(a) + 0.0 * cos(a);

  expected.matrix[2][0] = cos(a) * (-1.0) + sin(a) * (-1.0);
  expected.matrix[2][1] = 0;
  expected.matrix[2][2] = 1.0 * sin(a) + (-1.0) * cos(a);

  expected.matrix[3][0] = cos(a) * 1.0 + sin(a) * (-1.0);
  expected.matrix[3][1] = 0;
  expected.matrix[3][2] = -1.0 * sin(a) + (-1.0) * cos(a);

  expected.matrix[4][0] = cos(a) * 1.0 + sin(a) * 1.0;
  expected.matrix[4][1] = 0;
  expected.matrix[4][2] = -1.0 * sin(a) + 1.0 * cos(a);

  expected.matrix[5][0] = cos(a) * (-1.0) + sin(a) * 1.0;
  expected.matrix[5][1] = 0;
  expected.matrix[5][2] = 1.0 * sin(a) + 1.0 * cos(a);

  int res = s21_eq_matrix(&data.matrix_3d, &expected);
  ck_assert_int_eq(1, res);
  s21_remove_matrix(&expected);
  FreeMemory(&data);
}
END_TEST

START_TEST(test_rotate_z) {
  Parser(&data, str);
  Rotate_By_Oz(&data.matrix_3d, 18.0);
  matrix_t expected = {0};
  s21_create_matrix(6, 3, &expected);
  double a = 18.0 * M_PI / 180.0;

  expected.matrix[0][0] = cos(a) * 0.0 - sin(a) * 0.0;
  expected.matrix[0][1] = -0.0 * sin(a) + 0.0 * cos(a);
  expected.matrix[0][2] = 0;

  expected.matrix[1][0] = cos(a) * 0.0 - sin(a) * 1.0;
  expected.matrix[1][1] = -0.0 * sin(a) + 1.0 * cos(a);
  expected.matrix[1][2] = 0;

  expected.matrix[2][0] = cos(a) * (-1.0) - sin(a) * (0.0);
  expected.matrix[2][1] = 1.0 * sin(a) + (0.0) * cos(a);
  expected.matrix[2][2] = -1;

  expected.matrix[3][0] = cos(a) * 1.0 - sin(a) * (0.0);
  expected.matrix[3][1] = -1.0 * sin(a) + (0.0) * cos(a);
  expected.matrix[3][2] = -1;

  expected.matrix[4][0] = cos(a) * 1.0 - sin(a) * 0.0;
  expected.matrix[4][1] = -1.0 * sin(a) + 0.0 * cos(a);
  expected.matrix[4][2] = 1;

  expected.matrix[5][0] = cos(a) * (-1.0) - sin(a) * 0.0;
  expected.matrix[5][1] = 1.0 * sin(a) + 0.0 * cos(a);
  expected.matrix[5][2] = 1;

  int res = s21_eq_matrix(&data.matrix_3d, &expected);
  ck_assert_int_eq(1, res);
  s21_remove_matrix(&expected);
  FreeMemory(&data);
}
END_TEST

START_TEST(test_scale) {
  Parser(&data, str);
  Scale(&data.matrix_3d, 10);
  matrix_t expected = {0};
  s21_create_matrix(6, 3, &expected);

  expected.matrix[0][0] = 0;
  expected.matrix[0][1] = 0;
  expected.matrix[0][2] = 0;

  expected.matrix[1][0] = 0;
  expected.matrix[1][1] = 10;
  expected.matrix[1][2] = 0;

  expected.matrix[2][0] = -10;
  expected.matrix[2][1] = 0;
  expected.matrix[2][2] = -10;

  expected.matrix[3][0] = 10;
  expected.matrix[3][1] = 0;
  expected.matrix[3][2] = -10;

  expected.matrix[4][0] = 10;
  expected.matrix[4][1] = 0;
  expected.matrix[4][2] = 10;

  expected.matrix[5][0] = -10;
  expected.matrix[5][1] = 0;
  expected.matrix[5][2] = 10;

  int res = s21_eq_matrix(&data.matrix_3d, &expected);
  ck_assert_int_eq(1, res);
  s21_remove_matrix(&expected);
  FreeMemory(&data);
}
END_TEST

int main(void) {
  Suite *s1 = suite_create("Core");
  TCase *tc1_1 = tcase_create("Core");
  SRunner *sr = srunner_create(s1);

  suite_add_tcase(s1, tc1_1);
  tcase_add_test(tc1_1, parser_test);
  tcase_add_test(tc1_1, test_move_x);
  tcase_add_test(tc1_1, test_move_y);
  tcase_add_test(tc1_1, test_move_z);
  tcase_add_test(tc1_1, test_rotate_x);
  tcase_add_test(tc1_1, test_rotate_y);
  tcase_add_test(tc1_1, test_rotate_z);
  tcase_add_test(tc1_1, test_scale);

  srunner_run_all(sr, CK_ENV);
  srunner_ntests_failed(sr);
  srunner_free(sr);

  return (0);
}