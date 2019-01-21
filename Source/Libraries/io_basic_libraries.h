/*
Copyright (C) <2018-2019> <Tankut Zeytinoğlu>
You can find the text of zlib license in the root folder.
*/

#ifndef IO_BASIC_LIBRARIES_H
#define IO_BASIC_LIBRARIES_H

#include <stdio.h>
#include<glad/glad.h>
#include <SDL.h>
#include <SDL_image.h>

#include <stdlib.h>

#include <time.h>

/*general*/

typedef uint8_t u8;

typedef enum/*reconsider the validity*/
{
	false=0,
	true=1
}bool;

/***************************/

int fullscreen_w,fullscreen_h,fullscreen=0;

const int N=(W*H);

SDL_Window *window;
SDL_Renderer *renderer;
SDL_Texture *texture;

struct Texture{
	u8* pixels;
	int w,h;
};

typedef struct Texture Texture;

struct Texture *current_buffer;
struct Texture   screen_buffer;

Uint32 getpixel(SDL_Surface *surface, int x, int y)
{
	int bpp = surface->format->BytesPerPixel;
	Uint8 *p = (Uint8 *)surface->pixels + y * surface->pitch + x * bpp;

	switch(bpp) {
	case 1:
	return *p;
	break;

	case 2:
		return *(Uint16 *)p;
		break;

    case 3:
	if(SDL_BYTEORDER == SDL_BIG_ENDIAN)
			return p[0] << 16 | p[1] << 8 | p[2];
	else
		return p[0] | p[1] << 8 | p[2] << 16;
		break;

	case 4:
	return *(Uint32 *)p;
		break;

	default:
		return 0;
	}
}

int mouse_x,mouse_y,mouse_xp,mouse_yp;

int quit = 0;
SDL_Event event;

u8
 key_kp_0	=0,
 key_kp_1	=0,
 key_kp_2	=0,
 key_kp_3	=0,
 key_kp_4	=0,
 key_kp_5	=0,
 key_kp_6	=0,
 key_kp_7	=0,
 key_kp_8	=0,
 key_kp_9	=0,

 key_kp_0_p	=0,
 key_kp_1_p	=0,
 key_kp_2_p	=0,
 key_kp_3_p	=0,
 key_kp_4_p	=0,
 key_kp_5_p	=0,
 key_kp_6_p	=0,
 key_kp_7_p	=0,
 key_kp_8_p	=0,
 key_kp_9_p	=0,

 key_enter		=0
,key_backspace	=0
,key_delete		=0
,key_tab		=0
,key_esc		=0

,key_f1		=0
,key_f2		=0
,key_f3		=0
,key_f4		=0
,key_f5		=0
,key_f6		=0
,key_f7		=0
,key_f8		=0
,key_f9		=0
,key_f10	=0
,key_f11	=0
,key_f12	=0

,key_left	=0
,key_right	=0
,key_up		=0
,key_down	=0

,key_a=0
,key_b=0
,key_c=0
,key_d=0
,key_e=0
,key_f=0
,key_g=0
,key_h=0
,key_i=0
,key_j=0
,key_k=0
,key_l=0
,key_m=0
,key_n=0
,key_o=0
,key_p=0
,key_q=0
,key_r=0
,key_s=0
,key_t=0
,key_u=0
,key_v=0
,key_w=0
,key_x=0
,key_y=0
,key_z=0

,key_0=0
,key_1=0
,key_2=0
,key_3=0
,key_4=0
,key_5=0
,key_6=0
,key_7=0
,key_8=0
,key_9=0

,key_Ralt=0
,key_Lalt=0
,key_Rctrl=0
,key_Lctrl=0
,key_Rshift=0
,key_Lshift=0

,key_plus=0
,key_minus=0

,key_enter_p		=0
,key_backspace_p	=0
,key_delete_p		=0
,key_tab_p			=0
,key_esc_p			=0

,key_f1_p	=0
,key_f2_p	=0
,key_f3_p	=0
,key_f4_p	=0
,key_f5_p	=0
,key_f6_p	=0
,key_f7_p	=0
,key_f8_p	=0
,key_f9_p	=0
,key_f10_p	=0
,key_f11_p	=0
,key_f12_p	=0


,key_left_p	=0
,key_right_p=0
,key_up_p	=0
,key_down_p	=0

,key_a_p=0
,key_b_p=0
,key_c_p=0
,key_d_p=0
,key_e_p=0
,key_f_p=0
,key_g_p=0
,key_h_p=0
,key_i_p=0
,key_j_p=0
,key_k_p=0
,key_l_p=0
,key_m_p=0
,key_n_p=0
,key_o_p=0
,key_p_p=0
,key_q_p=0
,key_r_p=0
,key_s_p=0
,key_t_p=0
,key_u_p=0
,key_v_p=0
,key_w_p=0
,key_x_p=0
,key_y_p=0
,key_z_p=0

,key_0_p=0
,key_1_p=0
,key_2_p=0
,key_3_p=0
,key_4_p=0
,key_5_p=0
,key_6_p=0
,key_7_p=0
,key_8_p=0
,key_9_p=0

,key_Ralt_p=0
,key_Lalt_p=0
,key_Rctrl_p=0
,key_Lctrl_p=0
,key_Rshift_p=0
,key_Lshift_p=0

,key_plus_p=0
,key_minus_p=0

,mb_left	=0
,mb_right	=0

,mb_left_p	=0
,mb_right_p	=0

,mb_middle=0
,mb_middle_p=0

,char_add=0
,char_del=0

,cursor_movement=0;

;

int key_input=0,cursor_i=-1,cursor_row=0,cursor_col=0;
text default_key_string=emptyText,*key_string_ptr;

#define setCurrentKeyString(x) {key_string_ptr=&x;}


int char_input_down()
{
	return
	
	(key_a && !key_a_p) ||
	(key_b && !key_b_p) ||
	(key_c && !key_c_p) ||
	(key_d && !key_d_p) ||
	(key_e && !key_e_p) ||
	(key_f && !key_f_p) ||
	(key_g && !key_g_p) ||
	(key_h && !key_h_p) ||
	(key_i && !key_i_p) ||
	(key_j && !key_j_p) ||
	(key_k && !key_k_p) ||
	(key_l && !key_l_p) ||
	(key_m && !key_m_p) ||
	(key_n && !key_n_p) ||
	(key_o && !key_o_p) ||
	(key_p && !key_p_p) ||
	(key_q && !key_q_p) ||
	(key_r && !key_r_p) ||
	(key_s && !key_s_p) ||
	(key_t && !key_t_p) ||
	(key_u && !key_u_p) ||
	(key_v && !key_v_p) ||
	(key_w && !key_w_p) ||
	(key_x && !key_x_p) ||
	(key_y && !key_y_p) ||
	(key_z && !key_z_p) ||

	(key_0 && !key_0_p) ||
	(key_1 && !key_1_p) ||
	(key_2 && !key_2_p) ||
	(key_3 && !key_3_p) ||
	(key_4 && !key_4_p) ||
	(key_5 && !key_5_p) ||
	(key_6 && !key_6_p) ||
	(key_7 && !key_7_p) ||
	(key_8 && !key_8_p) ||
	(key_9 && !key_9_p) ||

	(key_plus && !key_plus_p) ||
	(key_minus && !key_minus_p);
}


void cleanKeyString()
{
	deleteText(key_string_ptr);
	cursor_i=-1;
	cursor_row=0;
	cursor_col=0;
}

void calculateRowColumn()
{
	cursor_col=getColumnAtIndex(key_string_ptr->str,cursor_i);
	cursor_row=getRowAtIndex(key_string_ptr->str,cursor_i);
}

int tab_space;

void putChar(char ch)
{
	insertCharacter(key_string_ptr,ch,cursor_i+1);
	cursor_i++;
					
	calculateRowColumn();
}

void endLine()
{
	{
		int i,j=0;
		
		for(i=cursor_i; key_string_ptr->str[i]!='\n' && i>=0; i--);
		i++;
		
		for(; key_string_ptr->str[i]=='\t'; i++,j++);
		
		insertString(key_string_ptr,"\n",cursor_i+1);
		cursor_i++;
		
		if(j>0)
		{
			for(i=0; i<j; i++)
			{
				insertString(key_string_ptr,"\t",cursor_i+1);
				cursor_i++;
			}
		}
		
		calculateRowColumn();
	}
}

void (*mouseWheelUp)();
void (*mouseWheelDown)();

int selected=0,selecting=0,selection_index[2],selection_transfer=0;
int one_line_input=0;

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

void activate_selection(int text_x,int text_y)
{
	update_cursor_by_mouse(text_x,text_y);

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

void handleTextBoxString(int text_x,int text_y)
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
				if(selected)
				{
					int I[2],n;
					
					sort2(selection_index[0],selection_index[1],I);
					
					deleteText(&buffer);
					buffer=subText(key_string_ptr,selection_index[I[0]]+1,selection_index[I[1]]);
					deleteSubText(key_string_ptr,selection_index[I[0]]+1,selection_index[I[1]]);
					
					insertString(key_string_ptr,buffer.str,cursor_i+1);
					
					n=selection_index[I[1]]-selection_index[I[0]]+1;
					selection_index[0]=cursor_i;
					selection_index[1]=cursor_i+n-1;
				}
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
					activate_selection(text_x,text_y);
					
					selected=0;
				}
			}
			else
			{
				activate_selection(text_x,text_y);
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

void drawTextBoxString(int text_x,int text_y,char *str,int active)
{
	if(selecting || selected)
	{
		int I[2];
		
		sort2(selection_index[0],selection_index[1],I);
		
		if(active)
		drawStringSelectedHW(str,text_x,text_y,selection_index[I[0]]+1,selection_index[I[1]]);
		else
		drawStringHW(str,text_x,text_y);
		
		if(in_selection()) invertColorHW();
		if(active)
		drawCursorHW(str,text_x,text_y,cursor_i);
	}
	else
	{
		drawStringHW(str,text_x,text_y);
		
		if(active)
		drawCursorHW(str,text_x,text_y,cursor_i);
	}
}

void UpdateEvents()
{
	key_kp_0_p	=key_kp_0;
	key_kp_1_p	=key_kp_1;
	key_kp_2_p	=key_kp_2;
	key_kp_3_p	=key_kp_3;
	key_kp_4_p	=key_kp_4;
	key_kp_5_p	=key_kp_5;
	key_kp_6_p	=key_kp_6;
	key_kp_7_p	=key_kp_7;
	key_kp_8_p	=key_kp_8;
	key_kp_9_p	=key_kp_9;	
	
	key_Ralt_p	=	key_Ralt;
	key_Lalt_p	=	key_Lalt;
	key_Rctrl_p	=	key_Rctrl;
	key_Lctrl_p	=	key_Lctrl;
	key_Rshift_p	=	key_Rshift;
	key_Lshift_p	=	key_Lshift;
	
	key_plus=key_plus_p;
	key_minus=key_minus_p;
	
	key_enter_p=key_enter;
	key_backspace_p=key_backspace;
	key_delete_p=key_delete;
	key_tab_p=key_tab;
	
	key_left_p=key_left;
	key_right_p=key_right;
	key_up_p=key_up;
	key_down_p=key_down;
	key_esc	= key_esc_p;

	key_f1	= key_f1_p;
	key_f2	= key_f2_p;
	key_f3	= key_f3_p;
	key_f4	= key_f4_p;
	key_f5	= key_f5_p;
	key_f6	= key_f6_p;
	key_f7	= key_f7_p;
	key_f8	= key_f8_p;
	key_f9	= key_f9_p;
	key_f10	= key_f10_p;
	key_f11	= key_f11_p;
	key_f12 = key_f12_p;
	
	key_0_p=key_0;
	key_1_p=key_1;
	key_2_p=key_2;
	key_3_p=key_3;
	key_4_p=key_4;
	key_5_p=key_5;
	key_6_p=key_6;
	key_7_p=key_7;
	key_8_p=key_8;
	key_9_p=key_9;
	
	key_a_p=key_a;
	key_b_p=key_b;
	key_c_p=key_c;
	key_d_p=key_d;
	key_e_p=key_e;
	key_f_p=key_f;
	key_g_p=key_g;
	key_h_p=key_h;
	key_i_p=key_i;
	key_j_p=key_j;
	key_k_p=key_k;		
	key_l_p=key_l;
	key_m_p=key_m;
	key_n_p=key_n;
	key_o_p=key_o;
	key_p_p=key_p;
	key_q_p=key_q;
	key_r_p=key_r;
	key_s_p=key_s;
	key_t_p=key_t;
	key_u_p=key_u;
	key_v_p=key_v;
	key_w_p=key_w;
	key_x_p=key_x;
	key_y_p=key_y;
	key_z_p=key_z;
	
	mb_left_p=mb_left;
	mb_right_p=mb_right;
	
	mb_middle_p=mb_middle;
	
	while(SDL_PollEvent(&event))
	{
		switch (event.type)
		{
			case SDL_QUIT:
				quit = 1;
				break;
			case SDL_TEXTINPUT:
				if(key_input)
					char_add=1;
				{/*warning : *event.text.text*/
			/*problematic*/
					if(selected)
					{
						int I[2];
						
						sort2(selection_index[0],selection_index[1],I);
						deleteSubText(key_string_ptr,selection_index[I[0]]+1,selection_index[I[1]]);
						
						cursor_i=selection_index[I[0]];
						
						selected=0;
					}
					
					insertCharacter(key_string_ptr,*event.text.text,cursor_i+1);
					cursor_i++;
					
					calculateRowColumn();
				}
				/*appendString(&key_string,event.text.text);*/
				break;
			case SDL_MOUSEWHEEL:
				if(event.wheel.y>0) (*mouseWheelUp)();
				if(event.wheel.y<0) (*mouseWheelDown)();
				break;
			case SDL_KEYDOWN:
				switch(event.key.keysym.sym)
				{
					case SDLK_KP_0:
						key_kp_0=1;
					break;
					case SDLK_KP_1:
						key_kp_1=1;
					break;
					case SDLK_KP_2:
						key_kp_2=1;
					break;
					case SDLK_KP_3:
						key_kp_3=1;
					break;
					case SDLK_KP_4:
						key_kp_4=1;
					break;
					case SDLK_KP_5:
						key_kp_5=1;
					break;
					case SDLK_KP_6:
						key_kp_6=1;
					break;
					case SDLK_KP_7:
						key_kp_7=1;
					break;
					case SDLK_KP_8:
						key_kp_8=1;
					break;
					case SDLK_KP_9:
						key_kp_9=1;
					break;
					case SDLK_RALT:
						key_Ralt=1;
					break;
					case SDLK_LALT:
						key_Lalt=1;
					break;
					case SDLK_RCTRL:
						key_Rctrl=1;
					break;
					case SDLK_LCTRL:
						key_Lctrl=1;
					break;
					case SDLK_RSHIFT:
						key_Rshift=1;
					break;
					case SDLK_LSHIFT:
						key_Lshift=1;
					break;
					case SDLK_KP_PLUS:
						key_plus=1;
					break;
					case SDLK_KP_MINUS:
						key_minus=1;
					break;
					case SDLK_ESCAPE:
						key_esc=1;
					break;
					
					case SDLK_F1:
						key_f1=1;
					break;
					case SDLK_F2:
						key_f2=1;
					break;
					case SDLK_F3:
						key_f3=1;
					break;
					case SDLK_F4:
						key_f4=1;
					break;
					case SDLK_F5:
						key_f5=1;
					break;
					case SDLK_F6:
						key_f6=1;
					break;
					case SDLK_F7:
						key_f7=1;
					break;
					case SDLK_F8:
						key_f8=1;
					break;
					case SDLK_F9:
						key_f9=1;
					break;
					case SDLK_F10:
						key_f10=1;
					break;
					case SDLK_F11:
						key_f11=1;
					break;
					case SDLK_F12:
						key_f12=1;
					break;
					case SDLK_KP_ENTER:
					case SDLK_RETURN:
						key_enter=1;
						
						if(one_line_input)
							break;
						char_add=1;
						
						if(key_input)
						endLine();
						/*
						if(key_input)
						{
							int i,j=0;
							
							for(i=cursor_i; key_string_ptr->str[i]!='\n' && i>=0; i--);
							i++;
							
							for(; key_string_ptr->str[i]=='\t'; i++,j++);
							
							insertString(key_string_ptr,"\n",cursor_i+1);
							cursor_i++;
							
							if(j>0)
							{
								for(i=0; i<j; i++)
								{
									insertString(key_string_ptr,"\t",cursor_i+1);
									cursor_i++;
								}
							}
							
							calculateRowColumn();
						}*/
						break;
					case SDLK_BACKSPACE:
						key_backspace=1;
						
						if(key_input)
						{
							char_del=1;
							
							if(selected)
							{
								int I[2];
								
								sort2(selection_index[0],selection_index[1],I);
								deleteSubText(key_string_ptr,selection_index[I[0]]+1,selection_index[I[1]]);
								
								cursor_i=selection_index[I[0]];
								
								selected=0;
								break;
							}
							
							
							if(cursor_i<0) break;
							
							deleteSubText(key_string_ptr,cursor_i,cursor_i);
							cursor_i--;
							
							calculateRowColumn();
						}
						break;
					case SDLK_DELETE:
						key_delete=1;
						
						if(key_input)
						{
							char_del=1;
							
							if(selected)
							{
								int I[2];
								
								sort2(selection_index[0],selection_index[1],I);
								deleteSubText(key_string_ptr,selection_index[I[0]]+1,selection_index[I[1]]);
								
								cursor_i=selection_index[I[0]];
								
								selected=0;
								break;
							}
							
							deleteSubText(key_string_ptr,cursor_i+1,cursor_i+1);
							
							calculateRowColumn();
						}
						break;
					case SDLK_TAB:
						key_tab=1;
						
						if(key_input)
						{
							char_add=1;
							
							insertString(key_string_ptr,"\t",cursor_i+1);
							cursor_i++;
							
							calculateRowColumn();
						}
						break;
					case SDLK_0:
						key_0=1;
						break;
					case SDLK_1:
						key_1=1;
						break;
					case SDLK_2:
						key_2=1;
						break;
					case SDLK_3:
						key_3=1;
						break;
					case SDLK_4:
						key_4=1;
						break;
					case SDLK_5:
						key_5=1;
						break;
					case SDLK_6:
						key_6=1;
						break;
					case SDLK_7:
						key_7=1;
						break;
					case SDLK_8:
						key_8=1;
						break;
					case SDLK_9:
						key_9=1;
						break;
					case SDLK_LEFT:
						key_left=1;
						
						cursor_movement=1;
						
						if(cursor_i>=0)
						cursor_i--;
						
						calculateRowColumn();
						break;
					case SDLK_RIGHT:
						key_right=1;
						
						cursor_movement=1;
						
						if(cursor_i<key_string_ptr->length-1)
						cursor_i++;
						
						calculateRowColumn();
						break;
					case SDLK_UP:
						key_up=1;
						
						cursor_movement=1;
						{
							int i,c,c_p,
							row,col,max_col_p;
							
							row=	getRowAtIndex(key_string_ptr->str,cursor_i);
							if(!row) break;
							col= getColumnAtIndex(key_string_ptr->str,cursor_i);
							
							max_col_p	=getMaxColumnAtRow(key_string_ptr->str,row-1);
							
							if(col<max_col_p)
							{
								for(i=cursor_i; key_string_ptr->str[i]!='\n'; i--);
								i--;
								for(		  ; key_string_ptr->str[i]!='\n' && i>=0; i--);
								i++;
								for(c=0		  ; key_string_ptr->str[i]!='\n'; i++)
								{
									if(key_string_ptr->str[i]=='\t')
									{
										c_p=c;
										
										if((c%tab_space)==0)
										c+=tab_space;
										else
										c+=tab_space-(c%tab_space);
										
										if(c>col)
										{
											cursor_i=i-1+!(col-c_p<c-col);
											break;
										}
										
										continue;
									}
									
									c_p=c;
									
									c++;
									
									if(c>col)
									{
										cursor_i=i-1+!(col-c_p<c-col);
										break;
									}
								}
								
							}
							else
							{
								for(i=cursor_i; key_string_ptr->str[i]!='\n'; i--);
								i--;
								cursor_i=i;
							}
							
							calculateRowColumn();
						}
						break;
					case SDLK_DOWN:
						key_down=1;
						
						cursor_movement=1;
						{
							int i,c,c_p,
							row,max_row_number,col,max_col_n;
							
							max_row_number=getMaxRowNumber(key_string_ptr->str);
							
							row=	getRowAtIndex(key_string_ptr->str,cursor_i);
							if(row==max_row_number-1) break;
							col= getColumnAtIndex(key_string_ptr->str,cursor_i);
							
							max_col_n	=getMaxColumnAtRow(key_string_ptr->str,row+1);

							if(col<max_col_n)
							{
								if(col==0)
									cursor_i++;

								for(i=cursor_i; key_string_ptr->str[i]!='\n'; i++);
								i++;
								for(c=0		  ; key_string_ptr->str[i]!='\n'; i++)
								{
									c_p=c;
									
									if(key_string_ptr->str[i]=='\t')
									{
										if((c%tab_space)==0)
										c+=tab_space;
										else
										c+=tab_space-(c%tab_space);
										
										if(c>col)
										{
											cursor_i=i-1+!(col-c_p<c-col);
											break;
										}
										
										continue;
									}
									
									c_p=c;
									
									c++;
									
									if(c>col)
									{
										cursor_i=i-1+!(col-c_p<c-col);
										break;
									}
								}
								
							}
							else
							{
								for(i=cursor_i; key_string_ptr->str[i]!='\n'; i++);
								i++;
								for(		  ; key_string_ptr->str[i]!='\n' && key_string_ptr->str[i]!='\0'; i++);
								i--;
								cursor_i=i;
							}
							
							calculateRowColumn();
						}
						break;
					case SDLK_a:
						key_a=1;
						break;
					case SDLK_b:
						key_b=1;
						break;
					case SDLK_c:
						key_c=1;
						
						if(key_Lctrl || key_Rctrl)
						{
							int I[2];
							
							sort2(selection_index[0],selection_index[1],I);
					
							deleteText(&buffer);
							buffer=subText(key_string_ptr,selection_index[I[0]]+1,selection_index[I[1]]);
						}
						break;
					case SDLK_d:
						key_d=1;
						break;
					case SDLK_e:
						key_e=1;
						break;
					case SDLK_f:
						key_f=1;
						break;
					case SDLK_g:
						key_g=1;
						break;
					case SDLK_h:
						key_h=1;
						break;
					case SDLK_i:
						key_i=1;
						break;
					case SDLK_j:
						key_j=1;
						break;
					case SDLK_k:
						key_k=1;
						break;
					case SDLK_l:
						key_l=1;
						break;
					case SDLK_m:
						key_m=1;
						break;
					case SDLK_n:
						key_n=1;
						break;
					case SDLK_o:
						key_o=1;
						break;
					case SDLK_q:
						key_q=1;
						break;
					case SDLK_p:
						key_p=1;
						break;
					case SDLK_r:
						key_r=1;
						break;
					case SDLK_s:
						key_s=1;
						break;
					case SDLK_t:
						key_t=1;
						break;
					case SDLK_u:
						key_u=1;
						break;
					case SDLK_v:
						key_v=1;
						
						if(key_Lctrl || key_Rctrl)
						{
							if(selected)
							{
								int I[2];
					
								sort2(selection_index[0],selection_index[1],I);
								
								deleteSubText(key_string_ptr,selection_index[I[0]]+1,selection_index[I[1]]);
								
								cursor_i=selection_index[I[0]];
								
								selected=0;
							}
							insertString(key_string_ptr,buffer.str,cursor_i+1);
							
							cursor_i+=buffer.length;
						}
						break;
					case SDLK_w:
						key_w=1;
						break;
					case SDLK_x:
						key_x=1;
						break;
					case SDLK_y:
						key_y=1;
						break;
					case SDLK_z:
						key_z=1;
						break;
				}
				break;
			case SDL_KEYUP:
				switch(event.key.keysym.sym)
				{
					case SDLK_KP_0:
						key_kp_0=0;
					break;
					case SDLK_KP_1:
						key_kp_1=0;
					break;
					case SDLK_KP_2:
						key_kp_2=0;
					break;
					case SDLK_KP_3:
						key_kp_3=0;
					break;
					case SDLK_KP_4:
						key_kp_4=0;
					break;
					case SDLK_KP_5:
						key_kp_5=0;
					break;
					case SDLK_KP_6:
						key_kp_6=0;
					break;
					case SDLK_KP_7:
						key_kp_7=0;
					break;
					case SDLK_KP_8:
						key_kp_8=0;
					break;
					case SDLK_KP_9:
						key_kp_9=0;
					break;
					case SDLK_RALT:
						key_Ralt=0;
					break;
					case SDLK_LALT:
						key_Lalt=0;
					break;
					case SDLK_RCTRL:
						key_Rctrl=0;
					break;
					case SDLK_LCTRL:
						key_Lctrl=0;
					break;
					case SDLK_RSHIFT:
						key_Rshift=0;
					break;
					case SDLK_LSHIFT:
						key_Lshift=0;
					break;
					case SDLK_KP_PLUS:
						key_plus=0;
					break;
					case SDLK_KP_MINUS:
						key_minus=0;
					break;
					case SDLK_ESCAPE:
						key_esc=0;
					break;
					
					case SDLK_F1:
						key_f1=0;
					break;
					case SDLK_F2:
						key_f2=0;
					break;
					case SDLK_F3:
						key_f3=0;
					break;
					case SDLK_F4:
						key_f4=0;
					break;
					case SDLK_F5:
						key_f5=0;
					break;
					case SDLK_F6:
						key_f6=0;
					break;
					case SDLK_F7:
						key_f7=0;
					break;
					case SDLK_F8:
						key_f8=0;
					break;
					case SDLK_F9:
						key_f9=0;
					break;
					case SDLK_F10:
						key_f10=0;
					break;
					case SDLK_F11:
						key_f11=0;
					break;
					case SDLK_F12:
						key_f12=0;
					break;
					case SDLK_KP_ENTER:
					case SDLK_RETURN:
						key_enter=0;
						break;
					case SDLK_BACKSPACE:
						key_backspace=0;
						break;
					case SDLK_DELETE:
						key_delete=0;
						break;
					case SDLK_TAB:
						key_tab=0;
						break;
					case SDLK_0:
						key_0=0;
						break;
					case SDLK_1:
						key_1=0;
						break;
					case SDLK_2:
						key_2=0;
						break;
					case SDLK_3:
						key_3=0;
						break;
					case SDLK_4:
						key_4=0;
						break;
					case SDLK_5:
						key_5=0;
						break;
					case SDLK_6:
						key_6=0;
						break;
					case SDLK_7:
						key_7=0;
						break;
					case SDLK_8:
						key_8=0;
						break;
					case SDLK_9:
						key_9=0;
						break;
					case SDLK_LEFT:
						key_left=0;
						break;
					case SDLK_RIGHT:
						key_right=0;
						break;
					case SDLK_UP:
						key_up=0;
						break;
					case SDLK_DOWN:
						key_down=0;
						break;
					case SDLK_a:
						key_a=0;
						break;
					case SDLK_b:
						key_b=0;
						break;
					case SDLK_c:
						key_c=0;
						break;
					case SDLK_d:
						key_d=0;
						break;
					case SDLK_e:
						key_e=0;
						break;
					case SDLK_f:
						key_f=0;
						break;
					case SDLK_g:
						key_g=0;
						break;
					case SDLK_h:
						key_h=0;
						break;
					case SDLK_i:
						key_i=0;
						break;
					case SDLK_j:
						key_j=0;
						break;
					case SDLK_k:
						key_k=0;
						break;
					case SDLK_l:
						key_l=0;
						break;
					case SDLK_m:
						key_m=0;
						break;
					case SDLK_n:
						key_n=0;
						break;
					case SDLK_o:
						key_o=0;
						break;
					case SDLK_q:
						key_q=0;
						break;
					case SDLK_p:
						key_p=0;
						break;
					case SDLK_r:
						key_r=0;
						break;
					case SDLK_s:
						key_s=0;
						break;
					case SDLK_t:
						key_t=0;
						break;
					case SDLK_u:
						key_u=0;
						break;
					case SDLK_v:
						key_v=0;
						break;
					case SDLK_w:
						key_w=0;
						break;
					case SDLK_x:
						key_x=0;
						break;
					case SDLK_y:
						key_y=0;
						break;
					case SDLK_z:
						key_z=0;
						break;
				}	
				break;
			case SDL_MOUSEBUTTONDOWN:
				switch(event.button.button)
				{
					case SDL_BUTTON_LEFT:
						mb_left=1;
					break;
					case SDL_BUTTON_RIGHT:
						mb_right=1;
					break;
					case SDL_BUTTON_MIDDLE:
						mb_middle=1;
					break;
					default:
					;
				}
			break;
			case SDL_MOUSEBUTTONUP:
				switch(event.button.button)
				{
					case SDL_BUTTON_LEFT:
						mb_left=0;
					break;
					case SDL_BUTTON_RIGHT:
						mb_right=0;
					break;
					case SDL_BUTTON_MIDDLE:
						mb_middle=0;
					break;
					default:
					;
				}
			break;
			/*case SDL_MOUSEMOTION:
				{
					int x,y;
					SDL_GetMouseState(&x,&y);
					printf("(%d,%d)\n",x,y);
				}
			break;*/
		}
	}
	
	mouse_xp=mouse_x;
	mouse_yp=mouse_y;
	
	if(key_f4==1 && key_f4_p==0)
	{
		fullscreen=!fullscreen;
		if(fullscreen)
		{
			SDL_SetWindowFullscreen(window,SDL_WINDOW_FULLSCREEN);
			/*SDL_MaximizeWindow(window);*/
			SDL_GetWindowSize(window,&fullscreen_w,&fullscreen_h);
		}
		else
			SDL_SetWindowFullscreen(window,SDL_FALSE);
	}
	
	if(fullscreen)
	{
		SDL_GetMouseState(&mouse_x,&mouse_y);
		mouse_x=mouse_x*W/fullscreen_w;
		mouse_y=mouse_y*H/fullscreen_h;
	}
	else
		SDL_GetMouseState(&mouse_x,&mouse_y);
	
	if(key_esc) quit=1;
	/*if(key_tab && !key_tab_p)
	{
		
	}*/
}

int mbLeftPress()
{
	return (mb_left && !mb_left_p);
}

int mbRightPress()
{
	return (mb_right && !mb_right_p);
}

int mbLeftRelease()
{
	return (!mb_left && mb_left_p);
}

int mbRightRelease()
{
	return (!mb_right && mb_right_p);
}

void initMouseDragging()
{
	SDL_WarpMouseInWindow(window,W/2,H/2);
	mouse_x=W/2;
	mouse_y=H/2;
}

void getMouseDraggingValue(int *x,int *y)
{
	*x=0;
	*y=0;
	
	if(!(mouse_x==W/2 && mouse_y==H/2))
	{
		*x=mouse_x-W/2;
		*y=mouse_y-H/2;
		
		SDL_WarpMouseInWindow(window,W/2,H/2);
		mouse_x=W/2;
		mouse_y=H/2;
	}
}

void UpdateScreen()
{
	SDL_UpdateTexture(texture, NULL, screen_buffer.pixels, W * 4*sizeof(char));
	SDL_RenderClear(renderer);
	SDL_RenderCopy(renderer, texture, NULL, NULL);
	
	SDL_RenderPresent(renderer);
}

void UpdateScreen_OpenGL()
{
	SDL_GL_SwapWindow(window);
}

int in=0;
clock_t calculation_time=0;

int target_fps=30;
int fps=0;
int Update()
{
	char_del=0;
	char_add=0;
	cursor_movement=0;
	
	UpdateEvents();
	UpdateScreen();
	
	fps++;
	if(fps==target_fps)
		fps=0;
	
	if(in)
	{
		int count=1000/target_fps-((clock()-calculation_time)/**1000/CLOCKS_PER_SEC*/);
		
		if(count>0)
		SDL_Delay(count);
	}
	in=1;
	calculation_time=clock();
	
	return 0;
}

int Update_OpenGL()
{
	char_del=0;
	char_add=0;
	cursor_movement=0;
	
	UpdateEvents();
	UpdateScreen_OpenGL();

	fps++;
	if(fps==target_fps)
		fps=0;
	
	if(in)
	{
		int count=33-((clock()-calculation_time)/**1000/CLOCKS_PER_SEC*/);
		
		if(count>0)
		SDL_Delay(count);
	}
	in=1;
	calculation_time=clock();
	
	return 0;
}

u8* loadPixels(char *file_path,int *w,int *h)
{
	SDL_Surface *tmp=IMG_Load(file_path);
	u8* pixels=malloc(tmp->w*tmp->h*4);
	
	*w=tmp->w;
	*h=tmp->h;
	
	{
		int i,j,k=0;
		for(j=0; j<tmp->h; j++)
			for(i=0; i<tmp->w; i++,k++)
			{
				Uint32 p;
				Uint8 r,g,b,a;
				p=getpixel(tmp,i,j);
				SDL_GetRGBA(p,tmp->format,&r,&g,&b,&a);
				pixels[k*4  ]=r;
				pixels[k*4+1]=g;
				pixels[k*4+2]=b;
				pixels[k*4+3]=a;
			}
	}
	
	SDL_FreeSurface(tmp);
	
	return pixels;
}

int file_exists(char *file_path)
{
	FILE *file;
	if((file=fopen(file_path,"r")))
	{
		fclose(file);
		
		return 1;
	}
	return 0;
}

void IO_Init(char* window_title)
{
	screen_buffer.pixels = malloc(N*4*sizeof(char));
	screen_buffer.w=W;
	screen_buffer.h=H;
	current_buffer=&screen_buffer;
	
	SDL_Init(SDL_INIT_VIDEO);
	IMG_Init(IMG_INIT_PNG);
	
    window = SDL_CreateWindow(window_title,
        SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SIZE_W, SIZE_H, 0);

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_PRESENTVSYNC);
	texture = SDL_CreateTexture(renderer,
		SDL_PIXELFORMAT_ARGB8888, SDL_TEXTUREACCESS_STATIC, W, H);
	
	SDL_GetMouseState(&mouse_x,&mouse_y);
	mouse_xp=mouse_x;
	mouse_yp=mouse_y;
	
	key_string_ptr=&default_key_string;
	
	buffer=empty_text;
}
/*
void glCheckErrors()
{
	switch(glGetError()) 
		{
			case GL_NO_ERROR:
			printf("no error\n");
			break;
			case GL_INVALID_ENUM:
			printf("invalid enum\n");
			break;
			case GL_INVALID_OPERATION:
			printf("invalid operation\n");
			break;
			case GL_INVALID_VALUE:
			printf("invalid value\n");
			break;
			case GL_INVALID_FRAMEBUFFER_OPERATION:
			printf("invalid framebuffer operation\n");
			break;
			case GL_OUT_OF_MEMORY:
			printf("out of memory\n");
			break;
		}
}*/

GLuint createShader(const char *source,GLenum type)
{
	GLuint shader;
	GLint compiled;
	
	shader=glCreateShader(type);
	
		
	
	if(!shader) return 0;

	printf("here\n");
	
	glShaderSource(shader,1,&source,NULL);
	glCompileShader(shader);
	glGetShaderiv(shader,GL_COMPILE_STATUS,&compiled);
	
	if(!compiled)
	{
		GLint infoLen=0;
		char *infoLog;
		
		glGetShaderiv(shader,GL_INFO_LOG_LENGTH,&infoLen);
		
		
		
		if(infoLen>1)
		{
			
			
			infoLen=malloc(sizeof(char)*infoLen);
			glGetShaderInfoLog(shader,infoLen,NULL,infoLog);
			printf("%s\n",infoLog);
			free(infoLog);
		}
		
		glDeleteShader(shader);
		
		printf("unable to compile the shader\n");
		
		return 0;
	}
	
	printf("Shader compiled successfully\n");
	return shader;
}

GLuint createProgram(GLchar *vertex_shader_str,GLchar *fragment_shader_str)
{	
	GLuint vertex_shader,fragment_shader,program;
	
	vertex_shader = createShader(vertex_shader_str,GL_VERTEX_SHADER);
	fragment_shader = createShader(fragment_shader_str,GL_FRAGMENT_SHADER);
	
    program = glCreateProgram();
    glAttachShader(program, vertex_shader);
    glAttachShader(program, fragment_shader);
	
	{
		GLint linked;
		
		glLinkProgram(program);
		
		glGetProgramiv(program,GL_LINK_STATUS,&linked);
		
		printf("<%d>\n",linked);
	}
	
	glUseProgram(program);
	
	return program;
}

GLuint GLprogram;
GLint uniColor;
GLint uniSampler;
GLint uniTexturing;
GLint uniTransform;
GLint uniBorder;

GLint attPosition;
GLint attTexCoord;

GLfloat transformMatrix[16]=
{
	1,0,0,0,
	0,1,0,0,
	0,0,1,0,
	0,0,0,1
};

void transform(matrix4f m)
{
	transformMatrix[ 0]=m.col[0].e[0]; transformMatrix[ 4]=m.col[1].e[0]; transformMatrix[ 8]=m.col[2].e[0]; transformMatrix[12]=m.col[3].e[0];
	transformMatrix[ 1]=m.col[0].e[1]; transformMatrix[ 5]=m.col[1].e[1]; transformMatrix[ 9]=m.col[2].e[1]; transformMatrix[13]=m.col[3].e[1];
	transformMatrix[ 2]=m.col[0].e[2]; transformMatrix[ 6]=m.col[1].e[2]; transformMatrix[10]=m.col[2].e[2]; transformMatrix[14]=m.col[3].e[2];
	transformMatrix[ 3]=m.col[0].e[3]; transformMatrix[ 7]=m.col[1].e[3]; transformMatrix[11]=m.col[2].e[3]; transformMatrix[15]=m.col[3].e[3];
	
	glUniformMatrix4fv(uniTransform,1,GL_FALSE,transformMatrix);
}

void initOpenGL()
{
	const char* vertex_shader_text =
	"attribute vec2 texcoord;\n"
	"attribute vec3 position;\n"
	"uniform mat4 transform;\n"
	"varying vec2 interpolated_texcoord;\n"
	"void main()\n"
	"{\n"
	"	 interpolated_texcoord=texcoord;\n"
	"    gl_Position =transform*vec4(position, 1.0);\n"
	"}\n";
	const char* fragment_shader_text =
	"uniform vec4 color;"
	"varying vec2 interpolated_texcoord;"
	"uniform sampler2D tex;"
	"uniform int texturing;"
	"uniform ivec4 border;"
	"void main()\n"
	"{\n"
	"	if(!("
		"(gl_FragCoord.x>=border.x && gl_FragCoord.x<border.x+border.z) &&"
		"(gl_FragCoord.y>=border.y && gl_FragCoord.y<border.y+border.w)"
		"))"
		"discard;"
	"	vec4 result;"
	"	result =(texture2D(tex,interpolated_texcoord)*texturing+(1-texturing))*color;\n"
	"	if(result.a>-0.001 && result.a<0.001) discard;"
	"	gl_FragColor=result;"
	"}\n";
	
	GLprogram=createProgram(vertex_shader_text,fragment_shader_text);
	
	attPosition=glGetAttribLocation(GLprogram,"position");
	attTexCoord=glGetAttribLocation(GLprogram,"texcoord");
	
	uniColor=glGetUniformLocation(GLprogram,"color");
	uniSampler=glGetUniformLocation(GLprogram,"tex");
	uniTexturing=glGetUniformLocation(GLprogram,"texturing");
	uniTransform=glGetUniformLocation(GLprogram,"transform");
	uniBorder=glGetUniformLocation(GLprogram,"border");
	
	printf("(%i,%i,%i,%i,%i,%i)",GLprogram,uniColor,uniSampler,uniTexturing,uniTransform,uniBorder);
	
	glUniformMatrix4fv(uniTransform,1,GL_FALSE,transformMatrix);
	
	glUniform1i(uniTexturing,0);
	
	glEnable(GL_TEXTURE_2D);
	/*glActiveTexture(GL_TEXTURE0);*/
	glBindTexture(GL_TEXTURE_2D,0);
	/*glUniform1i(uniSampler,0);*/
	
	glEnable(GL_DEPTH_TEST);
	
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE_MINUS_SRC_ALPHA);
	
	glViewport(0,0,W,H);
	
	glClearColor(0.0,0.0,0.0,1.0);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
}

void borderless();

SDL_GLContext glcontext;
void IO_Init_OpenGL(char* window_title)
{
	SDL_GLContext glc;

	if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
		printf("could not initialize sdl2: %s\n", SDL_GetError());
		return 1;
	}
	
	SDL_GL_LoadLibrary(NULL);
	
	/*SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_FORWARD_COMPATIBLE_FLAG);*/
	

	SDL_GL_SetAttribute(SDL_GL_ACCELERATED_VISUAL, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 2);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 1);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
	/*SDL_GL_SetSwapInterval(0);*/
	SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE, 24);

	SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8);
	
	window = SDL_CreateWindow(window_title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, W, H,SDL_WINDOW_OPENGL);
	
	glc = SDL_GL_CreateContext(window);
	
	if (!gladLoadGLLoader(SDL_GL_GetProcAddress))
        printf("Failed to initialize OpenGL context");
	
	initOpenGL();
	
	SDL_GetMouseState(&mouse_x,&mouse_y);
	mouse_xp=mouse_x;
	mouse_yp=mouse_y;
	
	key_string_ptr=&default_key_string;
	
	buffer=empty_text;
	
	borderless();
}

void IO_Quit()
{
	deleteText(&buffer);	
	deleteText(&default_key_string);
	
	SDL_DestroyTexture(texture);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    
    free(screen_buffer.pixels);
}

void IO_Quit_OpenGL()
{	
	deleteText(&buffer);
	deleteText(&default_key_string);

	SDL_GL_DeleteContext(glcontext);
    SDL_DestroyWindow(window);
    SDL_Quit();
}

#endif
