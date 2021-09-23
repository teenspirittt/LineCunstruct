
#include "huixel.h"
#include <QPainter>
#include <cmath>

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
  Bresenham(20, 1000, 600, 670, &qp);
}

void Rectangle::pixel(int x, int y, QPainter *qp) {
  int xx, yy;
  for (int i = 0; i < 800; ++i) {
    if (x >= 40 * i && x < 40 * (i + 1)) {
      xx = 40 * i;

    }
    if (y >= 40 * i && x < 40 * (i + 1)) {
      yy = 40 * i;
    }
  }

  this->setGeometry(0, 0, 800, 800);
  qp->fillRect(xx, yy, 40, 40, Qt::darkRed);

}

void


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

  pixel(x, y, qp);
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
    pixel(x, y, qp);
  }

}