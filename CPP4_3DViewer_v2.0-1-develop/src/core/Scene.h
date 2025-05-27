#ifndef SCENE_H
#define SCENE_H

#include <string>
#include <vector>

#include "Matrix.h"
#include "Object.h"

namespace s21 {
class Scene {
 private:
  Object object;
  Matrix matrix;

 public:
  Scene() {}
  ~Scene() {}

  void load_obj(const std::string& path) { object = Object::load_obj(path); }

  void render(int tv, int sv, QColor vertexColor) {
    glPushMatrix();
    glLoadIdentity();
    glTranslated(0, 0, -4);  // тут поправить надо будет передаелать на матрицу,
                             // и транспонировать
    matrix.applyToOpenGL();
    object.render(tv, sv, vertexColor);
    glPopMatrix();
  }

  void transform(Matrix& mat) { matrix = mat; }
  std::size_t countVertex() { return object.getVertexs().size() / 3; }
  std::size_t countSurface() { return object.getSurfaces().size() / 3; }
  std::size_t countEdge() { return object.getEdges().size(); }
};
}  // namespace s21

#endif