#include "s21_matrix.h"

int proverka(matrix_t *A, matrix_t *B) {
  int res = 0;
  if (A == NULL || B == NULL) {
    res = 1;
  } else if (A->columns <= 0 || A->rows <= 0 || B->columns <= 0 ||
             B->rows <= 0) {
    res = 1;
  } else {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        if (isnan(A->matrix[i][j]) || isinf(A->matrix[i][j])) {
          res = 2;
        }
      }
    }
    for (int i = 0; i < B->rows; i++) {
      for (int j = 0; j < B->columns; j++) {
        if (isnan(B->matrix[i][j]) || isinf(B->matrix[i][j])) {
          res = 2;
        }
      }
    }
  }
  return res;
}

int s21_create_matrix(int rows, int columns, matrix_t *result) {
  int res = 0;
  if (rows <= 0 || columns <= 0) {
    res = 1;
  } else {
    result->rows = rows;
    result->columns = columns;
    result->matrix = calloc(rows, sizeof(double *));
    for (int i = 0; i < rows; i++) {
      result->matrix[i] = calloc(columns, sizeof(double));
    }
  }
  return res;
}

void s21_remove_matrix(matrix_t *A) {
  if (A != NULL) {
    if (A->columns > 0 && A->rows > 0) {
      for (int i = 0; i < A->rows; i++) {
        if (A->matrix[i] != NULL) {
          free(A->matrix[i]);
        }
      }
      free(A->matrix);
    }
  }
  A->rows = 0;
  A->columns = 0;
  A->matrix = NULL;
}

int s21_eq_matrix(matrix_t *A, matrix_t *B) {
  int res = 1;
  if (A == NULL || B == NULL) {
    res = 0;
  } else if (A->columns != B->columns || A->rows != B->rows) {
    res = 0;
  }
  if (res == 1) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        if (fabs(A->matrix[i][j] - B->matrix[i][j]) > 1e-7) {
          res = 0;
        }
      }
    }
  }
  return res;
}

int s21_sum_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = proverka(A, B);
  if ((A->columns != B->columns || A->rows != B->rows) && res == 0) {
    res = 2;
  }
  if (res == 0) {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] + B->matrix[i][j];
      }
    }
  }
  return res;
}

int s21_sub_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = proverka(A, B);
  if ((A->columns != B->columns || A->rows != B->rows) && res == 0) {
    res = 2;
  }
  if (res == 0) {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] - B->matrix[i][j];
      }
    }
  }
  return res;
}

int s21_mult_number(matrix_t *A, double number, matrix_t *result) {
  int res = 0;
  if (A == NULL) {
    res = 1;
  } else if (A->columns <= 0 || A->rows <= 0) {
    res = 1;
  }
  if (res == 0) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        if (isnan(A->matrix[i][j]) || isinf(A->matrix[i][j])) {
          res = 2;
        }
      }
    }
  }
  if (res == 0) {
    s21_create_matrix(A->rows, A->columns, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[i][j] = A->matrix[i][j] * number;
      }
    }
  }
  return res;
}

int s21_mult_matrix(matrix_t *A, matrix_t *B, matrix_t *result) {
  int res = proverka(A, B);
  if (res == 0) {
    if (A->columns != B->rows && res == 0) {
      res = 2;
    }
  }
  if (res == 0) {
    s21_create_matrix(A->rows, B->columns, result);
    for (int i = 0; i < result->rows; i++) {
      for (int j = 0; j < result->columns; j++) {
        for (int x = 0; x < A->columns; x++) {
          result->matrix[i][j] += A->matrix[i][x] * B->matrix[x][j];
        }
      }
    }
  }
  return res;
}

int s21_transpose(matrix_t *A, matrix_t *result) {
  int res = 0;
  if (A == NULL) {
    res = 1;
  } else if (A->columns <= 0 || A->rows <= 0) {
    res = 1;
  }
  if (res == 0) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        if (isnan(A->matrix[i][j]) || isinf(A->matrix[i][j])) {
          res = 2;
        }
      }
    }
  }
  if (res == 0) {
    s21_create_matrix(A->columns, A->rows, result);
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        result->matrix[j][i] = A->matrix[i][j];
      }
    }
  }
  return res;
}

int s21_calc_complements(matrix_t *A, matrix_t *result) {
  int res = 0;
  if (A == NULL) {
    res = 1;
  } else if (A->columns <= 0 || A->rows <= 0) {
    res = 1;
  }
  if (res == 0) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        if (isnan(A->matrix[i][j]) || isinf(A->matrix[i][j])) {
          res = 2;
        }
      }
    }
    if (A->columns != A->rows) {
      res = 2;
    } else if (A->columns == 1) {
      res = 2;
    }
  }
  if (res == 0) {
    s21_create_matrix(A->rows, A->columns, result);
    for (int j = 0; j < A->rows; j++) {
      for (int i = 0; i < A->columns; i++) {
        matrix_t B;
        double res_minor = 0;
        s21_create_matrix(A->rows - 1, A->columns - 1, &B);
        int check_z = 0;
        for (int x = 0; x < A->rows; x++) {
          if (x == j) {
            check_z = 1;
          } else {
            int check = 0;
            for (int y = 0; y < A->columns; y++) {
              if (y == i) {
                check = 1;
              } else {
                B.matrix[x - check_z][y - check] = A->matrix[x][y];
              }
            }
          }
        }
        s21_determinant(&B, &res_minor);
        s21_remove_matrix(&B);
        if ((j + i) % 2 != 0) {
          result->matrix[j][i] += -1 * res_minor;
        } else {
          result->matrix[j][i] += res_minor;
        }
      }
    }
  }
  return res;
}

int s21_determinant(matrix_t *A, double *result) {
  int res = 0;
  if (A == NULL) {
    res = 1;
  } else if (A->columns <= 0 || A->rows <= 0) {
    res = 1;
  }
  if (res == 0) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        if (isnan(A->matrix[i][j]) || isinf(A->matrix[i][j])) {
          res = 2;
        }
      }
    }
    if (A->columns != A->rows) {
      res = 2;
    }
  }
  if (res == 0) {
    if (A->columns == 2) {
      *result =
          A->matrix[0][0] * A->matrix[1][1] - A->matrix[1][0] * A->matrix[0][1];
    } else if (A->columns == 1) {
      *result = A->matrix[0][0];
    } else {
      for (int i = 0; i < A->columns; i++) {
        matrix_t B;
        double res_minor = 0;
        s21_create_matrix(A->rows - 1, A->columns - 1, &B);
        for (int x = 1; x < A->rows; x++) {
          int check = 0;
          for (int y = 0; y < A->columns; y++) {
            if (y == i) {
              check = 1;
            } else {
              B.matrix[x - 1][y - check] = A->matrix[x][y];
            }
          }
        }
        s21_determinant(&B, &res_minor);
        s21_remove_matrix(&B);
        if (i % 2 != 0) {
          *result += A->matrix[0][i] * -1 * res_minor;
        } else {
          *result += A->matrix[0][i] * res_minor;
        }
      }
    }
  }
  return res;
}

int s21_inverse_matrix(matrix_t *A, matrix_t *result) {
  int res = 0;
  if (A == NULL) {
    res = 1;
  } else if (A->columns <= 0 || A->rows <= 0) {
    res = 1;
  }
  double temp = 0;
  if (res == 0) {
    for (int i = 0; i < A->rows; i++) {
      for (int j = 0; j < A->columns; j++) {
        if (isnan(A->matrix[i][j]) || isinf(A->matrix[i][j])) {
          res = 2;
        }
      }
    }
    s21_determinant(A, &temp);
    if (A->columns != A->rows || temp == 0) {
      res = 2;
    }
  }
  if (res == 0) {
    temp = 1 / temp;
    matrix_t B;
    s21_calc_complements(A, &B);
    matrix_t C;
    s21_transpose(&B, &C);
    s21_mult_number(&C, temp, result);
    s21_remove_matrix(&C);
    s21_remove_matrix(&B);
  }
  return res;
}