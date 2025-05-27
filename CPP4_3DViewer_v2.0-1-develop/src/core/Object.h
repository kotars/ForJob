#ifndef OBJECT_H
#define OBJECT_H

#include <GL/glut.h>

#include <QOpenGLFunctions>
#include <QOpenGLWidget>
#include <fstream>
#include <iostream>
#include <set>
#include <sstream>
#include <stdexcept>
#include <string>
#include <vector>

#include "Setting.h"
namespace s21 {
class Object {
 private:
  std::vector<double> vertexs;
  std::vector<unsigned int> surfaces;
  std::set<std::pair<std::size_t, std::size_t>> edges;
  Setting setting;

 public:
  Object() {}
  ~Object() {}

  // переписать load_obj
  static Object load_obj(const std::string& path) {
    Object obj;  // Создаем объект для заполнения
    std::ifstream file(path);
    if (!file.is_open()) {
      throw std::runtime_error("Failed to open file: " + path);
    }
    std::string line;
    while (std::getline(file, line)) {
      std::istringstream iss(line);
      std::string type;
      iss >> type;
      if (type == "v") {
        double x, y, z;
        iss >> x >> y >> z;
        obj.vertexs.push_back(x);
        obj.vertexs.push_back(y);
        obj.vertexs.push_back(z);
      } else if (type == "f") {
        std::vector<std::size_t> faceIndices;
        std::string vertex;
        while (iss >> vertex) {
          std::istringstream vertexStream(vertex);
          std::size_t vertexIndex;
          vertexStream >> vertexIndex;
          faceIndices.push_back(vertexIndex - 1);
          obj.surfaces.push_back(vertexIndex - 1);
        }
        for (std::size_t i = 0; i < faceIndices.size(); ++i) {
          std::size_t v1 = faceIndices[i];
          std::size_t v2 = faceIndices[(i + 1) % faceIndices.size()];
          if (v1 > v2) std::swap(v1, v2);
          obj.edges.insert(std::make_pair(v1, v2));
        }
      }
    }
    file.close();
    return obj;
  }

  void render(int tv, int sv, QColor vertexColor) {
    glVertexPointer(3, GL_DOUBLE, 0, vertexs.data());
    glEnableClientState(GL_VERTEX_ARRAY);
    glDrawElements(GL_TRIANGLES, surfaces.size(), GL_UNSIGNED_INT,
                   surfaces.data());
    glDisableClientState(GL_VERTEX_ARRAY);

    if (tv == 0) return;
    glColor3f(vertexColor.redF(), vertexColor.greenF(), vertexColor.blueF());
    glPointSize(sv);
    glEnable(GL_POINT_SMOOTH);
    if (tv == 2) {
      glDisable(GL_POINT_SMOOTH);
    }
    glBegin(GL_POINTS);
    for (size_t i = 0; i < vertexs.size(); i += 3) {
      glVertex3d(vertexs[i], vertexs[i + 1], vertexs[i + 2]);
    }
    glEnd();
  }

  std::vector<double> getVertexs() { return vertexs; }
  std::vector<unsigned int> getSurfaces() { return surfaces; }
  std::set<std::pair<std::size_t, std::size_t>> getEdges() { return edges; }
};
};  // namespace s21

#endif