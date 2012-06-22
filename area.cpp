#include "area.h"
#include <iostream>
#include <fstream>
#include <set>
#include <algorithm>
#include <math.h>
#include <QErrorMessage>

bool compIntersections(Intersection* int1, Intersection* int2) {
    return (int1->p.x < int2->p.x);
}

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


inline bool intersect1d (double l1, double r1, double l2, double r2) {
        if (l1 > r1)  std::swap (l1, r1);
        if (l2 > r2)  std::swap (l2, r2);
        return std::max (l1, l2) <= std::min (r1, r2) + EPS;
}

inline int vec (const Point2d & a, const Point2d & b, const Point2d & c) {
        double s = (b.x - a.x) * (c.y - a.y) - (b.y - a.y) * (c.x - a.x);
        return abs(s)<EPS ? 0 : s > 0 ? +1 : -1;
}

bool intersect (const Segment * a, const Segment * b) {
        return intersect1d (a->p.x, a->q.x, b->p.x, b->q.x)
                && intersect1d (a->p.y, a->q.y, b->p.y, b->q.y)
                && vec (a->p, a->q, b->p) * vec (a->p, a->q, b->q) <= 0
                && vec (b->p, b->q, a->p) * vec (b->p, b->q, a->q) <= 0;
}


bool operator< (const Segment & a, const Segment & b) {
        double x = std::max (std::min (a.p.x, a.q.x), std::min (b.p.x, b.q.x));
        return a.get_bott(x) < b.get_bott(x) - EPS;
}

Point2d find_point(const Segment* a, const Segment* b) {
    double k1 = ((a->q.y - a->p.y)/(a->q.x - a->p.x));
    double k2 = ((b->q.y - b->p.y)/(b->q.x - b->p.x));
    double b1 = a->p.y - (k1 * a->p.x);
    double b2 = b->p.y - (k2 * b->p.x);
    double x = (b2 - b1) / (k1 - k2);
    double y = (k1 * x) + b1;
    return Point2d(x, y);
}
struct point_f{
    long double x,y,z;
};

struct event {
        double x;
        int tp, id;

        event() { }
        event (double x, int tp, int id)
                : x(x), tp(tp), id(id)
        { }

        bool operator< (const event & e) const {
                if (abs (this->x - e.x) > EPS)
                    return this->x < e.x;
                return tp > e.tp;
        }
};


void intersection(const std::vector<Segment*> &segments, std::vector<Intersection*> &intersections) {

    int n = segments.size();
    intersections.clear();
    for (int i = 0; i < n; i++) {
        if(segments[i]->p.x > segments[i]->q.x)
            std::swap(segments[i]->p, segments[i]->q);
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
    std::set<Segment*> s_segs;
    std::vector< std::set<Segment*>::iterator > where;
    where.resize (segments.size());
    int counter=1;
    for (size_t i=0; i<e.size(); ++i) {
        int id = e[i].id;
        if (e[i].tp == +1) {
            std::set<Segment*>::iterator nxt = s_segs.lower_bound (segments[id]);
            std::set<Segment*>::iterator nxt2 = s_segs.lower_bound (segments[id]);
            std::set<Segment*>::iterator prv = (nxt==s_segs.begin()) ? s_segs.end(): --nxt2;
            if (nxt != s_segs.end() && intersect (*nxt, segments[id])){
                Point2d p(find_point(*nxt, segments[i]));
                intersections.push_back(new Intersection(p, *nxt, segments[id]));
            }
            if (prv != s_segs.end() && intersect (*prv, segments[id])) {
                Point2d p(find_point(*prv, segments[i]));
                intersections.push_back(new Intersection(p, *prv, segments[id]));
            }
            if (prv != s_segs.end() && nxt != s_segs.end() && intersect (*prv, *nxt)) {
                Point2d p(find_point(*prv, *nxt));
                intersections.push_back(new Intersection(p, *prv, *nxt));
            }
            where[id] = s_segs.insert (nxt, segments[id]);
        }
        else {
            std::set<Segment*>::iterator tmp = where[id], tmp2 = where[id], tih = where[id];
            std::set<Segment*>::iterator nxt = tmp++;
            std::set<Segment*>::iterator prv = (tmp2==s_segs.begin()) ? s_segs.end(): --tmp2;
            if (nxt != s_segs.end() && prv != s_segs.end() && intersect (*nxt, *prv)) {
                Point2d p(find_point(*nxt, *prv));
                intersections.push_back(new Intersection(p, *prv, *nxt));
            }
            if (nxt != s_segs.end() && tih != nxt && intersect (*nxt, *tih)) {
                Point2d p(find_point(*nxt, *tih));
                intersections.push_back(new Intersection(p, *nxt, *tih));
            }
            if (prv != s_segs.end() && tih != prv && intersect (*prv, *tih)) {
                Point2d p(find_point(*nxt, *tih));
                intersections.push_back(new Intersection(p, *prv, *tih));
            }
            s_segs.erase(where[id]);
        }
    }

    std::sort(intersections.begin(), intersections.end(), compIntersections);
}

Area::Area(QWidget *parent) :
    QWidget(parent) {

  mCurIntersection = -1;

  forwardTimer = new QTimer(this);
  backTimer = new QTimer(this);
  qforwardTimer = new QTimer(this);
  qbackTimer = new QTimer(this);
  timerSpeed = 500;
  qtimerSpeed = 10;
  mCurLine = 0;
  drawMode = false;
  mCurDrawPoint = NULL;
  mCurDrawingPoint = NULL;

  connect(forwardTimer, SIGNAL(timeout()), this, SLOT(forwardstep()));
  connect(backTimer, SIGNAL(timeout()), this, SLOT(backstep()));
  connect(qbackTimer, SIGNAL(timeout()), this, SLOT(qbackstep()));
  connect(qforwardTimer, SIGNAL(timeout()), this, SLOT(qforwardstep()));
}


void Area::forwardstep() {

    if (mCurIntersection < (int)(mIntersections.size() - 1)) {
        mCurIntersection++;
        mCurLine = mIntersections[mCurIntersection]->p.x;
    } else {
        forwardTimer->stop();
        mCurLine = width();
    }

    update();
}


void Area::backstep() {
    if (mCurIntersection > 0) {
        mCurIntersection--;
        mCurLine = mIntersections[mCurIntersection]->p.x;
    } else {
        backTimer->stop();
        mCurIntersection = -1;
        mCurLine = 0;
    }

    update();
}


void Area::qforwardstep() {


    if (mCurLine < width()) {
        mCurLine++;
        while ((mCurIntersection + 1 < mIntersections.size()) && (mIntersections[mCurIntersection + 1]->p.x < mCurLine)) mCurIntersection++;
    } else {
        qforwardTimer->stop();
    }

    update();
}

void Area::qbackstep() {
    if (mCurLine > 0) {
        mCurLine--;
        while ((mCurIntersection - 1 >= 0) && (mIntersections[mCurIntersection - 1]->p.x > mCurLine)) mCurIntersection--;
    } else {
        qbackTimer->stop();
    }
    update();
}


void Area::backsteps() {
    forwardTimer->stop();
    qforwardTimer->stop();
    qbackTimer->stop();
    backTimer->start(timerSpeed);
}


void Area::forwardsteps() {
    backTimer->stop();
    qforwardTimer->stop();
    qbackTimer->stop();
    forwardTimer->start(timerSpeed);
}

void Area::qbacksteps() {
    qforwardTimer->stop();
    forwardTimer->stop();
    backTimer->stop();
    qbackTimer->start(qtimerSpeed);
}


void Area::qforwardsteps() {
    qbackTimer->stop();
    forwardTimer->stop();
    backTimer->stop();
    qforwardTimer->start(qtimerSpeed);
}




void Area::pause() {
    backTimer->stop();
    forwardTimer->stop();
    qbackTimer->stop();
    qforwardTimer->stop();
}

void Area::stop() {

    forwardTimer->stop();
    backTimer->stop();
    qforwardTimer->stop();
    qbackTimer->stop();
    mCurLine = 0;

    mIntersections.clear();
    mSegments.clear();
    mCurIntersection = -1;

    update();
}

void Area::finish() {

    forwardTimer->stop();
    backTimer->stop();
    qforwardTimer->stop();
    qbackTimer->stop();

    mCurIntersection = mIntersections.size() - 1;
    mCurLine = width();

    update();
}


void Area::generetePoints(int numSegments, bool vert, bool multi, bool full) {

    mSegments.clear();

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

    if (mSegments.size() == 0) {
        mIntersections.clear();
        emit generationfail();
    } else {
        //intersection(mSegments, mIntersections);
    }

    update();

}

void Area::load(QString file) {

    mSegments.clear();

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
            mSegments.clear();
            mIntersections.clear();
            emit generationfail();
            return;
        }

    }

    if (maxX > width()) {
        for (int i = 0; i < numSegments; i++) {
            mSegments[i]->p.x = mSegments[i]->p.x / maxX * width();
            mSegments[i]->q.x = mSegments[i]->q.x / maxX * width();
        }
    }

    if (maxY > height()) {
        for (int i = 0; i < numSegments; i++) {
            mSegments[i]->p.y = mSegments[i]->p.y / maxY * height();
            mSegments[i]->q.y = mSegments[i]->q.y / maxY * height();
        }
    }

    mCurIntersection = -1;
    if (mSegments.size() == 0) {
        mIntersections.clear();
        emit generationfail();
    } else {
        intersection(mSegments, mIntersections);
    }
    update();
}

void Area::save(QString file) {

    std::ofstream fout(file.toAscii().data());

    fout << mSegments.size() << std::endl;

    for (int i = 0; i < mSegments.size(); i++) {

        fout << mSegments[i]->p.x << std::endl;
        fout << mSegments[i]->p.y << std::endl;
        fout << mSegments[i]->q.x << std::endl;
        fout << mSegments[i]->q.y << std::endl;
    }
}

void Area::saveresult(QString file) {

    std::ofstream fout(file.toAscii().data());

    fout << mIntersections.size() << std::endl;

    for (int i = 0; i < mIntersections.size(); i++) {

        fout << mIntersections[i]->p.x << " ";
        fout << mIntersections[i]->p.y << " ";
    }
}


Area::~Area() {
}


  void Area::paintEvent(QPaintEvent *event) {

      QPainter painter(this);
      draw(&painter);
  }

  void Area::undo() {

      if (history.size() > 0) {
          future.push_back(history.back());
          history.pop_back();
      }

      update();
  }

  void Area::redo() {

      if (future.size() > 0) {
          history.push_back(future.back());
          future.pop_back();
      }

      update();

  }

  void Area::draw() {
      drawMode = true;
      update();
  }

  void Area::stopdraw(){
      drawMode = false;
      mSegments.clear();
      for (std::list<Segment*>::iterator it = history.begin(); it != history.end(); ++it)
          mSegments.push_back(*it);

      history.clear();
      future.clear();
      mCurIntersection = -1;
      if (mSegments.size() == 0) {
          emit generationfail();
      } else {
          intersection(mSegments, mIntersections);
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
          history.push_back(new Segment(*mCurDrawPoint, Point2d(event->x(), event->y())));
          mCurDrawPoint = NULL;
          mCurDrawingPoint = NULL;
      }
  }

  void Area::draw(QPainter *painter) {

      if (! drawMode) {

          QPen blackPen(Qt::black, 2);
          QPen greenPen(Qt::green, 2);
          QPen orangePen(Qt::darkYellow, 2);

          for (int i = 0; i < mSegments.size(); i++) {

              if ((mCurLine > -1 ) && (mCurLine < width()) &&
                      (((mSegments[i]->p.x < mCurLine) && (mCurLine < mSegments[i]->q.x)) ||
                      ((mSegments[i]->q.x < mCurLine) && (mCurLine < mSegments[i]->p.x)))) {
                  painter->setPen(greenPen);
              } else {
                  if (mSuperSegments.count(i) > 0) painter->setPen(orangePen);
                  else painter->setPen(blackPen);
              }

              painter->drawLine(mSegments[i]->p.x, mSegments[i]->p.y, mSegments[i]->q.x, mSegments[i]->q.y);
          }

          if ((mCurIntersection > -1 ) && (mCurLine < width() ) ) {
              QPen magentaPen(Qt::magenta, 2);
              painter->setPen(magentaPen);
              painter->drawLine(mIntersections[mCurIntersection]->seg1->p.x, mIntersections[mCurIntersection]->seg1->p.y, mIntersections[mCurIntersection]->seg1->q.x, mIntersections[mCurIntersection]->seg1->q.y);
              painter->drawLine(mIntersections[mCurIntersection]->seg2->p.x, mIntersections[mCurIntersection]->seg2->p.y, mIntersections[mCurIntersection]->seg2->q.x, mIntersections[mCurIntersection]->seg2->q.y);
          }

          QPen pointPen(Qt::red, 3);
          painter->setPen(pointPen);
          for (int i = 0; ((i <= mCurIntersection) && (mIntersections[i]->p.x <= mCurLine)) ; i++) {
              painter->drawEllipse(mIntersections[i]->p.x, mIntersections[i]->p.y, 3, 3);
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
          for (std::list<Segment*>::iterator it = history.begin(); it != history.end(); ++it) {
              painter->drawLine((*it)->p.x, (*it)->p.y, (*it)->q.x, (*it)->q.y);
          }

          QPen bluePen(Qt::blue, 2);
          painter->setPen(bluePen);
          if ((mCurDrawPoint != NULL) && (mCurDrawingPoint != NULL)) {
                  painter->drawLine(mCurDrawPoint->x, mCurDrawPoint->y, mCurDrawingPoint->x, mCurDrawingPoint->y);
          }
      }
  }





