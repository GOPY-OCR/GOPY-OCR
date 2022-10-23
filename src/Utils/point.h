typedef struct {
    int x;
    int y;
} Point;

typedef struct {
    Point p1;
    Point p2;
} Rect;

typedef struct {
    int x;
    int y;
    int w;
    int h;
} Rect2;

typedef struct {
    Point p1;
    Point p2;
    float angle;
} TiltedRect;
