#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define M_PI 3.14159265358979323846264338327950288

typedef struct Matrix { // Матрица для хранения вершин
  double **matrix; // индекс строки = индекс вершины в .obj-файле
  int rows;
  int columns;
} matrix_t;

typedef struct Facets {
  int *vertexes; // массив номеров вершин, которые соединяем
  int number_of_vertexes_in_facets; // количество вершин, которые соединяем в
                                    // данном полигоне
} polygon_t;

typedef struct Data {
  int count_of_vertex; // количество вершин
  int count_of_facets; // количество полигонов
  matrix_t matrix_3d; // матрица в которой мы храним вершины в виде x y z
  polygon_t *polygons; // массив полигонов
  polygon_t *doubled_polygons;
  double *array;
  double *array_const;
  double max_coord;
} data_t;

void s21_remove_matrix(matrix_t *A);
int s21_create_matrix(int rows, int columns, matrix_t *result);
int s21_eq_matrix(matrix_t *A, matrix_t *B);

int SizesParser(data_t *data, char *filename);
int AllocateMemory(data_t *data);
int ReadFile(data_t *data, char *filename);
int array_to_massiv(matrix_t matrix, double *array, double *array2);
void FreeMemory(data_t *data);

double degrees_to_radians(double angle);
void Move_X(matrix_t *A, double a);
void Move_Y(matrix_t *A, double b);
void Move_Z(matrix_t *A, double c);
void Rotate_By_Ox(matrix_t *A, double alpha);
void Rotate_By_Oy(matrix_t *A, double alpha);
void Rotate_By_Oz(matrix_t *A, double alpha);
void Scale(matrix_t *A, double coef);
int DoublePolygons(data_t *data);
void FindMax(data_t data, double *max_coord);
int Parser(data_t *data, char *filename);