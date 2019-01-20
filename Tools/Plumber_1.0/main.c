/*

gcc main.c glad.c -IC:\mingw_dev_lib\include\SDL2 -LC:\mingw_dev_lib\lib -lmingw32 -lopengl32 -lSDL2main -lSDL2 -lSDL2_image -o main.exe -ansi -std=c89 -pedantic -w

*/

#define W 640
#define H 480

#define SIZE_W 640
#define SIZE_H 480

#include "../../Source/Libraries/all2.h"

int
text_offset_x=10,
text_offset_y=30,
text_area_offset_x=10,
text_area_offset_y=30;
text_area_w=W-20;
text_area_h=H-40;

int main(int argc, char **argv)
{	
	Window *win[3];
	Window *ptr[3];
	
	IO_Init_OpenGL("Plumber 1.0");
	key_input=0;
	
	initFontHW();

	win[0]=WindowC(50,50,300,200,"Window 1");
	cstyle.c=col(0,0,0);
	
	addElementToWindow(win[0],TextboxElement(60,60,250,150,"content"));
	addElementToWindow(win[0],SliderHElement(60,210,250,0));
	addElementToWindow(win[0],SliderVElement(310,60,150,0));
	attachElementToWindow(win[0],win[0]->element[0]);
	attachElementToWindow(win[0],win[0]->element[1]);
	attachElementToWindow(win[0],win[0]->element[2]);
	((Textbox*)(win[0]->element[0]->ptr))->margin=2;
	BindSlidersToTextbox(win[0]->element[0]->ptr,win[0]->element[1]->ptr,win[0]->element[2]->ptr);
	win[1]=WindowC(350,150,150,100,"Window 2");
	addElementToWindow(win[1],OneLineTextboxElement(360,160,100,"content"));
	addElementToWindow(win[1],ButtonElement(360,192,100,32,"OK"));
	attachElementToWindow(win[1],win[1]->element[0]);
	attachElementToWindow(win[1],win[1]->element[1]);
	((Textbox*)(win[1]->element[0]->ptr))->margin=2;
	
	win[2]=WindowC(200,200,200,200,"Window 3");
	addElementToWindow(win[2],TextElement(210,240,"Test"));
	addElementToWindow(win[2],SubmenuElement(210,210,100));
	addElementToWindow(win[2],CheckboxElement(300,240,14));
	
	attachElementToWindow(win[2],win[2]->element[0]);
	attachElementToWindow(win[2],win[2]->element[1]);
	attachElementToWindow(win[2],win[2]->element[2]);
	
	addItemToSubmenu(win[2]->element[1]->ptr,"option  0");
	addItemToSubmenu(win[2]->element[1]->ptr,"option  1");
	addItemToSubmenu(win[2]->element[1]->ptr,"option  2");
	addItemToSubmenu(win[2]->element[1]->ptr,"option  3");
	addItemToSubmenu(win[2]->element[1]->ptr,"option  4");
	addItemToSubmenu(win[2]->element[1]->ptr,"option  5");
	addItemToSubmenu(win[2]->element[1]->ptr,"option  6");
	addItemToSubmenu(win[2]->element[1]->ptr,"option  7");
	addItemToSubmenu(win[2]->element[1]->ptr,"option  8");
	addItemToSubmenu(win[2]->element[1]->ptr,"option  9");
	addItemToSubmenu(win[2]->element[1]->ptr,"option 10");
	addItemToSubmenu(win[2]->element[1]->ptr,"option 11");
	
	ptr[0]=win[0];
	ptr[1]=win[1];
	ptr[2]=win[2];
	while(!quit)
	{
		if(ButtonOnClick(ptr[1]->element[1]->ptr))
		{
			printf("click\n");
		}
		
		WindowsUpdate(win,3);
		
		if(!Update_OpenGL())
		{
			setColor2HW(64,64,64);
			clearHW();
			
			texturing(1);
			setColorA2HW(255,0,0,255);
			
			cstyle.c=col(255,255,0);
			drawStringHW("Plumber 1.0",10,10);
			
			depthTest(0);
			WindowsDraw(win,3);
			depthTest(1);
		}
	}
	WindowsDelete(win,3);
	
	quitFontHW();
	
	IO_Quit_OpenGL();
}
