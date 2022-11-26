#include "page-0.h"

GtkWidget* ButtonLoad;
GtkWindow* window0;
GtkImage* image0;

gchar* gridFilename;

#define PREVIEW_WIDTH  500
#define PREVIEW_HEIGHT 500

void page_0_init(GtkBuilder *builder)
{
    ButtonLoad = GTK_WIDGET(gtk_builder_get_object(builder, "ButtonLoad"));
    window0 = GTK_WINDOW(gtk_builder_get_object(builder, "window"));
    image0 = GTK_IMAGE(gtk_builder_get_object(builder, "image1"));
    
    g_signal_connect(ButtonLoad, "clicked", G_CALLBACK(on_ButtonLoad_clicked), NULL);
}

G_MODULE_EXPORT void on_ButtonLoad_clicked(void)
{
       if (gridFilename != NULL){
            // for some reason this function is called twice
            // so cancel the second call
            return;
        }
	GtkWidget *dialog;
	GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
	gint res;

	dialog = gtk_file_chooser_dialog_new ("Open File", 
                                              GTK_WINDOW(window0),
                                              action,("_Cancel"),
                                              GTK_RESPONSE_CANCEL,
                                              ("_Open"),
                                              GTK_RESPONSE_ACCEPT,NULL);

	res = gtk_dialog_run (GTK_DIALOG (dialog));
	if (res == GTK_RESPONSE_ACCEPT)
	{
		GtkFileChooser *chooser = GTK_FILE_CHOOSER (dialog);
		gridFilename = gtk_file_chooser_get_filename (chooser);
		
                GdkPixbuf *pixbuf = gdk_pixbuf_new_from_file_at_scale(gridFilename, 
                                                                      PREVIEW_WIDTH, 
                                                                      PREVIEW_HEIGHT, 
                                                                      TRUE,
                                                                      NULL);

                gtk_image_set_from_pixbuf(GTK_IMAGE(image0), pixbuf);
                
                next_page();
        }


	gtk_widget_destroy (dialog);
}

void clear_image(void)
{
    gridFilename = NULL;
    gtk_image_clear(image0);
}
