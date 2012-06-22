#ifndef AREA_H
#define AREA_H

#include <QWidget>
#include "util.h"
#include <vector>
#include <set>
#include <QtCore/QTimer>
#include <QtGui/QPainter>
#include <QtGui/QPalette>
#include <QtGui/QMouseEvent>


namespace Ui {
class Area;
}

class Area : public QWidget
{
    Q_OBJECT
    
public:
  explicit Area(QWidget *parent = 0);
  ~Area();

  void draw(QPainter *painter);
  void paintEvent(QPaintEvent *event);
  void mousePressEvent(QMouseEvent *event);
  void mouseReleaseEvent(QMouseEvent *event);
  void mouseMoveEvent(QMouseEvent *event);


public slots:

    void forwardstep();
    void backstep();
    void qforwardstep();
    void qbackstep();
    void forwardsteps();
    void backsteps();
    void qforwardsteps();
    void qbacksteps();
    void pause();
    void draw();
    void stopdraw();
    void stop();
    void undo();
    void redo();
    void finish();
    void load(QString file);
    void save(QString file);
    void saveresult(QString file);
    void generetePoints(int numSegments, bool vert, bool multi, bool full);

signals:
    void generationfail();

private:

     QTimer *forwardTimer;
     QTimer *backTimer;
     QTimer *qforwardTimer;
     QTimer *qbackTimer;
     int timerSpeed;
     int qtimerSpeed;
     int mCurLine;

     bool drawMode;

     std::vector<Segment*> mSegments;
     std::vector<Intersection*> mIntersections;
     std::set<int> mSuperSegments;
     int mCurIntersection;

     Point2d* mCurDrawPoint;
     Point2d* mCurDrawingPoint;
     std::list<Segment*> history;
     std::list<Segment*> future;
};

#endif // AREA_H
