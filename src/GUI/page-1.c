#include "page-1.h"

void page_1_init(Glob_GUI *glob)
{
    glob->page_1_CancelButton = GTK_BUTTON(gtk_builder_get_object(glob->builder, "Cancel1"));
    glob->page_1_ContinueButton = GTK_BUTTON(gtk_builder_get_object(glob->builder, "Continue1"));
    glob->page_1_Image = GTK_IMAGE(gtk_builder_get_object(glob->builder, "image1"));

    g_signal_connect(glob->page_1_CancelButton, "clicked", G_CALLBACK(on_CancelButton1_clicked), glob);
}

G_MODULE_EXPORT void on_CancelButton1_clicked(GtkButton *button, gpointer user_data)
{
    clear_image((Glob_GUI *)user_data);
    prev_page((Glob_GUI *)user_data);
}


