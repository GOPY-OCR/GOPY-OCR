#include "point.h"

Rect2 Rect_toRect2(Rect r) {
    return (Rect2) {r.p1.x, r.p1.y, r.p2.x - r.p1.x, r.p2.y - r.p1.y};
}

Rect Rect2_toRect(Rect2 r) {
    return (Rect) {{r.x, r.y}, {r.x + r.w, r.y + r.h}};
}
