#include "3D_Viewer.h"

int SizesParser(data_t *data, char *filename) {
  int error = 0;
  FILE *f;
  char s[1024];
  data->count_of_vertex = 0;
  data->count_of_facets = 0;
  if ((f = fopen(filename, "r")) != NULL) {
    while (fgets(s, 1024, f)) {
      if (s[0] == 'v') {
        if (s[1] == ' ') {
          data->count_of_vertex++;
        }
      } else {
        if (s[0] == 'f') {
          if (s[1] == ' ') {
            data->count_of_facets++;
          }
        }
      }
      s[0] = 0;
    }
    fclose(f);
  } else {
    error = 2;
  }

  return error;
}
// В первый раз пробежал по файлу и записали количество вершин и полигонов

int AllocateMemory(data_t *data) {
  int error = 0;
  error = s21_create_matrix(data->count_of_vertex + 1, 3, &data->matrix_3d);
  if (error == 0) {
    data->array =
        (double *)calloc((data->count_of_vertex + 1) * 3, sizeof(data));
    data->array_const =
        (double *)calloc((data->count_of_vertex + 1) * 3, sizeof(data));
    data->polygons =
        (polygon_t *)calloc(data->count_of_facets + 1, sizeof(polygon_t));
    data->doubled_polygons =
        (polygon_t *)calloc((data->count_of_facets + 1), sizeof(polygon_t));
    if (data->polygons == NULL) {
      error = 5;
    }
  }
  return error;
} // Выделил  память для матрицы вершин и массива полигонов

int ReadFile(data_t *data, char *filename) {
  int error = 0;
  FILE *f;
  char str[1024];
  int indexofvertexes = 1;
  int indexoffacets = 1;
  if ((f = fopen(filename, "r")) != NULL) {
    while (fgets(str, 1024, f)) {
      if (str[0] == 'v' && str[1] == ' ') {
        int i = 2;
        data->matrix_3d.matrix[indexofvertexes][0] = atof(str + i);
        for (int j = i; strchr("0123456789.-", str[j]); j++, i++) {
          continue;
        }
        i++;
        data->matrix_3d.matrix[indexofvertexes][1] = atof(str + i);
        for (int j = i; strchr("0123456789.-", str[j]); j++, i++) {
          continue;
        }
        data->matrix_3d.matrix[indexofvertexes][2] = atof(str + i);
        indexofvertexes++;
      } else {
        int number_of_spaces = 0;
        if (str[0] == 'f' && str[1] == ' ') {
          for (int i = 1; str[i] != '\0'; i++) {
            if (str[i] == ' ') {
              number_of_spaces++;
            }
          }
          data->polygons[indexoffacets].number_of_vertexes_in_facets =
              number_of_spaces;
          data->polygons[indexoffacets].vertexes =
              (int *)calloc(number_of_spaces, sizeof(int));
          int i = 2;
          for (int j = 0; j < number_of_spaces; j++) {
            data->polygons[indexoffacets].vertexes[j] = atoi(str + i);
            for (int k = i; strchr("0123456789/", str[k]); k++, i++) {
              continue;
            }
            i++;
          }
          indexoffacets++;
        }
      }
    }
  } else {
    error = 7;
  }
  return error;
}

//__________Очистка памяти__________//
void FreeMemory(data_t *data) {
  s21_remove_matrix(&data->matrix_3d);
  if (data->polygons != NULL) {
    for (int i = 0; i < data->count_of_facets + 1; i++) {
      if (data->polygons[i].vertexes != NULL) {
        free(data->polygons[i].vertexes);
      }
    }
    free(data->polygons);
  }
  data->polygons = NULL;
  free(data->array);
  free(data->array_const);
  data->array = NULL;
  data->array_const = NULL;
  data->count_of_facets = 0;
  data->count_of_vertex = 0;
}

int array_to_massiv(matrix_t matrix, double *array, double *array2) {
  int error = 0;
  int arraysize = 0;
  if (array != NULL) {
    for (int i = 0; i < matrix.rows; i++) {
      for (int j = 0; j < matrix.columns; j++) {
        array[arraysize] = array2[arraysize] = matrix.matrix[i][j];
        arraysize++;
      }
    }
  } else {
    error = 8;
  }

  return error;
}

int DoublePolygons(data_t *data) {
  int error = 0;
  for (int i = 1; i < data->count_of_facets + 1; i++) {
    int doubled_size = data->polygons[i].number_of_vertexes_in_facets * 2;
    data->doubled_polygons[i].number_of_vertexes_in_facets = doubled_size;
    data->doubled_polygons[i].vertexes =
        (int *)calloc(doubled_size, sizeof(int));
    int k = 1;
    for (int j = 1; j < data->polygons[i].number_of_vertexes_in_facets; j++) {
      data->doubled_polygons[i].vertexes[k] = data->polygons[i].vertexes[j];
      data->doubled_polygons[i].vertexes[k + 1] = data->polygons[i].vertexes[j];
      k += 2;
    }
    data->doubled_polygons[i].vertexes[0] = data->polygons[i].vertexes[0];
    data->doubled_polygons[i].vertexes[doubled_size - 1] =
        data->polygons[i].vertexes[0];
  }
  return error;
}

void FindMax(data_t data, double *max_coord) {
  double min = 0, max = 0;
  *max_coord = 0;
  for (int i = 0; i < (data.count_of_vertex + 1) * 3; i++) {
    if (max > data.array[i]) {
      max = data.array[i];
    }
    if (min < data.array[i]) {
      min = data.array[i];
    }
  }

  if (fabs(min) > fabs(max)) {
    *max_coord = fabs(min);
  } else {
    *max_coord = fabs(max);
  }

  *max_coord *= 1.2f;
}

int Parser(data_t *data, char *filename) {
  int error = 0;
  error = SizesParser(data, filename);
  if (error == 0) {
    error = AllocateMemory(data);
    if (error == 0) {
      error = ReadFile(data, filename);
      if (error == 0) {
        error =
            array_to_massiv(data->matrix_3d, data->array, data->array_const);
        error += DoublePolygons(data);
        if (error == 0) {
          FindMax(*data, &data->max_coord);
        }
      }
    }
  }

  return error;
}