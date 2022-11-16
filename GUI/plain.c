#include <stdlib.h>
 #include <sys/types.h>
 #include <signal.h>
 #include <unistd.h>
 #include <string.h>
 #include <gtk/gtk.h>
 #include <gtk/gtkx.h>
 #include <math.h>
 #include <ctype.h>

//Main Menu

GtkWidget* mainWindow;
GtkWidget* FirstFixed;
GtkWidget* ButtonLoad;

//Window when loaded
GtkWidget* LoadedWind;

//fin des déclarations

GtkBuilder* builder;

int main(int argc, char* argv[])
{
	gtk_init(&argc, &argv);
	builder = gtk_builder_new_from_file("GUI-project.glade");
	mainWindow = GTK_WIDGET(gtk_builder_get_object(builder,"MainWindow");
	g_signal_connect(mainWindow,"destroy",G_CALLBACK(gtk_main_quit),NULL);
	gtk_builder_connect_signals(builder,NULL);


	//activation des widgets
	
	//TODO
	
	gtk_widget_show(mainWindow);
	gtk_main();
	return EXIT_SUCCESS;
	


}


void on_ButtonLoad_clicked(GtkButton* b)
{
	//TODO
	//gtk_file_chooser_dialog_new
	gtk_widget_hide(mainWindow);
	g_signal_connect( LoadedWind, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	gtk_widget_show(LoadedWind);

}
