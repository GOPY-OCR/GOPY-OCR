#include "save.h"


GtkWidget *PreviousButton;
GtkWidget *SaveButton;


void save_init(Glob_GUI *glob)
{
    g_signal_connect(glob->anima_PreviousButton, "clicked", G_CALLBACK(on_PreviousButton_clicked), NULL);
    g_signal_connect(glob->anima_SaveButton, "clicked", G_CALLBACK(on_SaveButton_clicked), NULL);
}


