#include <QApplication>
#include "Lines.h"
#include "Rectangle.h"
#include <QVBoxLayout>
#include <QWidget>

int main(int argc, char *argv[]) {

  QApplication app(argc, argv);
  //Rectangle *rec = new Rectangle;
  Lines *window = new Lines;



  //QVBoxLayout* layout = new QVBoxLayout(window);
  //layout->addWidget(rec);
  window->resize(800, 800);
  window->setWindowTitle("Vectors");
  window->show();

  return app.exec();
}