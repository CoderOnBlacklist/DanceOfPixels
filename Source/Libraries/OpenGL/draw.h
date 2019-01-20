#ifndef DRAW_HW
#define DRAW_HW

void draw_stack(GLenum mode)
{	
		glVertexAttribPointer(attPosition,vertex_is,GL_FLOAT,GL_FALSE,0,verticesxd);
		glEnableVertexAttribArray(attPosition);
	
	if(texcoord_is)
	{
		glVertexAttribPointer(attTexCoord,texcoord_is,GL_FLOAT,GL_FALSE,0,texcoordsxd);
		glEnableVertexAttribArray(attTexCoord);
	}
	else
		glDisableVertexAttribArray(attTexCoord);
	
	glDrawArrays(mode,0,vertex_n);
}

void drawLinefHW(vector2f p1,vector2f p2)
{	
	model_stack();
	addv2(p1);
	addv2(p2);
	draw_stack(LINE_MODE);
}

void drawArrowfHW(vector2f p1,vector2f p2,float d,float angle)
{	
	vector2f backward,tip1,tip2;
	backward=subv2f(p1,p2);
	backward=normalizev2f(backward);
	backward=scalev2f(backward,d);
	tip1=rotatev2f(backward, angle);
	tip1=addv2f(tip1,p2);
	tip2=rotatev2f(backward,-angle);
	tip2=addv2f(tip2,p2);
	
	model_stack();
	addv2(p1);
	addv2(p2);
	addv2(p2);
	addv2(tip1);
	addv2(p2);
	addv2(tip2);
	draw_stack(LINE_MODE);
}

void drawThickLinefHW(vector2f p1,vector2f p2,float d)
{
	vector2f normal;
	normal=vec3f_to_vec2f(crossf(vec2f_to_vec3f(subv2f(p2,p1)),vec3f(0,0,1)));
	normal=normalizev2f(normal);
	model_stack();
	addv2( addv2f(p1,scalev2f(normal, d)) );
	addv2( addv2f(p1,scalev2f(normal,-d)) );
	addv2( addv2f(p2,scalev2f(normal, d)) );
	
	addv2( addv2f(p2,scalev2f(normal, d)) );
	addv2( addv2f(p2,scalev2f(normal,-d)) );
	addv2( addv2f(p1,scalev2f(normal,-d)) );
	draw_stack(TRIANGLE_MODE);
}

void drawTrianglefHW(triangle2f T)
{	
	model_stack();
	addv2(T.vertex[0]);
	addv2(T.vertex[1]);
	addv2(T.vertex[2]);
	draw_stack(TRIANGLE_MODE);
}

void drawTrianglefListHW(vector_array2f *vaV)
{
	int i;
	
	glEnableVertexAttribArray(attTexCoord);
	
	for(i=0; i<vaV->n; i++)
	{
		triangle2f v;
		v.vertex[0]=vaV->v[i*3  ];
		v.vertex[1]=vaV->v[i*3+1];
		v.vertex[2]=vaV->v[i*3+2];
		
		drawTrianglefHW(v);
	}
	
}

void drawTrianglefList2HW(vector_array2f *vaV,int n)
{
	int i;
	
	glEnableVertexAttribArray(attTexCoord);
	
	for(i=0; i<n; i++)
	{
		triangle2f v;
		v.vertex[0]=vaV->v[i*3  ];
		v.vertex[1]=vaV->v[i*3+1];
		v.vertex[2]=vaV->v[i*3+2];
		
		drawTrianglefHW(v);
	}
	
}

void drawRectangleFramefHW(vector2f p1,vector2f p2)/*imperfect*/
{
	drawLinefHW(vec2f(p1.e[0]+0.5,p1.e[1]+0.5),vec2f(p2.e[0]-0.5,p1.e[1]+0.5));
	drawLinefHW(vec2f(p2.e[0]-0.5,p1.e[1]+0.5),vec2f(p2.e[0]-0.5,p2.e[1]-0.5));
	drawLinefHW(vec2f(p2.e[0]-0.5,p2.e[1]-0.5),vec2f(p1.e[0]+0.5,p2.e[1]-0.5));
	drawLinefHW(vec2f(p1.e[0]+0.5,p2.e[1]-0.5),vec2f(p1.e[0]+0.5,p1.e[1]+0.5));
}

void drawRectanglefHW(vector2f p1,vector2f p2)
{
	
	drawTrianglefHW(tri2f(p1.e[0],p1.e[1],p2.e[0],p2.e[1],p2.e[0],p1.e[1]));
	drawTrianglefHW(tri2f(p1.e[0],p1.e[1],p1.e[0],p2.e[1],p2.e[0],p2.e[1]));
}

void drawCircleFramefHW(vector2f p,float r)/*imperfect*/
{
	int i,n;
	float slice;
	
	r-=0.1;
	slice=1/r;
	n=2*pi*r+1;
	
	model_stack();
	
	for(i=0; i<n; i++)
	{
		addv2(vec2f(p.e[0]+cos((i  )*slice)*r,p.e[1]+sin((i  )*slice)*r));
		addv2(vec2f(p.e[0]+cos((i+1)*slice)*r,p.e[1]+sin((i+1)*slice)*r));
	}
	
	draw_stack(LINE_MODE);
}

void drawCirclefHW(vector2f p,float r)/*imperfect*/
{
	int i,n;
	float slice;
	
	r-=0.1;
	slice=1/r;
	n=2*pi*r+1;
	
	model_stack();
	
	for(i=0; i<n; i++)
	{
		addv2(vec2f(p.e[0],p.e[1]));
		addv2(vec2f(p.e[0]+cos((i  )*slice)*r,p.e[1]+sin((i  )*slice)*r));
		addv2(vec2f(p.e[0]+cos((i+1)*slice)*r,p.e[1]+sin((i+1)*slice)*r));
	}
	
	draw_stack(TRIANGLE_MODE);
}


void useTextureUnit(GLenum i)
{
	glActiveTexture(GL_TEXTURE0+i);
}

void useTextureHW(TextureHW tex)
{
	glBindTexture(GL_TEXTURE_2D,tex.id);
}

void drawTrianglefTexturedHW(triangle2f T,triangle2f U,TextureHW texHW)
{
	useTextureHW(texHW);
	
	model_stack();
	
	addv2(T.vertex[0]);
	addv2(T.vertex[1]);
	addv2(T.vertex[2]);
	
	addt2(U.vertex[0]);
	addt2(U.vertex[1]);
	addt2(U.vertex[2]);
	
	draw_stack(TRIANGLE_MODE);
}

void drawTrianglefList2TexturedHW(vector_array2f *vaV,vector_array2f *vaU,int n,TextureHW texHW)
{
	int i;
	for(i=0; i<n; i++)
	{
		triangle2f v,u;
		v.vertex[0]=vaV->v[i*3  ];
		v.vertex[1]=vaV->v[i*3+1];
		v.vertex[2]=vaV->v[i*3+2];
		
		u.vertex[0]=vaU->v[i*3  ];
		u.vertex[1]=vaU->v[i*3+1];
		u.vertex[2]=vaU->v[i*3+2];
		
		drawTrianglefTexturedHW(v,u,texHW);
	}
	
}

void drawImageHW(TextureHW tex,int x,int y)
{	
	drawTrianglefTexturedHW(tri2f(x,y,x,y+tex.h,x+tex.w,y+tex.h),tri2f(0,0,0,1,1,1),tex);
	drawTrianglefTexturedHW(tri2f(x,y,x+tex.w,y+tex.h,x+tex.w,y),tri2f(0,0,1,1,1,0),tex);
}

void drawImageScaledHW(TextureHW tex,int x,int y,int x_orig,int y_orig,int w,int h)
{	
	drawTrianglefTexturedHW(tri2f(x-x_orig,y-y_orig,x-x_orig  ,y-y_orig+h,x+w-x_orig,y-y_orig+h),tri2f(0,0,0,1,1,1),tex);
	drawTrianglefTexturedHW(tri2f(x-x_orig,y-y_orig,x-x_orig+w,y-y_orig+h,x+w-x_orig,y-y_orig),tri2f(0,0,1,1,1,0),tex);
}

void drawImagePartHW(TextureHW tex,int x,int y,int tx,int ty,int tw,int th)
{
	drawTrianglefTexturedHW(tri2f(x,y,x,y+th,x+tw,y+th),tri2f((tx)/(float)tex.w,(ty)/(float)tex.h,(tx   )/(float)tex.w	,(ty+th)/(float)tex.h,(tx+tw)/(float)tex.w,(ty+th)/(float)tex.h),tex);
	drawTrianglefTexturedHW(tri2f(x,y,x+tw,y+th,x+tw,y),tri2f((tx)/(float)tex.w,(ty)/(float)tex.h,(tx+tw)/(float)tex.w	,(ty+th)/(float)tex.h,(tx+tw)/(float)tex.w,(ty   )/(float)tex.h),tex);
}

void drawImagePartScaledHW(TextureHW tex,int x,int y,int tx,int ty,int tw,int th,int x_orig,int y_orig,int w,int h)
{
	GLfloat xs,ys,x1,y1,x2,y2,w1,w2,h1,h2;
	
	xs=w/(float)tw;
	ys=h/(float)th;
	
	w1=x_orig;
	w2=tw-x_orig;
	
	h1=y_orig;
	h2=th-y_orig;
	
	x1=x-w1*xs;
	x2=x+w2*xs;
	
	y1=y-h1*ys;
	y2=y+h2*ys;
	
	drawTrianglefTexturedHW(tri2f(x1,y1,x1,y2,x2,y2),tri2f(tx/(float)tex.w,ty/(float)tex.h,(tx   )/(float)tex.w,(ty+th)/(float)tex.h,(tx+tw)/(float)tex.w,(ty+th)/(float)tex.h),tex);
	drawTrianglefTexturedHW(tri2f(x1,y1,x2,y2,x2,y1),tri2f(tx/(float)tex.w,ty/(float)tex.h,(tx+tw)/(float)tex.w,(ty+th)/(float)tex.h,(tx+tw)/(float)tex.w,(ty   )/(float)tex.h),tex);
}

void draw3DLineHW(vector3f p1,vector3f p2)
{
	model_stack();
	
	addv3(p1);
	addv3(p2);
	
	draw_stack(LINE_MODE);
}

void draw3DLineStippledHW(vector3f p1,vector3f p2,float x)/*google the name*/
{
	vector3f dir,pos;
	float len;
	int n;
	
	
	dir=subv3f(p2,p1);
	len=lengthv3f(dir);
	dir=scalev3f(dir,1/len*x);
	
	n=len/x;
	
	pos=p1;
	
	model_stack();
	
	{
		int i;
		bool draw=true;
		
		for(i=0; i<n; i++)
		{
			if(draw)
			{
				addv3(pos);
				addv3(addv3f(pos,dir));
			}
			draw=!draw;
			
			pos=addv3f(pos,dir);
		}
	}
	
	draw_stack(LINE_MODE);
}

void drawSphere(vector3f pos,float r,int meridian,int longitude)
{
	int a,b,i,j;
	float is,js;
	vector3f quad[4];
	
	is=2*pi/meridian;
	js=pi/(longitude+1);
	
	model_stack();
	
	for(j=0; j<longitude+1; j++)
		for(i=0; i<meridian; i++)
		{
			a=i;b=j;
			quad[0]=vec3f(
			pos.e[0]+cos((a)*is)*cos(-pi/2+(b)*js)*r,
			pos.e[1]+sin((a)*is)*cos(-pi/2+(b)*js)*r,
			pos.e[2]			+sin(-pi/2+(b)*js)*r
			);
			a=i+1;b=j;
			quad[1]=vec3f(
			pos.e[0]+cos((a)*is)*cos(-pi/2+(b)*js)*r,
			pos.e[1]+sin((a)*is)*cos(-pi/2+(b)*js)*r,
			pos.e[2]			+sin(-pi/2+(b)*js)*r
			);
			a=i+1;b=j+1;
			quad[2]=vec3f(
			pos.e[0]+cos((a)*is)*cos(-pi/2+(b)*js)*r,
			pos.e[1]+sin((a)*is)*cos(-pi/2+(b)*js)*r,
			pos.e[2]			+sin(-pi/2+(b)*js)*r
			);
			a=i;b=j+1;
			quad[3]=vec3f(
			pos.e[0]+cos((a)*is)*cos(-pi/2+(b)*js)*r,
			pos.e[1]+sin((a)*is)*cos(-pi/2+(b)*js)*r,
			pos.e[2]			+sin(-pi/2+(b)*js)*r
			);
			
			addv3(quad[0]);
			addv3(quad[1]);
			addv3(quad[2]);
			addv3(quad[2]);
			addv3(quad[3]);
			addv3(quad[0]);
		}
	
	draw_stack(TRIANGLE_MODE);
}

#endif