#ifndef CONTROLLER_H
#define CONTROLLER_H

#include <GL/glu.h>

#include <QOpenGLFunctions>
#include <QtOpenGLWidgets/QtOpenGLWidgets>
#include <string>

#include "../core/Setting.h"
#include "../model/Model.h"

namespace s21 {
class Controller {
 private:
  Model model;

 public:
  Controller();
  ~Controller();
  void close();
  Setting getSettings();

  void projectionSetup(int w, int h);
  void drawingSetting();

  int countVertex();
  int countEdge();

  void load_obj(const std::string& path);
  void setBackgroundColor(QColor selectedColor);
  void setVertexColor(const QColor& selectedColor);
  void setEdgeColor(const QColor& selectedColor);

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

  void setTypeProjection(int index, int w, int h);
  void setTypeEdges(int index);
  void setTypeVertex(int index);
};
};  // namespace s21

#endif