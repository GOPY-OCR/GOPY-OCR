#include "page-0.h"

#define PREVIEW_WIDTH  500
#define PREVIEW_HEIGHT 500

void page_0_init(Glob_GUI *glob)
{
    glob->page_0_LoadButton = GTK_BUTTON(gtk_builder_get_object(glob->builder, "ButtonLoad"));
    glob->window = GTK_WINDOW(gtk_builder_get_object(glob->builder, "window"));
    glob->original_image_path = NULL;

    g_signal_connect(glob->page_0_LoadButton, "clicked", G_CALLBACK(on_ButtonLoad_clicked), glob);
    printf("glob: %p\n", glob);
     
   
   //CSS, beware, here be dragons
    GtkCssProvider *  css = gtk_css_provider_new();
    gtk_css_provider_load_from_data(css, "* { background-image:none; background-color:#0D4848;}",-1,NULL);
    GtkStyleContext *context = gtk_widget_get_style_context(GTK_WIDGET(glob->page_0_LoadButton));
    gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(css),GTK_STYLE_PROVIDER_PRIORITY_USER);
}

G_MODULE_EXPORT void on_ButtonLoad_clicked(GtkButton *Button, gpointer user_data)
{
    (void)Button;
    if (user_data == NULL){
        // for some reason this function is called twice
        // so cancel the call where user_data is NULL
        return;
    }
    Glob_GUI *glob = (Glob_GUI *)user_data;
    GtkWidget *dialog;
    GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
    gint res;


    dialog = gtk_file_chooser_dialog_new ("Open File", 
            GTK_WINDOW(glob->window),
            action,("_Cancel"),
            GTK_RESPONSE_CANCEL,
            ("_Open"),
            GTK_RESPONSE_ACCEPT,NULL);

    res = gtk_dialog_run (GTK_DIALOG (dialog));
    if (res == GTK_RESPONSE_ACCEPT)
    {
        GtkFileChooser *chooser = GTK_FILE_CHOOSER (dialog);
        glob->original_image_path = gtk_file_chooser_get_filename (chooser);

        GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file_at_scale(glob->original_image_path, 
                PREVIEW_WIDTH, 
                PREVIEW_HEIGHT, 
                TRUE,
                NULL);

        gtk_image_set_from_pixbuf(GTK_IMAGE(glob->page_1_Image), pixbuf);

        next_page(glob);
    }

    gtk_widget_destroy (dialog);
}

void clear_image(Glob_GUI *glob)
{
    glob->original_image_path = NULL;
    gtk_image_clear(glob->page_1_Image);
}
