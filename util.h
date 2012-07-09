#ifndef MYUTIL_H
#define MYUTIL_H
#define EPS 1E-9

struct Point2d {
    double x;
    double y;

    Point2d() {
    }

    Point2d(int x, int y) {
        this->x = x;
        this->y = y;
    }
};

struct Segment {
    Point2d p;
    Point2d q;

    Segment() {
    }

    Segment(Point2d p, Point2d q) {
        this->p = p;
        this->q = q;
    }

    bool equal(Segment* s) {
        return ((this->p.x == s->p.x) && (this->p.y == s->p.y) && (this->q.x == s->q.x) && (this->q.y == s->q.y));
    }

    double get_bott(double x) const {
            if (abs (p.x - q.x) < EPS)  return p.y;
            return p.y + (q.y - p.y) * (x - p.x) / (q.x - p.x);
    }
};

struct Intersection {
    Point2d p;
    Segment seg1;
    Segment seg2;


    Intersection() {
    }

    Intersection(Point2d p, Segment seg1, Segment seg2) {
        this->p = p;
        this->seg1 = seg1;
        this->seg2 = seg2;
    }

    Intersection(Point2d p, Segment* seg1, Segment* seg2) {
        this->p = p;
        this->seg1 = Segment(seg1->p, seg1->q);
        this->seg2 = Segment(seg2->p, seg2->q);
    }

};



#endif // UTIL_H
