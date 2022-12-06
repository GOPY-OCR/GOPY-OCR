#include "anima.h"

void anima_init(Glob_GUI *glob)
{
    glob->anima_PreviousButton = GTK_BUTTON(gtk_builder_get_object(glob->builder, "PreviousButton"));
    glob->anima_SaveButton = GTK_BUTTON(gtk_builder_get_object(glob->builder, "SaveButton"));
    //CSS Button color changer 
    GtkCssProvider* css = gtk_css_provider_new();
    //modify hexa code to change color 
    gtk_css_provider_load_from_data(css, "* { background-image:none; background-color:#0D4848;}",-1,NULL);
        
    GtkStyleContext* context = gtk_widget_get_style_context(glob->anima_SaveButton);
    gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(css),GTK_STYLE_PROVIDER_PRIORITY_USER);
    
    context = gtk_widget_get_style_context(glob->anima_PreviousButton);
    gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(css),GTK_STYLE_PROVIDER_PRIORITY_USER);
   
	// connections des signaux

    g_signal_connect(glob->anima_PreviousButton, "clicked", G_CALLBACK(on_PreviousButton_clicked), glob);
    g_signal_connect(glob->anima_SaveButton, "clicked", G_CALLBACK(on_SaveButton_clicked), glob);
}


G_MODULE_EXPORT void on_PreviousButton_clicked(GtkButton *button, gpointer user_data)
{
      //g_print("should be displayed");
       if ((Glob_GUI *)user_data == NULL)
       {
          g_print("null");	
       }
       else 
	{
	    prev_page((Glob_GUI *)user_data);

	}
	g_print("pls help");
}


G_MODULE_EXPORT void on_SaveButton_clicked(GtkButton *button, gpointer user_data)
{
   Glob_GUI *glob = (Glob_GUI*) user_data;
   if ((Glob_GUI*) user_data == NULL)
   {
     g_print("starting save");
   }
   else
   {
    //permet de choisir le chemin 

        GtkWidget* dialog = gtk_file_chooser_dialog_new("Select your unsolved grid", GTK_WINDOW(glob->main), GTK_FILE_CHOOSER_ACTION_SAVE, ("_Cancel"),GTK_RESPONSE_CANCEL, (    "_Save"), GTK_RESPONSE_ACCEPT, NULL);
       //recupère le  chemin
       //char* outFile = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
       //SDL_Surface* surface = IMG_Load(//path of modified image);
       //IMG_SavePNG(surface,outfile);

   }
}
