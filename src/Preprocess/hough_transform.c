#include "hough_transform.h"

#define HARDCODED_PEAK_CANCEL_RADIUS_RHO 5
#define HARDCODED_PEAK_CANCEL_RADIUS_THETA 15

#define ROTATION_DETECTION_LINE_COUNT 10 // only keeps the 10 strongest lines for rotation detection
int detect_grid_rotation(Line *lines) {
    // this function assumes that there are at least ROTATION_DETECTION_LINE_COUNT lines in the array
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
    float width = image->w;
    float height = image->h;

    // pythagorean theorem to calculate the diagonal
    float d = sqrt(width*width + height*height);

    float num_thetas = 180;
    float num_rhos = d * 2;

    // step sizes
    float dtheta = 180.0 / num_thetas;
    float drho = (2*d) / num_rhos;

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
            draw_line(image, cartesian_lines[i], DEBUG_SDL_COLOR);
        }
    }

    array_free(thetas);
    array_free(rhos);
    matrice_free(accumulator);
    free(lines);

    return cartesian_lines;
}

matrice *create_hough_space_matrice(SDL_Surface *image, 
                                    array *thetas, 
                                    array *rhos, 
                                    float d, 
                                    float drho){
    matrice *accumulator = matrice_zeros(rhos->size, thetas->size);

    // precompute the sin and cos values of thetas
    array *cos_thetas = array_map(thetas, cos_degree);
    array *sin_thetas = array_map(thetas, sin_degree);
    

    float rho;
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

