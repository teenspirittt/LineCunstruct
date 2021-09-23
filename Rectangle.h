#pragma once

#include <QWidget>



int sign(int a);
class Rectangle : public QWidget {

 public:
  Rectangle(QWidget *parent = 0);
  void Bresenham(int x0, int y0, int x1, int y1, QPainter *qp);
  void pixel(int x, int y, QPainter *qp, QColor c);
  void DDA(int x0, int y0, int x1, int y1, QPainter *qp);
 protected:
  void paintEvent(QPaintEvent *event);
  void drawRectangle(QPainter *qp);
};

