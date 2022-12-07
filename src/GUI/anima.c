#include "anima.h"

GtkWidget *gtk_image_new_from_sdl_surface (SDL_Surface *surface)
{
    Uint32 src_format;
    Uint32 dst_format;

    GdkPixbuf *pixbuf;
    gboolean has_alpha;
    int rowstride;
    guchar *pixels;

    GtkWidget *image;

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
    pixbuf = gdk_pixbuf_new (GDK_COLORSPACE_RGB, has_alpha, 8,
                             surface->w, surface->h);
    rowstride = gdk_pixbuf_get_rowstride (pixbuf);
    pixels = gdk_pixbuf_get_pixels (pixbuf);

    // copy pixels                                                              
    SDL_LockSurface(surface);
    SDL_ConvertPixels (surface->w, surface->h, src_format,
               surface->pixels, surface->pitch,
               dst_format, pixels, rowstride);
    SDL_UnlockSurface(surface);

    // create GtkImage from pixbuf                                              
    image = gtk_image_new_from_pixbuf (pixbuf);

    // release our reference to the pixbuf                                      
    g_object_unref (pixbuf);

    return image;
}
void anima_init(Glob_GUI *glob)
{
    glob->anima_PreviousButton = GTK_BUTTON(gtk_builder_get_object(glob->builder, "PreviousButton"));
    glob->anima_SaveButton = GTK_BUTTON(gtk_builder_get_object(glob->builder, "SaveButton"));
    glob->page_1_Image = GTK_IMAGE(gtk_builder_geet_object(glob->builder, "ImageStepPreprocess"));

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
    g_signal_connect(glob->anima_StartButton, "clicked", G_CALLBACK(on_SaveButton_clicked), glob);
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
    // Convert the user pointer into the filename
    Glob_GUI *glob = user_data;
    gchar *path = glob->original_image_path;

    // 1.  Load the image as a SDL_Surface
    SDL_Surface *SDL_image = load_image(path);
    gtk_image_clear(Image);
    
    // 2.  Resize the image to speed up the next functions
    resize(&image);
    gtk_image_clear(Image);

    // 3.  Grayscale
    surface_to_grayscale(Image);
    gtk_image_clear(image);

    // 4.  Noise reduction + contrasts correction
    correct_brightness(Image);
    gtk_image_clear(image);

    // 5.  Binarization
    binarize(image);
    gtk_image_clear(Image);

    // 6.  Interpolation des images pas droites
    automatic_rot(&image);    
    gtk_image_clear(Image);

    // 7.  Grid detection
    Quad coords = grid_detection(image, 0);
    gtk_image_clear(Image);

    // 8.  Perspective correction of the image
    perspective_correction(&image, &coords);
    gtk_image_clear(Image);
    
    // 9.  Split the image in 81 small images
    SDL_Surface **splitted = split_sudoku(image);
    gtk_image_clear(Image);
    
    // 10. Resize the image to 28x28 for the neural network
    neural_network_resize(splitted);
    gtk_image_clear(Image);
    
    // 11. Resize the image to 28x28 for the neural network
    neural_network_resize(splitted);
    gtk_image_clear(Image);
    
    // 12. Neural network

    // 13. Solve the grid
    int *solved = Solve(grid);

    // 14. Postprocess
    image = postprocess(*grid, *solved);
    gtk_image_clear(Image);
}
