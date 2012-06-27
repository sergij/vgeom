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

void Area::computeIntersections() {

  std::vector<Segment*> segments;
  std::vector<Intersection*> intersections;

  for (int i = 0; i < mSegments.size(); i++) {
      segments.push_back(new Segment(mSegments[i].p, mSegments[i].q));
  }

<<<<<<< .merge_file_mG5bBz
bool comparator(const Segment* a, const Segment* b) {
        double x = std::max (std::min (a->p.x, a->q.x), std::min (b->p.x, b->q.x));
        qDebug("Comparator called");
        return a->get_bott(x) < b->get_bott(x) - EPS;
}
=======
  intersection(segments, intersections);

  mIntersections.release();

  for (int i = 0; i < intersections.size(); i++) {
      mIntersections.push_back(new Intersection(intersections[i]->p,
                                                intersections[i]->seg1, intersections[i]->seg2));
      delete intersections[i];
  }
>>>>>>> .merge_file_8dXI4w

  for (int i = 0; i < segments.size(); i++) {
      delete segments[i];
  }
}
<<<<<<< .merge_file_mG5bBz
struct point_f{
    long double x,y,z;
};

struct event {
        double x;
        int tp, id, id2;

        event() { }
        event (double x, int tp, int id, int id2=0)
            : x(x), tp(tp), id(id), id2(id2)
        { }

        bool operator< (const event & e) const {
                if (abs (this->x - e.x) > EPS)
                    return this->x < e.x;
                return tp > e.tp;
        }
};

void intersection(std::vector<Segment*> segments, std::vector<Intersection*> &intersections) {
    int n = segments.size();
    intersections.clear();
    for (int i = 0; i < n; i++) {
        if(segments[i]->p.x > segments[i]->q.x) {
            std::swap(segments[i]->p, segments[i]->q);
        }
        else if(segments[i]->p.x == segments[i]->q.x){
            if(segments[i]->p.y > segments[i]->q.y) {
                std::swap(segments[i]->p, segments[i]->q);
            }
        }
        Point2d p(segments[i]->p.x, segments[i]->p.y);
        Intersection* intersection = new Intersection(p, segments[ i ], segments[ i ]);
        intersections.push_back(intersection);
        p.x = segments[i]->q.x;
        p.y = segments[i]->q.y;
        Intersection* intersection2 = new Intersection(p, segments[ i ], segments[ i ]);
        intersections.push_back(intersection2);
    }
    std::vector<event> e;
    for (int i=0; i<n; ++i) {
        e.push_back (event (std::min (segments[i]->p.x, segments[i]->q.x), +1, i));
        e.push_back (event (std::max (segments[i]->p.x, segments[i]->q.x), -1, i));
    }
    std::sort(e.begin(), e.end());
    bool(*fn_pt)(const Segment*, const Segment*) = comparator;
    std::set<Segment*, bool(*)(const Segment*, const Segment*)> s_segs (fn_pt);
    std::vector< std::set<Segment*>::iterator > where(segments.size());
    std::vector<Segment*>::iterator to_find;

    int id2;
    for (size_t i=0; i<e.size(); ++i) {
        int id = e[i].id;

        if (e[i].tp == +1) {
            qDebug("plus");
            std::set<Segment*>::iterator s1 = s_segs.lower_bound (segments[id]);
            std::set<Segment*>::iterator nxt2 = s_segs.lower_bound (segments[id]);
            std::set<Segment*>::iterator s2 = (s1==s_segs.begin()) ? s_segs.end(): --nxt2;

            if (s1 != s_segs.end() && intersect(*s1, segments[id])){
                Point2d p(find_point(*s1, segments[id]));
                intersections.push_back(new Intersection(p, *s1, segments[id]));
                for(size_t j=i+1;j<e.size() - 1; j++) {
                    if(e[j+1].x>=p.x)
                    {
                        to_find=find(segments.begin(), segments.end(), (*s1));
                        if(to_find==segments.end())
                            break;
                        id2 = to_find - segments.begin();
                        e.insert(e.begin() + j, event(p.x, 0, id2, id));
                        break;
                    }
                }
            }
            if (s2 != s_segs.end() && intersect(*s2, segments[id]) ) {
                Point2d p(find_point(*s2, segments[id]));
                intersections.push_back(new Intersection(p, *s2, segments[id]));
                for(size_t j = i + 1;j<e.size() - 1; j++) {
                    if(e[j+1].x>=p.x)
                    {
                        to_find=find(segments.begin(), segments.end(), (*s2));
                        if(to_find==segments.end())
                            break;
                        id2 = to_find - segments.begin();
                        e.insert(e.begin() + j, event(p.x, 0, id2, id));
                        break;
                    }
                }
            }
            qDebug("pre insert");
            where[id] = s_segs.insert (s1, segments[id]);
            qDebug("post insert");
        }
        else if(e[i].tp == -1){
            qDebug("minus");
            std::set<Segment*>::iterator s = where[id], tmp2 = where[id], tih = where[id];
            tih++;
            std::set<Segment*>::iterator s1 = tih;
            std::set<Segment*>::iterator s2 = (tmp2==s_segs.begin()) ? s_segs.end(): --tmp2;
            if (s1 != s_segs.end() && s2 != s_segs.end() && intersect (*s1, *s2)) {
                Point2d p(find_point(*s1, *s2));
                if(p.x > e[i].x) {
                    intersections.push_back(new Intersection(p, *s1, *s2));
                    for(size_t j=i+1;j<e.size() - 1; j++) {
                        if(e[j+1].x >= p.x)
                        {
                            to_find=find(segments.begin(), segments.end(), (*s1));
                            if(to_find==segments.end())
                                break;
                            id = to_find - segments.begin();
                            to_find=find(segments.begin(), segments.end(), (*s2));
                            if(to_find==segments.end())
                                break;
                            id2 = to_find - segments.begin();
                            e.insert(e.begin() + j, event(p.x, 0, id, id2));
                            break;
                        }
                    }
                }
            }
            if(s_segs.begin() == s)
                qDebug("In begin");
            else
                qDebug("Not in begin");
            if(i==0)
                qDebug("zero");
            if(i==1)
                qDebug("one");
            if(i==2)
                qDebug("two");
            if(i==3)
                qDebug("three");
            qDebug("pre erase");
            if(find(s_segs.begin(), s_segs.end(), (*s))!=s_segs.end())
                qDebug("Norm");
            else
                qDebug("Not norm");
            s_segs.erase(s);
            qDebug("post erase");

        }
        else {
            qDebug("zero FAP");
            std::set<Segment*>::iterator s1 = where[e[i].id], tih = where[e[i].id];
            std::set<Segment*>::iterator s2 = where[e[i].id2], tih2 = where[e[i].id2];
            tih++;
            std::set<Segment*>::iterator s3 = tih;
            std::set<Segment*>::iterator s4 = (s2==s_segs.begin()) ? s_segs.end(): --tih2;
            if (s3 != s_segs.end() && s2 != s_segs.end() && intersect (*s3, *s2)) {
                Point2d p(find_point(*s3, *s2));
                if(p.x > e[i].x) {
                    intersections.push_back(new Intersection(p, *s3, *s2));
                    qDebug("INN222");
                    for(size_t j=i+1;j<e.size() - 1; j++) {
                        if(e[j+1].x >= p.x)
                        {
                            to_find=find(segments.begin(), segments.end(), (*s3));
                            if(to_find==segments.end())
                                break;
                            id = to_find - segments.begin();
                            to_find=find(segments.begin(), segments.end(), (*s2));
                            if(to_find==segments.end())
                                break;
                            id2 = to_find - segments.begin();
                            e.insert(e.begin() + j, event(p.x, 0, id, id2));
                            break;
                        }
                    }
                }
            }
            if (s1 != s_segs.end() && s4 != s_segs.end() && intersect (*s1, *s4)) {
                Point2d p(find_point(*s1, *s4));
                if(p.x > e[i].x) {
                    intersections.push_back(new Intersection(p, *s1, *s4));
                    qDebug("INN333");
                    for(size_t j=i+1;j<e.size() - 1; j++) {
                        if(e[j+1].x >= p.x)
                        {
                            to_find=find(segments.begin(), segments.end(), (*s1));
                            if(to_find==segments.end())
                                break;
                            id = to_find - segments.begin();
                            to_find=find(segments.begin(), segments.end(), (*s4));
                            if(to_find==segments.end())
                                break;
                            id2 = to_find - segments.begin();
                            e.insert(e.begin() + j, event(p.x, 0, id, id2));
                            break;
                        }
                    }
                }
            }
            qDebug("swap was processed");
//            where[e[i].id] = s2;
//            where[e[i].id2] = s1;
//            std::swap((*s1)->p, (*s2)->p);
//            std::swap((*s1)->q, (*s2)->q);
        }
    }
=======
>>>>>>> .merge_file_8dXI4w

void Area::cleanSegments() {

  mCurLine = 0;
  mCurIntersection = -1;
  mSegments.release();
  mIntersections.release();
  mSuperSegments.clear();

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

    cleanSegments();

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

    cleanSegments();

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

    if (mSegments.size() == 0) {
        emit generationFailAreaSignal();
    } else {
        computeIntersections();
    }

    update();

}

void Area::loadFromFileAreaSlot(QString file) {

    cleanSegments();

    int numSegments;
    int x1, y1, x2, y2;
    int maxX = 0, maxY = 0;

    std::ifstream fin(file.toAscii().data());

    if (!readIntFromFile(fin, numSegments)) {
        return;
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

            mSegments.release();
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

    if (mSegments.size() == 0) {
        emit generationFailAreaSignal();
    } else {
        computeIntersections();
    }

    update();
}

void Area::saveToFileAreaSlot(QString file) {

    std::ofstream fout(file.toAscii().data());

    fout << mSegments.size() << std::endl;

    for (size_t i = 0; i < mSegments.size(); i++) {

        fout << mSegments[i].p.x << std::endl;
        fout << mSegments[i].p.y << std::endl;
        fout << mSegments[i].q.x << std::endl;
        fout << mSegments[i].q.y << std::endl;
    }
}

void Area::saveResultToFileAreaSlot(QString file) {

    std::ofstream fout(file.toAscii().data());
    fout << mSegments.size() << std::endl;

    for (int i = 0; i < mSegments.size(); i++) {

        fout << mSegments[i].p.x << std::endl;
        fout << mSegments[i].p.y << std::endl;
        fout << mSegments[i].q.x << std::endl;
        fout << mSegments[i].q.y << std::endl;
    }

    fout << "results" << std::endl;

    fout << mIntersections.size() << std::endl;
    for (int i = 0; i < mIntersections.size(); i++) {
        fout << mIntersections[i].p.x << " ";
        fout << mIntersections[i].p.y << " ";
    }
}

void compareResultsAreaSlot() {

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

<<<<<<< .merge_file_mG5bBz
    for (size_t i = 0; i < mSegments.size(); i++) {
=======
    update();
}
>>>>>>> .merge_file_8dXI4w

void Area::redoAreaSlot() {
    if (future.size() > 0) {
        boost::ptr_list<Segment>::iterator it = --future.end();
        history.transfer( history.end(),
                           it,
                           future );
    }
    update();
}

void Area::drawAreaSlot() {
    drawMode = true;
    update();
}

void Area::stopDrawAreaSlot(){
    drawMode = false;
    cleanSegments();
    mSegments.transfer( mSegments.begin(),
                          history.begin(),
                          history.end(),
                          history );

    history.release();
    future.release();

    if (mSegments.size() == 0) {
        emit generationFailAreaSignal();
    } else {
        computeIntersections();
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
            painter->drawLine(mIntersections[mCurIntersection].seg1.p.x, mIntersections[mCurIntersection].seg1.p.y, mIntersections[mCurIntersection].seg1.q.x, mIntersections[mCurIntersection].seg1.q.y);
            painter->drawLine(mIntersections[mCurIntersection].seg2.p.x, mIntersections[mCurIntersection].seg2.p.y, mIntersections[mCurIntersection].seg2.q.x, mIntersections[mCurIntersection].seg2.q.y);
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
