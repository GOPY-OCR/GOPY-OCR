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
    float angle;
} TiltedRect;

typedef struct{
    Point p1;
    Point p2;
} Line;


Rect2 Rect_toRect2(Rect r);
Rect Rect2_toRect(Rect2 r);
Rect Rect_fromPoints(Point p1, Point p2);
