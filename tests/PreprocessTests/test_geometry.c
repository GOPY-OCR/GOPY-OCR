#include "point.h"
#include "geometry.h"

Test(geometry, test_line_intersection) {
    Line line1 = (Line){(Point){0, 0}, (Point){2, 8}};
    Line line2 = (Line){(Point){0, 1}, (Point){0, 20}};
    Point intersection = line_intersection(line1, line2);
    cr_assert_eq(intersection.x, -1, "Expected x to be -1, got %d", intersection.x);
    cr_assert_eq(intersection.y, -1, "Expected y to be -1, got %d", intersection.y);

    line1 = (Line){(Point){0, 10}, (Point){2, 0}};
    line2 = (Line){(Point){10, 0}, (Point){0, 5}};
    intersection = line_intersection(line1, line2);
    cr_assert_eq(intersection.x, 1);
    cr_assert_eq(intersection.y, 4);

    line1 = (Line){(Point){1, 1}, (Point){2, 2}};
    line2 = (Line){(Point){1, 2}, (Point){2, 1}};
    intersection = line_intersection(line1, line2);
    cr_assert_eq(intersection.x, 1);
    cr_assert_eq(intersection.y, 1);
}
