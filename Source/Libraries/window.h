/*
Copyright (C) <2018-2019> <Tankut Zeytinoğlu>
You can find the text of zlib license in the root folder.
*/

#ifndef WINDOW_H
#define WINDOW_H

typedef struct{
	int x,y,
	*target_x,*target_y,
	attachment_offset_x,attachment_offset_y,
	attach;
	
	int active;
	int lock;
	
	int type;
	void* ptr;
}Element;

Element* ElementC(int x, int y,int type,void* ptr)
{
	Element *E;
	
	E=malloc(sizeof(Element));
	E->x=x;
	E->y=y;
	E->type=type;
	E->ptr=ptr;
	E->active=0;
	E->lock=1;
	E->attach=0;
	
	return E;
}

void ElementD(Element* E)
{
	free(E);
}

int ElementFollowAttachment(Element *E)
{
	if(E->attach)
	{
		E->x=*E->target_x+E->attachment_offset_x;
		E->y=*E->target_y+E->attachment_offset_y;
		
		return 1;
	}
	return 0;
}

int click_mouse_x,click_mouse_y;

typedef struct{
	int selected;
	int size;

	Element *E;
}Checkbox;

Checkbox* CheckboxC(int size)
{
	Checkbox *cb;
	
	cb=malloc(sizeof(Checkbox));
	
	cb->size=size;
	
	return cb;
}

void CheckboxD(Checkbox *cb)
{
	free(cb);
}

int CheckboxOn(Checkbox *cb)
{
	return 
	((mouse_x>=cb->E->x && mouse_x<cb->E->x+cb->size) &&
	 (mouse_y>=cb->E->y && mouse_y<cb->E->y+cb->size));
}

void CheckboxUpdate(void *ptr)
{
	Checkbox *cb;
	cb=ptr;

	if(mbLeftPress())
	{
		if(CheckboxOn(cb)) cb->selected=!cb->selected;
	}
}

void CheckboxDraw(void *ptr)
{
	Checkbox *cb;
	cb=ptr;
	
	borderless();
	texturing(0);
	
	setColor2HW(255,255,255);
	drawRectanglefHW(vec2f(cb->E->x,cb->E->y),vec2f(cb->E->x+cb->size,cb->E->y+cb->size));
	setColor2HW(0,0,0);
	drawRectangleFramefHW(vec2f(cb->E->x,cb->E->y),vec2f(cb->E->x+cb->size,cb->E->y+cb->size));
	
	if(cb->selected)
	{
		/*dra*/
	}
}

typedef struct{
	style s;
	text content;

	Element *E;
}Text;

Text* TextC(char *str)
{
	Text *txt;
	
	txt=malloc(sizeof(Text));
	
	txt->s=cstyle;
	txt->content=empty_text;
	setText(&txt->content,str);
	
	return txt;
}

void TextD(Text *txt)
{
	deleteText(&txt->content);
	free(txt);
}

void TextUpdate(void *ptr)
{
	Text *txt;
	txt=ptr;

}

void TextDraw(void *ptr)
{
	Text *txt;
	txt=ptr;
	
	borderless();
	useStyle(txt->s);
	texturing(0);
	
	drawStringHW(txt->content.str,txt->E->x,txt->E->y);
}


typedef struct{
	text name;
	int id;
}Item;

Item ItemC(char *name,int id)
{
	Item item;
	
	item.name=empty_text;
	setText(&item.name,name);
	item.id=id;
	
	return item;
}

void ItemD(Item *item)
{
	deleteText(&item->name);
}

typedef struct{
	style s;
	Item* item;
	int n;
	int offset;
	int w;
	
	int open;
	
	int slider;
	int slider_button_offset;
	int slider_button_size;
	int slider_dragging;
	int max_item_number;
	int click_offset;
	
	int chosen_i;
	Element *E;
}Submenu;

Submenu* SubmenuC(int w)
{
	Submenu *submenu;
	
	submenu=malloc(sizeof(Submenu));
	submenu->n=0;
	submenu->item=0;
	submenu->chosen_i=0;
	
	submenu->w=w;
	
	submenu->s=cstyle;
	
	submenu->open=0;
	submenu->offset=0;
	
	submenu->slider=0;
	submenu->slider_button_offset=0;
	submenu->slider_button_size=0;
	submenu->slider_dragging=0;
	
	return submenu;
}

void SubmenuD(void *ptr)
{
	Submenu *submenu;
	submenu=ptr;
	
	{
		int i;
		for(i=0; i<submenu->n; i++)
			ItemD(&submenu->item[i]);
		
		free(submenu->item);

	}
	
	free(submenu);
}

int item_id=0;
void addItemToSubmenu(Submenu *submenu,char *name)
{
	Item *new_item;
	
	new_item=malloc(sizeof(Item)*(submenu->n+1));
	
	{
		int i;
		for(i=0; i<submenu->n; i++)
			new_item[i]=submenu->item[i];
		new_item[i]=ItemC(name,item_id++);
		
		if(submenu->n)
			free(submenu->item);
		
		submenu->item=new_item;
		submenu->n++;
	}
}

void addItemToSubmenu2(Submenu *submenu,char *name,int id)
{
	Item *new_item;
	
	new_item=malloc(sizeof(Item)*(submenu->n+1));
	
	{
		int i;
		for(i=0; i<submenu->n; i++)
			new_item[i]=submenu->item[i];
		new_item[i]=ItemC(name,id);
		
		if(submenu->n)
			free(submenu->item);
		
		submenu->item=new_item;
		submenu->n++;
	}
}

int SubmenuOn(Submenu *submenu)
{
	useStyle(submenu->s);
	
	return
	(mouse_x>=submenu->E->x && mouse_x<submenu->E->x+submenu->w+cstyle.scaler*cstyle.default_h) &&
	(mouse_y>=submenu->E->y && mouse_y<submenu->E->y+cstyle.scaler*cstyle.default_h);
}

void SubmenuUpdate(void *ptr)
{
	Submenu *submenu;
	submenu=ptr;
	
	useStyle(submenu->s);
	
	
	{
		float h=cstyle.scaler*cstyle.default_h;
		
		if(mbLeftPress())
		{	
			int i,onclick;
			
			if(submenu->open)
			{
				onclick=0;
				for(i=0; i<submenu->n; i++)
				{
					
					if
					(
						(mouse_x>=submenu->E->x 		&& mouse_x<submenu->E->x+submenu->w) &&
						(
							mouse_y>=submenu->E->y+h*(i+1)+submenu->offset && 
							mouse_y< submenu->E->y+h*(i+2)+submenu->offset
						
						)
					)
					{onclick=1;  break;}
				}
			
				if(onclick)
				{
					submenu->chosen_i=i;
					submenu->open=0;
				}
				else
				{
					if(submenu->slider)
					if
					(
						(mouse_x>=submenu->E->x+submenu->w && mouse_x<submenu->E->x+submenu->w+h) &&
						(
						 mouse_y>=submenu->E->y+h*2+submenu->slider_button_offset &&
						 mouse_y<submenu->E->y+h*2+submenu->slider_button_offset+submenu->slider_button_size
						)
					)
					{
						submenu->click_offset=submenu->slider_button_offset;
						click_mouse_y=mouse_y;
						submenu->slider_dragging=1;
					}
				}
			}
			
		}
		if(mbLeftRelease())
			submenu->slider_dragging=0;
		
		if(submenu->slider_dragging)
		{
			submenu->slider_button_offset=submenu->click_offset+mouse_y-click_mouse_y;
			
			if(submenu->slider_button_offset<0)
				submenu->slider_button_offset=0;
			if(submenu->slider_button_offset>(submenu->max_item_number*h-2*h-submenu->slider_button_size))
			submenu->slider_button_offset=(submenu->max_item_number*h-2*h-submenu->slider_button_size);
			
			submenu->offset=-(submenu->n-submenu->max_item_number)*h*
			submenu->slider_button_offset/(submenu->max_item_number*h-2*h-submenu->slider_button_size);
		}
		
		
		if(!submenu->E->lock)
		{
			if(SubmenuOn(submenu) && mbLeftPress())
			{
				submenu->open=!submenu->open;
				submenu->slider=0;
				submenu->offset=0;
				if((H-submenu->E->y)<(submenu->n+1)*h)
				{
					submenu->max_item_number=(int)((H-submenu->E->y)/h)-1;
					submenu->slider=1;
					submenu->slider_button_size=(submenu->max_item_number*h-2*h)*submenu->max_item_number/(float)submenu->n;
					submenu->slider_button_offset=0;
				}
			}
		}
	
	}
}

void SubmenuDraw(void *ptr)
{
	Submenu *submenu;
	submenu=ptr;
	
	borderless();
	
	{
		float scale;
		float h=cstyle.scaler*cstyle.default_h;
		
		texturing(0);
	
		useStyle(submenu->s);
		
		setColor2HW(255,255,255);
		drawRectanglefHW(vec2f(submenu->E->x,submenu->E->y),vec2f(submenu->E->x+submenu->w,submenu->E->y+h));
		
		setColor2HW(0,0,0);
		drawRectangleFramefHW(vec2f(submenu->E->x,submenu->E->y),vec2f(submenu->E->x+submenu->w,submenu->E->y+h));
		
		setColor2HW(128,128,0);
		drawRectanglefHW(vec2f(submenu->E->x+submenu->w,submenu->E->y),vec2f(submenu->E->x+cstyle.scaler*cstyle.default_h+submenu->w,submenu->E->y+h));
		
		setColor2HW(0,0,0);
		drawRectangleFramefHW(vec2f(submenu->E->x+submenu->w,submenu->E->y),vec2f(submenu->E->x+cstyle.scaler*cstyle.default_h+submenu->w,submenu->E->y+h));
		
		setColor2HW(0,0,0);
		
		scale=1/16.0f*h;
		
		drawLinefHW(vec2f(submenu->E->x+submenu->w+(8)*scale,submenu->E->y+(16-5)*scale),vec2f(submenu->E->x+submenu->w+(4)*scale,submenu->E->y+(6)*scale));
		drawLinefHW(vec2f(submenu->E->x+submenu->w+(8)*scale,submenu->E->y+(16-5)*scale),vec2f(submenu->E->x+submenu->w+(16-4)*scale,submenu->E->y+(6)*scale));
		
		if(submenu->slider)
		{
			if(submenu->open)
			{
				int i;

				drawingBorder(submenu->E->x,submenu->E->y+h,submenu->w+h,h*submenu->max_item_number);

				for(i=0; i<submenu->n; i++)
				{
					setColor2HW(255,255,255);
					if
					(
						(mouse_x>=submenu->E->x 		&& mouse_x<submenu->E->x+submenu->w) &&
						(
						 mouse_y>=submenu->E->y+h*(i+1)+submenu->offset && 
						 mouse_y< submenu->E->y+h*(i+2)+submenu->offset
						)
					)
					setColor2HW(0,0,255);
					drawRectanglefHW(vec2f(submenu->E->x,submenu->E->y+h*(i+1)+submenu->offset),vec2f(submenu->E->x+submenu->w,submenu->E->y+h*(i+2)+submenu->offset));	
				}
				
				setColor2HW(0,0,0);
				drawRectangleFramefHW(vec2f(submenu->E->x,submenu->E->y+h),vec2f(submenu->E->x+submenu->w,submenu->E->y+h*(submenu->max_item_number+1)));
				
				setColor2HW(64,64,64);
				drawRectanglefHW(vec2f(submenu->E->x+submenu->w,submenu->E->y+h),vec2f(submenu->E->x+submenu->w+h,submenu->E->y+h*(i+1)));
				
				setColor2HW(0,0,0);
				drawRectangleFramefHW(vec2f(submenu->E->x+submenu->w,submenu->E->y+h),vec2f(submenu->E->x+submenu->w+h,submenu->E->y+h*(i+1)));
				
				setColor2HW(128,128,0);
				drawRectanglefHW(vec2f(submenu->E->x+submenu->w,submenu->E->y+h),vec2f(submenu->E->x+submenu->w+h,submenu->E->y+h*2));
				
				setColor2HW(0,0,0);
				drawRectangleFramefHW(vec2f(submenu->E->x+submenu->w,submenu->E->y+h),vec2f(submenu->E->x+submenu->w+h,submenu->E->y+h*2));
				
				setColor2HW(128,128,0);
				drawRectanglefHW(vec2f(submenu->E->x+submenu->w,submenu->E->y+h*(submenu->max_item_number)),vec2f(submenu->E->x+submenu->w+h,submenu->E->y+h*(submenu->max_item_number+1)));
				
				setColor2HW(0,0,0);
				drawRectangleFramefHW(vec2f(submenu->E->x+submenu->w,submenu->E->y+h*(submenu->max_item_number)),vec2f(submenu->E->x+submenu->w+h,submenu->E->y+h*(submenu->max_item_number+1)));
				
				drawLinefHW(vec2f(submenu->E->x+submenu->w+(8)*scale,submenu->E->y+(16-5)*scale+h*submenu->max_item_number),vec2f(submenu->E->x+submenu->w+(4)*scale,submenu->E->y+(6)*scale+h*submenu->max_item_number));
				drawLinefHW(vec2f(submenu->E->x+submenu->w+(8)*scale,submenu->E->y+(16-5)*scale+h*submenu->max_item_number),vec2f(submenu->E->x+submenu->w+(16-4)*scale,submenu->E->y+(6)*scale+h*submenu->max_item_number));
				
				drawLinefHW(vec2f(submenu->E->x+submenu->w+(8)*scale,submenu->E->y+(6)*scale+h),vec2f(submenu->E->x+submenu->w+(4)*scale,submenu->E->y+(16-5)*scale+h));
				drawLinefHW(vec2f(submenu->E->x+submenu->w+(8)*scale,submenu->E->y+(6)*scale+h),vec2f(submenu->E->x+submenu->w+(16-4)*scale,submenu->E->y+(16-5)*scale+h));
				
				setColor2HW(128,128,128);
				drawRectanglefHW(vec2f(submenu->E->x+submenu->w,submenu->E->y+h*2+submenu->slider_button_offset),vec2f(submenu->E->x+submenu->w+h,submenu->E->y+h*2+submenu->slider_button_offset+submenu->slider_button_size));
				
				setColor2HW(0,0,0);
				drawRectangleFramefHW(vec2f(submenu->E->x+submenu->w,submenu->E->y+h*2+submenu->slider_button_offset),vec2f(submenu->E->x+submenu->w+h,submenu->E->y+h*2+submenu->slider_button_offset+submenu->slider_button_size));
				/*
				drawingBorder(submenu->E->x,submenu->E->y,submenu->w,h*(i+1));*/
				texturing(1);

				for(i=0; i<submenu->n; i++)
				{	
					cstyle.c=col(0,0,0);
					if
					(
						(mouse_x>=submenu->E->x 		&& mouse_x<submenu->E->x+submenu->w) &&
						(
						 mouse_y>=submenu->E->y+h*(i+1)+submenu->offset && 
						 mouse_y< submenu->E->y+h*(i+2)+submenu->offset
						)
					)
					cstyle.c=col(255,255,255);
					
					drawStringHW(submenu->item[i].name.str,submenu->E->x+3,submenu->E->y+h*(i+1)+submenu->offset);	
				}	
				
			}
		}
		else
		{
			if(submenu->open)
			{
				int i;

				for(i=0; i<submenu->n; i++)
				{
					setColor2HW(255,255,255);
					if
					(
						(mouse_x>=submenu->E->x 		&& mouse_x<submenu->E->x+submenu->w) &&
						(mouse_y>=submenu->E->y+h*(i+1) && mouse_y<submenu->E->y+h*(i+2))
					)
					setColor2HW(0,0,255);
					drawRectanglefHW(vec2f(submenu->E->x,submenu->E->y+h*(i+1)),vec2f(submenu->E->x+submenu->w,submenu->E->y+h*(i+2)));	
				}
				setColor2HW(0,0,0);
				drawRectangleFramefHW(vec2f(submenu->E->x,submenu->E->y+h),vec2f(submenu->E->x+submenu->w,submenu->E->y+h*(i+1)));
				
				drawingBorder(submenu->E->x,submenu->E->y,submenu->w,h*(i+1));
				texturing(1);

				for(i=0; i<submenu->n; i++)
				{	
					cstyle.c=col(0,0,0);
					if
					(
						(mouse_x>=submenu->E->x 		&& mouse_x<submenu->E->x+submenu->w) &&
						(mouse_y>=submenu->E->y+h*(i+1) && mouse_y<submenu->E->y+h*(i+2))
					)
					cstyle.c=col(255,255,255);
					
					drawStringHW(submenu->item[i].name.str,submenu->E->x+3,submenu->E->y+h*(i+1));	
				}
				
			}
		}
		
		drawingBorder(submenu->E->x,submenu->E->y,submenu->w,h);
		
		texturing(1);
		
		cstyle.c=col(0,0,0);
		drawStringHW(submenu->item[submenu->chosen_i].name.str,submenu->E->x+3,submenu->E->y);
		
		borderless();
	}
	
	
}

typedef struct{
	style s;
	text content;
	int w,h;
	
	int pressed;
	
	Element *E;
}Button;

Button* ButtonC(int w,int h,char *str)
{
	Button *button;
	
	button=malloc(sizeof(Button));
	button->content=empty_text;
	setText(&button->content,str);

	button->w=w;
	button->h=h;
	
	button->s=cstyle;
	
	button->pressed=0;
	
	return button;
}

void ButtonD(void *ptr)
{
	Button *button;
	button=ptr;
	
	deleteText(&button->content);
	free(button);
}

int ButtonOn(Button *button)
{
	return
	(mouse_x>=button->E->x && mouse_x<button->E->x+button->w) &&
	(mouse_y>=button->E->y && mouse_y<button->E->y+button->h);
}

int ButtonOnClick(Button *button)
{
	int on;
	on=ButtonOn(button);
	if(mbLeftRelease())
	{
		if(on)
		{
			if(button->pressed)
			{
				return 1;
			}
		}
	}
	return 0;
}

void ButtonUpdate(void *ptr)
{
	Button *button;
	button=ptr;
	
	if(!button->E->lock)
	{
		if(ButtonOn(button) && mbLeftPress())
		{
			button->pressed=1;
		}
	}
	if(mbLeftRelease())
	{
		button->pressed=0;
	}
}

void ButtonDraw(void *ptr)
{
	Button *button;
	button=ptr;
	
	borderless();
	
	texturing(0);
	
	setColor2HW(160,160,160);
	if(button->pressed)
	setColor2HW(128,128,128);
	drawRectanglefHW(vec2f(button->E->x,button->E->y),vec2f(button->E->x+button->w,button->E->y+button->h));
	
	setColor2HW(0,0,0);
	drawRectangleFramefHW(vec2f(button->E->x,button->E->y),vec2f(button->E->x+button->w,button->E->y+button->h));
	
	{
		int w,h;
		useStyle(button->s);
		w=getStringWidth(button->content.str);
		h=getStringHeight(button->content.str);
		drawStringHW(button->content.str,button->E->x+(button->w-w)/2,button->E->y+(button->h-h)/2);
	}
}

typedef struct
{
	int dragging;
	
	int length;
	int button_size;
	int button_offset;
	
	Element *E;
}SliderH;

SliderH* SliderHC(int length,int button_size)
{
	SliderH *slider;
	slider=malloc(sizeof(SliderH));
	
	slider->dragging=0;
	
	slider->length=length;
	slider->button_size=button_size;
	slider->button_offset=0;
	
	return slider;
}

void SliderHD(void *ptr)
{
	SliderH *slider;
	slider=ptr;
	
	free(slider);
}

int SliderHOn(SliderH *slider)
{
	return
	(mouse_x>=slider->E->x && mouse_x<slider->E->x+slider->length) &&
	(mouse_y>=slider->E->y && mouse_y<slider->E->y+16);
}

int SliderHButtonOn(SliderH *slider)
{
	return
	(mouse_x>=slider->E->x+16+slider->button_offset && mouse_x<slider->E->x+16+slider->button_offset+slider->button_size) &&
	(mouse_y>=slider->E->y && mouse_y<slider->E->y+16);
}

float SliderHGetRate(SliderH *slider)
{
	return slider->button_offset/(slider->length-32.0f-slider->button_size);
}
void SliderHSetRate(SliderH *slider,float rate)
{
	slider->button_offset=rate*(slider->length-32-slider->button_size);
}

void SliderHSetButtonSizeRate(SliderH *slider,float rate)
{
	slider->button_size=(slider->length-32)*rate;
}


int click_slider_offset;
void SliderHUpdate(void *ptr)
{
	SliderH *slider;
	slider=ptr;
	if(!slider->E->lock)
	{
		if(mbLeftPress())
		{
			if(SliderHButtonOn(slider))
			{
				click_slider_offset=slider->button_offset;
				click_mouse_x=mouse_x;
				slider->dragging=1;
			}
		}
		if(slider->dragging)
		{
			slider->button_offset=click_slider_offset+mouse_x-click_mouse_x;
			
			if(slider->button_offset<0)
				slider->button_offset=0;
			if(slider->button_offset+slider->button_size>slider->length-32)
				slider->button_offset=slider->length-32-slider->button_size;
		}
		if(mbLeftRelease())
			slider->dragging=0;
	}
}

void SliderHDraw(void *ptr)
{
	SliderH *slider;
	slider=ptr;
	
	borderless();
	
	texturing(0);
	
	setColor2HW(64,64,64);
	drawRectanglefHW(vec2f(slider->E->x,slider->E->y),vec2f(slider->E->x+slider->length,slider->E->y+16));
	
	setColor2HW(128,128,0);
	drawRectanglefHW(vec2f(slider->E->x,slider->E->y),vec2f(slider->E->x+16,slider->E->y+16));
	drawRectanglefHW(vec2f(slider->E->x+slider->length-16,slider->E->y),vec2f(slider->E->x+slider->length,slider->E->y+16));
	
	setColor2HW(0,0,0);
	drawLinefHW(vec2f(slider->E->x+5,slider->E->y+8),vec2f(slider->E->x+16-6,slider->E->y+4));
	drawLinefHW(vec2f(slider->E->x+5,slider->E->y+8),vec2f(slider->E->x+16-6,slider->E->y+16-4));
	
	drawLinefHW(vec2f(slider->E->x+slider->length-5,slider->E->y+8),vec2f(slider->E->x+slider->length-16+6,slider->E->y+4));
	drawLinefHW(vec2f(slider->E->x+slider->length-5,slider->E->y+8),vec2f(slider->E->x+slider->length-16+6,slider->E->y+16-4));
	
	setColor2HW(0,0,0);
	drawRectangleFramefHW(vec2f(slider->E->x,slider->E->y),vec2f(slider->E->x+slider->length,slider->E->y+16));
	
	setColor2HW(128,128,128);
	drawRectanglefHW(vec2f(slider->E->x+16+slider->button_offset,slider->E->y),vec2f(slider->E->x+16+slider->button_offset+slider->button_size,slider->E->y+16));
	setColor2HW(0,0,0);
	drawRectangleFramefHW(vec2f(slider->E->x+16+slider->button_offset,slider->E->y),vec2f(slider->E->x+16+slider->button_offset+slider->button_size,slider->E->y+16));
}

typedef struct
{
	int dragging;
	
	int length;
	int button_size;
	int button_offset;
	
	Element *E;
}SliderV;

SliderH* SliderVC(int length,int button_size)
{
	SliderH *slider;
	slider=malloc(sizeof(SliderH));
	
	slider->dragging=0;
	
	slider->length=length;
	slider->button_size=button_size;
	slider->button_offset=0;
	
	return slider;
}

void SliderVD(void *ptr)
{
	SliderV *slider;
	slider=ptr;
	
	free(slider);
}

int SliderVOn(SliderV *slider)
{
	return
	(mouse_y>=slider->E->y && mouse_y<slider->E->y+slider->length) &&
	(mouse_x>=slider->E->x && mouse_x<slider->E->x+16);
}

int SliderVButtonOn(SliderV *slider)
{
	return
	(mouse_y>=slider->E->y+16+slider->button_offset && mouse_y<slider->E->y+16+slider->button_offset+slider->button_size) &&
	(mouse_x>=slider->E->x && mouse_x<slider->E->x+16);
}

float SliderVGetRate(SliderV *slider)
{
	return slider->button_offset/(slider->length-32.0f-slider->button_size);
}

void SliderVSetRate(SliderV *slider,float rate)
{
	slider->button_offset=rate*(slider->length-32-slider->button_size);
}

void SliderVSetButtonSizeRate(SliderV *slider,float rate)
{
	slider->button_size=(slider->length-32)*rate;
}

int click_slider_offset;
void SliderVUpdate(void *ptr)
{
	SliderV *slider;
	slider=ptr;
	
	if(!slider->E->lock)
	{
		if(mbLeftPress())
		{
			if(SliderVButtonOn(slider))
			{
				click_slider_offset=slider->button_offset;
				click_mouse_y=mouse_y;
				slider->dragging=1;
			}
		}
		if(slider->dragging)
		{
			slider->button_offset=click_slider_offset+mouse_y-click_mouse_y;
			
			if(slider->button_offset<0)
				slider->button_offset=0;
			if(slider->button_offset+slider->button_size>slider->length-32)
				slider->button_offset=slider->length-32-slider->button_size;
		}
		if(mbLeftRelease())
			slider->dragging=0;
	}
}

void SliderVDraw(void *ptr)
{
	SliderV *slider;
	slider=ptr;
	
	borderless();
	
	texturing(0);
	
	setColor2HW(64,64,64);
	drawRectanglefHW(vec2f(slider->E->x,slider->E->y),vec2f(slider->E->x+16,slider->E->y+slider->length));
	
	setColor2HW(128,128,0);
	drawRectanglefHW(vec2f(slider->E->x,slider->E->y),vec2f(slider->E->x+16,slider->E->y+16));
	drawRectanglefHW(vec2f(slider->E->x,slider->E->y+slider->length-16),vec2f(slider->E->x+16,slider->E->y+slider->length));
	
	setColor2HW(0,0,0);
	drawLinefHW(vec2f(slider->E->x+8,slider->E->y+5),vec2f(slider->E->x+4,slider->E->y+16-6));
	drawLinefHW(vec2f(slider->E->x+8,slider->E->y+5),vec2f(slider->E->x+16-4,slider->E->y+16-6));
	
	drawLinefHW(vec2f(slider->E->x+8,slider->E->y+slider->length-5),vec2f(slider->E->x+4,slider->E->y+slider->length-16+6));
	drawLinefHW(vec2f(slider->E->x+8,slider->E->y+slider->length-5),vec2f(slider->E->x+16-4,slider->E->y+slider->length-16+6));
	
	setColor2HW(0,0,0);
	drawRectangleFramefHW(vec2f(slider->E->x,slider->E->y),vec2f(slider->E->x+16,slider->E->y+slider->length));
	
	setColor2HW(128,128,128);
	drawRectanglefHW(vec2f(slider->E->x,slider->E->y+16+slider->button_offset),vec2f(slider->E->x+16,slider->E->y+16+slider->button_offset+slider->button_size));
	setColor2HW(0,0,0);
	drawRectangleFramefHW(vec2f(slider->E->x,slider->E->y+16+slider->button_offset),vec2f(slider->E->x+16,slider->E->y+16+slider->button_offset+slider->button_size));
}

typedef struct{
	int margin;
	
	style s;
	text content;
	int w,h;
	int offset_x,offset_y;
	
	Element *E;
	
	int attach_to_sliders;
	SliderH *sliderH;
	SliderV *sliderV;
	
	int one_line;
}Textbox;

Textbox* TextboxC(int w,int h,char *str)
{
	Textbox *txt;
	
	txt=malloc(sizeof(Textbox));
	txt->content=empty_text;
	setText(&txt->content,str);

	txt->w=w;
	txt->h=h;
	
	txt->offset_x=0;
	txt->offset_y=0;
	
	txt->s=cstyle;
	
	txt->attach_to_sliders=0;
	txt->sliderH=0;
	txt->sliderV=0;
	
	txt->one_line=0;
	
	txt->margin=0;
	
	return txt;
}

void TextboxD(void *ptr)
{
	Textbox *txt;
	txt=ptr;
	
	deleteText(&txt->content);
	free(txt);
}

int TextboxOn(Textbox *txt)
{
	return
	(mouse_x>=txt->E->x && mouse_x<txt->E->x+txt->w) &&
	(mouse_y>=txt->E->y && mouse_y<txt->E->y+txt->h);
}

void BindSlidersToTextbox(Textbox *txt,SliderH *sliderH,SliderV *sliderV)
{
	txt->attach_to_sliders=1;
	txt->sliderH=sliderH;
	txt->sliderV=sliderV;
}

void SliderHSetOffsetX(Textbox *txt,SliderH *slider,float offset_x)
{
	float rate;
	useStyle(txt->s);
	rate=offset_x/(getStringWidth(txt->content.str)-txt->w);
	slider->button_offset+=rate*(slider->length-32-slider->button_size);
}

void SliderVSetOffsetY(Textbox *txt,SliderH *slider,float offset_y)
{
	float rate;
	useStyle(txt->s);
	rate=offset_y/(getStringHeight(txt->content.str)-txt->h);
	slider->button_offset+=rate*(slider->length-32-slider->button_size);
}

void UpdateTextOffset(Textbox *txt)
{
	if(txt->attach_to_sliders)
	{
		float rateH,rateV;
		int w,h;
		
		useStyle(txt->s);
		{
			if(txt->sliderH)
			{
				w=getStringWidth(txt->content.str);
				if(w<=txt->sliderH->length)
				{
					txt->sliderH->button_size=0;
					txt->offset_x=0;
				}
				else
				{
					SliderHSetButtonSizeRate(txt->sliderH,txt->w/(float)w);
					/*while(txt->offset_x+getCursorX(txt->content.str,cursor_i)>txt->w)
						SliderHSetOffsetX(txt,txt->sliderH,-cstyle.scaler*cstyle.default_w);*/
					rateH=SliderHGetRate(txt->sliderH);
					txt->offset_x=-(w-txt->w)*rateH;
					
					if(char_add || char_del || cursor_movement)
					{
						if(txt->offset_x+getCursorX(txt->content.str,cursor_i)>txt->w)
						SliderHSetOffsetX(txt,txt->sliderH,txt->offset_x+getCursorX(txt->content.str,cursor_i)-txt->w);
						if(txt->offset_x+getCursorX(txt->content.str,cursor_i)<0)
						SliderHSetOffsetX(txt,txt->sliderH,txt->offset_x+getCursorX(txt->content.str,cursor_i));
					}
				}
			}
			if(txt->sliderV)
			{
				h=getStringHeight(txt->content.str);
				if(h<=txt->sliderV->length)
				{
					txt->sliderV->button_size=0;
					txt->offset_y=0;
				}
				else
				{
					SliderVSetButtonSizeRate(txt->sliderV,txt->h/(float)h);
					rateV=SliderVGetRate(txt->sliderV);
					/*SliderVSetRate(txt->sliderV,rate);*/
					txt->offset_y=-(h-txt->h)*rateV;
					
					if(char_add || char_del || cursor_movement)
					{
						if(txt->offset_y+getCursorY(txt->content.str,cursor_i)+cstyle.scaler*cstyle.default_h>txt->h)
						SliderVSetOffsetY(txt,txt->sliderV,txt->offset_y+getCursorY(txt->content.str,cursor_i)+cstyle.scaler*cstyle.default_h-txt->h);
						if(txt->offset_y+getCursorY(txt->content.str,cursor_i)<0)
						SliderVSetOffsetY(txt,txt->sliderV,txt->offset_y+getCursorY(txt->content.str,cursor_i));
					}
				}
			}
			
		}
	}
	else
	{
		if(char_add || char_del || cursor_movement)
		{
			if(txt->offset_x+getCursorX(txt->content.str,cursor_i)>txt->w)
			txt->offset_x-=txt->offset_x+getCursorX(txt->content.str,cursor_i)-txt->w;
			if(txt->offset_x+getCursorX(txt->content.str,cursor_i)<0)
			{	
				txt->offset_x-=-txt->w;/*txt->offset_x+getCursorX(txt->content.str,cursor_i);*/
				if(getCursorX(txt->content.str,cursor_i)<txt->w)
				txt->offset_x=0;
			
				if(cursor_i<key_string_ptr->length-1)
						cursor_i++;
						
				calculateRowColumn();
			}
		}
	}
	
	/*char_add=0;
	char_del=0;*/
}

void TextboxUpdate(void *ptr)
{
	Textbox *txt;
	txt=ptr;
	
	if(!txt->E->lock)
	{
		if(mbLeftPress())
		{
			if(TextboxOn(txt))
			{
				txt->E->active=1;
				
				key_string_ptr=&txt->content;
				key_input=1;
				one_line_input=txt->one_line;
			}
			else
			{
				txt->E->active=0;
				
				key_input=0;
			}
		}
		if(txt->E->active)
		{
			handleTextBoxString(txt->E->x+txt->offset_x,txt->E->y+txt->offset_y);
		}
		
		UpdateTextOffset(txt);
	}
}

void TextboxDraw(void *ptr)
{
	Textbox *txt;
	txt=ptr;
	
	borderless();
	
	texturing(0);
	
	setColor2HW(255,255,255);
	drawRectanglefHW(vec2f(txt->E->x-txt->margin,txt->E->y-txt->margin),vec2f(txt->E->x+txt->w+txt->margin,txt->E->y+txt->h+txt->margin));
	
	if(txt->E->active && !txt->E->lock)
		setColor2HW(255,0,0);
	else
		setColor2HW(0,0,0);
	drawRectangleFramefHW(vec2f(txt->E->x-txt->margin,txt->E->y-txt->margin),vec2f(txt->E->x+txt->w+txt->margin,txt->E->y+txt->h+txt->margin));
	
	drawingBorder(txt->E->x-txt->margin,txt->E->y-txt->margin,txt->w+txt->margin*2,txt->h+txt->margin*2);
	
	useStyle(txt->s);
	drawTextBoxString(txt->E->x+txt->offset_x,txt->E->y+txt->offset_y,txt->content.str,txt->E->active && !txt->E->lock);
}

Element* OneLineTextboxElement(int x,int y,int w,char *str)
{
	Element *E;
	E=ElementC(x,y,0,TextboxC(w,cstyle.scaler*cstyle.default_h,str));
	((Textbox*)(E->ptr))->one_line=1;
	((Textbox*)(E->ptr))->E=E;
	
	return E;
}

Element* TextboxElement(int x,int y,int w,int h,char *str)
{
	Element *E;
	E=ElementC(x,y,0,TextboxC(w,h,str));
	
	((Textbox*)(E->ptr))->E=E;
	
	return E;
}

Element* SliderHElement(int x,int y,int length,int button_size)
{
	Element *E;
	
	E=ElementC(x,y,1,SliderHC(length,button_size));
	
	((SliderH*)(E->ptr))->E=E;
	
	return E;
}

Element* SliderVElement(int x,int y,int length,int button_size)
{
	Element *E;
	
	E=ElementC(x,y,2,SliderVC(length,button_size));
	
	((SliderV*)(E->ptr))->E=E;
	
	return E;
}

Element* ButtonElement(int x,int y,int w,int h,char *str)
{
	Element *E;
	E=ElementC(x,y,3,ButtonC(w,h,str));
	
	((Button*)(E->ptr))->E=E;
	
	return E;
}

Element* SubmenuElement(int x,int y,int w)
{
	Element *E;
	E=ElementC(x,y,4,SubmenuC(w));
	
	((Submenu*)(E->ptr))->E=E;
	
	return E;
}

Element* TextElement(int x,int y,char *str)
{
	Element *E;
	E=ElementC(x,y,5,TextC(str));
	
	((Text*)(E->ptr))->E=E;
	
	return E;
}

Element* CheckboxElement(int x,int y,char *str)
{
	Element *E;
	E=ElementC(x,y,6,CheckboxC(str));
	
	((Checkbox*)(E->ptr))->E=E;
	
	return E;
}

void (*drawElement[7])(void *ptr)=
{
	TextboxDraw,
	SliderHDraw,
	SliderVDraw,
	ButtonDraw,
	SubmenuDraw,
	TextDraw,
	CheckboxDraw
};

void DrawElement(Element *E)
{
	(*drawElement[E->type])(E->ptr);
}

void (*updateElement[7])(void *ptr)=
{
	TextboxUpdate,
	SliderHUpdate,
	SliderVUpdate,
	ButtonUpdate,
	SubmenuUpdate,
	TextUpdate,
	CheckboxUpdate
};

void UpdateElement(Element *E)
{
	ElementFollowAttachment(E);
	(*updateElement[E->type])(E->ptr);
}

void (*deleteElement[7])(void *ptr)=
{
	TextboxD,
	SliderHD,
	SliderVD,
	ButtonD,
	SubmenuD,
	TextD,
	CheckboxD
};

void DeleteElement(Element *E)
{
	(*deleteElement[E->type])(E->ptr);
	ElementD(E);
}

typedef struct{
	int x,y,w,h;
	text title;
	
	int active;
	int dragging;
	
	Element **element;
	int n;
}Window;


void addElementToWindow(Window *win,Element *E)
{
	Element **new_element;
	new_element=malloc((win->n+1)*sizeof(Element*));
	
	{
		int i;
		for(i=0; i<win->n; i++)
			new_element[i]=win->element[i];
		
		new_element[i]=E;
	}
	
	if(win->n) free(win->element);
	
	win->element=new_element;
	win->n++;
	
}


void attachElementToWindow(Window *win,Element *E)
{
	E->target_x=&win->x;
	E->target_y=&win->y;
	E->attachment_offset_x=E->x-win->x;
	E->attachment_offset_y=E->y-win->y;
	E->attach=1;
}

Window* WindowC(int x,int y,int w,int h,char *str)
{
	Window *win;
	win=malloc(sizeof(Window));
	win->title=empty_text;
	setText(&win->title,str);
	win->x=x;
	win->y=y;
	win->w=w;
	win->h=h;
	win->dragging=0;
	
	win->active=0;
	
	win->n=0;
	win->element=0;
	
	return win;
}

void WindowD(Window *win)
{
	int i;
	for(i=0; i<win->n; i++)
		DeleteElement(win->element[i]);
	
	if(win->n)
	free(win->element);
	
	deleteText(&win->title);
	free(win);
}

void WindowDraw(Window *win)
{
	borderless();
	texturing(0);
	
	setColorHW(col(128,128,128));
	drawRectanglefHW(vec2f(win->x,win->y),vec2f(win->x+win->w,win->y+win->h));
	setColorHW(col(128,0,255));
	drawRectanglefHW(vec2f(win->x,win->y-20),vec2f(win->x+win->w,win->y));
	setColorHW(col(255,0,0));
	drawRectanglefHW(vec2f(win->x+win->w-20,win->y-20),vec2f(win->x+win->w,win->y));
	
	setColorHW(col(0,0,0));
	drawRectangleFramefHW(vec2f(win->x,win->y),vec2f(win->x+win->w,win->y+win->h));
	drawRectangleFramefHW(vec2f(win->x,win->y-20),vec2f(win->x+win->w,win->y+win->h));
	drawRectangleFramefHW(vec2f(win->x+win->w-20,win->y-20),vec2f(win->x+win->w,win->y));
	
	drawLinefHW(vec2f(win->x+win->w-15,win->y-15),vec2f(win->x+win->w-5,win->y-5));
	drawLinefHW(vec2f(win->x+win->w-15,win->y-5),vec2f(win->x+win->w-5,win->y-15));
	
	texturing(1);
	
	cstyle.c=col(255,255,255);
	drawStringHW(win->title.str,win->x+4,win->y-20);
}

void WindowsDraw(Window **win,int n)
{
	int i,j;
	
	for(i=0; i<n; i++)
	{
		WindowDraw(win[i]);
		for(j=0; j<win[i]->n; j++)
		{
			DrawElement(win[i]->element[j]);
		}
	}
	borderless();
}

int WindowOn(Window *win)
{
	return
	(mouse_x>=win->x	&& mouse_x<win->x+win->w) &&
	(mouse_y>=win->y-20 && mouse_y<win->y+win->h);
}

int WindowTopOn(Window *win)
{
	return
	(mouse_x>=win->x	&& mouse_x<win->x+win->w) &&
	(mouse_y>=win->y-20 && mouse_y<win->y);
}

int click_window_x,click_window_y;
void WindowsUpdate(Window **win,int n)
{
	int i,j;
	
	if(mb_left && !mb_left_p)
	{
		int active_i=-1;
		void *active_ptr;
		
		for(i=0; i<n; i++)
		{
			win[i]->dragging=0;
			win[i]->active=0;
		}
		
		for(i=0; i<n; i++)
			if(WindowOn(win[i]))
			{
				active_i=i;
				active_ptr=win[i];
			}
		
		if(active_i>=0)
		{
			click_window_x=win[active_i]->x;
			click_window_y=win[active_i]->y;
			click_mouse_x=mouse_x;
			click_mouse_y=mouse_y;
			if(WindowTopOn(win[active_i]))
			win[active_i]->dragging=1;
			win[active_i]->active=1;
			{
				int i;
				for(i=active_i; i<n-1; i++)
					win[i]=win[i+1];
			}
			win[n-1]=active_ptr;
		}
	}
	
	for(i=0; i<n; i++)
		if(win[i]->dragging)
		{
			win[i]->x=click_window_x+mouse_x-click_mouse_x;
			win[i]->y=click_window_y+mouse_y-click_mouse_y;
		}
	
	for(i=0; i<n; i++)
	{
		for(j=0; j<win[i]->n; j++)
		{
			win[i]->element[j]->lock=!win[i]->active;
			UpdateElement(win[i]->element[j]);
		}
	}
	
	
	if(!mb_left && mb_left_p)
	{
		for(i=0; i<n; i++)
			win[i]->dragging=0;
	}
}

void WindowsDelete(Window **win,int n)
{
	int i;
	for(i=0; i<n; i++)
		WindowD(win[i]);
}

#endif
