#ifndef INTERSECTION_H
#define INTERSECTION_H

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
        if(segments[i]->p.x > segments[i]->q.x)
            std::swap(segments[i]->p, segments[i]->q);
        else if(segments[i]->p.x == segments[i]->q.x){
            if(segments[i]->p.y > segments[i]->q.y)
                std::swap(segments[i]->p, segments[i]->q);
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
    int counter=1, id2;
    for (size_t i=0; i<e.size(); ++i) {
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
                for(size_t j=i+1;j<e.size() - 1; j++) {
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
        else {
            qDebug("FAP");
        }
    }

    std::sort(intersections.begin(), intersections.end(), compIntersections);
}



#endif // INTERSECTION_H
