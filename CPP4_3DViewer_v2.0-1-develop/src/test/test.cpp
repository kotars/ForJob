#include <gtest/gtest.h>

#include <QApplication>
#include <filesystem>
#include <iostream>

#include "../core/Matrix.h"
#include "../core/Object.h"
#include "../core/Setting.h"

std::string path;

TEST(core_test, load_obj) {
  std::cout << path << '\n';
  auto obj = s21::Object::load_obj(path + "../obj_files/cube.obj");
  ASSERT_EQ(obj.getVertexs().size() / 3, 8);
  ASSERT_EQ(obj.getSurfaces().size() / 3, 12);
  ASSERT_EQ(obj.getEdges().size(), 18);
}

TEST(core_test, save_settings) {
  s21::Setting t;
  t.backgroundColor = QColor(101, 102, 103);
  t.edgeColor = QColor(104, 105, 106);
  t.vertexColor = QColor(107, 108, 109);
  t.tp = 1;
  t.te = 1;
  t.se = 2;
  t.tv = 2;
  t.sv = 7;
  s21::Setting::save(t);
  auto r = s21::Setting::load();

  ASSERT_EQ(t.backgroundColor.red(), r.backgroundColor.red());
  ASSERT_EQ(t.backgroundColor.green(), r.backgroundColor.green());
  ASSERT_EQ(t.backgroundColor.blue(), r.backgroundColor.blue());

  ASSERT_EQ(t.edgeColor.red(), r.edgeColor.red());
  ASSERT_EQ(t.edgeColor.green(), r.edgeColor.green());
  ASSERT_EQ(t.edgeColor.blue(), r.edgeColor.blue());

  ASSERT_EQ(t.vertexColor.red(), r.vertexColor.red());
  ASSERT_EQ(t.vertexColor.green(), r.vertexColor.green());
  ASSERT_EQ(t.vertexColor.blue(), r.vertexColor.blue());

  ASSERT_EQ(t.tp, r.tp);
  ASSERT_EQ(t.te, r.te);
  ASSERT_EQ(t.tv, r.tv);

  ASSERT_EQ(t.se, r.se);
  ASSERT_EQ(t.sv, r.sv);
}

int main(int argc, char **argv) {
  QApplication a(argc, argv);
  path = std::filesystem::absolute(argv[0]).string();
  path = path.substr(0, path.rfind('/') + 1);
  ::testing::InitGoogleTest(&argc, argv);
  return RUN_ALL_TESTS();
}