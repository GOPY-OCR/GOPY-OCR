#include "anima.h"

void anima_init(Glob_GUI *glob)
{
    glob->anima_PreviousButton = GTK_BUTTON(gtk_builder_get_object(glob->builder, "Previous"));
    glob->anima_SaveButton = GTK_BUTTON(gtk_builder_get_object(glob->builder, "Save"));

    g_signal_connect(glob->anima_PreviousButton, "clicked", G_CALLBACK(on_PreviousButton_clicked), glob);
    g_signal_connect(glob->anima_SaveButton, "clicked", G_CALLBACK(on_SaveButton_clicked), glob);
}


G_MODULE_EXPORT void on_PreviousButton_clicked(GtkButton *button, gpointer user_data)
{
    prev_page((Glob_GUI *)user_data);
}


G_MODULE_EXPORT void on_SaveButton_clicked(GtkButton *button, gpointer user_data)
{
    next_page((Glob_GUI *)user_data);
}
