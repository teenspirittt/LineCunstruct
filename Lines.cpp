#include <QPainter>
#include "Lines.h"
#include <QKeyEvent>
#include <cmath>

Lines::Lines(QWidget *parent)
    : QWidget(parent) {}

int sign(int a) {
  if (a > 0) {
    return 1;
  }
  if (a < 0) {
    return -1;
  }

  return 0;
}

void Lines::keyPressEvent(QKeyEvent *e) {
  if (e->key() == Qt::Key_Left) {
    flag1 = !flag1;
    update();
  }
}

void Lines::paintEvent(QPaintEvent *e) {
  Q_UNUSED(e);
  QPainter qp(this);
  drawGrid(&qp);
  qp.translate(400, 400);
  qp.scale(1, -1);
  Bresenham(x_start, y_start, x_end, y_end, &qp);
  if (flag1) {
    DDA(x_start, y_start, x_end, y_end, &qp);
  }

}

void Lines::drawGrid(QPainter *qp) {
  height = 800;
  width = 800;
  QWidget::setFixedSize(height, width);
  QPen pen(Qt::black, 1, Qt::DashLine);
  qp->setPen(pen);
  for (int i = 0; i < 800; i += CELL) {
    qp->drawLine(0, 0 + i, 800, 0 + i);
    qp->drawLine(0 + i, 0, 0 + i, 800);
  }

  QPen pen1(Qt::darkRed, 2, Qt::SolidLine);
  qp->setPen(pen1);
  qp->drawLine(400, 0, 400, 800);
  qp->drawLine(0, 400, 800, 400);

}

void Lines::pixel(int x, int y, QPainter *qp, QColor c) {
  int xx, yy;

  xx = x * CELL;
  yy = y * CELL;
  this->setGeometry(0, 0, 800, 800);
  qp->fillRect(xx, yy, CELL, CELL, c);

}

void Lines::DDA(int x0, int y0, int x1, int y1, QPainter *qp) {
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

void Lines::Bresenham(int x0, int y0, int x1, int y1, QPainter *qp) {
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