#include "hough_transform.h"

#define HARDCODED_PEAK_CANCEL_RADIUS_RHO 8
#define HARDCODED_PEAK_CANCEL_RADIUS_THETA 20
#define LINE_COLOR (SDL_Color){255, 0, 0, 255}


#define ROTATION_DETECTION_LINE_COUNT 10
int detect_grid_rotation(SDL_Surface *image) {
    Line *lines = find_image_lines(image, ROTATION_DETECTION_LINE_COUNT, 0);
    int rotation = median_line_angle(lines, ROTATION_DETECTION_LINE_COUNT);
    free(lines);

    if (rotation < 0) {
        rotation += 90;
    } else {
        rotation -= 90;
    }

    return -rotation;
}

// algorithm from
// https://towardsdatascience.com/lines-detection-with-hough-transform-84020b3b1549
Line *find_image_lines(SDL_Surface *image, int nb_lines, int draw_lines){
    double width = image->w;
    double height = image->h;

    // pythagorean theorem to calculate the diagonal
    double d = sqrt(width*width + height*height);

    double num_thetas = 180;
    double num_rhos = d * 2;

    // step sizes
    double dtheta = 180.0 / num_thetas;
    double drho = (2*d) / num_rhos;

    array *thetas = array_range(0, 180, dtheta);
    array *rhos = array_range(-d, d, drho);

    matrice *accumulator = create_hough_space_matrice(image, thetas, rhos, d, drho);

    // cancel the peaks that are too close to each other
    //int cancel_peak_radius = d * PEAK_CANCEL_RADIUS_RATIO;

    // finds the top nb_lines peaks in the accumulator
    // lines are represented by a point in the hough space
    // Point->x is the rho index and Point->y is the theta index
    Point *lines = find_peaks(accumulator, nb_lines, HARDCODED_PEAK_CANCEL_RADIUS_RHO, HARDCODED_PEAK_CANCEL_RADIUS_THETA);

    Line *cartesian_lines = hough_lines_to_lines(lines, nb_lines, thetas, rhos, d);
    if (draw_lines){
        for (int i = 0; i < nb_lines; i++){
            draw_line(image, cartesian_lines[i], LINE_COLOR);
        }
    }

    array_free(thetas);
    array_free(rhos);

    return cartesian_lines;
}

matrice *create_hough_space_matrice(SDL_Surface *image, 
                                    array *thetas, 
                                    array *rhos, 
                                    double d, 
                                    double drho){
    matrice *accumulator = matrice_zeros(rhos->size, thetas->size);

    // precompute the sin and cos values of thetas
    array *cos_thetas = array_map(thetas, cos_degree);
    array *sin_thetas = array_map(thetas, sin_degree);
    

    double rho;
    size_t i;

    SDL_LockSurface(image);
    for (int x = 0; x < image->w; x++){
        for (int y = 0; y < image->h; y++){
            if (!is_pixel_white(image, x, y)){
                // ignore black pixels
                continue;
            }

            for (int j = 0; j < thetas->size; j++){
                rho = x * array_get(cos_thetas, j) + 
                      y * array_get(sin_thetas, j);

                i = (size_t) ((rho + d) / drho); // rho index

                *matrice_get_ref(accumulator, i, j) += 1;
            }
        }
    }

    SDL_UnlockSurface(image);    
    array_free(cos_thetas);
    array_free(sin_thetas);

    return accumulator;
}

Point *find_peaks(matrice *accumulator, int nb_lines, int cancel_radius_rho, int cancel_radius_theta){
    Point *lines = malloc(sizeof(Point) * nb_lines);

    for (int i = 0; i < nb_lines * 2; i++){
        int x, y;
        matrice_max(accumulator, &x, &y);
        Point *line = malloc(sizeof(Point));
        *line = (Point){x, y};
        // for some reason if i%2 == 1, the line is not good
        if (i%2 == 0){
            lines[i/2] = *line;
        }
        
        // cancel the neighborhood of the peak to prevent finding it again
        for (int j = -cancel_radius_rho; j < cancel_radius_rho; j++){
            for (int k = -cancel_radius_theta; k < cancel_radius_theta; k++){

                if (x + j < 0 || x + j >= accumulator->rows || 
                    y + k < 0 || y + k >= accumulator->columns){
                    // out of bounds
                    continue;
                }
                *matrice_get_ref(accumulator, x + j, y + k) = 0;
            }
        }
    }

    return lines;
}

void draw_line(SDL_Surface *image, 
               Line line,
               SDL_Color color){
    // algorithm found on https://rosettacode.org/wiki/Bitmap/Bresenham%27s_line_algorithm#C
    int dx = abs(line.p2.x - line.p1.x);
    int sx = line.p1.x < line.p2.x ? 1 : -1;
    int dy = -abs(line.p2.y - line.p1.y);
    int sy = line.p1.y < line.p2.y ? 1 : -1;
    int err = dx + dy;
    int e2;
    Uint32 pixel = SDL_MapRGBA(image->format, color.r, color.g, color.b, color.a);

    while (!(line.p1.x == line.p2.x && line.p1.y == line.p2.y)){
        if (line.p1.x >= 0 && line.p1.x < image->w && line.p1.y >= 0 && line.p1.y < image->h){
            putpixel(image, line.p1.x, line.p1.y, pixel);
        }
        e2 = 2 * err;
        if (e2 >= dy){
            err += dy;
            line.p1.x += sx;
        }
        if (e2 <= dx){
            err += dx;
            line.p1.y += sy;
        }
    }
    // modified the algorithm a bit to not have a while(1) loop
    // and instead draw the last pixel outside the loop
    if (line.p1.x >= 0 && line.p1.x < image->w && line.p1.y >= 0 && line.p1.y < image->h){
        putpixel(image, line.p1.x, line.p1.y, pixel);
    }
}
