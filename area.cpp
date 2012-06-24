#include "area.h"
#include "util.h"
#include "intersection.h"
#include <iostream>
#include <fstream>
#include <set>
#include <algorithm>
#include <math.h>
#include <QErrorMessage>

bool readIntFromFile(std::ifstream &fin, int &res) {
    std::string tmp;

    if (fin >> tmp) {
        res = atoi(tmp.c_str());
        if ((res <= 0) && (tmp.compare(std::string("0")))) {
            QErrorMessage em;
            em.showMessage("Incorrect file");
            em.exec();
            return false;
        }
       return true;
     }
    QErrorMessage em;
    em.showMessage("Short file");
    em.exec();
    return false;
}

Area::Area(QWidget *parent) :
    QWidget(parent) {

  forwardTimer = new QTimer(this);
  backTimer = new QTimer(this);
  qforwardTimer = new QTimer(this);
  qbackTimer = new QTimer(this);

  timerSpeed = 500;
  qtimerSpeed = 10;

  mCurLine = 0;
  mCurIntersection = -1;

  drawMode = false;
  mCurDrawPoint = NULL;
  mCurDrawingPoint = NULL;

  connect(forwardTimer, SIGNAL(timeout()), this, SLOT(forwardStepAreaSlot()));
  connect(backTimer, SIGNAL(timeout()), this, SLOT(backStepAreaSlot()));
  connect(qbackTimer, SIGNAL(timeout()), this, SLOT(qbackStepAreaSlot()));
  connect(qforwardTimer, SIGNAL(timeout()), this, SLOT(qforwardStepAreaSlot()));
}

Area::~Area() {
}

void Area::forwardStepAreaSlot() {

    if (mCurIntersection < (int)(mIntersections.size() - 1)) {
        mCurIntersection++;
        mCurLine = mIntersections[mCurIntersection].p.x;
    } else {
        forwardTimer->stop();
        mCurLine = width();
    }

    update();
}

void Area::backStepAreaSlot() {
    if (mCurIntersection > 0) {
        mCurIntersection--;
        mCurLine = mIntersections[mCurIntersection].p.x;
    } else {
        backTimer->stop();
        mCurIntersection = -1;
        mCurLine = 0;
    }

    update();
}

void Area::qforwardStepAreaSlot() {
    if (mCurLine < width()) {
        mCurLine++;
        while ((mCurIntersection + 1 < mIntersections.size()) && (mIntersections[mCurIntersection + 1].p.x < mCurLine)) mCurIntersection++;
    } else {
        qforwardTimer->stop();
    }

    update();
}

void Area::qbackStepAreaSlot() {
    if (mCurLine > 0) {
        mCurLine--;
        while ((mCurIntersection - 1 >= 0) && (mIntersections[mCurIntersection - 1].p.x > mCurLine)) mCurIntersection--;
    } else {
        qbackTimer->stop();
    }
    update();
}

void Area::backStepsAreaSlot() {
    forwardTimer->stop();
    qforwardTimer->stop();
    qbackTimer->stop();
    backTimer->start(timerSpeed);
}

void Area::forwardStepsAreaSlot() {
    backTimer->stop();
    qforwardTimer->stop();
    qbackTimer->stop();
    forwardTimer->start(timerSpeed);
}

void Area::qbackStepsAreaSlot() {
    qforwardTimer->stop();
    forwardTimer->stop();
    backTimer->stop();
    qbackTimer->start(qtimerSpeed);
}

void Area::qforwardStepsAreaSlot() {
    qbackTimer->stop();
    forwardTimer->stop();
    backTimer->stop();
    qforwardTimer->start(qtimerSpeed);
}


void Area::pauseAreaSlot() {
    backTimer->stop();
    forwardTimer->stop();
    qbackTimer->stop();
    qforwardTimer->stop();
}

void Area::stopAreaSlot() {
    forwardTimer->stop();
    backTimer->stop();
    qforwardTimer->stop();
    qbackTimer->stop();
    mCurLine = 0;

    mIntersections.release();
    mSegments.release();
    mCurIntersection = -1;

    update();
}

void Area::finishAreaSlot() {

    forwardTimer->stop();
    backTimer->stop();
    qforwardTimer->stop();
    qbackTimer->stop();

    mCurIntersection = mIntersections.size() - 1;
    mCurLine = width();

    update();
}

void Area::generetePointsAreaSlot(int numSegments, bool vert, bool multi, bool full) {

    mSegments.release();
    if (full) {
        int dx = width() / numSegments;
        int dy = height() / numSegments;
        int y = height();
        int x = 0;

        for (int i = 0; i < numSegments; i++) {
            x += dx;
            y -= dy;
            mSegments.push_back(new Segment(Point2d(0, y), Point2d(x, 0)));
        }
        numSegments = 0;
     }

    if (vert) {
        int nvert = (numSegments / 20) + 1;
        numSegments -= nvert;
        for (int i = 0; i < nvert; i++) {
            int x = rand()%width();
            mSegments.push_back(new Segment(Point2d(x, rand()%height()), Point2d(x, rand()%height())));
            mSuperSegments.insert(i);
        }
    }

    if (multi) {
        int nmulti = std::min((numSegments / 20) + 3, numSegments);
        numSegments -= nmulti;
        int x = rand()%((int)(width()*0.8)) + width()*0.1;
        int y = rand()%((int)(height()*0.8)) + height()*0.1;
        for (int i = 0; i < nmulti; i++) {
            int dx = rand()%(std::min(std::abs(width() - x), x));
            int dy = rand()%(std::min(std::abs(height() - y), y));
            mSegments.push_back(new Segment(Point2d(x - dx, y - dy), Point2d(x + dx, y + dy)));
            mSuperSegments.insert(i);
        }
    }

    for (int i = 0; i < numSegments; i++) {;
        mSegments.push_back(new Segment(Point2d(rand()%width(), rand()%height()), Point2d(rand()%width(), rand()%height())));
    }

    mCurIntersection = -1;
    mCurLine = 0;

    if (mSegments.size() == 0) {
        mIntersections.release();
        emit generationFailAreaSignal();
    } else {
        //intersection(mSegments, mIntersections);
    }

    update();

}

void Area::loadFromFileAreaSlot(QString file) {

    mSegments.release();

    int numSegments;
    int x1, y1, x2, y2;
    int maxX = 0, maxY = 0;

    std::ifstream fin(file.toAscii().data());

    if (!readIntFromFile(fin, numSegments)) {
        mCurLine = 0;
        mCurIntersection = -1;
    }

    for (int i = 0; i < numSegments; i++) {

        if (readIntFromFile(fin, x1) && readIntFromFile(fin, y1)
                && readIntFromFile(fin, x2) && readIntFromFile(fin, y2)) {


            if (x1 > maxX) maxX = x1;
            if (y1 > maxY) maxY = y1;
            if (x2 > maxX) maxX = x2;
            if (y2 > maxY) maxY = y2;

            mSegments.push_back(new Segment(Point2d(x1, y1), Point2d(x2, y2)));

        } else {

            mCurLine = 0;
            mCurIntersection = -1;
            mSegments.release();
            mIntersections.release();
            emit generationFailAreaSignal();
            return;
        }

    }

    if (maxX > width()) {
        for (int i = 0; i < numSegments; i++) {
            mSegments[i].p.x = mSegments[i].p.x / maxX * width();
            mSegments[i].q.x = mSegments[i].q.x / maxX * width();
        }
    }

    if (maxY > height()) {
        for (int i = 0; i < numSegments; i++) {
            mSegments[i].p.y = mSegments[i].p.y / maxY * height();
            mSegments[i].q.y = mSegments[i].q.y / maxY * height();
        }
    }

    mCurIntersection = -1;
    if (mSegments.size() == 0) {
        mIntersections.release();
        emit generationFailAreaSignal();
    } else {
        //intersection(mSegments, mIntersections);
    }
    update();
}

void Area::saveToFileAreaSlot(QString file) {

    std::ofstream fout(file.toAscii().data());

    fout << mSegments.size() << std::endl;

    for (int i = 0; i < mSegments.size(); i++) {

        fout << mSegments[i].p.x << std::endl;
        fout << mSegments[i].p.y << std::endl;
        fout << mSegments[i].q.x << std::endl;
        fout << mSegments[i].q.y << std::endl;
    }
}

void Area::saveResultToFileAreaSlot(QString file) {

    std::ofstream fout(file.toAscii().data());
    fout << mIntersections.size() << std::endl;
    for (int i = 0; i < mIntersections.size(); i++) {
        fout << mIntersections[i].p.x << " ";
        fout << mIntersections[i].p.y << " ";
    }
}


void Area::paintEvent(QPaintEvent *event) {

    QPainter painter(this);
    drawAreaSlot(&painter);
}

void Area::undoAreaSlot() {

    if (history.size() > 0) {
        boost::ptr_list<Segment>::iterator it = --history.end();
        future.transfer( future.end(),
                              it,
                              history );
    }

    update();
}

void Area::redoAreaSlot() {
    if (future.size() > 0) {
        boost::ptr_list<Segment>::iterator it = --future.end();
        history.transfer( history.end(),
                           it,
                           future );
    }
//std::vector<Segment*> = mSegments.
    update();
}

void Area::drawAreaSlot() {
    drawMode = true;
    update();
}

void Area::stopDrawAreaSlot(){
    drawMode = false;
    mSegments.release();
    mSegments.transfer( mSegments.begin(),
                          history.begin(),
                          history.end(),
                          history );

    history.release();
    future.release();
    mCurIntersection = -1;
    mCurLine = 0;
    if (mSegments.size() == 0) {
        emit generationFailAreaSignal();
    } else {
        //intersection(mSegments, mIntersections);
    }
    update();
}


void Area::mouseMoveEvent(QMouseEvent *event) {
    if (drawMode) {
        if (mCurDrawPoint != NULL) {
            if (mCurDrawingPoint != NULL) delete mCurDrawingPoint;
            mCurDrawingPoint = new Point2d(event->x(), event->y());
        }
        update();
    }
}

void Area::mousePressEvent(QMouseEvent *event) {
    if (drawMode) {
       if (mCurDrawPoint != NULL) delete mCurDrawPoint;
       if (mCurDrawingPoint != NULL) delete mCurDrawingPoint;
       mCurDrawPoint = new Point2d(event->x(), event->y());
    }
}

void Area::mouseReleaseEvent(QMouseEvent *event) {
    if (drawMode) {
        history.push_back(new Segment(Point2d(mCurDrawPoint->x, mCurDrawPoint->y), Point2d(event->x(), event->y())));
        mCurDrawPoint = NULL;
        mCurDrawingPoint = NULL;
    }
}

void Area::drawAreaSlot(QPainter *painter) {

    if (! drawMode) {

        QPen blackPen(Qt::black, 2);
        QPen greenPen(Qt::green, 2);
        QPen orangePen(Qt::darkYellow, 2);

        for (int i = 0; i < mSegments.size(); i++) {

            if ((mCurLine > -1 ) && (mCurLine < width()) &&
                    (((mSegments[i].p.x < mCurLine) && (mCurLine < mSegments[i].q.x)) ||
                    ((mSegments[i].q.x < mCurLine) && (mCurLine < mSegments[i].p.x)))) {
                painter->setPen(greenPen);
            } else {
                if (mSuperSegments.count(i) > 0) painter->setPen(orangePen);
                else painter->setPen(blackPen);
            }

            painter->drawLine(mSegments[i].p.x, mSegments[i].p.y, mSegments[i].q.x, mSegments[i].q.y);
        }

        if ((mCurIntersection > -1 ) && (mCurLine < width() ) ) {
            QPen magentaPen(Qt::magenta, 2);
            painter->setPen(magentaPen);
            painter->drawLine(mIntersections[mCurIntersection].seg1->p.x, mIntersections[mCurIntersection].seg1->p.y, mIntersections[mCurIntersection].seg1->q.x, mIntersections[mCurIntersection].seg1->q.y);
            painter->drawLine(mIntersections[mCurIntersection].seg2->p.x, mIntersections[mCurIntersection].seg2->p.y, mIntersections[mCurIntersection].seg2->q.x, mIntersections[mCurIntersection].seg2->q.y);
        }

        QPen pointPen(Qt::red, 3);
        painter->setPen(pointPen);
        for (int i = 0; ((i <= mCurIntersection) && (mIntersections[i].p.x <= mCurLine)) ; i++) {
            painter->drawEllipse(mIntersections[i].p.x, mIntersections[i].p.y, 3, 3);
        }

        QPen bluePen(Qt::blue, 3);
        painter->setPen(bluePen);

        if (mCurLine == 0) {
            painter->drawLine(0, 0, 0, height() );
            painter->setOpacity(0.5);
            painter->fillRect(0, 0, width(), height(), Qt::gray);
        } else {
            if (mCurLine == width()) {
                painter->drawLine(width(), 0, width(), height() );
            } else {
                painter->drawLine(mCurLine, 0, mCurLine, height() );
                painter->setOpacity(0.5);
                painter->fillRect(mCurLine, 0, width(), height(), Qt::gray);
            }
        }


    } else {

        QPen grayPen(Qt::gray, 1);
        painter->setPen(grayPen);
        for (int i = 0; i < width(); i+=10) {
            painter->drawLine(i, 0, i, height());
        }
        for (int i = 0; i < height(); i+=10) {
            painter->drawLine(0, i, width(), i);
        }

        QPen blackPen(Qt::black, 2);
        painter->setPen(blackPen);
        for (boost::ptr_list<Segment>::iterator it = history.begin(); it != history.end(); ++it) {
            painter->drawLine(it->p.x, it->p.y, it->q.x, it->q.y);
        }

        QPen bluePen(Qt::blue, 2);
        painter->setPen(bluePen);
        if ((mCurDrawPoint != NULL) && (mCurDrawingPoint != NULL)) {
                painter->drawLine(mCurDrawPoint->x, mCurDrawPoint->y, mCurDrawingPoint->x, mCurDrawingPoint->y);
        }
    }
}





