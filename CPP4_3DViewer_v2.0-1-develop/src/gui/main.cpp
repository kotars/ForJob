#include <QApplication>

#include "MainWindow.h"

// пофиксить цвет вершин +++
// пофиксить размер вершин +++
// пофиксить тип вершин +++
// сделать save settingов +++
// задавать базовые настройки
// если не лень то анимация
int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
  s21::MainWindow w;
  w.show();
  return a.exec();
}