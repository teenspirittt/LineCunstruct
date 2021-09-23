#include <QApplication>
#include "lines.h"

int main(int argc, char *argv[]) {

  QApplication app(argc, argv);

  Lines window;

  window.resize(800, 800);
  window.setWindowTitle("Lines");
  window.show();

  return app.exec();
}