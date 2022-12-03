#include "main.h"

#define WINDOW_TITLE "GOPY - A Fully Automated Sudoku Solver"


int main(int argc, char* argv[])
{
    Glob_GUI *glob = malloc(sizeof(Glob_GUI));
    gtk_init(&argc, &argv);
    glob->builder = gtk_builder_new_from_file("GUI-project.glade");
    glob->main = GTK_WIDGET(gtk_builder_get_object(glob->builder,"main"));
    g_signal_connect(glob->main,"destroy",G_CALLBACK(gtk_main_quit),NULL);

    gtk_builder_connect_signals(glob->builder,NULL);

    // Set the title
    gtk_window_set_title(GTK_WINDOW(glob->main), WINDOW_TITLE);

    glob->Image = GTK_IMAGE(gtk_builder_get_object(glob->builder,"Image"));

    init_gui_utils(glob);
    init_pages(glob);

    gtk_widget_show(GTK_WIDGET(glob->main));
    gtk_main();
    return EXIT_SUCCESS;
}
