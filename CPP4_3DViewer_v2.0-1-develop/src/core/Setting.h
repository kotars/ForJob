#ifndef SETTING_H
#define SETTING_H

#include <QColor>
#include <QCoreApplication>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
namespace s21 {
struct Setting {
  int mx = 0, my = 0, mz = 0;  // Перемещение
  int rx = 0, ry = 0, rz = 0;  // Вращение
  int ax = 0, ay = 0, az = 0;  // Анимация
  int se = 1, sv = 1, s = 0;   // Размер
  int te = 0, tv = 0, tp = 0;  // Тип;

  QColor backgroundColor = Qt::white;
  QColor edgeColor = Qt::black;
  QColor vertexColor = Qt::red;

  static Setting load() {
    s21::Setting set;
    std::ifstream file(QCoreApplication::applicationDirPath().toStdString() +
                       "/./save.settings");
    if (!file.is_open()) {
      return set;
    }
    std::cout << QCoreApplication::applicationDirPath().toStdString() +
                     "/./save.settings"
              << '\n';
    int x, y, z;
    file >> x >> y >> z;
    set.backgroundColor.setRed(x);
    set.backgroundColor.setGreen(y);
    set.backgroundColor.setBlue(z);
    file >> x >> y >> z;
    set.edgeColor.setRed(x);
    set.edgeColor.setGreen(y);
    set.edgeColor.setBlue(z);
    std::size_t s;
    file >> s;
    set.tp = s;
    file >> s;
    set.te = s;
    file >> set.se;
    file >> x >> y >> z;
    set.vertexColor.setRed(x);
    set.vertexColor.setGreen(y);
    set.vertexColor.setBlue(z);
    file >> s;
    set.tv = s;
    file >> set.sv;
    file >> set.mx;
    file >> set.my;
    file >> set.mz;

    file >> set.rx;
    file >> set.ry;
    file >> set.rz;

    file >> set.s;
    return set;
  }

  static void save(Setting a) {
    std::ofstream file(QCoreApplication::applicationDirPath().toStdString() +
                       "/./save.settings");
    std::cout << QCoreApplication::applicationDirPath().toStdString() +
                     "/./save.settings"
              << '\n';
    file << a.backgroundColor.red() << ' ' << a.backgroundColor.green() << ' '
         << a.backgroundColor.blue() << ' ';
    file << a.edgeColor.red() << ' ' << a.edgeColor.green() << ' '
         << a.edgeColor.blue() << ' ';
    file << a.tp << ' ';

    file << a.te << ' ';
    file << a.se << ' ';
    file << a.vertexColor.red() << ' ' << a.vertexColor.green() << ' '
         << a.vertexColor.blue() << ' ';
    file << a.tv << ' ';
    file << a.sv << ' ';
    file << a.mx << ' ';
    file << a.my << ' ';
    file << a.mz << ' ';

    file << a.rx << ' ';
    file << a.ry << ' ';
    file << a.rz << ' ';

    file << a.s << ' ';
  }
};

};  // namespace s21
#endif