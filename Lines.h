#pragma once

#include <QWidget>


#define CELL 25
class Lines : public QWidget {
 private:
  int height;
  int width;

 public:
  Lines(QWidget *parent = 0);

 protected:
  void paintEvent(QPaintEvent *event);
  void drawLines(QPainter *qp);
};

