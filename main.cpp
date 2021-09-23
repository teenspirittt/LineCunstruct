#include <QApplication>
#include "Lines.h"
#include "Rectangle.h"
#include <QVBoxLayout>

int main(int argc, char *argv[]) {

  QApplication app(argc, argv);
  Rectangle *rec = new Rectangle;
  Lines *window = new Lines;

  // компановка виджетов todo
  QVBoxLayout* layout = new QVBoxLayout(window);
  layout->addWidget(rec);

  window->resize(800, 800);
  window->setWindowTitle("Vectors");
  window->show();

  return app.exec();
}