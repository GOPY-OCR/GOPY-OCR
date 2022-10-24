#include "geometry.h"

// Finds all the rectangles formed by the lines
// and tries to find the sudoku grid among them
// by looking for the median rectangle area, and 
// selecting the nb_rects closest to it that don't 
// overlap
Rect *find_rects(Line *lines, int nb_lines, int nb_rects){
    Rect *rects = malloc(sizeof(Rect) * nb_rects);

    // find all the lines intersections
    // and store them in a list
    Point *intersections = malloc(sizeof(Point) * nb_lines * nb_lines);
    int nb_intersections = 0;
    for (int i = 0; i < nb_lines; i++){
        for (int j = i + 1; j < nb_lines; j++){
            Point intersection = line_intersection(lines[i], lines[j]);
            if (intersection.x != -1 && intersection.y != -1){
                intersections[nb_intersections] = intersection;
                nb_intersections++;
            }
        }
    }

    // find all the rectangles formed by the lines
    // and store them in a list
    Rect *all_rects = malloc(sizeof(Rect) * nb_intersections * nb_intersections);
    int nb_all_rects = 0;
    for (int i = 0; i < nb_intersections; i++){
        for (int j = i + 1; j < nb_intersections; j++){
            Rect rect = Rect_fromPoints(intersections[i], intersections[j]);
            all_rects[nb_all_rects] = rect;
            nb_all_rects++;
        }
    }

    return rects;
}

Point line_intersection(Line line1, Line line2){
    // formula found on https://en.wikipedia.org/wiki/Line%E2%80%93line_intersection#Given_two_points_on_each_line
    double x1 = line1.p1.x;
    double y1 = line1.p1.y;
    double x2 = line1.p2.x;
    double y2 = line1.p2.y;
    double x3 = line2.p1.x;
    double y3 = line2.p1.y;
    double x4 = line2.p2.x;
    double y4 = line2.p2.y;

    double denom = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);

    if (denom == 0){
        return (Point){-1, -1};
    }

    double x = ((x1 * y2 - y1 * x2) * (x3 - x4) - (x1 - x2) * (x3 * y4 - y3 * x4)) / denom;
    double y = ((x1 * y2 - y1 * x2) * (y3 - y4) - (y1 - y2) * (x3 * y4 - y3 * x4)) / denom;

    if (x <= 0 || y <= 0){
        return (Point){-1, -1};
    }

    int xi = (int) x + 0.5;
    int yi = (int) y + 0.5;

    return (Point){xi, yi};
}
