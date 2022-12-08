#pragma once
#include "gtk/gtk.h"

typedef struct Glob_GUI {
    GtkBuilder *builder;
    GtkWidget *main;
    GtkWindow *window;
    GtkImage *Image;
    GtkStack *Pages;

    GtkButton *anima_PreviousButton;
    GtkButton *anima_SaveButton;
    GtkButton *anima_StartButton;

    GtkButton *page_0_LoadButton;

    GtkButton *page_1_CancelButton;
    GtkButton *page_1_ContinueButton;
    GtkImage *page_1_Image;
    GtkSwitch *page_1_Switch;

    GtkImage *Image_anima; 
    GtkButton *anima_NextStep;
    GtkButton *anima_PrevStep;
    GtkButton *anima_LastStep;

    int anima_manual;

    gchar *original_image_path;
    int current_page;
    int page_nb;
} Glob_GUI;
