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
gchar* gridFilename;
GtkWidget* Image1;
//Window when loaded
GtkWidget* LoadedWind;

//fin des déclarations

GtkBuilder* builder;

int main(int argc, char* argv[])
{
	gtk_init(&argc, &argv);
	builder = gtk_builder_new_from_file("GUI-project.glade");
	mainWindow = GTK_WIDGET(gtk_builder_get_object(builder,"MainWindow"));
	g_signal_connect(mainWindow,"destroy",G_CALLBACK(gtk_main_quit),NULL);
	
	LoadedWind = GTK_WIDGET(gtk_builder_get_object(builder,"ImageWhenLoadedWindow"));
	g_signal_connect(LoadedWind,"destroy",G_CALLBACK(gtk_main_quit),NULL);

	gtk_builder_connect_signals(builder,NULL);


	//activation des widgets

	FirstFixed = GTK_WIDGET(gtk_builder_get_object(builder,"FirstFixed"));
	ButtonLoad = GTK_WIDGET(gtk_builder_get_object(builder,"ButtonLoad"));
	Image1 = GTK_WIDGET(gtk_builder_get_object(builder,"Image1"));

	gtk_widget_show(mainWindow);
	gtk_main();
	return EXIT_SUCCESS;



}


G_MODULE_EXPORT void on_ButtonLoad_clicked(GtkButton* b)
{


	GtkWidget *dialog;
	GtkFileChooserAction action = GTK_FILE_CHOOSER_ACTION_OPEN;
	gint res;

	dialog = gtk_file_chooser_dialog_new ("Open File", GTK_WINDOW(mainWindow),action,("_Cancel"),GTK_RESPONSE_CANCEL,("_Open"),GTK_RESPONSE_ACCEPT,NULL);

	res = gtk_dialog_run (GTK_DIALOG (dialog));
	if (res == GTK_RESPONSE_ACCEPT)
	{
		GtkFileChooser *chooser = GTK_FILE_CHOOSER (dialog);
		gridFilename = gtk_file_chooser_get_filename (chooser);
		//open_file(filename);
		GdkPixbuf* pix = gdk_pixbuf_new_from_file_at_scale(gridFilename,800,700,TRUE,NULL);
		gtk_image_set_from_pixbuf(GTK_IMAGE(Image1),pix);

	}

	gtk_widget_destroy (dialog);

	gtk_widget_hide(mainWindow);
	//g_signal_connect( LoadedWind, "destroy", G_CALLBACK(gtk_main_quit), NULL);
	gtk_widget_show(LoadedWind);

}

