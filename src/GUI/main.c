#include "main.h"

#define WINDOW_TITLE "GOPY - A Fully Automated Sudoku Solver"

//Main Menu
GtkWidget* window;
GtkWidget* Image;

//fin des déclarations

GtkBuilder* builder;

int main(int argc, char* argv[])
{
	gtk_init(&argc, &argv);
	builder = gtk_builder_new_from_file("GUI-project.glade");
	window = GTK_WIDGET(gtk_builder_get_object(builder,"main"));
	g_signal_connect(window,"destroy",G_CALLBACK(gtk_main_quit),NULL);
	
	gtk_builder_connect_signals(builder,NULL);

        // Set the title
        gtk_window_set_title(GTK_WINDOW(window), WINDOW_TITLE);

        Image = GTK_WIDGET(gtk_builder_get_object(builder,"Image"));

        init_gui_utils(builder);
        init_pages(builder);

	gtk_widget_show(window);
	gtk_main();
	return EXIT_SUCCESS;
}



