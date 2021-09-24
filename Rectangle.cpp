
#include "Rectangle.h"
#include <QPainter>
#include <cmath>
#include "Lines.h"
#include <QTimer>


#define MAX(a, b) ((a) > (b) ? (a) : (b))
const int x_start = 0;
const int y_start = 0;
const int x_end = 10;
const int y_end = 10;

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
  qp.translate(400, 400);
  qp.scale(1, -1);
  //qp.setWindow(QRect(-400, -400, 800, 800));
  Bresenham(x_start, y_start, x_end, y_end, &qp);
  QTimer::singleShot(3000, this,)
  DDA(x_start, y_start, x_end, y_end, &qp);

}

void Rectangle::pixel(int x, int y, QPainter *qp, QColor c) {
  int xx, yy;
  /*for (int i = 0; i < 800; ++i) {
    if (x >= CELL * i && x < CELL * (i + 1)) {
      xx = CELL * i;

    }
    if (y >= CELL * i && x < CELL * (CELL + 1)) {
      yy = CELL * i;
    }
  }*/
  xx = x * CELL;
  yy = y * CELL;
  this->setGeometry(0, 0, 800, 800);
  qp->fillRect(xx, yy, CELL, CELL, c);

}

void Rectangle::DDA(int x0, int y0, int x1, int y1, QPainter *qp) {

  //приращения
  double dx = x1 - x0, dy = y1 - y0;
  double N = MAX(fabs(dx), fabs(dy)); // число шагов построения
  double x = x0, y = y0;
  pixel(x, y, qp, Qt::darkCyan);
  for (int k = 0; k <= N; k++) {
    if (fabs(dx) >= fabs(dy)) {
      x = x + dx / N;
      y = y + (dy / fabs(dx));
    } else if (fabs(dx) < fabs(dy)) {
      x = x + (dx / fabs(dy));
      y = y + dy / N;
    }
    pixel(floor(x), floor(y), qp, Qt::darkCyan);
  }
}

void Rectangle::Bresenham(int x0, int y0, int x1, int y1, QPainter *qp) {
  int x = x0, y = y0;
  int dx = abs(x1 - x0);
  int dy = abs(y1 - y0);
  int s1 = sign(x1 - x0);
  int s2 = sign(y1 - y0);
  bool flag = false;
  if (dy > dx) {
    int tmp = dx;
    dx = dy;
    dy = tmp;
    flag = true;
  }
  if (s1 < 0) x += s1;
  if (s2 < 0) y += s2;

  int e = 2 * dy - dx;
  for (int i = 0; i <= dx; i++) {
    pixel(x, y, qp, Qt::darkBlue);
    while (e >= 0) {
      if (flag) {
        x += s1;
      } else {
        y += s2;
      }
      e -= 2 * dx;
    }
    if (flag) {
      e += s2;
    } else {
      x += s1;
    }
    e += 2 * dy;
  }
}

/*void Rectangle::Bresenham(int x0, int y0, int x1, int y1, QPainter *qp) {
  //приращения
  double dx = x1 - x0, dy = y1 - y0;
  double x = x0, y = y0;
  double incx, incy, pdx, pdy, es, el, E;
  incx = sign(dx);
  incy = sign(dy);
  if (dx < 0) {
    dx = -dx;
  }
  if (dy < 0) {
    dy = -dy;
  }
  if (dx > dy) {
    pdx = incx;
    pdy = 0;
    es = dy;
    el = dx;
  } else {
    pdx = 0;
    pdy = incy;
    es = dx;
    el = dy;
  }
  x = x0;
  y = y0;
  E = el / 2;

  pixel(x, y, qp, Qt::darkGreen);

  for (int i = 0; i < el; i++) {
    E -= es;
    if (E < 0) {
      E += el;
      x += incx;
      y += incy;
    } else {
      x += pdx;
      y += pdy;
    }
    pixel(x, y, qp, Qt::darkGreen);
  }*/
/*for (int i = 0; i < N; i++) {
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
}*/

