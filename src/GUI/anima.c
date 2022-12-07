#include "anima.h"

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

void anima_init(Glob_GUI *glob)
{
    glob->anima_PreviousButton = GTK_BUTTON(gtk_builder_get_object(glob->builder, "PreviousButton"));
    glob->anima_SaveButton = GTK_BUTTON(gtk_builder_get_object(glob->builder, "SaveButton"));
    glob->page_1_Image = GTK_IMAGE(gtk_builder_get_object(glob->builder, "ImageStepPreprocess"));
    glob->anima_StartButton = GTK_BUTTON(gtk_builder_get_object(glob->builder, "StartButton"));

    //CSS Button color changer 
    GtkCssProvider* css = gtk_css_provider_new();
    //modify hexa code to change color 
    gtk_css_provider_load_from_data(css, "* { background-image:none; background-color:#0D4848;}",-1,NULL);
        
    GtkStyleContext* context = gtk_widget_get_style_context(glob->anima_SaveButton);
    gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(css),GTK_STYLE_PROVIDER_PRIORITY_USER);
    
    context = gtk_widget_get_style_context(glob->anima_PreviousButton);
    gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(css),GTK_STYLE_PROVIDER_PRIORITY_USER);
   
	// connections des signaux
    g_signal_connect(glob->anima_PreviousButton, "clicked", G_CALLBACK(on_PreviousButton_clicked), glob);
    g_signal_connect(glob->anima_SaveButton, "clicked", G_CALLBACK(on_SaveButton_clicked), glob);
    g_signal_connect(glob->anima_StartButton, "clicked", G_CALLBACK(on_StartButton_clicked), glob);
}


G_MODULE_EXPORT void on_PreviousButton_clicked(GtkButton *button, gpointer user_data)
{
    //g_print("should be displayed");
    if ((Glob_GUI *)user_data == NULL)
    {
       g_print("null");	
    }
    else 
	{
	    prev_page((Glob_GUI *)user_data);
	}
	g_print("pls help");
}


G_MODULE_EXPORT void on_SaveButton_clicked(GtkButton *button, gpointer user_data)
{
   Glob_GUI *glob = (Glob_GUI*) user_data;
   if ((Glob_GUI*) user_data == NULL)
   {
     g_print("starting save");
   }
   else
   {
    //permet de choisir le chemin 

        GtkWidget* dialog = gtk_file_chooser_dialog_new("Select your unsolved grid", GTK_WINDOW(glob->main), GTK_FILE_CHOOSER_ACTION_SAVE, ("_Cancel"),GTK_RESPONSE_CANCEL, (    "_Save"), GTK_RESPONSE_ACCEPT, NULL);
       //recupère le  chemin
       //char* outFile = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
       //SDL_Surface* surface = IMG_Load(//path of modified image);
       //IMG_SavePNG(surface,outfile);

   }
}

void update_image(GtkImage *image, SDL_Surface *new_surface) {

}

G_MODULE_EXPORT void on_StartButton_clicked(GtkButton *button, gpointer user_data)
{
    g_print("\nlol\n");
    // Convert the user pointer into the filename
    Glob_GUI *glob = user_data;
    GtkImage *Image = glob->page_1_Image;
    gchar *path = glob->original_image_path;

    Params p = get_params(path);

    // 1.  Load the image as a SDL_Surface
    SDL_Surface *SDL_image = load_image(path);
    
    // 2.  Resize the SDL_image to speed up the next functions
    resize(&SDL_image);
    gtk_image_set_from_sdl_surface(Image, SDL_image);

    // 3.  Grayscale
    surface_to_grayscale(Image);
    gtk_image_set_from_sdl_surface(Image, SDL_image);

    // 4.  Noise reduction + contrasts correction
    correct_brightness(Image);
    gtk_image_set_from_sdl_surface(Image, SDL_image);

    // 5.  Binarization
    binarize(SDL_image, p.b_th);
    gtk_image_set_from_sdl_surface(Image, SDL_image);

    // 6.  Interpolation des images pas droites
    automatic_rot(&SDL_image);    
    gtk_image_set_from_sdl_surface(Image, SDL_image);

    // 7.  Grid detection
    Quad coords = grid_detection(SDL_image, 0, p);
    SDL_Surface *copy = new_blank_surface(SDL_image);
    SDL_BlitSurface(SDL_image, NULL, copy, NULL);
    grid_detection(copy, 1, p);
    gtk_image_set_from_sdl_surface(Image, copy);

    SDL_FreeSurface(copy);

    // 8.  Perspective correction of the image
    perspective_correction(&SDL_image, &coords);
    gtk_image_set_from_sdl_surface(Image, SDL_image);
    
    // 9.  Split the image in 81 small images
    //SDL_Surface **splitted = split_sudoku(SDL_image);
    
    // 10. Resize the image to 28x28 for the neural network
    //neural_network_resize(splitted);
    
    // 12. Neural network


    // 13. Solve the grid
    //int *solved = Solve(grid);

    // 14. Postprocess
    //SDL_Surface  = postprocess(*grid, *solved);
}
