#include "anima.h"
#include <gtk/gtk.h>


GtkWidget *PreviousButton;
GtkWidget *SaveButton;


void anima_init(GtkBuilder *builder)
{
    PreviousButton = GTK_WIDGET(gtk_builder_get_object(builder, "Previous"));
    SaveButton = GTK_WIDGET(gtk_builder_get_object(builder, "Save"));

    g_signal_connect(PreviousButton, "clicked", G_CALLBACK(on_PreviousButton_clicked), NULL);
    g_signal_connect(SaveButton, "clicked", G_CALLBACK(on_SaveButton_clicked), NULL);
}


G_MODULE_EXPORT void on_PreviousButton_clicked(GtkButton *button, gpointer user_data)
{
    clear_image();
    prev_page();
}


G_MODULE_EXPORT void on_SaveButton_clicked(GtkButton *button, gpointer user_data)
{
    next_page();
}
