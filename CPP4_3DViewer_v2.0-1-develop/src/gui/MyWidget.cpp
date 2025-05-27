#include "MyWidget.h"

// переписать полностью отрисовку OpenGL
// ахахаххахахахаха moving измени
namespace s21 {

void MyWidget::initializeGL() {
  initializeOpenGLFunctions();
  glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
  glEnable(GL_DEPTH_TEST);
}

void MyWidget::resizeGL(int w, int h) {
  glViewport(0, 0, w, h);
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  controller.projectionSetup(w, h);
  glMatrixMode(GL_MODELVIEW);
}
Setting MyWidget::getSettings() { return controller.getSettings(); }

void MyWidget::paintGL() {
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  glMatrixMode(GL_MODELVIEW);
  glLoadIdentity();
  glDisable(GL_CULL_FACE);
  glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
  controller.drawingSetting();
}
void MyWidget::timerEvent(QTimerEvent* event) { update(); }
void MyWidget::close() { controller.close(); }

int MyWidget::countVertex() { return controller.countVertex(); }

int MyWidget::countEdge() { return controller.countEdge(); }

void MyWidget::load_obj(const std::string& path) { controller.load_obj(path); }

void MyWidget::setBackgroundColor(const QColor& selectedColor) {
  controller.setBackgroundColor(selectedColor);
  update();
}
void MyWidget::setVertexColor(const QColor& color) {
  controller.setVertexColor(color);
  update();
}

void MyWidget::setEdgeColor(const QColor& color) {
  controller.setEdgeColor(color);
  update();
}

void MyWidget::setMovingX(int value) { controller.setMovingX(value); }
void MyWidget::setMovingY(int value) { controller.setMovingY(value); }
void MyWidget::setMovingZ(int value) { controller.setMovingZ(value); }

void MyWidget::setRotationX(int value) { controller.setRotationX(value); }
void MyWidget::setRotationY(int value) { controller.setRotationY(value); }
void MyWidget::setRotationZ(int value) { controller.setRotationZ(value); }

void MyWidget::setAnimationX(int value) { controller.setAnimationX(value); }
void MyWidget::setAnimationY(int value) { controller.setAnimationY(value); }
void MyWidget::setAnimationZ(int value) { controller.setAnimationZ(value); }
void MyWidget::setSizeEdge(int value) {
  controller.setSizeEdge(value);
  update();
}
void MyWidget::setSizeVertex(int value) {
  controller.setSizeVertex(value);
  update();
}
void MyWidget::setScaling(int value) {
  controller.setScaling(value);
  update();
}
void MyWidget::setTypeProjection(int index) {
  makeCurrent();
  controller.setTypeProjection(index, width(), height());
  update();
}
void MyWidget::setTypeVertex(int index) {
  controller.setTypeVertex(index);
  update();
}
void MyWidget::setTypeEdges(int index) {
  controller.setTypeEdges(index);
  update();
}
}  // namespace s21
