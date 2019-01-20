/*

 gcc main.c -IC:\mingw_dev_lib\include\SDL2 -LC:\mingw_dev_lib\lib -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -o main.exe -ansi -std=c89 -pedantic -w

*/
 
#defineW 640
#define H 480

#include "Libraries\all.h"
/*
#include "Libraries\io_basic_libraries.h"
#include "Libraries\math.h"
#include "Libraries\string.h"
#include "Libraries\pixel_manipulation.h"
#include "Libraries\draw.h"
#include "Libraries\font.h"

#include "Libraries\pseudo_physics2d.h"*/

int main(int argc, char ** argv)
{
	int block_x=0,block_y=0,spot_x=0,spot_y=0;
	Texture apple,apple2;
	font font1;
	triangle2f T1,T2;
	vector2i test_point=vec2i(35,210);
	vector_array2f vaT=emptyva2f(),vaU=emptyva2f();
	
	clock_t timer;
	int fps,frames;
	float aaa=0;
	
	arrow2i line[2];
	
	triangle2i testTriangle,testTriangle2;
	
	vector2i p,size;
	p=vec2i(160,120);
	size=vec2i(320,240);
	
	line[0].from.e[0]=100;
	line[0].from.e[1]=0;
	line[0].to	.e[0]=0;
	line[0].to	.e[1]=100;
	
	line[1].from.e[0]=200;
	line[1].from.e[1]=0;
	line[1].to	.e[0]=0;
	line[1].to	.e[1]=200;
	
	#define SSS 64
	
	testTriangle.vertex[0].e[0]=0;
	testTriangle.vertex[0].e[1]=0;
	testTriangle.vertex[1].e[0]=SSS;
	testTriangle.vertex[1].e[1]=0;
	testTriangle.vertex[2].e[0]=0;
	testTriangle.vertex[2].e[1]=SSS;
	testTriangle2.vertex[0].e[0]=SSS;
	testTriangle2.vertex[0].e[1]=0;
	testTriangle2.vertex[1].e[0]=SSS;
	testTriangle2.vertex[1].e[1]=SSS;
	testTriangle2.vertex[2].e[0]=0;
	testTriangle2.vertex[2].e[1]=SSS;

	{
		/*processor speed measurement*/
		
		/*
		clock_t tm;
		int count,I;
		
		for(I=0; I<5; I++)
		{
			count=0;
			
			tm=clock();
			while((clock()-tm)<CLOCKS_PER_SEC)
			{
				count++;
			}	
			
			printf("processor speed : %f\n",count/1024.0f/1024.0f);
		}*/
	}
	
	
	addBufferva2f(&vaT,6);
	addBufferva2f(&vaU,6);
	
	pushva2f(&vaT,vec2f(80	,80	));
	pushva2f(&vaT,vec2f(80	,0	));
	pushva2f(&vaT,vec2f(0	,0	));
	pushva2f(&vaT,vec2f(0	,0	));
	pushva2f(&vaT,vec2f(0	,80	));
	pushva2f(&vaT,vec2f(80	,80	));
	
	pushva2f(&vaU,vec2f(256	,256 ));
	pushva2f(&vaU,vec2f(256	,0	 ));
	pushva2f(&vaU,vec2f(0	,0	 ));
	pushva2f(&vaU,vec2f(0	,0	 ));
	pushva2f(&vaU,vec2f(0	,256 ));
	pushva2f(&vaU,vec2f(256	,256 ));

	
	T1.vertex[0]=vec2f(10,200);
	T1.vertex[1]=vec2f(50,200);
	T1.vertex[2]=vec2f(50,250);
	
	T2.vertex[0]=vec2f(10,270);
	T2.vertex[1]=vec2f(50,270);
	T2.vertex[2]=vec2f(10,330);
	
	IO_Init("DanceOfPixels");
	initMath();
	/*initDraw();*/
	
	apple =loadTexture("apple.png");
	apple2=loadTexture("apple2.png");
	
	font1=createFont(loadTexture("Fonts/font.png"),9,18,14,7,0);
	/*
	{
		float x,X=6345.9345f;
		int i,k,y1,y2;
		
		clock_t q;
		
		q=clock();
		for(i=0; i<1000000; i++)
		y1=(int)X;
		printf("\ntime 1 = %i\n",clock()-q);
		
		q=clock();
		{
			int i,n,result=0;
				float i_f;
		for(k=0; k<1000000; k++)
		{
			result=0;
			x=X;
			{
				
				{
					x/=10;
					
						if(x<10.0f)
					{
						i=1;
					}
					else if(x<100.0f)
					{
						i=2;
						x/=10.0f;
					}
					else if(x<1000.0f)
					{
						i=3;
						x/=100.0f;
					}
					else if(x<10000.0f)
					{
						i=4;
						x/=1000.0f;
					}
					
				}

				n=i;
				
				/*
				{
					for(i_f=1,i=0; i_f<=10.0f; i_f+=1.0f,i++)
					{
						if(x<i_f)
						{
							result+=i;
							result*=10;
							x-=i_f-1.0f;
							x*=10;
							break;
						}
					}
				}
				if(n==1) goto ok;
				{
					for(i_f=1,i=0; i_f<=10.0f; i_f+=1.0f,i++)
					{
						if(x<i_f)
						{
							result+=i;
							result*=10;
							x-=i_f-1.0f;
							x*=10;
							break;
						}
					}
				}
				if(n==2) goto ok;
				{
					for(i_f=1,i=0; i_f<=10.0f; i_f+=1.0f,i++)
					{
						if(x<i_f)
						{
							result+=i;
							result*=10;
							x-=i_f-1.0f;
							x*=10;
							break;
						}
					}
				}
				if(n==3) goto ok;
				{
					for(i_f=1,i=0; i_f<=10.0f; i_f+=1.0f,i++)
					{
						if(x<i_f)
						{
							result+=i;
							result*=10;
							x-=i_f-1.0f;
							x*=10;
							break;
						}
					}
				}
				
				ok:
				y2=result/10;
			}
		}
		
		}
		end:
		
		printf("\ntime 2 = %i\n",clock()-q);
		
		printf("\ny1 = %i\n",y1);
		printf("y2 = %i\n",y2);
	}
	*/
	{
		int i,j;
		for(i=0; i<N; i++)
		{
			pixels[i*4  ]=194;/*blue*/
			pixels[i*4+1]=  0;/*green*/
			pixels[i*4+2]= 60;/*red*/
			pixels[i*4+3]=255;
		}
		
		
		/*
		for(j=0; j<256; j++)
			for(i=0; i<256; i++)
			{
				getTexturePixel(apple,i,j);
				drawPixel(i,j);
			}
		
		for(i=0; i<32; i++)
			for(j=0; j<32; j++)
				drawPixel2(i,j,150,255,0);*/
	}
	
	timer=clock();
	frames=-1;
	fps=0;
	
	while(!quit)
	{
		if(!Update())
		{
			frames++;
			
			if((clock()-timer)>=CLOCKS_PER_SEC)
			{
				fps=frames;
				
				timer=clock();
				frames=-1;
			}
			
			int i,j;
			
			if(key_0)
			{
				block_x+=(key_right-key_left)*10*(30.0f/fps);
				block_y+=(key_down-key_up)*10*(30.0f/fps);

				spot_x+=(key_d-key_a)*1;
				spot_y+=(key_s-key_w)*1;
			}
			
			if(key_t)
			{
				if(key_1)
				{
					T1.vertex[0].e[0]+=(key_right-key_left)*5;
					T1.vertex[0].e[1]+=(key_down-key_up)*5;
				}
				if(key_2)
				{
					T1.vertex[1].e[0]+=(key_right-key_left)*5;
					T1.vertex[1].e[1]+=(key_down-key_up)*5;
				}
				if(key_3)
				{
					T1.vertex[2].e[0]+=(key_right-key_left)*5;
					T1.vertex[2].e[1]+=(key_down-key_up)*5;
				}
			}
			if(key_y)
			{
				if(key_1)
				{
					T2.vertex[0].e[0]+=(key_right-key_left)*5;
					T2.vertex[0].e[1]+=(key_down-key_up)*5;
				}
				if(key_2)
				{
					T2.vertex[1].e[0]+=(key_right-key_left)*5;
					T2.vertex[1].e[1]+=(key_down-key_up)*5;
				}
				if(key_3)
				{
					T2.vertex[2].e[0]+=(key_right-key_left)*5;
					T2.vertex[2].e[1]+=(key_down-key_up)*5;
				}
			}
			if(key_u)
			{
				{
					test_point.e[0]+=(key_right-key_left)*5;
					test_point.e[1]+=(key_down-key_up)*5;
				}
			}
			
			{
				static int uuu=0;
				if(!key_x_p && key_x) uuu=!uuu; 
				
				if(uuu)
				{
					if(key_1)
					{
						testTriangle2.vertex[0].e[0]+=(key_right-key_left)*4;
						testTriangle2.vertex[0].e[1]+=(key_down	-key_up)*4;
					}
					if(key_2)
					{
						testTriangle2.vertex[1].e[0]+=(key_right-key_left)*4;
						testTriangle2.vertex[1].e[1]+=(key_down	-key_up)*4;
					}
					if(key_3)
					{
						testTriangle2.vertex[2].e[0]+=(key_right-key_left)*4;
						testTriangle2.vertex[2].e[1]+=(key_down	-key_up)*4;
					}
				}
				else
				{
					if(key_1)
					{
						testTriangle.vertex[0].e[0]+=(key_right	-key_left)*4;
						testTriangle.vertex[0].e[1]+=(key_down	-key_up)*4;
					}
					if(key_2)
					{
						testTriangle.vertex[1].e[0]+=(key_right	-key_left)*4;
						testTriangle.vertex[1].e[1]+=(key_down	-key_up)*4;
					}
					if(key_3)
					{
						testTriangle.vertex[2].e[0]+=(key_right	-key_left)*4;
						testTriangle.vertex[2].e[1]+=(key_down	-key_up)*4;
					}
				}
			}
			
			
			if(key_4)
			{
				line[0].from.e[0]+=(key_right	-key_left)*4;
				line[0].from.e[1]+=(key_down	-key_up)*4;
			}
			if(key_5)
			{
				line[0].to	.e[0]+=(key_right	-key_left)*4;
				line[0].to	.e[1]+=(key_down	-key_up)*4;
			}
			if(key_6)
			{
				line[1].from.e[0]+=(key_right	-key_left)*4;
				line[1].from.e[1]+=(key_down	-key_up)*4;
			}
			if(key_7)
			{
				line[1].to	.e[0]+=(key_right	-key_left)*4;
				line[1].to	.e[1]+=(key_down	-key_up)*4;
			}
			
			if(key_f==1 && key_f_p==0)
			{
				fullscreen=!fullscreen;
				if(fullscreen)
				{
					SDL_MaximizeWindow(window);
					SDL_GetWindowSize(window,&fullscreen_w,&fullscreen_h);
				}
				else
					SDL_RestoreWindow(window);
			}
			/*blue-green-red-alpha*/
			
			
			/*
			{
			int j;
			for(j=0; j<20; j++)
			for(i=0; i<N; i++)
			{
				pixels[i*4  ]=194;
				pixels[i*4+1]=  0;
				pixels[i*4+2]= 60;
			}
			}*/
			
			setColor(0,255,255);
					{
						int w=640,h=480,x=0,y=0,pp;
						triangle2i ttt[2],uuu[2];
						
						uuu[0].vertex[2]=vec2i(0,0);
						uuu[0].vertex[1]=vec2i(256,0);
						uuu[0].vertex[0]=vec2i(256,256);
						
						uuu[1].vertex[2]=vec2i(256,256);
						uuu[1].vertex[1]=vec2i(0,256);
						uuu[1].vertex[0]=vec2i(0,0);
					
						ttt[0].vertex[2]=vec2i(x	,y);
						ttt[0].vertex[1]=vec2i(x+w	,y);
						ttt[0].vertex[0]=vec2i(x+w	,y+h);
				
						ttt[1].vertex[2]=vec2i(x+w	,y+h);
						ttt[1].vertex[1]=vec2i(x	,y+h);
						ttt[1].vertex[0]=vec2i(x	,y);
						
						for(pp=0; pp<2; pp++)
						{
							drawTriangleTextured(ttt[0],uuu[0],apple);
							drawTriangleTextured(ttt[1],uuu[1],apple);
						}
						
						{
							static int iii=0;
							if(!key_i_p && key_i) iii=!iii; 
							
							if(iii)
							{
								setColor(255,255,255);
								drawRectangleFrame(x,y,w,h);
							}
						}
					}
			
			
			/*zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz*/
			
			/*{
				static int iii=0;
				if(!key_h_p && key_h) iii=!iii; 
					
				if(iii)
				{
					
				}
			}*/
			
			setColor(0,0,0);
					drawLine(vec2i(W/2,H/2),vec2i(mouse_x,mouse_y));
			
			for(i=0; i<32; i++)
				for(j=0; j<32; j++)
					drawPixel2Safe(i+block_x,j+block_y,255,0,0);
			
			drawPixel2Safe(spot_x,spot_y,0,255,0);
			
			setColor(0,255,0);
			drawCircleFrame(vec2i(spot_x,spot_y),4);
			setColor(255,255,0);
			drawLine(vec2i(0,spot_y),vec2i(W,spot_y));
			setColor(255,0,255);
			drawPixelSafe(getLineX(vec2i(W/2,H/2),vec2i(mouse_x,mouse_y),spot_y),spot_y);
			
			drawCircleFrame(
			vec2i(getLineX(vec2i(W/2,H/2),vec2i(mouse_x,mouse_y),spot_y),spot_y),
			4
			);
			
			
			/*zzzzzzzzzzzzzzzzzzzzzzzzzzzzzzz*/
			
			{
				triangle2i uuu[2];
			
				uuu[0].vertex[2]=vec2i(0,0);
				uuu[0].vertex[1]=vec2i(256,0);
				uuu[0].vertex[0]=vec2i(256,256);
				
				uuu[1].vertex[2]=vec2i(256,256);
				uuu[1].vertex[1]=vec2i(0,256);
				uuu[1].vertex[0]=vec2i(0,0);
				
				setColor(255,0,255);
				
				{
					int k;
					
					for(k=0; k<1/*80*7*/; k++)
					{
						setColor(255,255,0);
						if(LineToLineSegmenti(line[0],line[1]))
						setColor(255,0,0);
						drawLine(line[0].from,line[0].to);
						setColor(255,0,255);
						if(LineToLineSegmenti(line[0],line[1]))
						setColor(255,0,0);
						drawLine(line[1].from,line[1].to);
						
						
						/*xxxxxxxxxxxxxxxxxxxxxx*/
						
						setColor(55,255,200);
						drawRectangleFramev(p,size);
						
						{
							triangle2i UV,UV2;
							UV.vertex[0].e[0]=0;
							UV.vertex[0].e[1]=0;
							UV.vertex[1].e[0]=256;
							UV.vertex[1].e[1]=0;
							UV.vertex[2].e[0]=0;
							UV.vertex[2].e[1]=256;
							
							UV2.vertex[0].e[0]=256;
							UV2.vertex[0].e[1]=0;
							UV2.vertex[1].e[0]=256;
							UV2.vertex[1].e[1]=256;
							UV2.vertex[2].e[0]=0;
							UV2.vertex[2].e[1]=256;
							
							
							/*drawTriangleTextured(testTriangle,UV,apple);*/
							/*drawTriangleTextured(testTriangle2,UV2,apple);*/
							
							{
								int intersection;
								
								intersection=TriangleToTriangle(tri2i_to_tri2f(testTriangle),tri2i_to_tri2f(testTriangle2));
								
								setColor(255-128*intersection,100-50 *intersection,255-128*intersection);
								drawTriangle(testTriangle2);
								setColor(100-50 *intersection,255-128*intersection,100-50 *intersection);
							
								drawTriangle(testTriangle);
							}
						}
						
						{
							static int uuu=0;
							if(!key_u_p && key_u) uuu=!uuu; 
							
							if(uuu)
							{
								setColor(255,255,255);
								drawTriangleFrame(testTriangle);
							}
						}
						
						{
							static float angle=0;
						drawImageTransformed(apple2,300,300,64,64,32,32,angle);
						angle+=pi/50;
						
						}
						
						setColor(0,255,0);
						
						/*xxxxxxxxxxxxxxxxxxxxxx*/
						
						/*{
							int ymin,ymax,x1;
							if(line[0].from.e[1]<line[0].to.e[1])
							{
								ymin=line[0].from.e[1];
								ymax=line[0].to  .e[1];
							}
							else
							{
								ymax=line[0].from.e[1];
								ymin=line[0].to  .e[1];
							}
							
							setColor(100,255,100);
							
							f_glxs_current_seperation=0;
							
							if(line[0].from.e[1]<line[0].to.e[1])
							x1=getLineXStart(line[0].from,line[0].to,ymin);
							else
							x1=getLineXStart(line[0].to,line[0].from,ymin);
							
							drawPixelSafe(x1,ymin);
							
							setColor(255,255,255);
							drawCircleFrame(line[0].from,6);
							setColor(100,255,100);
							
							{
							
							static int print=0;
							
							if(key_p && !key_p_p) print=!print;
							
							if(print)
							printf("%i = %i\n",0,x1);
							
							{
								int i,n=ymax-ymin;
								for(i=0; i<n; i++)
								{
									x1=(*fp[f_glxs_mode[0]])();
									if(print)
									printf("%i = %i\n",i+1,x1);
									drawPixelSafe(x1,ymin+i+1);
								}
							}
							
							if(print)
							printf("glxs_mode = %i\n",f_glxs_mode[0]);
							
							}
							
							{
							
								static int visible=0;
								if(key_v && !key_v_p) visible=!visible;
								
								if(visible)
								{
									setColor(255,0,0);
									drawLine(line[0].from,line[0].to);
								}
							
							}
						}*/

						cfont=font1;
						
						
						/*drawLineHorizontal	(0,320,0	);*/
						/*drawLineHorizontal	(0,320,0+240-1);*/
						/*drawLineVertical	(0,240,0	);
						drawLineVertical	(0,240,0+320-1);*/
					/*drawTriangle2Textured(ttt[0],uuu[0],apple);
					drawTriangle2Textured(ttt[1],uuu[1],apple);
					*/
					/*
					setColor(0,255,0);*/
					/*drawRectangleUnsafe(0,0,W,H);
					*/
					
					
					/*setColor(255,155,155);*/
					/*if(key_z)*/
					
					/* v  yyyyyyyyyyyyyyyyyyyyyyyyyy*/
					
					
					/* ^  yyyyyyyyyyyyyyyyyyyyyyyyyy*/
					
					/*{
						vector_array2f a;
						a=fcopyva2f(&vaT);
						
						translateva2f(&a,vec2f(-40,-40));
						rotateva2f(&a,aaa);
						aaa+=0.1;
						translateva2f(&a,vec2f(200+40,200+40));
						drawTriangleList(&a,2);
						
						deleteva2f(&a);
					}*/
					
					}
				}
				
				/*
				drawTriangleListTextured(&vaT,&vaU,2,apple);
				*/
				/*tri2f_to_tri2i(triangle));
				*/
				/*{
					triangle2i tri;
					tri.vertex[0]=vec2i(60,60);
					tri.vertex[1]=vec2i(160,90);
					tri.vertex[2]=vec2i(100,140);
					
				
					setColor(255,255,255);
					drawTriangle2(ttt[0]);
					setColor(  0,  0,  0);
					if(key_t)
					drawTriangleFrame(ttt[0]);
				}*/
				/*tri2f_to_tri2i(triangle));
				*/
				/*
				setColor(0,255,0);
				drawTriangleFrame(tri2f_to_tri2i(T1));
				setColor(255,0,255);
				drawTriangleFrame(tri2f_to_tri2i(T2));
				setColor(0,255,255);
				drawCircleFrame(test_point,4);
				
				setColor(255,255,0);
				drawCircleFrame(test_point,4);
				
				{
					vector2f resultant_point;
					PointInTriangleWrtPointInTriangle(
						vec2i_to_vec2f(test_point),
						T1,
						&resultant_point,
						T2
					);
					
					setColor(255,255,255);
					drawCircleFrame(vec2f_to_vec2i(resultant_point),4);
				}*/
				
				/*******************************************************************/
				
				/*
				setColor(255,255,0);
				drawLineHorizontal(32,64,132);
				drawLine(vec2i(32,133),vec2i(64,133));
				
				setColor(255,255,0);
				drawLine(vec2i(200,200),vec2i(100,300));
				
				{
					vector2f IP=LineToLineIP(arr2f(200,200,100,300),arr2f(W/2,H/2,mouse_x,mouse_y));
					drawCircleFrame(vec2f_to_vec2i(IP),6);
					
					setColor(150,255,255);
					drawPixelSafe(IP.e[0],IP.e[1]);
				}*/
				
				/*drawImage2(apple,154,90,0,0,256,256);*/
				
				cfont=font1;
				{	
					int i;
					text	txt =emptyText();
					
					/*appendString(&txt,"I will be ready when the time comes. \nI love you so much ! \nhow are you? \nlalalalala \nlol. ");
					
					txt2=subText(&txt,0,19);
					appendFloat(&txt2,8780.123,3);
					txt3=FloatToText(-pi,2);
					
					appendString(&txt,"\nbirth date : ");
					appendInteger(&txt,1993);
					appendString(&txt,"\nheight : ");
					appendInteger(&txt,185);*/
					appendString(&txt," cm.\n FPS = ");
					appendInteger(&txt,fps);
					
					drawString(txt.str,0,0);
					/*drawText(txt2.str,300,300);
					drawText(txt3.str,300,400);*/
					
					deleteText(&txt);
				}
			}
		}
	}
	
	deleteTexturePixels(apple);
	
	deleteFontTexture(font1);
	
	IO_Quit();
	
    return 0;
}
