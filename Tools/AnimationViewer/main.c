/*

gcc main.c glad.c -IC:\mingw_dev_lib\include\SDL2 -LC:\mingw_dev_lib\lib -lmingw32 -lopengl32 -lSDL2main -lSDL2 -lSDL2_image -o main.exe -ansi -std=c89 -pedantic -w

*/

#define W 640
#define H 480

#define SIZE_W 640
#define SIZE_H 480

#include "../../Source/Libraries/all2.h"

int main(int argc, char **argv)
{	
	TextureHW tex_stickman;
	Image img_stickman;
	Sprite spr_stickman_running;
	
	IO_Init_OpenGL("Animation Viewer");
	key_input=0;
	
	initFontHW();
	
	tex_stickman=loadTextureHW("stickman.png");
	
	img_stickman=createImageHW(tex_stickman);
	
	spr_stickman_running=SpriteC(img_stickman,ImagePartC(0,0,256,256),vec2i(32,64),0);
	
	printf("tex id = %d\n",spr_stickman_running.image.texHW.id);
	
	while(!quit)
	{
		if(!Update_OpenGL())
		{
			glClearColor(0,1,1,1);
			glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
			
			texturing(1);/*HW*/
			setColorA2HW(255,0,0,255);
			
			drawStringHW("Animation Viewer 1.0",10,10);
			
			{
				static float index=0;
				static int dir=1;
				
				
				drawSpriteIndex(spr_stickman_running,100,100,Rclampf(index,0,4));
				
				index+=0.5*dir;
				if(dir>0 && index>4)
				{
					dir=-abs(dir);
				}
				else if(dir<0 && index<0)
				{
					dir=abs(dir);
				}
			}
		}
	}
	
	quitFontHW();
	
	deleteImage(&img_stickman);
	
	SpriteD(&spr_stickman_running);
	
	IO_Quit_OpenGL();
}