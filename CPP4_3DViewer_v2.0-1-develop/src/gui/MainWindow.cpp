#include "MainWindow.h"

#include "./ui_MainWindow.h"

namespace s21 {
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  mywidget = new MyWidget(ui->widget);
  ui->widget->setLayout(new QVBoxLayout());
  ui->widget->layout()->addWidget(mywidget);

  Setting set = mywidget->getSettings();
  ui->spinBox->setValue(set.mx);
  ui->spinBox_2->setValue(set.my);
  ui->spinBox_3->setValue(set.mz);

  ui->spinBox_4->setValue(set.rx);
  ui->spinBox_5->setValue(set.ry);
  ui->spinBox_6->setValue(set.rz);
  ui->spinBox_7->setValue(set.s);

  ui->comboBox->setCurrentIndex(static_cast<int>(set.tp));
  ui->comboBox_2->setCurrentIndex(static_cast<int>(set.te));
  ui->spinBox_10->setValue(set.se);
  ui->comboBox_3->setCurrentIndex(static_cast<int>(set.tv));
  ui->spinBox_11->setValue(set.sv);
}

MainWindow::~MainWindow() {
  delete ui;
  delete mywidget;
}

void MainWindow::closeEvent(QCloseEvent *event) { mywidget->close(); }

// loadobj надо исправить
void MainWindow::on_pushButton_clicked() {
  QString filePath =
      QFileDialog::getOpenFileName(this, tr("Выбрать файл"), QString(),
                                   tr("Object file(*.obj);;Все файлы (*.*)"));

  if (filePath.isEmpty()) {
    qDebug() << "Пользователь отменил выбор файла.";
    return;
  }
  mywidget->load_obj(filePath.toStdString());
  statusBar()->showMessage(
      QString("FileName: %1, Количество вершин: %2, Количество ребер: %3")
          .arg(filePath)
          .arg(mywidget->countVertex())
          .arg(mywidget->countEdge()));
}
void MainWindow::on_pushButton_2_clicked() {
  // Логика для обработки нажатия кнопки
  QColor selectedColor =
      QColorDialog::getColor(Qt::black, this, "Выберите цвет ребер");
  if (selectedColor.isValid()) {
    mywidget->setEdgeColor(selectedColor);
  }
}
void MainWindow::on_pushButton_3_clicked() {
  QColor selectedColor =
      QColorDialog::getColor(Qt::red, this, "Выберите цвет вершин");
  if (selectedColor.isValid()) {
    mywidget->setVertexColor(selectedColor);
  }
}
void MainWindow::on_pushButton_4_clicked() {
  QColor selectedColor =
      QColorDialog::getColor(Qt::white, this, "Выберите цвет фона");
  if (selectedColor.isValid()) {
    mywidget->setBackgroundColor(selectedColor);
  }
}
void MainWindow::on_pushButton_5_clicked() {
  // Логика для обработки нажатия кнопки
  qDebug() << "Кнопка Animation!";
}
void MainWindow::on_pushButton_6_clicked() { qDebug() << "Кнопка Screen!"; }
void MainWindow::on_pushButton_7_clicked() {
  // Логика для обработки нажатия кнопки
  qDebug() << "Кнопка GIF!";
}
void MainWindow::on_spinBox_valueChanged(int value) {
  mywidget->setMovingX(value);
}
void MainWindow::on_spinBox_2_valueChanged(int value) {
  mywidget->setMovingY(value);
}
void MainWindow::on_spinBox_3_valueChanged(int value) {
  mywidget->setMovingZ(value);
}
void MainWindow::on_spinBox_4_valueChanged(int value) {
  mywidget->setRotationX(value);
}
void MainWindow::on_spinBox_5_valueChanged(int value) {
  mywidget->setRotationY(value);
}
void MainWindow::on_spinBox_6_valueChanged(int value) {
  mywidget->setRotationZ(value);
}
void MainWindow::on_spinBox_7_valueChanged(int value) {
  mywidget->setScaling(value);
}
void MainWindow::on_spinBox_8_valueChanged(int value) {
  mywidget->setSizeEdge(value);
}
void MainWindow::on_spinBox_9_valueChanged(int value) {
  mywidget->setSizeVertex(value);
}
void MainWindow::on_spinBox_10_valueChanged(int value) {
  mywidget->setAnimationX(value);
}
void MainWindow::on_spinBox_11_valueChanged(int value) {
  mywidget->setAnimationY(value);
}
void MainWindow::on_spinBox_12_valueChanged(int value) {
  mywidget->setAnimationY(value);
}
void MainWindow::on_comboBox_currentIndexChanged(int index) {
  mywidget->setTypeProjection(index);
}
void MainWindow::on_comboBox_2_currentIndexChanged(int index) {
  mywidget->setTypeEdges(index);
}
void MainWindow::on_comboBox_3_currentIndexChanged(int index) {
  mywidget->setTypeVertex(index);
}
};  // namespace s21