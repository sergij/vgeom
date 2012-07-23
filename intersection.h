#ifndef INTERSECTION_H
#define INTERSECTION_H

#include "area.h"
#include <iostream>
#include <fstream>
#include <set>
#include <algorithm>
double XxX=0;
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
    if(a->p.x==a->q.x) return Point2d(a->p.x, b->get_y(a->p.x));
    if(b->p.x==b->q.x) return Point2d(b->p.x, a->get_y(b->p.x));
    return Point2d(x, y);
}

struct event {
        double x, y;
        int tp, id, id2;

        event() { }
        event (double x, double y, int tp, int id, int id2=0)
            : x(x), tp(tp), id(id), id2(id2)
        { }

        bool operator< (const event & e) const {
            if (abs (this->x - e.x) > EPS)
                return this->x < e.x;
            if (abs (this->y - e.y) > EPS)
                return this->y < e.y;
            return tp > e.tp;
        }
};


struct ltstr
{
  bool operator()(const Segment * a, const Segment * b) const {
      return a->get_y(XxX) < b->get_y(XxX) - EPS;
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
        e.push_back (event (segments[i]->p.x, segments[i]->p.y, +1, i));
        e.push_back (event (segments[i]->q.x, segments[i]->p.y, -1, i));
    }
    std::stable_sort(e.begin(), e.end());
    std::set<Segment*, ltstr> s_segs;
    std::vector< std::set<Segment*>::iterator > where;
    std::vector<Segment*>::iterator to_find;
    where.resize (segments.size());

    int id2;
    for (size_t i=0; i<e.size(); ++i) {

        int id = e[i].id;
        XxX = e[i].x;

        std::cout << e[i].tp << std::endl;
        if (e[i].tp == +1) {
            std::set<Segment*>::iterator s1 = s_segs.lower_bound (segments[id]);
            std::set<Segment*>::iterator nxt2 = s_segs.lower_bound (segments[id]);
            std::set<Segment*>::iterator s2 = (s1==s_segs.begin()) ? s_segs.end(): --nxt2;

            if (s1 != s_segs.end() && intersect(*s1, segments[id])){
                Point2d p(find_point(*s1, segments[id]));
                intersections.push_back(new Intersection(p, *s1, segments[id]));
                to_find=find(segments.begin(), segments.end(), (*s1));
                id2 = to_find - segments.begin();
                e.push_back(event(p.x, p.y, 0, id2, id));
                std::stable_sort(e.begin(), e.end());
            }
            if (s2 != s_segs.end() && intersect(*s2, segments[id]) ) {
                Point2d p(find_point(*s2, segments[id]));
                intersections.push_back(new Intersection(p, *s2, segments[id]));
                to_find=find(segments.begin(), segments.end(), (*s2));
                id2 = to_find - segments.begin();
                e.push_back(event(p.x, p.y, 0, id2, id));
                std::stable_sort(e.begin(), e.end());
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
                    intersections.push_back(new Intersection(p, *s1, *s2));
                    to_find=find(segments.begin(), segments.end(), (*s1));
                    id = to_find - segments.begin();
                    to_find=find(segments.begin(), segments.end(), (*s2));
                    id2 = to_find - segments.begin();
                    e.push_back(event(p.x, p.y, 0, id, id2));
                    std::stable_sort(e.begin(), e.end());
                }
            }
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
                    to_find=find(segments.begin(), segments.end(), (*s3));
                    id = to_find - segments.begin();
                    to_find=find(segments.begin(), segments.end(), (*s2));
                    id2 = to_find - segments.begin();
                    e.push_back(event(p.x, p.y, 0, id, id2));
                    std::stable_sort(e.begin(), e.end());
                }
            }
            if (s1 != s_segs.end() && s4 != s_segs.end() && intersect (*s1, *s4)) {
                Point2d p(find_point(*s1, *s4));
                if(p.x > e[i].x) {
                    intersections.push_back(new Intersection(p, *s1, *s4));
                    to_find=find(segments.begin(), segments.end(), (*s1));
                    id = to_find - segments.begin();
                    to_find=find(segments.begin(), segments.end(), (*s4));
                    id2 = to_find - segments.begin();
                    e.push_back(event(p.x, p.y, 0, id, id2));
                    std::stable_sort(e.begin(), e.end());
                }
            }
            where[e[i].id] = s1;
            where[e[i].id2] = s2;

        }
    }

    std::sort(intersections.begin(), intersections.end(), compIntersections);
}

#endif // INTERSECTION_H
