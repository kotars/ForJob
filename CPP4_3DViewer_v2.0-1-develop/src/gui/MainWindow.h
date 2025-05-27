#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <GL/glu.h>

#include <QColorDialog>
#include <QDebug>
#include <QFile>
#include <QFileDialog>
#include <QImage>
#include <QMessageBox>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <QPixmap>
#include <QString>
#include <QTimer>

#include "MyWidget.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE
namespace s21 {
class MainWindow : public QMainWindow {
  Q_OBJECT

 public:
  MainWindow(QWidget *parent = nullptr);
  void closeEvent(QCloseEvent *event) override;
  ~MainWindow();

 private:
  Ui::MainWindow *ui;
  MyWidget *mywidget;

 private slots:
  void on_pushButton_clicked();
  void on_pushButton_2_clicked();
  void on_pushButton_3_clicked();
  void on_pushButton_4_clicked();
  void on_pushButton_5_clicked();
  void on_pushButton_6_clicked();
  void on_pushButton_7_clicked();

  void on_spinBox_valueChanged(int value);
  void on_spinBox_2_valueChanged(int value);
  void on_spinBox_3_valueChanged(int value);
  void on_spinBox_4_valueChanged(int value);
  void on_spinBox_5_valueChanged(int value);
  void on_spinBox_6_valueChanged(int value);
  void on_spinBox_7_valueChanged(int value);
  void on_spinBox_8_valueChanged(int value);
  void on_spinBox_9_valueChanged(int value);
  void on_spinBox_10_valueChanged(int value);
  void on_spinBox_11_valueChanged(int value);
  void on_spinBox_12_valueChanged(int value);

  void on_comboBox_currentIndexChanged(int index);
  void on_comboBox_2_currentIndexChanged(int index);
  void on_comboBox_3_currentIndexChanged(int index);
};
};  // namespace s21
#endif  // MAINWINDOW_H
