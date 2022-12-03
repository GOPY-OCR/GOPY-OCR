#include "save.h"


GtkWidget *PreviousButton;
GtkWidget *SaveButton;


void save_init(GtkBuilder *builder)
{
    PreviousButton = GTK_WIDGET(gtk_builder_get_object(builder, "Previous"));
    SaveButton = GTK_WIDGET(gtk_builder_get_object(builder, "Save"));

    g_signal_connect(PreviousButton, "clicked", G_CALLBACK(on_PreviousButton_clicked), NULL);
    g_signal_connect(SaveButton, "clicked", G_CALLBACK(on_SaveButton_clicked), NULL);
}


