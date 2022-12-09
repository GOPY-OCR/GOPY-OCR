#pragma once
#include "gtk/gtk.h"
#include "anima_steps.h"

typedef struct Glob_GUI {
    GtkBuilder *builder;
    GtkWidget *main;
    GtkWindow *window;
    GtkImage *Image;
    GtkStack *Pages;

    GtkButton *anima_PreviousButton;
    GtkButton *anima_SaveButton;

    GtkButton *page_0_LoadButton;

    GtkButton *page_1_CancelButton;
    GtkButton *page_1_ContinueButton;
    GtkImage *page_1_Image;
    GtkSwitch *page_1_Switch;

    GtkImage *Image_anima;
    GtkButton *anima_NextStep; // Next step button
    GtkButton *anima_PrevStep; // Prev step button
    GtkButton *anima_LastStep; // Directly go to the last step (postprocess)
    int anima_auto; // Automatic mode or not
    Anima_Steps *anima; // All the steps

    gchar *original_image_path;
    int current_page;
    int page_nb;
} Glob_GUI;
