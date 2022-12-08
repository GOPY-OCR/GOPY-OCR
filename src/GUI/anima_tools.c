#include "anima_tools.h"

void gtk_image_set_from_sdl_surface(GtkImage *image, SDL_Surface *surface)
{
    Uint32 src_format;
    Uint32 dst_format;

    GdkPixbuf *pixbuf;
    gboolean has_alpha;
    int rowstride;
    guchar *pixels;

    // select format                                                            
    src_format = surface->format->format;
    has_alpha = SDL_ISPIXELFORMAT_ALPHA(src_format);
    if (has_alpha) {
        dst_format = SDL_PIXELFORMAT_RGBA32;
    }
    else {
        dst_format = SDL_PIXELFORMAT_RGB24;
    }

    // create pixbuf                                                            
    pixbuf = gdk_pixbuf_new(GDK_COLORSPACE_RGB, has_alpha, 8,
                             surface->w, surface->h);
    rowstride = gdk_pixbuf_get_rowstride(pixbuf);
    pixels = gdk_pixbuf_get_pixels(pixbuf);

    // copy pixels                                                              
    SDL_LockSurface(surface);
    SDL_ConvertPixels(surface->w, surface->h, src_format,
               surface->pixels, surface->pitch,
               dst_format, pixels, rowstride);
    SDL_UnlockSurface(surface);

    // create GtkImage from pixbuf                                              
    gtk_image_set_from_pixbuf(image, pixbuf);

    // release our reference to the pixbuf                                      
    g_object_unref(pixbuf);
}

SDL_Surface *copy_surface(SDL_Surface *base) {
    SDL_Surface *copy = new_blank_surface(base);
    SDL_BlitSurface(base, NULL, copy, NULL);
    return copy;
}

void compute_all_steps(Glob_GUI *glob);
{
    glob->steps = malloc(sizeof(Anima_Steps));
    Anima_Steps *res = glob->steps;
    res->cur_step = 0;
    res->nb_steps = NB_STEPS;
    res->nb_pre_steps = NB_PRE_STEPS;
    res->prep = calloc(res->nb_pre_steps, sizeof(SDL_Surface *));

    // Convert the user pointer into the filename
    GtkImage *Image = glob->Image_anima;
    gchar *path = glob->original_image_path;

    Params p = get_params(path);

    // 1.  Load the image as a SDL_Surface
    SDL_Surface *image_sdl = load_image(path);
    res->prep[0] = copy_surface(image_sdl);
    
    // 2.  Resize the image_sdl to speed up the next functions
    resize(&image_sdl);
    res->prep[1] = copy_surface(image_sdl);
    //gtk_image_set_from_sdl_surface(Image, image_sdl);

    // 3.  Grayscale
    surface_to_grayscale(image_sdl);
    res->prep[2] = copy_surface(image_sdl);

    // 4.  Noise reduction + contrasts correction
    correct_brightness(image_sdl);
    res->prep[3] = copy_surface(image_sdl);

    // 5.  Binarization
    binarize(image_sdl, p.b_th);
    res->prep[4] = copy_surface(image_sdl);

    // 6.  Interpolation des images pas droites
    automatic_rot(&image_sdl);    
    res->prep[5] = copy_surface(image_sdl);

    // 7.  Grid detection
    Quad coords = grid_detection(image_sdl, 0, p, 1);
    res->prep[6] = copy_surface(image_sdl);
    grid_detection(res->prep[6], 1, p, 0);

    // 8.  Perspective correction of the image
    perspective_correction(&image_sdl, &coords);
    res->prep[7] = copy_surface(image_sdl);
    
    // 9.  Split the image in 81 small images
    SDL_Surface **splitted = split_sudoku(image_sdl);
    
    // 10. Resize the image to 28x28 for the neural network
    neural_network_resize(splitted);
    
    // 12. Neural network
    res->detected = neural_network(splitted);
    save_grid_file("/tmp/grid_00", grid);
    
    // 13. Solve the grid
    res->solved = calloc(81, sizeof(int));
    for (size_t i = 0; i < 81; i++)
        res->solved[i] = res->detected[i];

    if (!Solve(res->solved)) {
        g_print("Not solvable grid\n");
    }

    else {
        save_grid_file("/tmp/grid_00.result", solved);

        // 14. Postprocess
        SDL_Surface *final_result = postprocess(grid, solved);
        res->post = copy_surface(image_sdl);

        save_image(final_result, "/tmp/sodoko_result.png");
    }

    free(grid);
    free(solved);
}
