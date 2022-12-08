#include "gui-utils.h"

char page_name[] = "page?";

void init_gui_utils(Glob_GUI *glob)
{
	glob->Pages = GTK_STACK(gtk_builder_get_object(glob->builder,"pages"));
	glob->current_page = 0;
	glob->page_nb = 3;  
}

void switch_page(Glob_GUI *glob, int page)
{       //switch name if either anima or pageI
	glob->current_page = page;
	int replace_i = sizeof(page_name) - 2;
	if (page == 2)
	{
		page_name[0] = 'A';
		page_name[1] = 'n';
		page_name[2] = 'i';
		page_name[3] = 'm';
		page_name[4] = 'a';





	}
	else 
	{
		page_name[0] = 'p';
		page_name[1] = 'a';
		page_name[2] = 'g';
		page_name[3] = 'e';
		//page_name = temp;
		page_name[replace_i] = '0' + page;

		
	}
	g_print(page_name);
	gtk_stack_set_visible_child_name(glob->Pages, page_name);

}

void next_page(Glob_GUI *glob)
{
	if (glob->current_page < glob->page_nb - 1)
	{
		glob->current_page++;
		switch_page(glob, glob->current_page);
	}
}

void prev_page(Glob_GUI *glob)
{
	if (glob->current_page > 0)
	{
		glob->current_page--;
		switch_page(glob, glob->current_page);
	}
}
