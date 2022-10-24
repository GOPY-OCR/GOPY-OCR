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


Test(geometry, test_find_rects) {
    // 1 square test
    Line lines[4] = {
        (Line){(Point){1, 1}, (Point){10, 1}},
        (Line){(Point){1, 1}, (Point){1, 10}},
        (Line){(Point){1, 10}, (Point){10, 10}},
        (Line){(Point){10, 1}, (Point){10, 10}}
    };

    int num_rects = 0;
    Rect *rects = find_rects(lines, 4, &num_rects);
    cr_assert_eq(num_rects, 1, "Expected 1 rectangle, got %d", num_rects);
    cr_assert_eq(rects[0].p1.x, 1, "Expected x to be 1, got %d", rects[0].p1.x);
    cr_assert_eq(rects[0].p1.y, 1, "Expected y to be 1, got %d", rects[0].p1.y);
    cr_assert_eq(rects[0].p2.x, 10, "Expected x to be 10, got %d", rects[0].p2.x);
    cr_assert_eq(rects[0].p2.y, 10, "Expected y to be 10, got %d", rects[0].p2.y);

    // 9 square test (there are 36 rectangles)
    Line lines2[8] = {
        // vertical lines
        (Line){(Point){1, 1}, (Point){1, 10}},
        (Line){(Point){4, 1}, (Point){4, 10}},
        (Line){(Point){7, 1}, (Point){7, 10}},
        (Line){(Point){10, 1}, (Point){10, 10}},

        // horizontal lines
        (Line){(Point){1, 1}, (Point){10, 1}},
        (Line){(Point){1, 4}, (Point){10, 4}},
        (Line){(Point){1, 7}, (Point){10, 7}},
        (Line){(Point){1, 10}, (Point){10, 10}}
    };

    rects = find_rects(lines2, 8, &num_rects);
    cr_assert_eq(num_rects, 36, "Expected 36 rectangles, got %d", num_rects);

}
