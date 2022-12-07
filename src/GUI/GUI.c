#include "GUI.h"

#define WINDOW_TITLE "GOPY - A Fully Automated Sudoku Solver"


int GUI(int argc, char* argv[])
{
    Glob_GUI *glob = malloc(sizeof(Glob_GUI));
    gtk_init(&argc, &argv);
    glob->builder = gtk_builder_new_from_file(GUI_GLADE);
    glob->main = GTK_WIDGET(gtk_builder_get_object(glob->builder,"main"));
    g_signal_connect(glob->main,"destroy",G_CALLBACK(gtk_main_quit),NULL);

    gtk_builder_connect_signals(glob->builder,NULL);
    GtkCssProvider * css = gtk_css_provider_new();

    gtk_css_provider_load_from_data(css, "* { background-image:none; background-color:#032D39;}",-1,NULL);
    GtkStyleContext * context = gtk_widget_get_style_context(glob->main);
    gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(css),GTK_STYLE_PROVIDER_PRIORITY_USER);

    // Set the title
    gtk_window_set_title(GTK_WINDOW(glob->main), WINDOW_TITLE);

    glob->Image = GTK_IMAGE(gtk_builder_get_object(glob->builder,"Image"));

    init_gui_utils(glob);
    init_pages(glob);

    gtk_widget_show(GTK_WIDGET(glob->main));
    gtk_main();
    return EXIT_SUCCESS;
}
