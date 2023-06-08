#include "3D_Viewer.h"
#define EPS 1e-6

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int out = 0;
  result->matrix = NULL;
  result->rows = rows;
  result->columns = columns;
  if (rows <= 0 || columns <= 0)
    out = 1;
  if (!out) {
    result->matrix = (double **)malloc(sizeof(double *) * rows +
                                       sizeof(double) * rows * columns);
    if (result->matrix) {
      double *ptr = (double *)(result->matrix + rows);
      for (int i = 0; i < rows; i++)
        result->matrix[i] = (ptr + columns * i);

      for (int i = 0; i < rows; i++) {
        for (int j = 0; j < columns; j++)
          result->matrix[i][j] = 0;
      }
    } else {
      out = 1;
    }
  }
  return out;
}

void s21_remove_matrix(matrix_t *A) {
  if (A->matrix)
    free(A->matrix);
  A->matrix = NULL;
  A->rows = 0;
  A->columns = 0;
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int out = 1;
  if (A == NULL || B == NULL)
    out = 0;
  if (out && A->rows == B->rows && A->columns == B->columns) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns && out; j++) {
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) > EPS)
          out = 0;
        else
          continue;
      }
    }
  } else {
    out = 0;
  }
  return out;
}
