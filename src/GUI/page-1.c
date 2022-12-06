#include "page-1.h"

void page_1_init(Glob_GUI *glob)
{
    glob->page_1_CancelButton = GTK_BUTTON(gtk_builder_get_object(glob->builder, "Cancel1"));
    glob->page_1_ContinueButton = GTK_BUTTON(gtk_builder_get_object(glob->builder, "Continue1"));
    glob->page_1_Image = GTK_IMAGE(gtk_builder_get_object(glob->builder, "image1"));

    GtkCssProvider *  css = gtk_css_provider_new();
    gtk_css_provider_load_from_data(css, "* { background-image:none; background-color:#0D4848;}",-1,NULL);
    GtkCssProvider *context = gtk_widget_get_style_context(glob->page_1_CancelButton);
    gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(css),GTK_STYLE_PROVIDER_PRIORITY_USER);

    context = gtk_widget_get_style_context(glob->page_1_ContinueButton);
    gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(css),GTK_STYLE_PROVIDER_PRIORITY_USER);


    g_signal_connect(glob->page_1_CancelButton, "clicked", G_CALLBACK(on_CancelButton1_clicked), glob);
    g_signal_connect(glob->page_1_ContinueButton, "clicked",G_CALLBACK(on_Continue1_clicked),glob);
}

G_MODULE_EXPORT void on_CancelButton1_clicked(GtkButton *button, gpointer user_data)
{
    clear_image((Glob_GUI *)user_data);
    prev_page((Glob_GUI *)user_data);
}

G_MODULE_EXPORT void on_Continue1_clicked(GtkButton *button, gpointer user_data)
{
   Glob_GUI *glob = (Glob_GUI *)user_data;
   if (glob == NULL)
   {
	   g_print("aled");
   }

   else
   {
	   next_page(glob);
   }
}
