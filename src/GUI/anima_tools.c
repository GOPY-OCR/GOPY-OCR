#include "anima_tools.h"

void free_anima_steps(Anima_Steps *anima) {
    for (size_t i = 0; i < anima->nb_steps; i++) {
        SDL_FreeSurface(anima->steps[i]);
    }

    free(anima->steps);
    free(anima->detected);
    free(anima->solved);
    free(anima);
}

void dialog_error(GtkWindow *window, GtkMessageType type, char *msg)
{
    char *title = "Info";
    if (type == GTK_MESSAGE_ERROR)
        title = "Error";
    if (type == GTK_MESSAGE_WARNING)
        title = "Warning";

    GtkWidget *dialog;
    GtkDialogFlags flags = GTK_DIALOG_DESTROY_WITH_PARENT;
    dialog = gtk_message_dialog_new_with_markup(window,
                                      flags,
                                      type,
                                      GTK_BUTTONS_CLOSE,
                                      "<b>%s</b>: %s", title, msg);

    gtk_window_set_title(GTK_WINDOW(dialog), title);
    gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}

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

void compute_all_steps(Glob_GUI *glob) {
    glob->anima = malloc(sizeof(Anima_Steps));
    Anima_Steps *res = glob->anima;
    res->cur_step = 0;
    res->nb_steps = NB_STEPS;
    res->steps = calloc(NB_STEPS, sizeof(SDL_Surface *));

    // Convert the user pointer into the filename
    gchar *path = glob->original_image_path;

    Params p = get_params(path);

    // 1.  Load the image as a SDL_Surface
    SDL_Surface *image_sdl = load_image(path);
    
    // 2.  Resize the image_sdl to speed up the next functions
    resize(&image_sdl);
    res->steps[0] = copy_surface(image_sdl);

    // 3.  Grayscale
    surface_to_grayscale(image_sdl);
    res->steps[1] = copy_surface(image_sdl);

    // 4.  Noise reduction + contrasts correction
    correct_brightness(image_sdl);
    res->steps[2] = copy_surface(image_sdl);

    // 5.  Binarization
    binarize(image_sdl, p.b_th);
    res->steps[3] = copy_surface(image_sdl);

    // 6.  Interpolation des images pas droites
    automatic_rot(&image_sdl);
    res->steps[4] = copy_surface(image_sdl);
    resize(&(res->steps[4]));

    // 7.  Grid detection
    res->steps[5] = copy_surface(res->steps[4]);
    grid_detection(res->steps[5], 1, p, 0);
    Quad coords = grid_detection(image_sdl, 0, p, 1);

    // 8.  Perspective correction of the image
    res->steps[6] = copy_surface(res->steps[4]);
    perspective_correction(&(res->steps[6]), &coords);
    perspective_correction(&image_sdl, &coords);
    
    // 9.  Split the image in 81 small images
    SDL_Surface **splitted = split_sudoku(image_sdl);
    
    // 10. Resize the image to 28x28 for the neural network
    neural_network_resize(splitted);
    
    // 12. Neural network
    res->detected = neural_network(splitted);
    res->steps[7] = postprocess(res->detected, res->detected);
    resize(&(res->steps[7]));
    
    // 13. Solve the grid
    res->solved = calloc(81, sizeof(int));
    for (size_t i = 0; i < 81; i++)
        res->solved[i] = res->detected[i];

    if (!Solve(res->solved)) {
        g_print("Not solvable grid\n");
        res->steps[8] = NULL;
    }

    else {
        // 14. Postprocess
        res->steps[8] = postprocess(res->detected, res->solved);
        resize(&(res->steps[8]));
    }
}
