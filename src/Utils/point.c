#include "point.h"

Rect2 Rect_toRect2(Rect r) {
    return (Rect2) {r.p1.x, r.p1.y, r.p2.x - r.p1.x, r.p2.y - r.p1.y};
}

Rect Rect2_toRect(Rect2 r) {
    return (Rect) {{r.x, r.y}, {r.x + r.w, r.y + r.h}};
}


Rect Rect_fromPoints(Point p1, Point p2) {
    Rect r = (Rect) {p1, p2};
    if (r.p1.x > r.p2.x) {
        int tmp = r.p1.x;
        r.p1.x = r.p2.x;
        r.p2.x = tmp;
    }
    if (r.p1.y > r.p2.y) {
        int tmp = r.p1.y;
        r.p1.y = r.p2.y;
        r.p2.y = tmp;
    }

    return r;
}

int Point_equals(Point p1, Point p2) {
    return p1.x == p2.x && p1.y == p2.y;
}

int Rect_equals(Rect r1, Rect r2) {
    return Point_equals(r1.p1, r2.p1) && Point_equals(r1.p2, r2.p2);
}

int Rect_Area(Rect r) {
    int area = (r.p2.x - r.p1.x) * (r.p2.y - r.p1.y);
    if(area <= 0)
        return 0; // probably an overflow. these cases should not matter for our purposes
    return (r.p2.x - r.p1.x) * (r.p2.y - r.p1.y);
}

int Rect_Collides(Rect r1, Rect r2) {
    return r1.p1.x < r2.p2.x && r1.p2.x > r2.p1.x && r1.p1.y < r2.p2.y && r1.p2.y > r2.p1.y;
}


