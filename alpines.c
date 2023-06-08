#include "3D_Viewer.h"

double degrees_to_radians(double angle) { return angle * M_PI / 180.0; }

void Move_X(matrix_t *A, double a) {
  for (int i = 0; i < A->rows; i++) {
    A->matrix[i][0] += a;
  }
}

void Move_Y(matrix_t *A, double b) {
  for (int i = 0; i < A->rows; i++) {
    A->matrix[i][1] += b;
  }
}

void Move_Z(matrix_t *A, double c) {
  for (int i = 0; i < A->rows; i++) {
    A->matrix[i][2] += c;
  }
}

void Rotate_By_Ox(matrix_t *A, double alpha) {
  alpha = degrees_to_radians(alpha);
  for (int i = 0; i < A->rows; i++) {
    double temp_y = A->matrix[i][1];
    double temp_z = A->matrix[i][2];
    A->matrix[i][1] = cos(alpha) * temp_y + sin(alpha) * temp_z;
    A->matrix[i][2] = -temp_y * sin(alpha) + temp_z * cos(alpha);
  }
}

void Rotate_By_Oy(matrix_t *A, double alpha) {
  alpha = degrees_to_radians(alpha);
  for (int i = 0; i < A->rows; i++) {
    double temp_x = A->matrix[i][0];
    double temp_z = A->matrix[i][2];
    A->matrix[i][0] = temp_x * cos(alpha) + temp_z * sin(alpha);
    A->matrix[i][2] = -temp_x * sin(alpha) + temp_z * cos(alpha);
  }
}

void Rotate_By_Oz(matrix_t *A, double alpha) {
  alpha = degrees_to_radians(alpha);
  for (int i = 0; i < A->rows; i++) {
    double temp_x = A->matrix[i][0];
    double temp_y = A->matrix[i][1];
    A->matrix[i][0] = temp_x * cos(alpha) - temp_y * sin(alpha);
    A->matrix[i][1] = -temp_x * sin(alpha) + temp_y * cos(alpha);
  }
}

void Scale(matrix_t *A, double coef) {
  for (int i = 0; i < A->rows; i++) {
    for (int j = 0; j < 3; j++) {
      A->matrix[i][j] *= coef;
    }
  }
}
