
#include "Rectangle.h"
#include <QPainter>
#include <cmath>
#include "Lines.h"

#define MAX(a, b) ((a) > (b) ? (a) : (b))

int sign(int a) {
  if (a > 0) {
    return 1;
  }
  if (a < 0) {
    return -1;
  }

  return 0;
}

Rectangle::Rectangle(QWidget *parent)
    : QWidget(parent) {}

void Rectangle::paintEvent(QPaintEvent *e) {
  Q_UNUSED(e);
  QPainter qp(this);
  Bresenham(33 * CELL, 33 * CELL, 5 * CELL, 8 * CELL, &qp);

  DDA(33 * CELL, 33 * CELL, 5 * CELL, 8 * CELL, &qp);
}

void Rectangle::pixel(int x, int y, QPainter *qp, QColor c) {
  int xx, yy;
  for (int i = 0; i < 800; ++i) {
    if (x >= CELL * i && x < CELL * (i + 1)) {
      xx = CELL * i;

    }
    if (y >= CELL * i && x < 40 * (CELL + 1)) {
      yy = CELL * i;
    }
  }

  this->setGeometry(0, 0, 800, 800);
  qp->fillRect(xx, yy, CELL, CELL, c);

}

void Rectangle::DDA(int x0, int y0, int x1, int y1, QPainter *qp) {

  //приращения
  double dx = x1 - x0, dy = y1 - y0;
  QColor bich(240, 10, 80, 10);
  double N = MAX(fabs(dx), fabs(dy)); // число шагов построения
  double x = x0, y = y0;
  pixel(x, y, qp, bich);
  for (int k = 0; k < N; k++) {
    if (fabs(dx) >= fabs(dy)) {
      x = x + dx / N;
      y = y + (dy / fabs(dx));
    } else if (fabs(dx) < fabs(dy)) {
      x = x + (dx / fabs(dy));
      y = y + dy / N;
    }
    pixel(floor(x), floor(y), qp, bich);
  }
}

void Rectangle::Bresenham(int x0, int y0, int x1, int y1, QPainter *qp) {

  //приращения
  double dx = x1 - x0, dy = y1 - y0;
  double N = MAX(fabs(dx), fabs(dy)); // число шагов построения
  double x = x0, y = y0;
  double E;
  if (fabs(dx) > fabs(dy)) {
    E = fabs(dy / dx) - 0.5;
  } else {
    E = fabs(dx / dy) - 0.5;
  }

  pixel(x, y, qp, Qt::darkGreen);
  for (int i = 0; i < N; i++) {
    if (fabs(dx) > fabs(dy)) {
      x += (dx / N);
      if (E >= 0) {
        y += sign(dy);
        E += (fabs(dy / dx) - 1);
      } else {
        E += fabs(dy / dx);
      }
    } else {
      y += (dy / N);
      if (E >= 0) {
        x += sign(dx);
        E += (fabs(dx / dy) - 1);
      } else {
        E += fabs(dx / dy);
      }
    }
    pixel(x, y, qp, Qt::darkGreen);
  }

}