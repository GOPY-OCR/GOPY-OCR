#include "anima.h"

void anima_init(Glob_GUI *glob)
{
    glob->anima_PreviousButton = GTK_BUTTON(gtk_builder_get_object(glob->builder, "PreviousButton"));
    glob->anima_SaveButton = GTK_BUTTON(gtk_builder_get_object(glob->builder, "SaveButton"));
    glob->Image_anima = GTK_IMAGE(gtk_builder_get_object(glob->builder, "ImageStepPreprocess"));
    glob->anima_NextStep = GTK_BUTTON(gtk_builder_get_object(glob->builder, "AnimaNextStep"));
    glob->anima_PrevStep = GTK_BUTTON(gtk_builder_get_object(glob->builder, "AnimaPrevStep"));
    glob->anima_LastStep = GTK_BUTTON(gtk_builder_get_object(glob->builder, "AnimaLastStep"));

    glob->anima_NextStep = GTK_BUTTON(gtk_builder_get_object(glob->builder, "AnimaNextStep"));
    glob->anima_PrevStep = GTK_BUTTON(gtk_builder_get_object(glob->builder, "AnimaPrevStep"));
    glob->anima_LastStep = GTK_BUTTON(gtk_builder_get_object(glob->builder, "AnimaLastStep"));



    //CSS Button color changer 
    GtkCssProvider* css = gtk_css_provider_new();
    //modify hexa code to change color 
    gtk_css_provider_load_from_data(css, "* { background-image:none; background-color:#0D4848;}",-1,NULL);
        
    GtkStyleContext* context = gtk_widget_get_style_context(glob->anima_SaveButton);
    gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(css),GTK_STYLE_PROVIDER_PRIORITY_USER);
    
    context = gtk_widget_get_style_context(glob->anima_PreviousButton);
    gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(css),GTK_STYLE_PROVIDER_PRIORITY_USER);
    
    context = gtk_widget_get_style_context(glob->anima_NextStep);
    gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(css),GTK_STYLE_PROVIDER_PRIORITY_USER);

    context = gtk_widget_get_style_context(glob->anima_PrevStep);
    gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(css),GTK_STYLE_PROVIDER_PRIORITY_USER);

    context = gtk_widget_get_style_context(glob->anima_LastStep);
    gtk_style_context_add_provider(context, GTK_STYLE_PROVIDER(css),GTK_STYLE_PROVIDER_PRIORITY_USER);


	// connections des signaux
    g_signal_connect(glob->anima_PreviousButton, "clicked", G_CALLBACK(on_PreviousButton_clicked), glob);
    g_signal_connect(glob->anima_SaveButton, "clicked", G_CALLBACK(on_SaveButton_clicked), glob);
    g_signal_connect(glob->anima_NextStep, "clicked", G_CALLBACK(on_NextStep_clicked), glob);
    g_signal_connect(glob->anima_PrevStep, "clicked", G_CALLBACK(on_PrevStep_clicked), glob);
    g_signal_connect(glob->anima_LastStep, "clicked", G_CALLBACK(on_LastStep_clicked), glob);
}

void anima_start(Glob_GUI *glob) {
    compute_all_steps(glob);
    if (glob->anima == NULL)
        errx(EXIT_FAILURE, "Something went wrong during the computing of all steps");

    Anima_Steps *anima = glob->anima;

    if (glob->anima_auto) {
        if (anima->steps[anima->nb_steps - 1] == NULL) {
            dialog_error(glob->window, GTK_MESSAGE_ERROR, "Unsolvable grid...");
            anima->cur_step = anima->nb_steps - 2;
            gtk_image_set_from_sdl_surface(glob->Image_anima, anima->steps[anima->cur_step]);
        }
        
        else {
            anima->cur_step = anima->nb_steps - 1;
            gtk_image_set_from_sdl_surface(glob->Image_anima, anima->steps[anima->cur_step]);
        }
    }
     
    else {
        gtk_image_set_from_sdl_surface(glob->Image_anima, anima->steps[0]);
    }
}


G_MODULE_EXPORT void on_PreviousButton_clicked(GtkButton *button, gpointer user_data)
{
    Glob_GUI * glob = (Glob_GUI*) user_data;  
    
    if ((Glob_GUI *)user_data != NULL)
	{
        gtk_image_clear(GTK_IMAGE(glob->Image_anima));
        prev_page((Glob_GUI *)user_data);
        free_anima_steps(glob->anima);
	}
}


G_MODULE_EXPORT void on_SaveButton_clicked(GtkButton *button, gpointer user_data)
{
   Glob_GUI *glob = (Glob_GUI*) user_data;
   if ((Glob_GUI*) user_data != NULL)
   {
    //permet de choisir le chemin 

       GtkWidget* dialog = gtk_file_chooser_dialog_new("Select your unsolved grid", GTK_WINDOW(glob->window), GTK_FILE_CHOOSER_ACTION_SAVE, ("_Cancel"),GTK_RESPONSE_CANCEL, ("_Save"), GTK_RESPONSE_ACCEPT, NULL);
       //recupère le  chemin
       gint res = gtk_dialog_run (GTK_DIALOG (dialog));
       if (res == GTK_RESPONSE_ACCEPT) {
           char* outFile = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
           IMG_SavePNG(glob->anima->steps[glob->anima->cur_step], outFile);
       }
       gtk_widget_destroy (dialog);
   }
}

G_MODULE_EXPORT void on_NextStep_clicked(GtkButton *button, gpointer user_data) {
    Glob_GUI *glob = user_data;
    if (glob == NULL || glob->anima->cur_step == glob->anima->nb_steps - 1)
        return;

    Anima_Steps *anima = glob->anima;
    g_print("%i\n", anima->cur_step + 1);

    if (anima->cur_step + 1 < anima->nb_steps) {
        if (anima->cur_step + 1 == anima->nb_steps - 1 && 
                anima->steps[anima->cur_step + 1] == NULL) {
            dialog_error(glob->window, GTK_MESSAGE_ERROR, "Unsolvable grid...");
        }
        else if (anima->steps[anima->cur_step + 1] == NULL)
            dialog_error(glob->window, GTK_MESSAGE_ERROR, "Something went wrong with the next step...");

        else
            gtk_image_set_from_sdl_surface(glob->Image_anima, anima->steps[++anima->cur_step]);
    }
}

G_MODULE_EXPORT void on_PrevStep_clicked(GtkButton *button, gpointer user_data) {
    Glob_GUI *glob = user_data;
    if (glob == NULL || glob->anima->cur_step == 0)
        return;

    Anima_Steps *anima = glob->anima;

    if (anima->cur_step > 0)
        gtk_image_set_from_sdl_surface(glob->Image_anima, anima->steps[--anima->cur_step]);
}

G_MODULE_EXPORT void on_LastStep_clicked(GtkButton *button, gpointer user_data) {
    Glob_GUI *glob = user_data;
    if (glob == NULL)
        return;
    
    Anima_Steps *anima = glob->anima;

    if (anima->steps[anima->nb_steps - 1] == NULL) {
        dialog_error(glob->window, GTK_MESSAGE_ERROR, "Unsolvable grid...");
        anima->cur_step = anima->nb_steps - 2;
        gtk_image_set_from_sdl_surface(glob->Image_anima, anima->steps[anima->cur_step]);
    }
    
    else {
        anima->cur_step = anima->nb_steps - 1;
        gtk_image_set_from_sdl_surface(glob->Image_anima, anima->steps[anima->cur_step]);
    }
}

