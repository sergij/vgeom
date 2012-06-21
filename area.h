#ifndef AREA_H
#define AREA_H

#include <QWidget>
#include "util.h"
#include <vector>
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


private slots:

    void forwardstep();
    void backstep();
    void forwardsteps();
    void backsteps();
    void pause();
    void stop();
    void finish();
    void load(QString file);
    void save(QString file);
    void generetePoints(int numSegments);


private:
    QTimer *forwardTimer;
    QTimer *backTimer;
    int timerSpeed;

    std::vector<Segment*> mSegments;
    std::vector<Intersection*> mIntersections;
    int mCurIntersection;

};

#endif // AREA_H
