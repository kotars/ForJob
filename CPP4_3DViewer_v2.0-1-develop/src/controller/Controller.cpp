#include "Controller.h"

namespace s21 {
Controller::Controller() {}
Controller::~Controller() {}

void Controller::close() { model.saveSettings(); }
Setting Controller::getSettings() { return model.getSettings(); }

void Controller::projectionSetup(int w, int h) { model.projectionSetup(w, h); }
void Controller::drawingSetting() { model.drawingSetting(); }

int Controller::countVertex() { return model.countVertex(); }

int Controller::countEdge() { return model.countEdge(); }

void Controller::load_obj(const std::string& path) { model.load_obj(path); }

void Controller::setBackgroundColor(QColor selectedColor) {
  model.setBackgroundColor(selectedColor);
}

void Controller::setVertexColor(const QColor& color) {
  model.setVertexColor(color);
}

void Controller::setEdgeColor(const QColor& color) {
  model.setEdgeColor(color);
}

void Controller::setMovingX(int value) { model.setMovingX(value); }

void Controller::setMovingY(int value) { model.setMovingY(value); }

void Controller::setMovingZ(int value) { model.setMovingZ(value); }

void Controller::setRotationX(int value) { model.setRotationX(value); }

void Controller::setRotationY(int value) { model.setRotationY(value); }

void Controller::setRotationZ(int value) { model.setRotationZ(value); }

void Controller::setAnimationX(int value) { model.setAnimationX(value); }

void Controller::setAnimationY(int value) { model.setAnimationY(value); }

void Controller::setAnimationZ(int value) { model.setAnimationZ(value); }
void Controller::setSizeEdge(int value) { model.setSizeEdge(value); }
void Controller::setSizeVertex(int value) { model.setSizeVertex(value); }
void Controller::setScaling(int value) { model.setScaling(value); }

void Controller::setTypeProjection(int index, int w, int h) {
  model.setTypeProjection(index, w, h);
}
void Controller::setTypeVertex(int index) { model.setTypeVertex(index); }
void Controller::setTypeEdges(int index) { model.setTypeEdges(index); }
};  // namespace s21
