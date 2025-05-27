#ifndef MATRIX_H
#define MATRIX_H

#include <GL/gl.h>

#include <array>
#include <cmath>
#include <stdexcept>

class Matrix {
 private:
  std::array<std::array<double, 4>, 4> matrix;  // Двумерный массив 4x4

 public:
  // Конструктор: единичная матрица по умолчанию
  Matrix() { loadIdentity(); }

  // Загрузить единичную матрицу
  void loadIdentity() {
    matrix = {{{1.0, 0.0, 0.0, 0.0},
               {0.0, 1.0, 0.0, 0.0},
               {0.0, 0.0, 1.0, 0.0},
               {0.0, 0.0, 0.0, 1.0}}};
  }

  // Получить указатель на данные (для передачи в OpenGL)
  const double* getData() const {
    return &matrix[0][0];  // Указатель на первый элемент
  }

  // Применить матрицу в OpenGL
  void applyToOpenGL() const { glMultMatrixd(getData()); }

  // Трансляция
  Matrix& translate(double x, double y, double z) {
    Matrix translation;
    translation.matrix[0][3] += x;
    translation.matrix[1][3] += y;
    translation.matrix[2][3] += z;
    *this = *this * translation;
    return *this;
  }

  // Масштабирование
  Matrix& scale(double x, double y, double z) {
    Matrix scaling;
    scaling.matrix = {{{x, 0.0, 0.0, 0.0},
                       {0.0, y, 0.0, 0.0},
                       {0.0, 0.0, z, 0.0},
                       {0.0, 0.0, 0.0, 1.0}}};
    *this = *this * scaling;
    return *this;
  }

  // Вращение вокруг оси (угол в градусах)
  Matrix& rotate(double angle, double x, double y, double z) {
    double radians = angle * M_PI / 180.0;  // Переводим угол в радианы
    double c = std::cos(radians);
    double s = std::sin(radians);
    double length = std::sqrt(x * x + y * y + z * z);
    if (length == 0.0) {
      throw std::invalid_argument("Rotation axis must not be zero.");
    }
    x /= length;
    y /= length;
    z /= length;

    Matrix rotation;
    rotation.matrix = {{{c + x * x * (1 - c), x * y * (1 - c) - z * s,
                         x * z * (1 - c) + y * s, 0.0},
                        {y * x * (1 - c) + z * s, c + y * y * (1 - c),
                         y * z * (1 - c) - x * s, 0.0},
                        {z * x * (1 - c) - y * s, z * y * (1 - c) + x * s,
                         c + z * z * (1 - c), 0.0},
                        {0.0, 0.0, 0.0, 1.0}}};
    *this = *this * rotation;
    return *this;
  }

  // Умножение матрицы на другую матрицу
  Matrix operator*(const Matrix& other) const {
    Matrix result;

    for (int row = 0; row < 4; ++row) {
      for (int col = 0; col < 4; ++col) {
        result.matrix[row][col] = 0.0;
        for (int k = 0; k < 4; ++k) {
          result.matrix[row][col] += matrix[row][k] * other.matrix[k][col];
        }
      }
    }

    return result;
  }

  // Получить матрицу в виде массива
  const std::array<std::array<double, 4>, 4>& getMatrix() const {
    return matrix;
  }
  Matrix build() {
    Matrix result;
    for (int i = 0; i < 4; i++) {
      for (int j = 0; j < 4; ++j) {
        result.matrix[i][j] = matrix[j][i];  // понять для чего он нужен
      }
    }
    return result;
  }
};

#endif