#ifndef AREA_H
#define AREA_H

#include <QWidget>
#include "util.h"
#include <set>
#include <boost/ptr_container/ptr_vector.hpp>
#include <boost/ptr_container/ptr_list.hpp>
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

  void drawAreaSlot(QPainter *painter);
  void paintEvent(QPaintEvent *event);
  void mousePressEvent(QMouseEvent *event);
  void mouseReleaseEvent(QMouseEvent *event);
  void mouseMoveEvent(QMouseEvent *event);


public slots:

  // single step slots
    void forwardStepAreaSlot();
    void backStepAreaSlot();

  // continuous step slots
    void qforwardStepAreaSlot();
    void qbackStepAreaSlot();

  // single steps slots
    void forwardStepsAreaSlot();
    void backStepsAreaSlot();

  // continuous step slots
    void qforwardStepsAreaSlot();
    void qbackStepsAreaSlot();

  // step control slots
    void pauseAreaSlot();
    void stopAreaSlot();
    void finishAreaSlot();

  // draw control slots
    void drawAreaSlot();
    void stopDrawAreaSlot();
    void undoAreaSlot();
    void redoAreaSlot();

  // file control steps
    void loadFromFileAreaSlot(QString file);
    void saveToFileAreaSlot(QString file);
    void saveResultToFileAreaSlot(QString file);

  // generation control steps
    void generetePointsAreaSlot(int numSegments, bool vert, bool multi, bool full);

signals:

  // generation signals
    void generationFailAreaSignal();

private:

     QTimer *forwardTimer;
     QTimer *backTimer;
     QTimer *qforwardTimer;
     QTimer *qbackTimer;
     int timerSpeed;
     int qtimerSpeed;

     boost::ptr_vector<Segment> mSegments;
     boost::ptr_vector<Intersection> mIntersections;
     std::set<int> mSuperSegments; // vert, multi intersec

     int mCurLine;
     int mCurIntersection;

     bool drawMode;
     Point2d* mCurDrawPoint;
     Point2d* mCurDrawingPoint;
     boost::ptr_list<Segment> history;
     boost::ptr_list<Segment> future;
};

#endif // AREA_H
