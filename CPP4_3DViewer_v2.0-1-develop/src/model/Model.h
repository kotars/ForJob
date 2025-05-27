#ifndef MODEL_H
#define MODEL_H

#include <GL/glut.h>

#include <QDebug>
#include <QOpenGLFunctions>
#include <QOpenGLWidget>

#include "../core/Scene.h"
#include "../core/Setting.h"

// после изменения M, T, R сразу применять
namespace s21 {
class Model {
 private:
  Setting setting = Setting::load();
  Scene scene;

 public:
  Model();
  ~Model();
  Setting getSettings();

  void projectionSetup(int w, int h);
  void drawingSetting();
  void updateTranslate();
  void saveSettings();

  int countVertex();
  int countSurface();
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
}  // namespace s21

#endif