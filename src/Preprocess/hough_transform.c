#include "hough_transform.h"

#define PEAK_CANCEL_RADIUS_RATIO 0.1

// algorithm from
// https://towardsdatascience.com/lines-detection-with-hough-transform-84020b3b1549
Rect find_sudoku_grid(SDL_Surface *image, int nb_lines, int draw_lines){
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
    int cancel_peak_radius = d * PEAK_CANCEL_RADIUS_RATIO;

    // finds the top nb_lines peaks in the accumulator
    // lines are represented by a point in the hough space
    // Point->x is the rho index and Point->y is the theta index
    Point *lines = find_peaks(accumulator, nb_lines, cancel_peak_radius);

    if (draw_lines){
        draw_hough_lines_on_image(image, lines, nb_lines, thetas, rhos, d);
    }

    //Rect rect = find_sudoku_rect(image, lines, nb_lines, thetas, rhos, d);
    Rect rect = (Rect){(Point){0, 0}, (Point){0, 0}};

    array_free(thetas);
    array_free(rhos);

    return rect;
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

Point *find_peaks(matrice *accumulator, int nb_lines, int cancel_radius){
    Point *lines = malloc(sizeof(Point) * nb_lines);

    for (int i = 0; i < nb_lines; i++){
        int x, y;
        matrice_max(accumulator, &x, &y);
        Point *line = malloc(sizeof(Point));
        *line = (Point){x, y};
        lines[i] = *line;
        
        // cancel the neighborhood of the peak to prevent finding it again
        for (int j = -cancel_radius; j < cancel_radius; j++){
            for (int k = -cancel_radius; k < cancel_radius; k++){

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

#define LINE_COLOR (SDL_Color){255, 0, 0, 255}
void draw_hough_lines_on_image(SDL_Surface *image, 
                               Point *lines, 
                               int nb_lines,
                               array *thetas, 
                               array *rhos, 
                               double d){

    SDL_LockSurface(image);

    for (int i = 0; i < nb_lines; i++){
        Point line = lines[i];
        double theta = array_get(thetas, line.y);
        double rho = array_get(rhos, line.x);

        // convert coordinates from hough space to cartesian space
        double a = cos_degree(theta);
        double b = sin_degree(theta);
        double x0 = a * rho;
        double y0 = b * rho;

        int x1 = (int) (x0 + d * (-b));
        int y1 = (int) (y0 + d * (a));
        int x2 = (int) (x0 - d * (-b));
        int y2 = (int) (y0 - d * (a));

        draw_line(image, x1, y1, x2, y2, LINE_COLOR);
    }

    SDL_UnlockSurface(image);
}


void draw_line(SDL_Surface *image, 
               int x1, 
               int y1, 
               int x2, 
               int y2, 
               SDL_Color color){
    // algorithm found on https://rosettacode.org/wiki/Bitmap/Bresenham%27s_line_algorithm#C
    int dx = abs(x2 - x1);
    int sx = x1 < x2 ? 1 : -1;
    int dy = -abs(y2 - y1);
    int sy = y1 < y2 ? 1 : -1;
    int err = dx + dy;
    int e2;
    Uint32 pixel = SDL_MapRGBA(image->format, color.r, color.g, color.b, color.a);

    while (!(x1 == x2 && y1 == y2)){
        if (x1 >= 0 && x1 < image->w && y1 >= 0 && y1 < image->h){
            putpixel(image, x1, y1, pixel);
        }
        e2 = 2 * err;
        if (e2 >= dy){
            err += dy;
            x1 += sx;
        }
        if (e2 <= dx){
            err += dx;
            y1 += sy;
        }
    }
    // modified the algorithm a bit to not have a while(1) loop
    // and instead draw the last pixel outside the loop
    if (x1 >= 0 && x1 < image->w && y1 >= 0 && y1 < image->h){
        putpixel(image, x1, y1, pixel);
    }
}
