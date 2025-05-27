#include "Model.h"

namespace s21 {
Model::Model() { updateTranslate(); }
Model::~Model() {}
Setting Model::getSettings() { return setting; }

void Model::projectionSetup(int w, int h) {
  if (setting.tp == 0) {
    gluPerspective(45.0f, float(w) / float(h), 0.1f, 100.0f);
  } else {
    glOrtho(-2, 2, -2, 2, 1, 100);
  }
}
void Model::drawingSetting() {
  glClearColor(setting.backgroundColor.redF(), setting.backgroundColor.greenF(),
               setting.backgroundColor.blueF(), 1);
  glColor3f(setting.edgeColor.redF(), setting.edgeColor.greenF(),
            setting.edgeColor.blueF());
  glLineWidth(setting.se);

  if (setting.te == 1) {
    glEnable(GL_LINE_STIPPLE);
    glLineStipple(1, 0x0101);
  }

  scene.render(setting.tv, setting.sv, setting.vertexColor);
  if (setting.te == 1) {
    glDisable(GL_LINE_STIPPLE);
  }
}

void Model::updateTranslate() {
  Matrix builder;
  auto t = builder
               .translate(static_cast<double>(setting.mx) / 10,
                          static_cast<double>(setting.my) / 10,
                          static_cast<double>(setting.mz) / 10)
               .scale(static_cast<double>(setting.s + 5) / 10,
                      static_cast<double>(setting.s + 5) / 10,
                      static_cast<double>(setting.s + 5) / 10)
               .rotate(setting.rx, 1, 0, 0)
               .rotate(setting.ry, 0, 1, 0)
               .rotate(setting.rz, 0, 0, 1)
               .build();
  scene.transform(t);
}
void Model::saveSettings() { Setting::save(setting); }

int Model::countVertex() { return scene.countVertex(); }
int Model::countSurface() { return scene.countSurface(); }
int Model::countEdge() { return scene.countEdge(); }
void Model::load_obj(const std::string& path) { scene.load_obj(path); }

void Model::setVertexColor(const QColor& color) { setting.vertexColor = color; }

void Model::setEdgeColor(const QColor& color) { setting.edgeColor = color; }

void Model::setBackgroundColor(QColor selectedColor) {
  setting.backgroundColor = selectedColor;
}

void Model::setMovingX(int value) {
  setting.mx = value;
  updateTranslate();
}
void Model::setMovingY(int value) {
  setting.my = value;
  updateTranslate();
}

void Model::setMovingZ(int value) {
  setting.mz = value;
  updateTranslate();
}

void Model::setRotationX(int value) {
  setting.rx = value;
  updateTranslate();
}

void Model::setRotationY(int value) {
  setting.ry = value;
  updateTranslate();
}

void Model::setRotationZ(int value) {
  setting.rz = value;
  updateTranslate();
}

void Model::setAnimationX(int value) { setting.ax = value; }

void Model::setAnimationY(int value) { setting.ay = value; }

void Model::setAnimationZ(int value) { setting.az = value; }
void Model::setSizeEdge(int value) { setting.se = value; }
void Model::setSizeVertex(int value) { setting.sv = value; }
void Model::setScaling(int value) {
  setting.s = value;
  updateTranslate();
}

void Model::setTypeEdges(int index) { setting.te = index; }
void Model::setTypeVertex(int index) { setting.tv = index; }
void Model::setTypeProjection(int index, int w, int h) {
  setting.tp = index;
  glMatrixMode(GL_PROJECTION);
  glLoadIdentity();
  if (setting.tp == 0) {
    gluPerspective(45.0f, (float)w / (float)h, 0.1f, 100.0f);
  } else if (setting.tp == 1) {
    glOrtho(-2, 2, -2, 2, 1, 100);  // параллельная проекция
  }
  glMatrixMode(GL_MODELVIEW);
}

}  // namespace s21