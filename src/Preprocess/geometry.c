#include "geometry.h"


Rect *find_rects(Line *lines, int nb_lines, int *nb_rects) {
    // find all the lines intersections
    // and store them in a list
    int nb_intersections = 0;
    Point *intersections = find_intersections(lines, nb_lines, &nb_intersections);

    // find all the rectangles formed by the lines
    // and store them in a list
    Rect *rects = malloc(sizeof(Rect) * nb_intersections * nb_intersections);
    *nb_rects = 0;
    for (int i = 0; i < nb_intersections; i++){
        for (int j = i + 1; j < nb_intersections; j++){
            Rect rect = Rect_fromPoints(intersections[i], intersections[j]);

            if (rect.p1.x == rect.p2.x || rect.p1.y == rect.p2.y)
                continue;

            rects[*nb_rects] = rect;
            (*nb_rects)++;
        }
    }

    // remove duplicates
    for (int i = 0; i < *nb_rects; i++){
        for (int j = i + 1; j < *nb_rects; j++){
            if (Rect_equals(rects[i], rects[j])){
                rects[j] = rects[*nb_rects - 1];
                (*nb_rects)--;
                j--;
            }
        }
    }

    free(intersections);

    return rects;
}

Point *find_intersections(Line *lines, int nb_lines, int *nb_intersections) {
    // find all the lines intersections
    // and store them in a list
    Point *intersections = malloc(sizeof(Point) * nb_lines * nb_lines);
    *nb_intersections = 0;
    for (int i = 0; i < nb_lines; i++){
        for (int j = i + 1; j < nb_lines; j++){
            Point intersection = line_intersection(lines[i], lines[j]);
            if (intersection.x != -1 && intersection.y != -1){
                intersections[*nb_intersections] = intersection;
                (*nb_intersections)++;
            }
        }
    }

    // remove duplicates
    for (int i = 0; i < *nb_intersections; i++){
        for (int j = i + 1; j < *nb_intersections; j++){
            if (Point_equals(intersections[i], intersections[j])){
                intersections[j] = intersections[*nb_intersections - 1];
                (*nb_intersections)--;
                j--;
            }
        }
    }

    intersections = realloc(intersections, sizeof(Point) * (*nb_intersections));

    return intersections;
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

// Returns the median angle of the vertical lines
// this is used to rotate the image 
int median_line_angle(Line *lines, int nb_lines){
    int *angles = malloc(sizeof(int) * nb_lines);
    int nb_angles = 0;
    for (int i = 0; i < nb_lines; i++){

        if (lines[i].p1.x == lines[i].p2.x && lines[i].p1.y == lines[i].p2.y)
            // line is a point
            continue;

        int dx = lines[i].p2.x - lines[i].p1.x;
        int dy = lines[i].p2.y - lines[i].p1.y;


        if (intabs(dx) < intabs(dy)){
            // this line has an angle between -45 and 45 degrees
            if (dx < 0){
                dx = -dx;
                dy = -dy;
            }

            // compute the angle
            int angle = (int) (atan2(dy, dx) * 180 / M_PI);

            angles[nb_angles++] = angle;
        }
    }

    sort_int_array(angles, nb_angles);

    int median_angle = angles[nb_angles / 2];


    return median_angle;
}

Line *hough_lines_to_lines(Point *lines,
        int nb_lines,
        array *thetas,
        array *rhos,
        double d){
    Line *lines_out = malloc(sizeof(Line) * nb_lines);

    for (int i = 0; i < nb_lines; i++){
        double theta = array_get(thetas, lines[i].y);
        double rho = array_get(rhos, lines[i].x);

        // convert coordinates from hough space to cartesian space
        double a = cos_degree(theta);
        double b = sin_degree(theta);
        double x0 = a * rho;
        double y0 = b * rho;

        Point p1 = (Point){(int) (x0 + d * (-b)), (int) (y0 + d * a)};
        Point p2 = (Point){(int) (x0 - d * (-b)), (int) (y0 - d * a)};

        lines_out[i] = (Line){p1, p2};
    }

    return lines_out;
}
