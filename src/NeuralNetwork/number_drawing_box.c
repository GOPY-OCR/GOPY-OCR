#include "number_drawing_box.h"

#define NUMBER_DRAWING_BOX_MAX_POINTS 100

#define DRAWING_IMAGE_SCALE 10

// global variables
struct 
{
    // the following arrays are buffers for the coordinates to draw
    // on next frame
    double coords_x[NUMBER_DRAWING_BOX_MAX_POINTS];
    double coords_y[NUMBER_DRAWING_BOX_MAX_POINTS];
    int count;
    SDL_Surface *surface;
} glob;

NeuralNetwork *OCR_NN;


static void destroy(GtkWidget *widget, gpointer data)
{
    gtk_main_quit();
}

static void draw(GtkWidget *widget, cairo_t *cr, gpointer data)
{
    Uint32 white = SDL_MapRGB(glob.surface->format, 255, 255, 255);
    // draw the mouse coordinates on the surface
    SDL_LockSurface(glob.surface);
    for (int i = 0; i < glob.count; i++)
    {
        // convert mouse coordinates to surface coordinates
        int x = glob.coords_x[i] / DRAWING_IMAGE_SCALE;
        int y = glob.coords_y[i] / DRAWING_IMAGE_SCALE;

        if (x >= 0 && x < glob.surface->w && y >= 0 && y < glob.surface->h)
        {
            // draw the pixel
            putpixel(glob.surface, x, y, white);
        }
        
    }
    SDL_UnlockSurface(glob.surface);

    glob.count = 0;

    // draw the surface on the screen
    cairo_surface_t *surface = cairo_image_surface_create_for_data(
        glob.surface->pixels,
        CAIRO_FORMAT_ARGB32,
        glob.surface->w,
        glob.surface->h,
        glob.surface->pitch);

    // scale the surface to fit the drawing area
    cairo_scale(cr, DRAWING_IMAGE_SCALE, DRAWING_IMAGE_SCALE);

    cairo_set_source_surface(cr, surface, 0, 0);
    cairo_paint(cr);

    // predict the drawn digit
    int num = predict_surface(glob.surface, OCR_NN);
    fflush(stdout);
    printf("Predicted number: %d\r", num);
}

static gboolean motion_event_handler(GtkWidget *widget, GdkEventMotion *event, gpointer data)
{
    if (event->state & GDK_BUTTON1_MASK) {
        glob.coords_x[glob.count] = event->x;
        glob.coords_y[glob.count] = event->y;
        glob.count++;
        gtk_widget_queue_draw(widget);
    }
    return TRUE;
}

void glob_init()
{
    glob.count = 0;
    glob.surface = SDL_CreateRGBSurface(0, 28, 28, 32, 0, 0, 0, 0);
    Uint32 black = SDL_MapRGB(glob.surface->format, 0, 0, 0);
    SDL_FillRect(glob.surface, NULL, black);

    OCR_NN = load_neural_network("ocr_save.nn");
}

int main_gui_demo(int argc, char *argv[]){
    glob_init();

    gtk_init(&argc, &argv);
    GtkWidget *window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "Window");
    g_signal_connect(window, "destroy", G_CALLBACK(destroy), NULL);

    GtkWidget *box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
    gtk_container_add(GTK_CONTAINER(window), box);

    GtkWidget *drawing_area = gtk_drawing_area_new();
    gtk_widget_set_size_request(drawing_area, 28 * DRAWING_IMAGE_SCALE, 28 * DRAWING_IMAGE_SCALE);
    gtk_widget_add_events(drawing_area, GDK_BUTTON_PRESS_MASK | GDK_BUTTON_RELEASE_MASK | GDK_POINTER_MOTION_MASK);

    g_signal_connect(G_OBJECT(drawing_area), "draw", G_CALLBACK(draw), NULL);
    g_signal_connect(G_OBJECT(drawing_area), "motion-notify-event", G_CALLBACK(motion_event_handler), NULL);

    gtk_box_pack_start(GTK_BOX(box), drawing_area, TRUE, TRUE, 0);
    gtk_widget_show_all(window);

    gtk_main();
    return 0;
}

