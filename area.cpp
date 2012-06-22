#include "area.h"
#include <iostream>
#include <fstream>
#include <set>
#include <algorithm>

bool compIntersections(Intersection* int1, Intersection* int2) {
    return (int1->p.x < int2->p.x);
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


void intersection(std::vector<Segment*> &segments, std::vector<Intersection*> &intersections) {
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
    std::set<Segment*> s_segs;
    std::vector< std::set<Segment*>::iterator > where;
    std::vector<Segment*>::iterator to_find;
    where.resize (segments.size());

    int id2;
    for (size_t i=0; i<e.size(); ++i) {
        qDebug("Beginning");
        int id = e[i].id;
        if (e[i].tp == +1) {
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
            where[id] = s_segs.insert (s1, segments[id]);
        }
        else if(e[i].tp == -1){
            std::set<Segment*>::iterator s = where[id], tmp2 = where[id], tih = where[id];
            tih++;
            std::set<Segment*>::iterator s1 = tih;
            std::set<Segment*>::iterator s2 = (tmp2==s_segs.begin()) ? s_segs.end(): --tmp2;
            if (s1 != s_segs.end() && s2 != s_segs.end() && intersect (*s1, *s2)) {
                Point2d p(find_point(*s1, *s2));
                if(p.x > e[i].x) {
                    if (p.x < e[e.size()-1].x)
                        qDebug("fine");
                    intersections.push_back(new Intersection(p, *s1, *s2));
                    qDebug("INN");
                    for(size_t j=i+1;j<e.size() - 1; j++) {
                        qDebug("searching");
                        if(e[j+1].x >= p.x)
                        {
                            if (p.x < e[j+1].x && p.x > e[j].x)
                                qDebug("VFine");
                            to_find=find(segments.begin(), segments.end(), (*s1));
                            if(to_find==segments.end())
                                break;
                            id = to_find - segments.begin();
                            to_find=find(segments.begin(), segments.end(), (*s2));
                            if(to_find==segments.end())
                                break;
                            id2 = to_find - segments.begin();
                            qDebug("inserting");
                            e.insert(e.begin() + j, event(p.x, 0, id, id2));
                            qDebug("inserted");
                            break;
                        }
                    }
                }
                qDebug("Finished");
            }
//            if (s1 != s_segs.end() && tih != s1 && intersect (*s1, *tih)) {
//                Point2d p(find_point(*s1, *tih));
//                intersections.push_back(new Intersection(p, *s1, *tih));
//            }
//            if (s2 != s_segs.end() && tih != s2 && intersect (*s2, *tih)) {
//                Point2d p(find_point(*s1, *tih));
//                intersections.push_back(new Intersection(p, *s2, *tih));
//            }
            s_segs.erase(s);
        }
        else {
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
                qDebug("Finished");
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
                qDebug("Finished");
            }
            std::swap(where[e[i].id], where[e[i].id2]);
            std::swap(s1, s2);
        }
    }

    std::sort(intersections.begin(), intersections.end(), compIntersections);
}

Area::Area(QWidget *parent) :
    QWidget(parent) {

    mCurIntersection = -1;

    forwardTimer = new QTimer(this);
    backTimer = new QTimer(this);
    timerSpeed = 500;

    connect(forwardTimer, SIGNAL(timeout()), this, SLOT(forwardstep()));
    connect(backTimer, SIGNAL(timeout()), this, SLOT(backstep()));
}

void Area::forwardstep() {


    if (mCurIntersection < (int)(mIntersections.size() - 1)) {
        mCurIntersection++;
    } else {
        forwardTimer->stop();
    }

    update();
}

void Area::backstep() {
    if (mCurIntersection > 0) {
        mCurIntersection--;
    } else {
        backTimer->stop();
        mCurIntersection = -1;
    }
    update();
}

void Area::backsteps() {
    forwardTimer->stop();
    backTimer->start(timerSpeed);
}


void Area::forwardsteps() {
    backTimer->stop();
    forwardTimer->start(timerSpeed);
}

void Area::pause() {
    backTimer->stop();
    forwardTimer->stop();
}

void Area::stop() {

    forwardTimer->stop();
    backTimer->stop();

    mIntersections.clear();
    mSegments.clear();
    mCurIntersection = -1;

    update();
}

void Area::finish() {

    forwardTimer->stop();
    backTimer->stop();

    mCurIntersection = mIntersections.size() - 1;

    update();
}

void Area::generetePoints(int numSegments) {

    mSegments.clear();

    for (int i = 0; i < numSegments; i++) {
        Segment* s = new Segment(Point2d(rand()%width(), rand()%height()), Point2d(rand()%width(), rand()%height()));
        mSegments.push_back(s);
    }

    mCurIntersection = -1;
    intersection(mSegments, mIntersections);

}

void Area::load(QString file) {

    mSegments.clear();

    int numSegments;
    int x1, y1, x2, y2;
    int maxX = 0, maxY = 0;

    std::ifstream fin(file.toAscii().data());

    fin >> numSegments;

    for (int i = 0; i < numSegments; i++) {
        fin >> x1;
        fin >> y1;
        fin >> x2;
        fin >> y2;

        if (x1 > maxX) maxX = x1;
        if (y1 > maxY) maxY = y1;
        if (x2 > maxX) maxX = x2;
        if (y2 > maxY) maxY = y2;

        Segment* s = new Segment(Point2d(x1, y1), Point2d(x2, y2));
        mSegments.push_back(s);
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
    intersection(mSegments, mIntersections);
}

void Area::save(QString file) {

    std::ofstream fout(file.toAscii().data());

    fout << mSegments.size() << std::endl;

    for (size_t i = 0; i < mSegments.size(); i++) {

        fout << mSegments[i]->p.x << " ";
        fout << mSegments[i]->p.y << " ";
        fout << mSegments[i]->q.x << " ";
        fout << mSegments[i]->q.y << std::endl;
    }


}

Area::~Area() {
}

void Area::paintEvent(QPaintEvent *event) {

    QPainter painter(this);
    draw(&painter);
}

void Area::draw(QPainter *painter) {

    QPen blackPen(Qt::black, 2);
    QPen greenPen(Qt::green, 2);

    for (size_t i = 0; i < mSegments.size(); i++) {

        if ((mCurIntersection > -1 ) && (mCurIntersection < mIntersections.size() - 1 ) &&
                (((mSegments[i]->p.x < mIntersections[mCurIntersection]->p.x) && (mIntersections[mCurIntersection]->p.x < mSegments[i]->q.x)) ||
                ((mSegments[i]->q.x < mIntersections[mCurIntersection]->p.x) && (mIntersections[mCurIntersection]->p.x < mSegments[i]->p.x)))) {
            painter->setPen(greenPen);
        } else {
            painter->setPen(blackPen);
        }

        painter->drawLine(mSegments[i]->p.x, mSegments[i]->p.y, mSegments[i]->q.x, mSegments[i]->q.y);
    }

    if ((mCurIntersection > -1 ) && (mCurIntersection < mIntersections.size() - 1 ) ) {
        QPen magentaPen(Qt::magenta, 2);
        painter->setPen(magentaPen);
        painter->drawLine(mIntersections[mCurIntersection]->seg1->p.x, mIntersections[mCurIntersection]->seg1->p.y, mIntersections[mCurIntersection]->seg1->q.x, mIntersections[mCurIntersection]->seg1->q.y);
        painter->drawLine(mIntersections[mCurIntersection]->seg2->p.x, mIntersections[mCurIntersection]->seg2->p.y, mIntersections[mCurIntersection]->seg2->q.x, mIntersections[mCurIntersection]->seg2->q.y);
    }

    QPen pointPen(Qt::red, 3);
    painter->setPen(pointPen);
    for (int i = 0; i <= mCurIntersection; i++) {
        painter->drawEllipse(mIntersections[i]->p.x, mIntersections[i]->p.y, 3, 3);
    }

    QPen bluePen(Qt::blue, 3);
    painter->setPen(bluePen);

    if (mCurIntersection == -1) {
        painter->drawLine(0, 0, 0, height() );
        painter->setOpacity(0.5);
        painter->fillRect(0, 0, width(), height(), Qt::gray);
    } else {
        if (mCurIntersection == mIntersections.size() - 1) {
            painter->drawLine(width(), 0, width(), height() );
        } else {
            painter->drawLine(mIntersections[mCurIntersection]->p.x, 0, mIntersections[mCurIntersection]->p.x, height() );
            painter->setOpacity(0.5);
            painter->fillRect(mIntersections[mCurIntersection]->p.x, 0, width(), height(), Qt::gray);
        }

    }
}


