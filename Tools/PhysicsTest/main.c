/*

gcc main.c glad.c -IC:\mingw_dev_lib\include\SDL2 -LC:\mingw_dev_lib\lib -lmingw32 -lopengl32 -lSDL2main -lSDL2 -lSDL2_image -o main.exe -ansi -std=c89 -pedantic -w

*/

#define W 640
#define H 480

#define SIZE_H 640
#define SIZE_W 480

#include "../../Source/Libraries/all2.h"



int main(int argc, char **argv)
{
	vector_array2f square,square2,square3,terrain,wall,ball;
	irregular player1,player2,terrain1,wall1,ball1;
	
	vector2f points[4];
	
	vector2f circle_pos=vec2f(100,100);
	triangle2f triangle=tri2f(300,300,400,300,400,400);
	
	int grid_w=20,grid_h=20;
	vector3f cam_pos=vec3f(150,150,150),cam_dir=vec3f(pi/4*3,pi/4,0);
	
	square=emptyva2f();
	pushva2f(&square,vec2f(-16,-16));
	pushva2f(&square,vec2f(16,-16));
	pushva2f(&square,vec2f(16,16));
	pushva2f(&square,vec2f(-16,16));
	pushva2f(&square,vec2f(-16,-16));
	
	square2=emptyva2f();
	pushva2f(&square2,vec2f(-32,-32));
	pushva2f(&square2,vec2f(32,-32));
	pushva2f(&square2,vec2f(32,32));
	pushva2f(&square2,vec2f(-32,32));
	pushva2f(&square2,vec2f(-32,-32));
	
	square3=emptyva2f();
	pushva2f(&square3,vec2f(-128,-128));
	pushva2f(&square3,vec2f(128,-128));
	pushva2f(&square3,vec2f(128,128));
	pushva2f(&square3,vec2f(-128,128));
	pushva2f(&square3,vec2f(-128,-128));
	
	terrain=emptyva2f();
	pushva2f(&terrain,vec2f(0,0));
	pushva2f(&terrain,vec2f(100,100));
	pushva2f(&terrain,vec2f(200,0));
	pushva2f(&terrain,vec2f(300,100));
	pushva2f(&terrain,vec2f(400,0));
	
	wall=emptyva2f();
	pushva2f(&wall,vec2f(0,0));
	pushva2f(&wall,vec2f(0,256));
	pushva2f(&wall,vec2f(256,256));
	pushva2f(&wall,vec2f(256,0));
	pushva2f(&wall,vec2f(0,0));
	
	ball=emptyva2f();
	pushva2f(&ball,vec2f(8,-16));
	pushva2f(&ball,vec2f(16,0));
	pushva2f(&ball,vec2f(8,16));
	pushva2f(&ball,vec2f(-8,16));
	pushva2f(&ball,vec2f(-16,0));
	pushva2f(&ball,vec2f(-8,-16));
	pushva2f(&ball,vec2f(8,-16));
	
	player1=irregularC(vec2f(100,100),&square2,8);
	player2=irregularC(vec2f(200,100),&square2,8);
	terrain1=irregularC(vec2f(20,350),&terrain,8);
	wall1=irregularC(vec2f(250,10),&wall,8);
	ball1=irregularC(vec2f(300,60),&ball,8);
	irregularSetVelocity(&ball1,vec2f(0.5,-0.5));
	
	points[0]=vec2f(200,20);
	points[1]=vec2f(20,200);
	points[2]=vec2f(300,20);
	points[3]=vec2f(20,300);
	
	IO_Init_OpenGL("Physics Test");
	key_input=0;
	
	initFontHW();
	
	PerspectiveMatrix=perspective_m4f(1.73,10000,1,1);
	
	while(!quit)
	{
		if(key_1)
		{
			points[0].e[0]+=(key_right-key_left)*4;
			points[0].e[1]+=(key_down-key_up)*4;
		}
		if(key_2)
		{
			points[1].e[0]+=(key_right-key_left)*4;
			points[1].e[1]+=(key_down-key_up)*4;
		}
		if(key_3)
		{
			points[2].e[0]+=(key_right-key_left)*4;
			points[2].e[1]+=(key_down-key_up)*4;
		}
		if(key_4)
		{
			points[3].e[0]+=(key_right-key_left)*4;
			points[3].e[1]+=(key_down-key_up)*4;
		}
		if(key_5)
		{
			circle_pos.e[0]+=(key_right-key_left)*5;
			circle_pos.e[1]+=(key_down-key_up)*5;
		}
		
		
		{
			static bool dragging=false, start_dragging=false;
			static time_t click;
			
			if( mb_right && !mb_right_p)
			{
				click=clock();
				start_dragging=true;
				
				initMouseDragging();
				SDL_ShowCursor(SDL_DISABLE);
			}
			if(start_dragging)
			{
				if((clock()-click)>(CLOCKS_PER_SEC/20))
				{
					dragging=true;
				}
			}
			
			if(!mb_right &&  mb_right_p) {SDL_ShowCursor(SDL_ENABLE); dragging=false; start_dragging=false;}
			if(dragging)
			{
				int xx,yy;
				
				getMouseDraggingValue(&xx,&yy);
				{
					cam_dir.e[0]+=xx/100.0f;
					cam_dir.e[1]-=yy/100.0f;
				
					if(cam_dir.e[1]<-pi/2) cam_dir.e[1]=-pi/2;
					if(cam_dir.e[1]> pi/2) cam_dir.e[1]= pi/2;
				}
			}
		}
		
		{
			vector3f move_cam;
			
			cam_pos.e[2]+=(key_x-key_z)*5;
			
			move_cam=vec3f(1,0,0);
			move_cam=rotateZv3f(move_cam,(cam_dir.e[0]+pi/2));
			move_cam=scalev3f(move_cam,5*(key_right-key_left));
			
			cam_pos=addv3f(cam_pos,move_cam);
			
			move_cam=vec3f(1,0,0);
			move_cam=rotateZv3f(move_cam,(cam_dir.e[0]));
			move_cam=scalev3f(move_cam,5*(key_up-key_down));
			
			cam_pos=addv3f(cam_pos,move_cam);
		
		}
		
		{
			int i;
			for(i=0; i<10; i++)
			{
				if(key_6)
				{
					irregularApplyImpulse(&player1,vec2f((key_right-key_left),(key_down-key_up)),2);
				}
				irregularIncSpeed(&player1,-0.002);
				irregularRotationalFriction(&player1,0.00001);
				
				
				if(key_7)
				{
					irregularApplyImpulse(&player2,vec2f((key_right-key_left),0),2);
				}
				/*irregularIncSpeed(&player2,-0.002);*/
				irregularHorizontalSpeedLimit(&player2,0.5);
				irregularApplyImpulse(&player2,vec2f(0,1),0.01);
				
				
				irregularRotationalFriction(&player2,0.00001);
				
				irregularUpdate(&player1,0.4,0.2);
				irregularUpdate(&player2,4,1);
				
				irregularUpdate(&ball1,2,2);
				
				if(irregularCollision(&player1,&player2))
				{
					irregularResolutionRotational(&player1,&player2,0.5,0,0.0001,0.0003);
					/*irregularRotationalFriction(&player2,0.00001);
					irregularIncSpeed(&player1,-0.002);*/
					/*irregularSurfaceFriction(&player1,&player2,0.1);
					*/
				}
				
				if(irregularCollision(&player2,&terrain1))
				{
					if(key_a)
					{
						player2.pos.e[1]-=4;
						player2.vel.e[1]=-2;
					}
					
					/*
					irregularResolutionRotationalFriction(&player2,&terrain1,0,0.5,0.0001,0.005);*/
					
					irregularResolutionFriction(&player2,&terrain1,1,0,1.5,0.5);
					/*irregularSurfaceFriction(&player1,&player2,0.1);
					*/
				}
				/*irregularHorizontalFriction(&player2,0.005);*/
				irregularIncSpeed(&player2,-0.005);
				
				if(irregularCollision(&ball1,&wall1))
				{
					irregularBounce(&ball1,&wall1,1,1);
				}
				
			}
		}
		
		
		if(!Update_OpenGL())
		{
			setColor2HW(128,128,128);
			clearHW();
			
			transform(unitm4f);
			
			texturing(1);
			setColor2HW(255,255,0);
			
			drawStringHW("Physics Test",10,10);
			
			texturing(0);
			
			setColor2HW(0,0,0);
		
			
			setColor2HW(0,0,0);
			irregularDraw(&player1);
			irregularDraw(&player2);
			irregularDraw(&terrain1);
			irregularDraw(&wall1);
			irregularDraw(&ball1);
			{
				
			setColor2HW(255,255,0);
			if(ThickLineSegmentToThickLineSegment(arr2fv(points[0],points[1]),8,arr2fv(points[2],points[3]),8))
			setColor2HW(255,255,255);
			
			drawThickLinefHW(points[0],points[1],8);
			drawThickLinefHW(points[2],points[3],8);
			
			
			}
			
			setColor2HW(255,0,0);
			if(CircleToTriangle(circle_pos,16,triangle)||
			CircleToThickLineSegment(circle_pos,16,arr2fv(points[0],points[1]),8)
			)
			
			setColor2HW(255,255,255);
			drawCirclefHW(circle_pos,16);
			setColor2HW(255,255,0);
			drawTrianglefHW(triangle);
			
			/*
			ViewMatrix=view_m4f(cam_pos,cam_dir);

		
			setColor2HW(255,255,255);
			texturing(0);

			reset_m4f();
			ModelMatrix=result_m4f;
				
			sendPVM();
			
			model_stack();
			
			{
				int i;
				for(i=1; i<25; i++)
				{
					addv3(vec3f( -500 , i*grid_h,0   ));
					addv3(vec3f(  500 , i*grid_h,0   ));
					addv3(vec3f( -500 ,-i*grid_h,0   ));
					addv3(vec3f(  500 ,-i*grid_h,0   ));
				}
				for(i=1; i<25; i++)
				{
					addv3(vec3f( i*grid_w , -500 , 0   ));
					addv3(vec3f( i*grid_w ,  500 , 0   ));
					addv3(vec3f(-i*grid_w , -500 , 0   ));
					addv3(vec3f(-i*grid_w ,  500 , 0   ));
				}
			}
			
			draw_stack(LINE_MODE);
			
			texturing(0);
			
			reset_m4f();
			ModelMatrix=result_m4f;
			
			sendPVM();
			
			depthTest(0);
			
			setColor2HW(255,0,0);
			draw3DLineHW(vec3f(0,0,0),vec3f( 500,0,0));
			setColor2HW(128,0,0);
			draw3DLineHW(vec3f(0,0,0),vec3f(-500,0,0));
			setColor2HW(0,255,0);
			draw3DLineHW(vec3f(0,0,0),vec3f(0, 500,0));
			setColor2HW(0,128,0);
			draw3DLineHW(vec3f(0,0,0),vec3f(0,-500,0));
			setColor2HW(0,0,255);
			draw3DLineHW(vec3f(0,0,0),vec3f(0,0, 500));
			setColor2HW(0,0,128);
			draw3DLineHW(vec3f(0,0,0),vec3f(0,0,-500));
			
			depthTest(1);*/
		}
	}
	
	deleteva2f(&square);
	deleteva2f(&square2);
	deleteva2f(&square3);
	deleteva2f(&terrain);
	deleteva2f(&wall);
	deleteva2f(&ball);
	
	quitFontHW();
	
	IO_Quit_OpenGL();
}
