#define W 800
#define H 600

#define SIZE_W 800
#define SIZE_H 600

#include "../../Source/Libraries/all2.h"

/*memory leak detection*/
/*
#ifdef _MSC_VER
#include <crtdbg.h>
#else
#define _ASSERT(expr) ((void)0)

#define _ASSERTE(expr) ((void)0)
#endif
*/

int
text_offset_x=10,
text_offset_y=30,
text_area_offset_x=10,
text_area_offset_y=30;
text_area_w=W-20;
text_area_h=H-40;

int selected=0,selecting=0,selection_index[2],selection_transfer=0;


int in_selection()
{
	int I[2];
	
	sort2(selection_index[0],selection_index[1],I);
	
	return ( cursor_i >  selection_index[I[0]]-1 && cursor_i < selection_index[I[1]]+1 );
}

int in_selectionI()
{
	int I[2];
	
	sort2(selection_index[0],selection_index[1],I);
	
	return ( cursor_i >  selection_index[I[0]] && cursor_i < selection_index[I[1]] );
}

void update_cursor_by_mouse(int text_x,int text_y)
{
	int i;
	i=getCursorIndexFromMouseCoordinates(key_string_ptr->str,text_x,text_y,mouse_x,mouse_y);
						
	cursor_i=i-1;
}

void activate_selection()
{
	update_cursor_by_mouse(text_offset_x,text_offset_y);

	calculateRowColumn();
						
	selection_index[0]=cursor_i;
	selecting=1;
}

/*
	0 : selecting
	
*/

/*132465789*/
text buffer=emptyText;

int
buffer_state=0;

#define BUFFER_STATE_EMPTY	0
#define BUFFER_STATE_COPY	1
#define BUFFER_STATE_CUT	2

#define reset_buffer() {deleteText(&buffer);}
/*123456789*/

void handleTextBox(int text_x,int text_y)
{
	if(selection_transfer)
	{
		update_cursor_by_mouse(text_x,text_y);

		if(!mb_left && mb_left_p)
		{
			/*current state *selecting=0; selected=1;*/
			
			if(in_selectionI())
			{
				selection_transfer=0;
			}
			else
			{
				/*transfer*/
				
				selection_transfer=0;
			}
		}
	}
	else
	{
		if(mb_left && !mb_left_p)
		{
			if(selected)
			{
				update_cursor_by_mouse(text_x,text_y);
				
				if(in_selectionI())
				{
					selection_transfer=1;
				}
				else
				{		
					activate_selection();
					
					selected=0;
				}
			}
			else
			{
				activate_selection();
			}
		}
		
		/*unoptimized*/
		if(selecting)
		{
			update_cursor_by_mouse(text_x,text_y);
			
			selection_index[1]=cursor_i;
		
			if(!mb_left && mb_left_p) 
			{ selecting=0; selected=(selection_index[0]!=selection_index[1]); }
		}
	}
}

void drawTextBoxString(int text_x,int text_y)
{
	if(selecting || selected)
	{
		int I[2];
		
		sort2(selection_index[0],selection_index[1],I);
				
		setColorA2(255,255,255,255);
				
		drawStringSelected(key_string_ptr->str,text_x,text_y,selection_index[I[0]]+1,selection_index[I[1]]);
		if(in_selection()) invertColor();
			drawCursor(key_string_ptr->str,text_x,text_y,cursor_i);
	}
	else
	{
		setColorA2(255,255,255,255);
		
		drawString(key_string_ptr->str,text_x,text_y);
		drawCursor(key_string_ptr->str,text_x,text_y,cursor_i);
	}
}

int main(int argc,char **argv)
{	
	IO_Init("Plumber");
	initMath();
	initFont();

	key_input=1;
	
	while(!quit)
	{
		if(!Update())
		{
			/*if((key_c && !key_c_p) && (key_Rctrl || key_Lctrl))
			{
				
			}*/
			
			handleTextBox(text_offset_x,text_offset_y);
			
			setColor2(0,55,255);
			clear();
			invertColor();
			/*cfont=default_font;*/
			
			
			{
				text i=emptyText;
				
				appendString(&i,"col = ");
				appendInteger2(&i,cursor_col,5);
				
				appendString(&i,"  row = ");
				appendInteger2(&i,cursor_row,5);
				
				drawString(i.str,300,10);
				
				deleteText(&i);
				
				setColor2(255,255,255);
				drawString("Plumber Text Editor 0.01",10,10);
			}
			
			drawTextBoxString(text_offset_x,text_offset_y);
			
		}
	}
	
	quitFont();
	IO_Quit();
	
	return;
}
