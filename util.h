#ifndef UTIL_H
#define UTIL_H
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

    double get_bott(double x) const {
            if (abs (p.x - q.x) < EPS)  return p.y;
            return p.y + (q.y - p.y) * (x - p.x) / (q.x - p.x);
    }
//    bool operator< (const Segment & b) {
//            double x = std::max (std::min (this->p.x, this->q.x), std::min (b.p.x, b.q.x));
//            return this->get_bott(x) < b.get_bott(x) - EPS;
//    }
};
//bool operator< (const Segment & a, const Segment & b) {
//        double x = std::max (std::min (a.p.x, a.q.x), std::min (b.p.x, b.q.x));
//        return a.get_bott(x) < b.get_bott(x) - EPS;
//}
struct Intersection {
    Point2d p;
    Segment* seg1;
    Segment* seg2;


    Intersection() {
    }

    Intersection(Point2d p, Segment* seg1, Segment* seg2) {
        this->p = p;
        this->seg1 = seg1;
        this->seg2 = seg2;
    }
};



#endif // UTIL_H
