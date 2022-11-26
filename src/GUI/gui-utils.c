#include "main.h"

#define PAGES_NB 2

GtkStack* Pages;
int current_page = 0;
char page_name[] = "page?";

void init_gui_utils(GtkBuilder *builder)
{
    Pages = GTK_STACK(gtk_builder_get_object(builder,"pages"));
}

void switch_page(int page)
{
    current_page = page;
    int replace_i = sizeof(page_name) - 2;
    page_name[replace_i] = '0' + page;
    gtk_stack_set_visible_child_name(Pages, page_name);
}

void next_page()
{
    if (current_page < PAGES_NB - 1)
    {
        current_page++;
        switch_page(current_page);
    }
}

void prev_page()
{
    if (current_page > 0)
    {
        current_page--;
        switch_page(current_page);
    }
}
