#include "perspective_correction.h"

void perspective_correction(SDL_Surface **src, Quad *grid){
    SDL_Surface *dst = SDL_CreateRGBSurface(SDL_SWSURFACE, (*src)->w, (*src)->h, 32, 0, 0, 0, 0);
    SDL_LockSurface(*src);
    SDL_LockSurface(dst);
    
    for(int x = 0; x < (*src)->w; x++){
        for(int y = 0; y < (*src)->h; y++){
            Point p = {x, y};
            Point proj = get_perspective_point(p, grid, (*src)->w, (*src)->h);
            
            assert(proj.x >= 0 && proj.x < (*src)->w);
            assert(proj.y >= 0 && proj.y < (*src)->h);

            Uint32 *pixel = getpixel(*src, proj.x, proj.y);
            putpixel(dst, x, y, *pixel);
        }
    }

    SDL_UnlockSurface(*src);
    SDL_UnlockSurface(dst);

    SDL_FreeSurface(*src);
    *src = dst;
}

Point get_perspective_point(Point src, Quad *grid, int width, int height){
    float d = width * height;
    return (Point){
            grid->p1.x * (width-src.x)*(height-src.y)/d+ 
            grid->p2.x * src.x*(height-src.y)/d+ 
            grid->p3.x * (width-src.x)*src.y/d+ 
            grid->p4.x * src.x*src.y/d,
            grid->p1.y * (width-src.x)*(height-src.y)/d + 
            grid->p2.y * src.x*(height-src.y)/d + 
            grid->p3.y * (width-src.x)*src.y/d + 
            grid->p4.y * src.x*src.y/d};
}

