/*

gcc main.c glad.c -IC:\mingw_dev_lib\include\SDL2 -LC:\mingw_dev_lib\lib -lmingw32 -lopengl32 -lSDL2main -lSDL2 -lSDL2_image -o main.exe -ansi -std=c89 -pedantic -w

*/

#define W 800
#define H 600

#define SIZE_H 800
#define SIZE_W 600

#include "../../Source/Libraries/all2.h"


arrow3f getClickLine()/*problematic*/
{
	vector4f mouse_click_point;
	vector4f cam_eye;
	
	matrix4f invView;
	vector2f mouse_pos;
	
	arrow3f result;
	
	invView=invertm4f(ViewMatrix);
	
	mouse_pos.e[0]=mouse_x;
	mouse_pos.e[1]=mouse_y;
	SWmapToHWMap(mouse_pos);
	mouse_click_point=vec4f(mouse_pos.e[0],mouse_pos.e[1],1.73,1);
	cam_eye=vec4f(0,0,0,1);
	mouse_click_point=m4fxv4f(invView,mouse_click_point);
	cam_eye=m4fxv4f(invView,cam_eye);
	result=arr3f(cam_eye.e[0],cam_eye.e[1],cam_eye.e[2],mouse_click_point.e[0],mouse_click_point.e[1],mouse_click_point.e[2]);
}

void printVertices(vector_array3f *a)
{
	int i;
	printf("\n");
	for(i=0; i<a->n; i++)
	{
		printf("(%f,%f,%f)\n",a->v[i].e[0],a->v[i].e[1],a->v[i].e[2]);
	}
}

void printIndices(number_arrayi *a)
{
	int i;
	printf("\n");
	for(i=0; i<a->n; i++)
	{
		printf("(%i)\n",a->v[i]);
	}
}

float mouse3d_x,mouse3d_y,mouse3d_z;
float click3d_x,click3d_y,click3d_z;
int click_x,click_y;

int grid_w=20,grid_h=20;
	vector3f cam_pos,cam_dir;

int selection_mode=0,mouse_mode=0;

bool	left_dragging=false,right_dragging=false,
		start_mouse3d_dragging=false,mouse3d_dragging=false,
		start_mouse_dragging=false,mouse_dragging=false;

void mouse3d_z_up()
{
	mouse3d_z+=4;
}
void mouse3d_z_down()
{
	mouse3d_z-=4;
}

vector2f projection(vector3f v)
{
	vector2f r;
	vector4f p4;
					
	p4=(m4fxv4f(getPVM(),vec4f(v.e[0],v.e[1],v.e[2],1)));
	r=vec2f(p4.e[0]/p4.e[3],p4.e[1]/p4.e[3]);
	HWmapToSWMap(r);
	
	return r;
}

float projectionZ(vector3f v)
{
	float z;
	vector4f p4;
					
	p4=(m4fxv4f(getPVM(),vec4f(v.e[0],v.e[1],v.e[2],1)));
	z=(p4.e[2]/p4.e[3]);
	
	return z;
}

void leftDragging()
{
	static bool start_dragging=false;
	static time_t click;
	
	if( mb_left && !mb_left_p)
	{
		if(mouse_mode==0)
		{
			click_x=mouse_x;
			click_y=mouse_y;
		}
		else
		{
			click3d_x=mouse3d_x;
			click3d_y=mouse3d_y;
			click3d_z=mouse3d_z;
		}
		
		click=clock();
		start_dragging=true;
	}
	if(start_dragging)
	{
		if((clock()-click)>(CLOCKS_PER_SEC/20))
		{
			left_dragging=true;
		}
	}
	
	if(!mb_left &&  mb_left_p) {left_dragging=false; start_dragging=false;}
	if(left_dragging)
	{
	}
}

void rightDragging()
{
	static bool start_dragging=false;
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
			right_dragging=true;
		}
	}
	
	if(!mb_right &&  mb_right_p) {SDL_ShowCursor(SDL_ENABLE); right_dragging=false; start_dragging=false;}
	if(right_dragging)
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

vector3f average_point(vector_array3f *points)
{
	vector3f average;
	int i;
	for(i=0; i<points->n; i++)
	{
		average.e[0]+=points->v[i].e[0];
		average.e[1]+=points->v[i].e[1];
		average.e[2]+=points->v[i].e[2];
	}
	average.e[0]/=points->n;
	average.e[1]/=points->n;
	average.e[2]/=points->n;
	
	return average;
}

vector3f average_point_indices(vector_array3f *points,number_arrayi *indices)
{
	vector3f average;
	int i;
	
	average=vec3f(0,0,0);
	for(i=0; i<indices->n; i++)
	{
		average.e[0]+=points->v[indices->v[i]].e[0];
		average.e[1]+=points->v[indices->v[i]].e[1];
		average.e[2]+=points->v[indices->v[i]].e[2];
	}
	average.e[0]/=indices->n;
	average.e[1]/=indices->n;
	average.e[2]/=indices->n;
	
	return average;
}

void transform_indices(vector_array3f *vector_array,number_arrayi *indices,matrix4f transform_matrix)
{
	vector4f v4;
	int i;
	for(i=0; i<indices->n; i++)
	{
		v4.e[0]=vector_array->v[indices->v[i]].e[0];
		v4.e[1]=vector_array->v[indices->v[i]].e[1];
		v4.e[2]=vector_array->v[indices->v[i]].e[2];
		v4.e[3]=1;
		
		v4=m4fxv4f(transform_matrix,v4);
		
		vector_array->v[indices->v[i]].e[0]=v4.e[0];
		vector_array->v[indices->v[i]].e[1]=v4.e[1];
		vector_array->v[indices->v[i]].e[2]=v4.e[2];
	}
}

void drawTriangles(vector_array3f *vertex_drawed,number_arrayi *indices)
{
	glEnable(GL_CULL_FACE);
			
	setColor2HW(192,192,192);
			
	glCullFace(GL_BACK);

	{
		int i,j,jn,triangle_n;
		
		triangle_n=indices->n/3;
		jn=triangle_n/3333;
		
		for(j=0; j<jn; j++)
		{
			model_stack();
			for(i=0; i<3333; i++)
			{
				addv3(vertex_drawed->v[indices->v[(i+j*3333)*3  ]]);
				addv3(vertex_drawed->v[indices->v[(i+j*3333)*3+1]]);
				addv3(vertex_drawed->v[indices->v[(i+j*3333)*3+2]]);
			}
			draw_stack(TRIANGLE_MODE);
		}
		
		jn=triangle_n%3333;
		
		{
			model_stack();
			for(i=0; i<jn; i++)
			{
				addv3(vertex_drawed->v[indices->v[(i+j*3333)*3  ]]);
				addv3(vertex_drawed->v[indices->v[(i+j*3333)*3+1]]);
				addv3(vertex_drawed->v[indices->v[(i+j*3333)*3+2]]);
			}
			draw_stack(TRIANGLE_MODE);
		}
	}
	
	setColor2HW(160,160,255);
	
	glCullFace(GL_FRONT);
	{
		int i,j,jn,triangle_n;
		
		triangle_n=indices->n/3;
		jn=triangle_n/3333;
		
		for(j=0; j<jn; j++)
		{
			model_stack();
			for(i=0; i<3333; i++)
			{
				addv3(vertex_drawed->v[indices->v[(i+j*3333)*3  ]]);
				addv3(vertex_drawed->v[indices->v[(i+j*3333)*3+1]]);
				addv3(vertex_drawed->v[indices->v[(i+j*3333)*3+2]]);
			}
			draw_stack(TRIANGLE_MODE);
		}
		
		jn=triangle_n%3333;
		
		{
			model_stack();
			for(i=0; i<jn; i++)
			{
				addv3(vertex_drawed->v[indices->v[(i+j*3333)*3  ]]);
				addv3(vertex_drawed->v[indices->v[(i+j*3333)*3+1]]);
				addv3(vertex_drawed->v[indices->v[(i+j*3333)*3+2]]);
			}
			draw_stack(TRIANGLE_MODE);
		}
	}
	
	glDisable(GL_CULL_FACE);
}

void drawLines(vector_array3f *vertex_drawed,number_arrayi *indices)
{		
	setColor2HW(0,0,0);
	{
		int i,j,jn,triangle_n;
		
		triangle_n=indices->n/3;
		jn=triangle_n/1666;
		
		for(j=0; j<jn; j++)
		{
			model_stack();
			for(i=0; i<1666; i++)
			{
				addv3(vertex_drawed->v[indices->v[(i+j*1666)*3  ]]); addv3(vertex_drawed->v[indices->v[(i+j*3333)*3+1]]);
				addv3(vertex_drawed->v[indices->v[(i+j*1666)*3+1]]); addv3(vertex_drawed->v[indices->v[(i+j*3333)*3+2]]);
				addv3(vertex_drawed->v[indices->v[(i+j*1666)*3+2]]); addv3(vertex_drawed->v[indices->v[(i+j*3333)*3  ]]);
			}
			draw_stack(TRIANGLE_MODE);
		}
		
		jn=triangle_n%1666;
		
		{
			model_stack();
			for(i=0; i<jn; i++)
			{
				addv3(vertex_drawed->v[indices->v[(i+j*1666)*3  ]]);
				addv3(vertex_drawed->v[indices->v[(i+j*1666)*3+1]]);
				addv3(vertex_drawed->v[indices->v[(i+j*1666)*3+2]]);
			}
			draw_stack(LINE_MODE);
		}
	}
}

void getSelectedTriangles(number_arrayi *indices,number_arrayi *selected_vertices,number_arrayi *selected_triangles)
{
	int triangles_n=indices->n/3,i;
	
	for(i=0; i<triangles_n; i++)
	{
		if(
		in_number_array(selected_vertices,indices->v[i*3+0])&&
		in_number_array(selected_vertices,indices->v[i*3+1])&&
		in_number_array(selected_vertices,indices->v[i*3+2])
		)
		pushnaiLargerExpansion(&selected_triangles,i,10000);
	}
}

void drawGrid()
{
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
}

void draw3Axises()
{
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
}

void drawSelectedLines(vector_array3f *vertex_d,number_arrayi *selected_vertices,bool line,bool loop)
{
	int i;

	setColor2HW(255,0,255);
	if(line)
	for(i=0; i<selected_vertices->n-1; i++)
	{
		drawLinefHW(projection(vertex_d->v[selected_vertices->v[i]]),
					projection(vertex_d->v[selected_vertices->v[i+1]]));
	}
	
	if(loop)
		drawLinefHW(projection(vertex_d->v[selected_vertices->v[i]]),
					projection(vertex_d->v[selected_vertices->v[0]]));
}

void drawPoints(vector_array3f *vertex_d,number_arrayi *selected_vertices)
{
	int i;
	
	setColor2HW(0,0,0);	
	
	for(i=0; i<vertex_d->n; i++)
	{
		setZ(projectionZ(vertex_d->v[i]));
		drawCirclefHW(projection(vertex_d->v[i]),3);
	}
	setColor2HW(255,255,0);
	
	for(i=0; i<selected_vertices->n; i++)
	{
		vector3f point;
		point=vertex_d->v[selected_vertices->v[i]];
		setZ(projectionZ(point)-0.0001);
		drawCirclefHW(projection(point),3);
	}
}

int main(int argc, char **argv)
{
	Window *win[2];
	
	bool line=false,loop=false;
	float circle_radius=8;
	
	vector_array3f vertex,vertex_transformed,*vertex_d,*vertex_e;
	number_arrayi index,selected_vertices,selected_triangles,*index_d,*index_e,*selected_vertices_e;
	
	selected_vertices_e=&selected_vertices;
	
	index_e=&index;
	vertex_e=&vertex;
	
	index_d=&index;
	vertex_d=&vertex;
	
	vertex=emptyva3f();
	vertex_transformed=emptyva3f();
	index=emptynai();
	selected_vertices=emptynai();
	selected_triangles=emptynai();
	
	
	mouseWheelUp	=&mouse3d_z_up;
	mouseWheelDown	=&mouse3d_z_down;
	
	target_fps=60;
	
	cam_pos=vec3f(150,150,150);
	cam_dir=vec3f(pi/4+pi,-pi/4,0);
	
	IO_Init_OpenGL("Animation Viewer 3D");
	key_input=0;
	
	initFontHW();
	
	PerspectiveMatrix=perspective_m4f(1.73,10000,1,1);
	
	mouse3d_x=0;
	mouse3d_y=0;
	mouse3d_z=0;
	
	glFrontFace(GL_CCW);
	
	win[0]=WindowC(50,50,300,200,"Window 1");
	
	win[1]=WindowC(350,150,300,200,"Window 2");
	
	while(!quit)
	{
		WindowsUpdate(win,2);
		
		if(key_p)
		{
			if(key_0 && !key_0_p)
			{
				printVertices(&vertex);
			}
			else if(key_1 && !key_1_p)
			{
				printIndices(&index);
			}
		}
		
		if(key_c)
		{
			if(key_0 && !key_0_p)
			{
				pushva3fLargerExpansion(vertex_e,vec3f(grid_w,0,0),10000);
				pushva3fLargerExpansion(vertex_e,vec3f(0,grid_h,0),10000);
				pushva3fLargerExpansion(vertex_e,vec3f(0,0,0),10000);
				
				pushnaiLargerExpansion(index_e,vertex_e->n-3,10000);
				pushnaiLargerExpansion(index_e,vertex_e->n-2,10000);
				pushnaiLargerExpansion(index_e,vertex_e->n-1,10000);
			}
		}
		
		if(key_q && !key_q_p)
		{
			selection_mode++;
			if(selection_mode>2)
				selection_mode=0;
			
			if(selection_mode==0 && mouse_mode==0)
				SDL_ShowCursor(SDL_ENABLE);
			else
				SDL_ShowCursor(SDL_DISABLE);
		}
		
		{
			static clock_t click;
			if(key_w && !key_w_p)
			{
				mouse_mode++;
				if(mouse_mode>1)
					mouse_mode=0;
				
				if(mouse_mode==1)
				{
					click=clock();
					
					initMouseDragging();
					start_mouse3d_dragging=true;
				}
				else
				{
					mouse3d_dragging=false;
					start_mouse3d_dragging=false;
				}
				
				if(selection_mode==0 && mouse_mode==0)
					SDL_ShowCursor(SDL_ENABLE);
				else
					SDL_ShowCursor(SDL_DISABLE);
			}
			
			if(start_mouse3d_dragging)
			{
				if((clock()-click)>(CLOCKS_PER_SEC/20))
				{
					mouse3d_dragging=true;
					/*start=false*/
				}
			}
		}
		
		if(selection_mode==2)
		{
			circle_radius+=(key_plus-key_minus);
			
			if(circle_radius< 8) circle_radius= 8;
			if(circle_radius>50) circle_radius=50;
		}
		
		if(mouse_mode==1)
		{
			if(mb_middle && !mb_middle_p)
			{
				mouse3d_x=0;
				mouse3d_y=0;
				mouse3d_z=0;
			}
		
			if(!mb_right && mouse3d_dragging)
			{
				int xx,yy;
				
				getMouseDraggingValue(&xx,&yy);
				{
					mouse3d_x+=cos(cam_dir.e[0])*(-yy)+cos(cam_dir.e[0]+pi/2)*xx;
					mouse3d_y+=sin(cam_dir.e[0])*(-yy)+sin(cam_dir.e[0]+pi/2)*xx;
				}
				
			}
		}
		
		{
			static bool
			translate=false,
			scale=false,
			rotate=false;
			
			static float amount=0;
			static int axis=0;
			static time_t press;
			
			if(selected_vertices.n)
			{
				if(key_l && !key_l_p)
				{
					if(line) loop=true;
					line=true;
				}
				if(key_kp_0 && !key_kp_0_p)
				{	
					if(line)
					{
						int i,n;
						n=selected_vertices_e->n;
						
						for(i=0; i<n; i++)
						{
							pushva3fLargerExpansion(vertex_e,vertex_e->v[selected_vertices_e->v[i]],10000);
						}
						
						for(i=0; i<n-1; i++)
						{
							
							pushnaiLargerExpansion(index_e,vertex_e->n-selected_vertices.n+i+1,10000);
							pushnaiLargerExpansion(index_e,vertex_e->n-selected_vertices.n+i,10000);
							pushnaiLargerExpansion(index_e,selected_vertices_e->v[i],10000);
							
							pushnaiLargerExpansion(index_e,selected_vertices_e->v[i],10000);
							pushnaiLargerExpansion(index_e,selected_vertices_e->v[i+1],10000);
							pushnaiLargerExpansion(index_e,vertex_e->n-selected_vertices_e->n+i+1,10000);
							
						}
						
						if(loop)
						{
							pushnaiLargerExpansion(index_e,vertex_e->n-selected_vertices_e->n,10000);
							pushnaiLargerExpansion(index_e,vertex_e->n-selected_vertices_e->n+i,10000);
							pushnaiLargerExpansion(index_e,selected_vertices_e->v[i],10000);
							
							pushnaiLargerExpansion(index_e,selected_vertices_e->v[i],10000);
							pushnaiLargerExpansion(index_e,selected_vertices_e->v[0],10000);
							pushnaiLargerExpansion(index_e,vertex.n-selected_vertices_e->n,10000);
						}

						deletenai(selected_vertices_e);
						
						for(i=0; i<n; i++)
							pushnaiLargerExpansion(selected_vertices_e,vertex_e->n-n+i,10000);
						
					}
					
					line=false;
					loop=false;
				}
				else if(key_kp_1 && !key_kp_1_p)
				{	
					if(line)
					{
						vector3f average;
						
						int i,n;
						n=selected_vertices_e->n;
						
						average=average_point_indices(vertex_e,selected_vertices_e);
						
						{
							pushva3fLargerExpansion(vertex_e,average,10000);
						}
						
						for(i=0; i<n-1; i++)
						{
							pushnaiLargerExpansion(index_e,selected_vertices_e->v[i],10000);
							pushnaiLargerExpansion(index_e,selected_vertices_e->v[i+1],10000);
							pushnaiLargerExpansion(index_e,vertex_e->n-1,10000);
						}
						
						if(loop)
						{
							pushnaiLargerExpansion(index_e,selected_vertices_e->v[i],10000);
							pushnaiLargerExpansion(index_e,selected_vertices_e->v[0],10000);
							pushnaiLargerExpansion(index_e,vertex_e->n-1,10000);
						}

						deletenai(selected_vertices_e);
						
						pushnaiLargerExpansion(selected_vertices_e,vertex_e->n-1,10000);
						
					}
					
					line=false;
					loop=false;
				}
				if(key_t && !key_t_p)
				{
					vertex_d=&vertex_transformed;
					
					amount=0;
					
					deleteva3f(&vertex_transformed);
					vertex_transformed=fcopyva3f(vertex_e);
				
					axis=-1;
					translate=true;
					
					press=clock();
					
					initMouseDragging();
					start_mouse_dragging=true;
				}
				if(key_s && !key_s_p)
				{
					vertex_d=&vertex_transformed;

					amount=0;
					
					deleteva3f(&vertex_transformed);
					vertex_transformed=fcopyva3f(vertex_e);
					
					axis=-1;
					scale=true;
					
					press=clock();
					
					initMouseDragging();
					start_mouse_dragging=true;
				}
				if(key_r && !key_r_p)
				{
					vertex_d=&vertex_transformed;

					amount=0;
					
					deleteva3f(&vertex_transformed);
					vertex_transformed=fcopyva3f(vertex_e);
					
					axis=-1;
					rotate=true;
					
					press=clock();
					
					initMouseDragging();
					start_mouse_dragging=true;
				}
				
				if(start_mouse_dragging)
				{
					if((clock()-press)>(CLOCKS_PER_SEC/20))
					{
						mouse_dragging=true;
					}
				}
				
				if(mb_left && !mb_left_p)
				{
					mouse_dragging=false;
					start_mouse_dragging=false;
					
					translate=false;
					scale=false;
					rotate=false;
					
					copyvacontent3f(&vertex_transformed,vertex_e);
					
					vertex_d=vertex_e;
				}

				if(mouse_dragging)
				{
					int xx,yy;
					
					if(key_n && !key_n_p) axis=0;
					if(key_x && !key_x_p) axis=1;
					if(key_y && !key_y_p) axis=2;
					if(key_z && !key_z_p) axis=3;
						
					getMouseDraggingValue(&xx,&yy);
					
					if(yy)
					{
						if(axis!=-1)
						amount+=yy;
						copyvacontent3f(vertex_e,&vertex_transformed);
						
						if(translate)
						{
							matrix4f trans;
								 if(axis==1)
							{
								trans=translation_m4f(vec3f(amount/10.0f,0,0));
								transform_indices(&vertex_transformed,selected_vertices_e,trans);
							}
							else if(axis==2)
							{
								trans=translation_m4f(vec3f(0,amount/10.0f,0));
								transform_indices(&vertex_transformed,selected_vertices_e,trans);
							}
							else if(axis==3)
							{
								trans=translation_m4f(vec3f(0,0,amount/10.0f));
								transform_indices(&vertex_transformed,selected_vertices_e,trans);
							}
						}
						if(scale)
						{
							matrix4f trans;
							vector3f average;
							
							average=average_point_indices(vertex_e,selected_vertices_e);
								 
								 if(axis==0)
							{
								reset_m4f();
								mul_m4f(translation_m4f(scalev3f(average,-1)));
								mul_m4f(scaling_m4f(vec3f(1+amount/50.0f,1+amount/50.0f,1+amount/50.0f)));
								mul_m4f(translation_m4f(average));
								
								transform_indices(&vertex_transformed,selected_vertices_e,result_m4f);
							}
							else if(axis==1)
							{
								reset_m4f();
								mul_m4f(translation_m4f(scalev3f(average,-1)));
								mul_m4f(scaling_m4f(vec3f(1+amount/50.0f,1,1)));
								mul_m4f(translation_m4f(average));
								
								transform_indices(&vertex_transformed,selected_vertices_e,result_m4f);
							}
							else if(axis==2)
							{
								reset_m4f();
								mul_m4f(translation_m4f(scalev3f(average,-1)));
								mul_m4f(scaling_m4f(vec3f(1,1+amount/50.0f,1)));
								mul_m4f(translation_m4f(average));
								
								transform_indices(&vertex_transformed,selected_vertices_e,result_m4f);
							}
							else if(axis==3)
							{
								reset_m4f();
								mul_m4f(translation_m4f(scalev3f(average,-1)));
								mul_m4f(scaling_m4f(vec3f(1,1,1+amount/50.0f)));
								mul_m4f(translation_m4f(average));
								
								transform_indices(&vertex_transformed,selected_vertices_e,result_m4f);
							}
						}
						if(rotate)
						{
							matrix4f trans;
							vector3f average;
							
							average=average_point_indices(vertex_e,selected_vertices_e);
							
								 if(axis==0)
							{
							}
							else if(axis==1)
							{
								reset_m4f();
								mul_m4f(translation_m4f(scalev3f(average,-1)));
								mul_m4f(rotationX_m4f(amount/30.0f));
								mul_m4f(translation_m4f(average));
								
								transform_indices(&vertex_transformed,selected_vertices_e,result_m4f);
							}
							else if(axis==2)
							{
								reset_m4f();
								mul_m4f(translation_m4f(scalev3f(average,-1)));
								mul_m4f(rotationY_m4f(amount/30.0f));
								mul_m4f(translation_m4f(average));
								
								transform_indices(&vertex_transformed,selected_vertices_e,result_m4f);
							}
							else if(axis==3)
							{
								reset_m4f();
								mul_m4f(translation_m4f(scalev3f(average,-1)));
								mul_m4f(rotationZ_m4f(amount/30.0f));
								mul_m4f(translation_m4f(average));
								
								transform_indices(&vertex_transformed,selected_vertices_e,result_m4f);
							}
						}
						
					}
				}
			}
		}
		
		if(selection_mode==1 && mouse_mode==0)
		{
			if(left_dragging && !mb_left)
			{
				deletenai(selected_vertices_e);
				{
					int i;
					for(i=0; i<vertex_e->n; i++)
					{
						vector2f point=projection(vertex_e->v[i]);
						
						float min_x,min_y,w,h;
						min_x=min(mouse_x,click_x);
						min_y=min(mouse_y,click_y);
						w=absf(mouse_x-click_x);
						h=absf(mouse_y-click_y);
						
						if(PointInRectangle(point,vec2f(min_x,min_y),vec2f(w,h)))
						pushnaiLargerExpansion(selected_vertices_e,i,10000);
					}
				}
			}
		}
		
		if(selection_mode==1 && mouse_mode==0)
		{
			if(left_dragging && !mb_left)
			{
				deletenai(selected_vertices_e);
				{
					int i;
					for(i=0; i<vertex.n; i++)
					{
						vector2f point=projection(vertex_e->v[i]);
						
						float min_x,min_y,w,h;
						min_x=min(mouse_x,click_x);
						min_y=min(mouse_y,click_y);
						w=absf(mouse_x-click_x);
						h=absf(mouse_y-click_y);
						
						if(PointInRectangle(point,vec2f(min_x,min_y),vec2f(w,h)))
						pushnaiLargerExpansion(selected_vertices_e,i,10000);
					}
				}
			}
		}
		
		if(selection_mode==2 && mouse_mode==0)
		{		
			if(mb_left)
			{
				{
					int i;
					for(i=0; i<vertex_e->n; i++)
					{
						vector2f point=projection(vertex_e->v[i]);
						
						if(point_distance(point,vec2f(mouse_x,mouse_y))<circle_radius)
						{
							if(!in_number_array(selected_vertices_e,i))
								pushnaiLargerExpansion(selected_vertices_e,i,10000);
						}
					}
				}
			}
			if(mb_middle)
			{
				{
					int i;
					for(i=0; i<selected_vertices_e->n; i++)
					{
						vector2f point=projection(vertex_e->v[selected_vertices_e->v[i]]);
						
						if(point_distance(point,vec2f(mouse_x,mouse_y))<circle_radius)
							deletefromnai(selected_vertices_e,i--,10000);
					}
				}
			}
		}
		
		
		
		leftDragging();
		rightDragging();
		
		{
			vector3f move_cam;
			
			if(key_Lshift || key_Rshift)
			cam_pos.e[2]+=(key_plus-key_minus)*5;
			
			move_cam=vec3f(1,0,0);
			move_cam=rotateZv3f(move_cam,(cam_dir.e[0]+pi/2));
			move_cam=scalev3f(move_cam,5*(key_right-key_left));
			
			cam_pos=addv3f(cam_pos,move_cam);
			
			move_cam=vec3f(1,0,0);
			move_cam=rotateZv3f(move_cam,(cam_dir.e[0]));
			move_cam=scalev3f(move_cam,5*(key_up-key_down));
			
			cam_pos=addv3f(cam_pos,move_cam);
		
		}
		
		
		if(!Update_OpenGL())
		{
			setZ(0);
			
			setColor2HW(64,64,64);
			clearHW();
			
			transform(unitm4f);
			
			texturing(0);
			
			if(!right_dragging)
			if(mouse_mode==0)
			{
				switch(selection_mode)
				{
					case 1:
					setColor2HW(255,0,255);
					drawLinefHW(vec2f(mouse_x-8,mouse_y),vec2f(mouse_x+8,mouse_y));
					drawLinefHW(vec2f(mouse_x,mouse_y-8),vec2f(mouse_x,mouse_y+8));
					if(left_dragging)
					{
						setColor2HW(255,255,0);
						drawRectangleFramefHW(vec2f(click_x,click_y),vec2f(mouse_x,mouse_y));
					}
					break;
					case 2:
					setColor2HW(255,0,255);
					drawCircleFramefHW(vec2f(mouse_x,mouse_y),circle_radius);
					break;
				}
			}
			
			
			texturing(1);
			setColorA2HW(255,0,0,255);
			
			drawStringHW("Animation Viewer 3D 1.0",10,10);
			
			{
				text data;
				data=empty_text;
				
				appendString(&data,"3d mouse x = ");
				appendFloat(&data,mouse3d_x,2);
				appendString(&data,"\n3d mouse y = ");
				appendFloat(&data,mouse3d_y,2);
				appendString(&data,"\n3d mouse z = ");
				appendFloat(&data,mouse3d_z,2);
			
				drawStringHW(data.str,W/2,10);
				
				deleteText(&data);
			}
			
			ViewMatrix=view_m4f(cam_pos,cam_dir);
		
			setColor2HW(255,255,255);
			texturing(0);
			
			reset_m4f();
			ModelMatrix=result_m4f;
				
			sendPVM();
			
			drawGrid(grid_w,grid_h);
			
			if(mouse_mode==1)
			{
				float mouse3d_size=5;

				texturing(0);
				
				setColor2HW(255,0,0);
				draw3DLineHW(vec3f(mouse3d_x-mouse3d_size,mouse3d_y,mouse3d_z),vec3f(mouse3d_x+mouse3d_size,mouse3d_y,mouse3d_z));
				setColor2HW(0,255,0);
				draw3DLineHW(vec3f(mouse3d_x,mouse3d_y-mouse3d_size,mouse3d_z),vec3f(mouse3d_x,mouse3d_y+mouse3d_size,mouse3d_z));
				setColor2HW(0,0,255);
				draw3DLineHW(vec3f(mouse3d_x,mouse3d_y,mouse3d_z-mouse3d_size),vec3f(mouse3d_x,mouse3d_y,mouse3d_z+mouse3d_size));
			
			}
			
			
			texturing(0);

			reset_m4f();
			ModelMatrix=result_m4f;
			
			sendPVM();
			
			drawTriangles(vertex_d,index_d);
			drawLines(vertex_d,index_d);
			
		
			transform(unitm4f);
			
			
			drawSelectedLines(vertex_d,selected_vertices_e,line,loop);
			drawPoints(vertex_d,selected_vertices_e);
			
			texturing(0);
			
			reset_m4f();
			ModelMatrix=result_m4f;
			
			sendPVM();
			
			draw3Axises();
			
			transform(unitm4f);
			texturing(0);
			
			depthTest(0);
			WindowsDraw(win,2);
			depthTest(1);
		}
	}
	
	WindowsDelete(win,2);
	
	deleteva3f(&vertex_transformed);
	deleteva3f(&vertex);
	deletenai(&index);
	
	quitFontHW();
	
	IO_Quit_OpenGL();
}