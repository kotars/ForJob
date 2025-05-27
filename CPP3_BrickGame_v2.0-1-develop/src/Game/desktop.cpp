#include <QApplication>

#include "../gui/desktop/s21_desktop.h"

int main(int argc, char *argv[]) {
  QApplication a(argc, argv);
#ifdef SNAKE
  s21::SnakeModel model;
  s21::SnakeControle controller(&model);
  s21::MainWindow<s21::SnakeControle> w(&controller);
#else
  s21::TetrisModel model;
  s21::TetrisController controller(&model);
  s21::MainWindow<s21::TetrisController> w(&controller);
#endif
  w.show();
  return a.exec();
}