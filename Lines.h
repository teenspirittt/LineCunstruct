#pragma once

#include <QWidget>

#define MAX(a, b) ((a) > (b) ? (a) : (b))
const int x_start = 0;
const int y_start = 0;
const int x_end = -1;
const int y_end = -1;

int sign(int a);
#define CELL 25
class Lines : public QWidget {

 private:
  int height;
  int width;
  bool flag1;
 public:

  Lines(QWidget *parent = 0);
  void Bresenham(int x0, int y0, int x1, int y1, QPainter *qp);
  void pixel(int x, int y, QPainter *qp, QColor c);
  void DDA(int x0, int y0, int x1, int y1, QPainter *qp);

 protected:
  void paintEvent(QPaintEvent *e);
  void drawGrid(QPainter *qp);
  void keyPressEvent(QKeyEvent *e);

};
