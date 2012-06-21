#ifndef UTIL_H
#define UTIL_H

struct Point2d {
    int x;
    int y;

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
};



#endif // UTIL_H
