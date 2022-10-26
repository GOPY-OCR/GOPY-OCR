#pragma once
#include "point.h"
#include "stdlib.h"
#include "array.h"
#include "maths.h"
#include <math.h>

// returns the intersection point of two lines
// or (-1,-1) if there are no intersection
// 
// note that this function will return (-1, -1) even
// if your two lines collide at (0,0)
Point line_intersection(Line line1, Line line2);

// Finds all the rectangles formed by the lines
Rect *find_rects(Line *lines, int nb_lines, int *nb_rects);


// Converts an array of points in the hough space
// to an array of lines in cartesian space
Line *hough_lines_to_lines(Point *lines,
                           int nb_lines,
                           array *thetas,
                           array *rhos,
                           double d);



int median_line_angle(Line *lines, int nb_lines);

Line *hough_lines_to_lines(Point *lines,
                           int nb_lines,
                           array *thetas,
                           array *rhos,
                           double d);
