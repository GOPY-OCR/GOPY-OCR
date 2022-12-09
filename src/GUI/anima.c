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
    if (glob->steps == NULL)
        errx(EXIT_FAILURE, "Something went wrong during the computing of all steps");

    gtk_image_set_from_sdl_surface(glob->Image_anima, glob->steps->prep[0]);

    if (glob->anima_auto) {
        if (glob->steps->post == NULL) {
            dialog_error(glob->window, GTK_MESSAGE_ERROR, "Unsolvable grid...");
        }

        else
            gtk_image_set_from_sdl_surface(glob->Image_anima, glob->steps->post);
    }
}


G_MODULE_EXPORT void on_PreviousButton_clicked(GtkButton *button, gpointer user_data)
{
   
     Glob_GUI * glob = (Glob_GUI*) user_data;  
    
    if ((Glob_GUI *)user_data == NULL)
    {
       g_print("null");	
    }
    else 
	{
	   	gtk_image_clear(GTK_IMAGE(glob->Image_anima));
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
   else if (glob->steps->post != NULL)
   {
    //permet de choisir le chemin 

       GtkWidget* dialog = gtk_file_chooser_dialog_new("Select your unsolved grid", GTK_WINDOW(glob->window), GTK_FILE_CHOOSER_ACTION_SAVE, ("_Cancel"),GTK_RESPONSE_CANCEL, ("_Save"), GTK_RESPONSE_ACCEPT, NULL);
       //recupère le  chemin
       gint res = gtk_dialog_run (GTK_DIALOG (dialog));
       if (res == GTK_RESPONSE_ACCEPT) {
           char* outFile = gtk_file_chooser_get_filename(GTK_FILE_CHOOSER(dialog));
           IMG_SavePNG(glob->steps->post, outFile);
       }
       gtk_widget_destroy (dialog);
   }
}

G_MODULE_EXPORT void on_NextStep_clicked(GtkButton *button, gpointer user_data) {
    Glob_GUI *glob = user_data;
    if (glob == NULL || glob->steps->cur_step == glob->steps->nb_steps - 1)
        return;

    Anima_Steps *steps = glob->steps;

    if (++steps->cur_step < steps->nb_pre_steps)
        gtk_image_set_from_sdl_surface(glob->Image_anima, steps->prep[steps->cur_step]);

    else if (steps->cur_step == steps->nb_pre_steps) {
        // Show detected grid    
    }
    else {
        if (glob->steps->post == NULL) {
            dialog_error(glob->window, GTK_MESSAGE_ERROR, "Unsolvable grid...");
        }
    }
}

G_MODULE_EXPORT void on_PrevStep_clicked(GtkButton *button, gpointer user_data) {
    Glob_GUI *glob = user_data;
    if (glob == NULL || glob->steps->cur_step == 0)
        return;

    Anima_Steps *steps = glob->steps;

    if (--steps->cur_step < steps->nb_pre_steps)
        gtk_image_set_from_sdl_surface(glob->Image_anima, steps->prep[steps->cur_step]);

    else if (steps->cur_step == steps->nb_pre_steps) {
        // Show detected grid    
    }
    else {
        if (glob->steps->post == NULL) {
            dialog_error(glob->window, GTK_MESSAGE_ERROR, "Unsolvable grid...");
        }
    }
}

G_MODULE_EXPORT void on_LastStep_clicked(GtkButton *button, gpointer user_data) {
    Glob_GUI *glob = user_data;
    if (glob == NULL)
        return;
    
    Anima_Steps *steps = glob->steps;

    if (glob->steps->post == NULL) {
        dialog_error(glob->window, GTK_MESSAGE_ERROR, "Unsolvable grid...");
    }
}

