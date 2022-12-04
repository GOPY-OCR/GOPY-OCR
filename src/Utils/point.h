#pragma once

typedef struct{
    int x;
    int y;
} Point;

typedef struct{
    Point p1;
    Point p2;
} Rect;

typedef struct{
    int x;
    int y;
    int w;
    int h;
} Rect2;

typedef struct{
    Point p1;
    Point p2;
    double angle;
} TiltedRect;

typedef struct{
    Point p1;
    Point p2;
} Line;

typedef struct{
    Point p1;
    Point p2;
    Point p3;
    Point p4;
} Quad; // Quadrilateral (not straight rectangle)


Rect2 Rect_toRect2(Rect r);
Rect Rect2_toRect(Rect2 r);
Rect Rect_fromPoints(Point p1, Point p2);
int Point_equals(Point p1, Point p2);
int Rect_equals(Rect r1, Rect r2);

int Rect_Area(Rect r);
int Rect_Collides(Rect r1, Rect r2);
