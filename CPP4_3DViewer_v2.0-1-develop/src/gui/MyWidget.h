#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QOpenGLFunctions>
#include <QWidget>
#include <QtOpenGLWidgets/QtOpenGLWidgets>
#include <string>

#include "../controller/Controller.h"
#include "../core/Setting.h"

namespace s21 {
class MyWidget : public QOpenGLWidget, protected QOpenGLFunctions {
  Q_OBJECT
 private:
  Controller controller;

 public:
  MyWidget(QWidget* parent = nullptr) : QOpenGLWidget(parent) {
    startTimer(16);
  }
  ~MyWidget() {}
  void close();
  Setting getSettings();

  int countVertex();
  int countEdge();
  // PushButton
  void load_obj(const std::string& path);
  void setBackgroundColor(const QColor& selectedColor);
  void setVertexColor(const QColor& selectedColor);
  void setEdgeColor(const QColor& selectedColor);

  // SpinBox
  void setMovingX(int value);
  void setMovingY(int value);
  void setMovingZ(int value);

  void setRotationX(int value);
  void setRotationY(int value);
  void setRotationZ(int value);

  void setAnimationX(int value);
  void setAnimationY(int value);
  void setAnimationZ(int value);

  void setSizeEdge(int value);
  void setSizeVertex(int value);
  void setScaling(int value);

  void setTypeProjection(int index);
  void setTypeEdges(int index);
  void setTypeVertex(int index);

 protected:
  void initializeGL() override;
  void resizeGL(int w, int h) override;
  void paintGL() override;
  void timerEvent(QTimerEvent* event) override;
};
};  // namespace s21

#endif