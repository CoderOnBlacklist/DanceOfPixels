/*
Copyright (C) <2018-2019> <Tankut Zeytinoğlu>
You can find the text of zlib license in the root folder.
*/

#ifndef DRAW_H
#define DRAW_H

float g_depth;
float *depthBuffer;
#define setDepth(x) g_depth=x

int getLineX(vector2i p1,vector2i p2,int y)
{
	int
	
	x1=p1.e[0],
	x2=p2.e[0],
	y1=p1.e[1],
	y2=p2.e[1],
	
	delta_x,delta_y,
	sign_dx,sign_dy,
	slope_nominator=0;
	
	delta_x=x2-x1;
	delta_y=y2-y1;
	
	sign_dx=sign(delta_x);
	sign_dy=sign(delta_y);
	
	{
		int i,j;
		
		delta_x*=sign_dx;
		delta_y*=sign_dy;
		
		if(delta_x>delta_y)
		{
			for(i=-1,j=0; i<delta_x+1; i++)
			{
				slope_nominator+=delta_y;
				if(slope_nominator>delta_x)
				{
					slope_nominator-=delta_x;
					j++;
				}
				if((y1+j*sign_dy)==y)	return x1+i*sign_dx;
			}
		}
		else
		{
			for(i=0,j=-1; j<delta_y+1; j++)
			{
				slope_nominator+=delta_x;
				if(slope_nominator>delta_y)
				{
					slope_nominator-=delta_y;
					i++;
				}
				if((y1+j*sign_dy)==y)	return x1+i*sign_dx;
			}
		}
	}
	
	return -1993;
}


#define f_glxsN 3

int f_glxs_slope_nominator[f_glxsN],
	f_glxs_delta_x[f_glxsN],
	f_glxs_delta_y[f_glxsN],
	f_glxs_sign_dx[f_glxsN],
	f_glxs_sign_dy[f_glxsN],
	f_glxs_xstart [f_glxsN],
	f_glxs_x	  [f_glxsN],
	f_glxsI=0
	;
void getLineXStart(vector2i p1,vector2i p2,int xstart)
{
	f_glxs_delta_x[f_glxsI]=(p2.e[0]-p1.e[0]);
	f_glxs_delta_y[f_glxsI]=(p2.e[1]-p1.e[1]);
	
	f_glxs_sign_dx[f_glxsI]=sign(f_glxs_delta_x);
	f_glxs_sign_dy[f_glxsI]=sign(f_glxs_delta_y);
	
	f_glxs_slope_nominator[f_glxsI]=0;
	
	f_glxs_xstart[f_glxsI]=xstart;
	f_glxs_x	 [f_glxsI]=xstart;
}

void getNextLineX()
{
	f_glxs_slope_nominator[f_glxsI]+=f_glxs_delta_x[f_glxsI];
	f_glxs_x[f_glxsI]=
	f_glxs_xstart[f_glxsI]+
   (f_glxs_slope_nominator[f_glxsI]/f_glxs_delta_y[f_glxsI])*
	f_glxs_sign_dx[f_glxsI]-
 (1-f_glxs_sign_dx[f_glxsI])/2;
	;
}
/*optimized parts will be improved later on*/
void getLineXStartOpt(vector2i p1,vector2i p2,int xstart)/*problematic*/
{
	f_glxs_delta_x[f_glxsI]=(p2.e[0]-p1.e[0]);
	f_glxs_delta_y[f_glxsI]=(p2.e[1]-p1.e[1]);
	
	f_glxs_sign_dx[f_glxsI]=sign(f_glxs_delta_x);
	f_glxs_sign_dy[f_glxsI]=sign(f_glxs_delta_y);
	
	f_glxs_slope_nominator[f_glxsI]=f_glxs_delta_x[f_glxsI];
	
	f_glxs_xstart[f_glxsI]=xstart;
	f_glxs_x	 [f_glxsI]=xstart;
}

void getNextLineXOpt()/*problematic*/
{
	/*multiple integer division problem*/
	f_glxs_x[f_glxsI]+=
   (f_glxs_slope_nominator[f_glxsI]/f_glxs_delta_y[f_glxsI])*
	f_glxs_sign_dx[f_glxsI]/*-
 (1-f_glxs_sign_dx[f_glxsI])/2*/;
	;
}

/*int (*fp[3])();*/

void drawLineHorizontal(int x1,int x2,int y)
{
	int i;
	for(i=x1; i<x2; i++)
		drawPixelSafe(i,y);
}
void drawLineVertical(int y1,int y2,int x)
{
	int j;
	for(j=y1; j<y2; j++)
		drawPixelSafe(x,j);
}

void drawLine(vector2i p1,vector2i p2)
{
	int
	
	x1=p1.e[0],
	x2=p2.e[0],
	y1=p1.e[1],
	y2=p2.e[1],
	
	delta_x,delta_y,
	sign_dx,sign_dy,
	slope_nominator=0;
	
	delta_x=x2-x1;
	delta_y=y2-y1;
	
	sign_dx=sign(delta_x);
	sign_dy=sign(delta_y);
	
	{
		int i,j;
		
		delta_x*=sign_dx;
		delta_y*=sign_dy;
		
		if(delta_x>delta_y)
		{
			for(i=0,j=0; i<delta_x; i++)
			{
				slope_nominator+=delta_y;
				if(slope_nominator>delta_x)
				{
					slope_nominator-=delta_x;
					j++;
				}
				drawPixelSafe(x1+i*sign_dx,y1+j*sign_dy);
			}
		}
		else
		{
			for(i=0,j=0; j<delta_y; j++)
			{
				slope_nominator+=delta_x;
				if(slope_nominator>delta_y)
				{
					slope_nominator-=delta_y;
					i++;
				}
				drawPixelSafe(x1+i*sign_dx,y1+j*sign_dy);
			}
		}
	}	
}

/*void drawLineCompatible(vector2i p1,vector2i p2)
{
	int x,ymin,
	i,
	x1=p1.e[0],
	x2=p2.e[0],
	y1=p1.e[1],
	y2=p2.e[1],
	
	sign_dx,
	
	delta_x,delta_y;
	
	delta_x=abs(x2-x1);
	delta_y=abs(y2-y1);
	
	sign_dx=sign(x2-x1); might be removed
	
	ymin=min(y1,y2);
	
	if(point_distance(vec2i_to_vec2f(p1),vec2i_to_vec2f(p2))<1) return;
	
	if(delta_y)
	{
		f_glxsI=0;
		
		if(y1<y2)
		{
			x=x1;
			getLineXStart(p1,p2,x);
		}
		else
		{
			x=x2;
			getLineXStart(p2,p1,x);
		}
		
		if(delta_y>delta_x)
		{
			for(i=0; i<delta_y; i++)
			{
				drawPixelSafe(x,ymin+i);
				f_glxsI=0;
				getNextLineX();
				x=f_glxs_x[0];
			}
		}
		else
		{ problematic area
			int xp,x1,x2;
			xp=x;
			printf("%d\n",x);
			for(i=0; i<delta_y; i++)
			{				
				x1=x;
				x2=xp;
				
				if(x1>x2) swap(x1,x2);
				
				xp=x;
				
				f_glxsI=0;
				getNextLineX();
				
				x=f_glxs_x[0];
			}
		}
		
		
		return;
	}
		if(x1>x2) swap(x1,x2);
		drawLineHorizontal(x1,x2,y1);
}
*/

void drawTriangleFrame(triangle2i T)
{
	int ordered_indices[3];
	
	sort3(T.vertex[0].e[1],T.vertex[1].e[1],T.vertex[2].e[1],ordered_indices);
	
	drawLine(T.vertex[ordered_indices[2]],T.vertex[ordered_indices[0]]);
	drawLine(T.vertex[ordered_indices[2]],T.vertex[ordered_indices[1]]);
	drawLine(T.vertex[ordered_indices[1]],T.vertex[ordered_indices[0]]);
}
/*
void drawTriangle(triangle2i T)
{
	int
	ordered_indices[3],i,
	x[3],y[3],
	dy,
	x1,x2;

	sort3(T.vertex[0].e[1],T.vertex[1].e[1],T.vertex[2].e[1],ordered_indices);
	
	x[0]=T.vertex[ordered_indices[0]].e[0];
	y[0]=T.vertex[ordered_indices[0]].e[1];
	x[1]=T.vertex[ordered_indices[1]].e[0];
	y[1]=T.vertex[ordered_indices[1]].e[1];
	x[2]=T.vertex[ordered_indices[2]].e[0];
	y[2]=T.vertex[ordered_indices[2]].e[1];
	
	dy=y[1]-y[0];
	if(dy)
	{
		{
			f_glxsI=0;
			x1=x[0];
			getLineXStart(vec2i(x[0],y[0]),vec2i(x[1],y[1]),x1);

			f_glxsI=1;
			x2=x[0];
			getLineXStart(vec2i(x[0],y[0]),vec2i(x[2],y[2]),x2);
		}
		
		for(i=0; i<dy; i++)
		{	
			if(x1>x2)
			{
				int tmp;
				tmp=x1;
				x1=x2;
				x2=tmp;
			}
			
			{
				int j,a;
				for(j=x1; j<x2; j++)
				{
					a=( W*(y[0]+i)+j )*4;
					pixels[a  ]=b;
					pixels[a+1]=g;
					pixels[a+2]=r;
				}
			}
			
			f_glxsI=0; getNextLineX(); x1=f_glxs_x[0];
			f_glxsI=1; getNextLineX(); x2=f_glxs_x[1];
		}
	}
	
	dy=y[2]-y[1];
	if(dy)
	{		
		{	
			int tmp_x,k,n;
			n=y[1]-y[0];

			f_glxsI=1;
			getLineXStart(vec2i(x[0],y[0]),vec2i(x[2],y[2]),x[0]);
			tmp_x=x[0];
			for(k=0; k<n; k++)
			{
				getNextLineX();
				tmp_x=f_glxs_x[1];
			}
			
			x2=tmp_x;
			
			f_glxsI=0;
			x1=x[1];
			getLineXStart(vec2i(x[1],y[1]),vec2i(x[2],y[2]),x1);	
		}
		
		for(i=0; i<dy; i++)
		{
			if(x1>x2) 
			{
				int tmp;
				tmp=x1;
				x1=x2;
				x2=tmp;
			}
			
			{
				int j,a;
				for(j=x1; j<x2; j++)
				{
					a=( W*(y[1]+i)+j )*4;
					pixels[a  ]=b;
					pixels[a+1]=g;
					pixels[a+2]=r;
				}
			}
			
			f_glxsI=0; getNextLineX(); x1=f_glxs_x[0];
			f_glxsI=1; getNextLineX(); x2=f_glxs_x[1];
		}
	}

}
*/
void drawTriangle(triangle2i T)/*safe*/
{
	int
	ordered_indices[3],i,
	x[3],y[3],
	dy,
	x1,x2;

	sort3(T.vertex[0].e[1],T.vertex[1].e[1],T.vertex[2].e[1],ordered_indices);
	
	x[0]=T.vertex[ordered_indices[0]].e[0];
	y[0]=T.vertex[ordered_indices[0]].e[1];
	x[1]=T.vertex[ordered_indices[1]].e[0];
	y[1]=T.vertex[ordered_indices[1]].e[1];
	x[2]=T.vertex[ordered_indices[2]].e[0];
	y[2]=T.vertex[ordered_indices[2]].e[1];
	
	dy=y[1]-y[0];
	if(dy)
	{
		{
			f_glxsI=0;
			x1=x[0];
			getLineXStart(vec2i(x[0],y[0]),vec2i(x[1],y[1]),x1);

			f_glxsI=1;
			x2=x[0];
			getLineXStart(vec2i(x[0],y[0]),vec2i(x[2],y[2]),x2);
		}
		
		for(i=0; i<dy; i++)
		{	
			if((y[0]+i<0) || y[0]+i>=current_buffer->h)
			{
				f_glxsI=0; getNextLineX(); x1=f_glxs_x[0];
				f_glxsI=1; getNextLineX(); x2=f_glxs_x[1];
				continue;
			}
			
			if(x1>x2)
			{
				int tmp;
				tmp=x1;
				x1=x2;
				x2=tmp;
			}
			
			if(x1<0) x1=0;
			if(x2>=current_buffer->w) x2=current_buffer->w;
			
			{
				int j,a;
				for(j=x1; j<x2; j++)
				{
					a=( current_buffer->w*(y[0]+i)+j )*4;
					current_buffer->pixels[a  ]=g_color.b;
					current_buffer->pixels[a+1]=g_color.g;
					current_buffer->pixels[a+2]=g_color.r;
				}
			}
			
			f_glxsI=0; getNextLineX(); x1=f_glxs_x[0];
			f_glxsI=1; getNextLineX(); x2=f_glxs_x[1];
		}
	}
	
	dy=y[2]-y[1];
	if(dy)
	{		
		{	
			int tmp_x,k,n;
			n=y[1]-y[0];

			f_glxsI=1;
			getLineXStart(vec2i(x[0],y[0]),vec2i(x[2],y[2]),x[0]);
			tmp_x=x[0];
			for(k=0; k<n; k++)
			{
				getNextLineX();
				tmp_x=f_glxs_x[1];
			}
			
			x2=tmp_x;
			
			f_glxsI=0;
			x1=x[1];
			getLineXStart(vec2i(x[1],y[1]),vec2i(x[2],y[2]),x1);	
		}
		
		for(i=0; i<dy; i++)
		{
			if((y[1]+i<0) || y[1]+i>=current_buffer->h)
			{
				f_glxsI=0; getNextLineX(); x1=f_glxs_x[0];
				f_glxsI=1; getNextLineX(); x2=f_glxs_x[1];
				continue;
			}
			
			if(x1>x2) 
			{
				int tmp;
				tmp=x1;
				x1=x2;
				x2=tmp;
			}
			
			if(x1<0) x1=0;
			if(x2>=current_buffer->w) x2=current_buffer->w;
			
			{
				int j,a;
				for(j=x1; j<x2; j++)
				{
					a=( current_buffer->w*(y[1]+i)+j )*4;
					current_buffer->pixels[a  ]=g_color.b;
					current_buffer->pixels[a+1]=g_color.g;
					current_buffer->pixels[a+2]=g_color.r;
				}
			}
			
			f_glxsI=0; getNextLineX(); x1=f_glxs_x[0];
			f_glxsI=1; getNextLineX(); x2=f_glxs_x[1];
		}
	}
}

vector2f interpolateInTriangle(float i0,float i1,float i2,triangle2f tri)
{
	float a,b,c,d;
	matrix2f inv;
	vector2f v,gradient;
	a=tri.vertex[1].e[0]-tri.vertex[0].e[0];
	b=tri.vertex[1].e[1]-tri.vertex[0].e[1];
	c=tri.vertex[2].e[0]-tri.vertex[0].e[0];
	d=tri.vertex[2].e[1]-tri.vertex[0].e[1];
	inv=invertm2f(
		mat2f(
			a,b,
			c,d
		)
	);
	v.e[0]=i1-i0;
	v.e[1]=i2-i0;
	
	gradient=m2fxv2f(inv,v);
	
	return gradient;
}

arrow2f getTriangleTextureTranslationReference(triangle2f vf,triangle2f tf)
{
	int i;
	vector2f gradient[2];
		
	triangle2f tri=vf;
	float a,b,c,d,det;
	matrix2f inv;
	
	vector2f v1[2],v2;
	
	a=tri.vertex[1].e[0]-tri.vertex[0].e[0];
	b=tri.vertex[1].e[1]-tri.vertex[0].e[1];
	c=tri.vertex[2].e[0]-tri.vertex[0].e[0];
	d=tri.vertex[2].e[1]-tri.vertex[0].e[1];
	
	det=a*d-b*c;
	
	inv.col[0].e[0]= d/det; inv.col[1].e[0]=-b/det;
	inv.col[0].e[1]=-c/det; inv.col[1].e[1]= a/det;

	v1[0].e[0]=inv.col[0].e[0];
	v1[0].e[1]=inv.col[1].e[0];
	
	v1[1].e[0]=inv.col[0].e[1];
	v1[1].e[1]=inv.col[1].e[1];
	
	v2.e[0]=tf.vertex[1].e[0]-tf.vertex[0].e[0];
	v2.e[1]=tf.vertex[2].e[0]-tf.vertex[0].e[0];
		
	gradient[0].e[0] = v1[0].e[0]*v2.e[0] + v1[0].e[1]*v2.e[1];
	gradient[0].e[1] = v1[1].e[0]*v2.e[0] + v1[1].e[1]*v2.e[1];

	v2.e[0]=tf.vertex[1].e[1]-tf.vertex[0].e[1];
	v2.e[1]=tf.vertex[2].e[1]-tf.vertex[0].e[1];
		
	gradient[1].e[0] = v1[0].e[0]*v2.e[0] + v1[0].e[1]*v2.e[1];
	gradient[1].e[1] = v1[1].e[0]*v2.e[0] + v1[1].e[1]*v2.e[1];
	
	{
		arrow2f result;
		
		result.from.e[0]=gradient[0].e[0];
		result.from.e[1]=gradient[1].e[0];
		result.to.	e[0]=gradient[0].e[1];
		result.to.	e[1]=gradient[1].e[1];

		return result;
	}
}
void drawTriangleTextured(triangle2i T, triangle2i U, Texture tex)
{
	int
	ordered_indices[3],i,
	x[3],y[3],
	dy,
	x1,x2,xp,q,q2;

	arrow2f reference;
	vector2f texCoord,temp;
	
	sort3(T.vertex[0].e[1],T.vertex[1].e[1],T.vertex[2].e[1],ordered_indices);
	
	x[0]=T.vertex[ordered_indices[0]].e[0];
	y[0]=T.vertex[ordered_indices[0]].e[1];
	x[1]=T.vertex[ordered_indices[1]].e[0];
	y[1]=T.vertex[ordered_indices[1]].e[1];
	x[2]=T.vertex[ordered_indices[2]].e[0];
	y[2]=T.vertex[ordered_indices[2]].e[1];
	
	reference=getTriangleTextureTranslationReference(tri2i_to_tri2f(T),tri2i_to_tri2f(U));
	
	texCoord=vec2i_to_vec2f(U.vertex[ordered_indices[0]]);
	
	texCoord.e[0]+=(reference.from.e[0]+reference.to.e[0])*0.5f;
	texCoord.e[1]+=(reference.from.e[1]+reference.to.e[1])*0.5f;
	
	dy=y[1]-y[0];
	if(dy)
	{
		{
			f_glxsI=0;
			x1=x[0];
			getLineXStart(vec2i(x[0],y[0]),vec2i(x[1],y[1]),x1);

			f_glxsI=1;
			x2=x[0];
			getLineXStart(vec2i(x[0],y[0]),vec2i(x[2],y[2]),x2);
		}
		
		if(x1>x2) xp=x2; else xp=x1;
		
		for(i=0; i<dy; i++)
		{	
			if(x1>x2)
			{
				int tmp;
				tmp=x1;
				x1=x2;
				x2=tmp;
			}
			
			texCoord.e[0]+=reference.from.e[0]*(x1-xp);
			texCoord.e[1]+=reference.from.e[1]*(x1-xp);
			
			if((y[0]+i<0) || y[0]+i>=current_buffer->h)
			{
				xp=x2;
				
				{
					f_glxs_slope_nominator[0]+=f_glxs_delta_x[0];
					f_glxs_x[0]=
					f_glxs_xstart[0]+
				   (f_glxs_slope_nominator[0]/f_glxs_delta_y[0])*
					f_glxs_sign_dx[0]-
				 (1-f_glxs_sign_dx[0])/2;
					;
				}
				x1=f_glxs_x[0];
				
		
				{
					f_glxs_slope_nominator[1]+=f_glxs_delta_x[1];
					f_glxs_x[1]=
					f_glxs_xstart[1]+
				   (f_glxs_slope_nominator[1]/f_glxs_delta_y[1])*
					f_glxs_sign_dx[1]-
				 (1-f_glxs_sign_dx[1])/2;
					;
				}
				x2=f_glxs_x[1];
				
				texCoord.e[0]+=reference.to.e[0];
				texCoord.e[1]+=reference.to.e[1];
				
				continue;
			}
			
			if(x1<0)
			{	
				texCoord.e[0]+=reference.from.e[0]*(-x1);
				texCoord.e[1]+=reference.from.e[1]*(-x1);
				
				x1=0;
			}
			if(x2>=current_buffer->w)
				x2=current_buffer->w;
				
			q=( current_buffer->w*(y[1]+i)+x1 )*4;
			{
				int j,tx,ty;
				for(j=x1; j<x2; j++)
				{
					tx=((int)texCoord.e[0]);/*%tex.w;*/
					ty=((int)texCoord.e[1]);/*%tex.h;*/
					
					if(tx<0 || tx>=tex.w || ty<0 || ty>=tex.h)
					{
						texCoord.e[0]+=reference.from.e[0];
						texCoord.e[1]+=reference.from.e[1];
						
						continue;
					}
					
					q2=(tex.w*ty+tx)*4;
					g_color.a=tex.pixels[q2+3];
					
					if(g_color.a)
					{
						current_buffer->pixels[q  ]=tex.pixels[q2+2];
						current_buffer->pixels[q+1]=tex.pixels[q2+1];
						current_buffer->pixels[q+2]=tex.pixels[q2  ];
					
						q+=4;
					}
					
					texCoord.e[0]+=reference.from.e[0];
					texCoord.e[1]+=reference.from.e[1];
				}
			}
			
			xp=x2;
			

			{
				f_glxs_slope_nominator[0]+=f_glxs_delta_x[0];
				f_glxs_x[0]=
				f_glxs_xstart[0]+
			   (f_glxs_slope_nominator[0]/f_glxs_delta_y[0])*
				f_glxs_sign_dx[0]-
			 (1-f_glxs_sign_dx[0])/2;
				;
			}
			x1=f_glxs_x[0];
			

			{
				f_glxs_slope_nominator[1]+=f_glxs_delta_x[1];
				f_glxs_x[1]=
				f_glxs_xstart[1]+
			   (f_glxs_slope_nominator[1]/f_glxs_delta_y[1])*
				f_glxs_sign_dx[1]-
			 (1-f_glxs_sign_dx[1])/2;
				;
			}
			x2=f_glxs_x[1];
			
			texCoord.e[0]+=reference.to.e[0];
			texCoord.e[1]+=reference.to.e[1];
		}
	}
	
	texCoord=vec2i_to_vec2f(U.vertex[ordered_indices[1]]);
	
	texCoord.e[0]+=(reference.from.e[0]+reference.to.e[0])*0.5f;
	texCoord.e[1]+=(reference.from.e[1]+reference.to.e[1])*0.5f;
	
	dy=y[2]-y[1];
	if(dy)
	{		
		{	
			int tmp_x,k,n;
			n=y[1]-y[0];

			f_glxsI=1;
			getLineXStart(vec2i(x[0],y[0]),vec2i(x[2],y[2]),x[0]);
			tmp_x=x[0];
			for(k=0; k<n; k++)
			{
				getNextLineX();
				tmp_x=f_glxs_x[1];
			}
			
			x2=tmp_x;
			
			f_glxsI=0;
			x1=x[1];
			getLineXStart(vec2i(x[1],y[1]),vec2i(x[2],y[2]),x1);	
		}
		
		if(x1>x2)
		{
			xp=x2;
			
			texCoord.e[0]+=reference.from.e[0]*(x2-x1);
			texCoord.e[1]+=reference.from.e[1]*(x2-x1);
		}
		else
			xp=x1;
		
		for(i=0; i<dy; i++)
		{
			if(x1>x2)
			{
				int tmp;
				tmp=x1;
				x1=x2;
				x2=tmp;
			}
			
			texCoord.e[0]+=reference.from.e[0]*(x1-xp);
			texCoord.e[1]+=reference.from.e[1]*(x1-xp);
			
			if((y[1]+i<0) || y[1]+i>=current_buffer->h)
			{
				xp=x2;
			
				{
					f_glxs_slope_nominator[0]+=f_glxs_delta_x[0];
					f_glxs_x[0]=
					f_glxs_xstart[0]+
				   (f_glxs_slope_nominator[0]/f_glxs_delta_y[0])*
					f_glxs_sign_dx[0]-
				 (1-f_glxs_sign_dx[0])/2;
					;
				}
				x1=f_glxs_x[0];
				

				{
					f_glxs_slope_nominator[1]+=f_glxs_delta_x[1];
					f_glxs_x[1]=
					f_glxs_xstart[1]+
				   (f_glxs_slope_nominator[1]/f_glxs_delta_y[1])*
					f_glxs_sign_dx[1]-
				 (1-f_glxs_sign_dx[1])/2;
					;
				}
				x2=f_glxs_x[1];
				
				texCoord.e[0]+=reference.to.e[0];
				texCoord.e[1]+=reference.to.e[1];
				
				continue;
			}
			
			if(x1<0)
			{	
				texCoord.e[0]+=reference.from.e[0]*(-x1);
				texCoord.e[1]+=reference.from.e[1]*(-x1);
				
				x1=0;
			}
			if(x2>=current_buffer->w)
			{
				x2=current_buffer->w;
			}
			
			q=( current_buffer->w*(y[1]+i)+x1 )*4;
			{
				int j,tx,ty;
				for(j=x1; j<x2; j++)
				{	
					tx=((int)texCoord.e[0]);/*%tex.w;*/
					ty=((int)texCoord.e[1]);/*%tex.h;*/
					
					if(tx<0 || tx>=tex.w || ty<0 || ty>=tex.h)
					{
						texCoord.e[0]+=reference.from.e[0];
						texCoord.e[1]+=reference.from.e[1];
						
						continue;
					}
					
					q2=(tex.w*ty+tx)*4;
					
					g_color.a=tex.pixels[q2+3];
					
					if(g_color.a)
					{
						current_buffer->pixels[q  ]=tex.pixels[q2+2];
						current_buffer->pixels[q+1]=tex.pixels[q2+1];
						current_buffer->pixels[q+2]=tex.pixels[q2  ];
					
						q+=4;
					}
					
					texCoord.e[0]+=reference.from.e[0];
					texCoord.e[1]+=reference.from.e[1];
				}
			}
			
			xp=x2;
			
		 
			{
				f_glxs_slope_nominator[0]+=f_glxs_delta_x[0];
				f_glxs_x[0]=
				f_glxs_xstart[0]+
			   (f_glxs_slope_nominator[0]/f_glxs_delta_y[0])*
				f_glxs_sign_dx[0]-
			 (1-f_glxs_sign_dx[0])/2;
				;
			}
			x1=f_glxs_x[0];
			
		
			{
				f_glxs_slope_nominator[1]+=f_glxs_delta_x[1];
				f_glxs_x[1]=
				f_glxs_xstart[1]+
			   (f_glxs_slope_nominator[1]/f_glxs_delta_y[1])*
				f_glxs_sign_dx[1]-
			 (1-f_glxs_sign_dx[1])/2;
				;
			}
			x2=f_glxs_x[1];
			
			texCoord.e[0]+=reference.to.e[0];
			texCoord.e[1]+=reference.to.e[1];
		}
	}

}

void drawTriangleTexturedColored(triangle2i T, triangle2i U, Texture tex)
{
	int
	ordered_indices[3],i,
	x[3],y[3],
	dy,
	x1,x2,xp;

	arrow2f reference;
	vector2f texCoord,temp;
	
	saveColor(0);
	
	sort3(T.vertex[0].e[1],T.vertex[1].e[1],T.vertex[2].e[1],ordered_indices);
	
	x[0]=T.vertex[ordered_indices[0]].e[0];
	y[0]=T.vertex[ordered_indices[0]].e[1];
	x[1]=T.vertex[ordered_indices[1]].e[0];
	y[1]=T.vertex[ordered_indices[1]].e[1];
	x[2]=T.vertex[ordered_indices[2]].e[0];
	y[2]=T.vertex[ordered_indices[2]].e[1];
	
	reference=getTriangleTextureTranslationReference(tri2i_to_tri2f(T),tri2i_to_tri2f(U));
	
	texCoord=vec2i_to_vec2f(U.vertex[ordered_indices[0]]);
	
	texCoord.e[0]+=(reference.from.e[0]+reference.to.e[0])*0.5f;
	texCoord.e[1]+=(reference.from.e[1]+reference.to.e[1])*0.5f;
	
	dy=y[1]-y[0];
	if(dy)
	{
		{
			f_glxsI=0;
			x1=x[0];
			getLineXStart(vec2i(x[0],y[0]),vec2i(x[1],y[1]),x1);

			f_glxsI=1;
			x2=x[0];
			getLineXStart(vec2i(x[0],y[0]),vec2i(x[2],y[2]),x2);
		}
		
		if(x1>x2) xp=x2; else xp=x1;
		
		for(i=0; i<dy; i++)
		{	
			if(x1>x2)
			{
				int tmp;
				tmp=x1;
				x1=x2;
				x2=tmp;
			}
			
			texCoord.e[0]+=reference.from.e[0]*(x1-xp);
			texCoord.e[1]+=reference.from.e[1]*(x1-xp);
			
			{
				
				int j,q,tx,ty;
				for(j=x1; j<x2; j++)
				{	
					tx=texCoord.e[0];
					ty=texCoord.e[1];
					
					if(tx<0 || tx>=tex.w || ty<0 || ty>=tex.h) goto end;
					
					g_color.a=tex.pixels[(tex.w*ty+tx)*4+3];
					
					if(!g_color.a) goto end;
					
					g_color.r=tex.pixels[(tex.w*ty+tx)*4  ];
					g_color.g=tex.pixels[(tex.w*ty+tx)*4+1];
					g_color.b=tex.pixels[(tex.w*ty+tx)*4+2];
					
					scaleColor(colorRecord[0]);
					/*unoptimized because of double assignment*/
					q=( current_buffer->w*(y[0]+i)+j )*4;
					current_buffer->pixels[q  ]=g_color.b;
					current_buffer->pixels[q+1]=g_color.g;
					current_buffer->pixels[q+2]=g_color.r;
					
					end:
					
					texCoord.e[0]+=reference.from.e[0];
					texCoord.e[1]+=reference.from.e[1];
				}
			}
			
			xp=x2;
			
			f_glxsI=0; getNextLineX(); x1=f_glxs_x[0];
			f_glxsI=1; getNextLineX(); x2=f_glxs_x[1];
			
			texCoord.e[0]+=reference.to.e[0];
			texCoord.e[1]+=reference.to.e[1];
		}
	}
	
	texCoord=vec2i_to_vec2f(U.vertex[ordered_indices[1]]);
	
	texCoord.e[0]+=(reference.from.e[0]+reference.to.e[0])*0.5f;
	texCoord.e[1]+=(reference.from.e[1]+reference.to.e[1])*0.5f;
	
	dy=y[2]-y[1];
	if(dy)
	{		
		{	
			int tmp_x,k,n;
			n=y[1]-y[0];

			f_glxsI=1;
			getLineXStart(vec2i(x[0],y[0]),vec2i(x[2],y[2]),x[0]);
			tmp_x=x[0];
			for(k=0; k<n; k++)
			{
				getNextLineX();
				tmp_x=f_glxs_x[1];
			}
			
			x2=tmp_x;
			
			f_glxsI=0;
			x1=x[1];
			getLineXStart(vec2i(x[1],y[1]),vec2i(x[2],y[2]),x1);	
		}
		
		if(x1>x2)
		{
			xp=x2;
			
			texCoord.e[0]+=reference.from.e[0]*(x2-x1);
			texCoord.e[1]+=reference.from.e[1]*(x2-x1);
		}
		else
		{
			xp=x1;
		}
		
		for(i=0; i<dy; i++)
		{
			if(x1>x2)
			{
				int tmp;
				tmp=x1;
				x1=x2;
				x2=tmp;
			}
			
			texCoord.e[0]+=reference.from.e[0]*(x1-xp);
			texCoord.e[1]+=reference.from.e[1]*(x1-xp);
			
			{
				int j,q,tx,ty;
				for(j=x1; j<x2; j++)
				{	
					tx=texCoord.e[0];
					ty=texCoord.e[1];
					
					if(tx<0 || tx>=tex.w || ty<0 || ty>=tex.h) goto end2;
					
					g_color.a=tex.pixels[(tex.w*ty+tx)*4+3];
					
					if(!g_color.a) goto end2;
					
					g_color.r=tex.pixels[(tex.w*ty+tx)*4  ];
					g_color.g=tex.pixels[(tex.w*ty+tx)*4+1];
					g_color.b=tex.pixels[(tex.w*ty+tx)*4+2];
					
					scaleColor(colorRecord[0]);
					
					q=( current_buffer->w*(y[1]+i)+j )*4;
					current_buffer->pixels[q  ]=g_color.b;
					current_buffer->pixels[q+1]=g_color.g;
					current_buffer->pixels[q+2]=g_color.r;
					
					end2:
					
					texCoord.e[0]+=reference.from.e[0];
					texCoord.e[1]+=reference.from.e[1];
				}
			}
			
			xp=x2;
			
			f_glxsI=0; getNextLineX(); x1=f_glxs_x[0];
			f_glxsI=1; getNextLineX(); x2=f_glxs_x[1];
			
			texCoord.e[0]+=reference.to.e[0];
			texCoord.e[1]+=reference.to.e[1];
		}
	}
	
	loadColor(0);
}

void drawTriangleList(vector_array2f *vaV,int n)/*safety parameter and function pointers will be implemented later on*/
{
	int i;
	for(i=0; i<n; i++)
	{
		triangle2i v;
		v.vertex[0]=roundv2f(vaV->v[i*3  ]);
		v.vertex[1]=roundv2f(vaV->v[i*3+1]);
		v.vertex[2]=roundv2f(vaV->v[i*3+2]);
		
		drawTriangle(v);
	}
	
}

void drawRectangleUnsafe(int x,int y,int w,int h)
{
	int i,j,u,v,x2,y2;
	x2=x+w;
	y2=y+h;
	for(j=y; j<y2; j++)
	{
		u=current_buffer->w*j;
		for(i=x; i<x2; i++)
			{
				v=(u+i)*4;
				current_buffer->pixels[v  ]=g_color.b;
				current_buffer->pixels[v+1]=g_color.g;
				current_buffer->pixels[v+2]=g_color.r;
			}
	}
}

void drawRectangleFrame(int x,int y,int w,int h)
{
	drawLineHorizontal	(x,x+w,y	);
	drawLineHorizontal	(x,x+w,y+h-1);
	drawLineVertical	(y,y+h,x	);
	drawLineVertical	(y,y+h,x+w-1);
}

void drawRectangleFramev(vector2i p,vector2i size)
{
	drawRectangleFrame(p.e[0],p.e[1],size.e[0],size.e[1]);
}

void drawRectangle(int x,int y,int w,int h)
{
	int i,j,x1,x2,y1,y2;
	
	x1=x;
	y1=y;
	x2=x+w;
	y2=y+h;
	
	if(x	< 0) x1=0;
	if(x+w	> current_buffer->w) x2=current_buffer->w;
	if(y	< 0) y1=0;
	if(y+h	> current_buffer->h) y2=current_buffer->h;
	
	for(i=x1; i<x2; i++)
		for(j=y1; j<y2; j++)
			drawPixel(i,j);
}

void drawRectanglev(vector2i p,vector2i size)
{
	drawRectangleUnsafe(p.e[0],p.e[1],size.e[0],size.e[1]);
}

void drawCircleFrame(vector2i p,int r)
{
	int perimeter=(int)(2*pi*r)+1;
	float slice=1.0f/r;
	
	{
		int i;
		for(i=0; i<perimeter-1; i++)
			drawLine(vec2i(p.e[0]+cos((i  )*slice)*r,p.e[1]+sin((i  )*slice)*r),
					 vec2i(p.e[0]+cos((i+1)*slice)*r,p.e[1]+sin((i+1)*slice)*r));

			drawLine(vec2i(p.e[0]+cos((i  )*slice)*r,p.e[1]+sin((i  )*slice)*r),
					 vec2i(p.e[0]+cos((0  )*slice)*r,p.e[1]+sin((0  )*slice)*r));
	}
}


void drawCircle(vector2i p,int r)
{
	int q,x,y;
	const float e=1.01;
	int perimeter=((int)(2*pi*r))*e+1,i,j;
	float slice=1.0f/r/e;
	
	if(p.e[0]+r<=0 || p.e[0]-r>=current_buffer->w) return;
	if(p.e[1]+r<=0 || p.e[1]-r>=current_buffer->h) return;
	
	if(
	(p.e[0]+r>0 && p.e[0]-r<0) ||
	(p.e[1]+r>0 && p.e[1]-r<0) ||
	(p.e[0]+r>current_buffer->w && p.e[0]-r<current_buffer->w) ||
	(p.e[1]+r>current_buffer->h && p.e[1]-r<current_buffer->h)
	)
	{
		for(j=0; j<r; j++)
			for(i=0; i<perimeter; i++)
			{
				x=p.e[0]+cos(slice*i)*(j+0.5);
				y=p.e[1]+sin(slice*i)*(j+0.5);
				
				if(x<0 || x>=current_buffer->w) continue;
				if(y<0 || y>=current_buffer->h) continue;
				
				q=(current_buffer->w*y+x);
				if(g_depth>depthBuffer[q]) continue;
				
				q=(current_buffer->w*y+x)*4;
				current_buffer->pixels[q  ]=g_color.b;
				current_buffer->pixels[q+1]=g_color.g;
				current_buffer->pixels[q+2]=g_color.r;
			}
	}
	else
	{
		for(j=0; j<r; j++)
			for(i=0; i<perimeter; i++)
			{
				x=p.e[0]+cos(slice*i)*(j+0.5);
				y=p.e[1]+sin(slice*i)*(j+0.5);
				
				q=(current_buffer->w*y+x);
				if(g_depth>depthBuffer[q]) continue;
				
				q=(current_buffer->w*y+x)*4;
				current_buffer->pixels[q  ]=g_color.b;
				current_buffer->pixels[q+1]=g_color.g;
				current_buffer->pixels[q+2]=g_color.r;
			}
	}
}


void drawCircle2(vector2i p,float r)
{
	int q,x,y,x1,x2;
	const float e=1.01;
	int perimeter=(((int)(2*pi*r))*e)/2+1,i;
	float slice=1.0f/r/e;
	
	{
		for(i=0; i<perimeter; i++)
		{
			x1=p.e[0]+cos(slice*( i)+pi/2)*r*0.99;
			x2=p.e[0]+cos(slice*(-i)+pi/2)*r*0.99;
			y =p.e[1]+sin(slice*( i)+pi/2)*r*0.99;
			
			if(y<0) continue;
			if(y>=current_buffer->h) continue;
			if(x1<0) x1=0;
			if(x2>current_buffer->w) x2=current_buffer->w;
			
			for(x=x1; x<x2; x++)
			{	
				q=(current_buffer->w*y+x)*4;
				current_buffer->pixels[q  ]=g_color.b;
				current_buffer->pixels[q+1]=g_color.g;
				current_buffer->pixels[q+2]=g_color.r;
			}
		}
	}
}

void drawCircleDB2(vector2i p,int r)
{
	int q,x,y,x1,x2;
	const float e=1.01;
	int perimeter=((int)(2*pi*r))*e+1,i;
	float slice=1.0f/r/e;
	
	if(p.e[0]+r<=0 || p.e[0]-r>=current_buffer->w) return;
	if(p.e[1]+r<=0 || p.e[1]-r>=current_buffer->h) return;
	
	if(
	(p.e[0]+r>0 && p.e[0]-r<0) ||
	(p.e[1]+r>0 && p.e[1]-r<0) ||
	(p.e[0]+r>current_buffer->w && p.e[0]-r<current_buffer->w) ||
	(p.e[1]+r>current_buffer->h && p.e[1]-r<current_buffer->h)
	)
	{
		for(i=0; i<perimeter; i++)
		{
			x1=p.e[0]+cos(slice*( i)+pi/2)*r;
			x2=p.e[0]+cos(slice*(-i)+pi/2)*r;
			y =p.e[1]+sin(slice*( i)+pi/2)*r;
			
			for(x=x1; x<x2; x++)
			{
				if(x<0 || x>=current_buffer->w) continue;
				if(y<0 || y>=current_buffer->h) continue;
				
				q=(current_buffer->w*y+x);
				if(g_depth<depthBuffer[q])
				depthBuffer[q]=g_depth;
			}
		}
	}
	else
	{
		for(i=0; i<perimeter; i++)
		{
			x1=p.e[0]+cos(slice*( i)+pi/2)*r;
			x2=p.e[0]+cos(slice*(-i)+pi/2)*r;
			y =p.e[1]+sin(slice*( i)+pi/2)*r;
			
			for(x=x1; x<x2; x++)
			{
				q=(current_buffer->w*y+x);
				if(g_depth<depthBuffer[q])
				depthBuffer[q]=g_depth;
			}
		}
	}
}

#define drawCircleB(p,r)	\
{							\
	drawCircleDB(p,r);		\
	drawCircle(p,r);		\
}

#define drawCircleB2(p,r)	\
{							\
	drawCircleDB2(p,r);		\
	drawCircle2(p,r);		\
}

void drawImage(Texture tex,int x,int y)
{
	int i,j,is=0,js=0,ie=tex.w,je=tex.h;
	
	saveColor(0);
	
	if(x<0) is=-x;
	if(y<0) js=-y;
	if(x+tex.w>current_buffer->w) ie=tex.w-((x+tex.w)-current_buffer->w);
	if(y+tex.h>current_buffer->h) je=tex.h-((y+tex.h)-current_buffer->h);
	
	for(j=js; j<je; j++)
		for(i=is; i<ie; i++)
		{
			getTexturePixelA(tex,i,j);
			drawPixelA(x+i,y+j);
		}
		
	loadColor(0);
}
void drawImageColored(Texture tex,int x,int y)
{
	int i,j,is=0,js=0,ie=tex.w,je=tex.h;
	
	saveColor(0);
	
	if(x<0) is=-x;
	if(y<0) js=-y;
	if(x+tex.w>current_buffer->w) ie=tex.w-((x+tex.w)-current_buffer->w);
	if(y+tex.h>current_buffer->h) je=tex.h-((y+tex.h)-current_buffer->h);
	
	for(j=js; j<je; j++)
		for(i=is; i<ie; i++)
		{
			getTexturePixelA(tex,i,j);
			scaleColor(colorRecord[0]);
			drawPixelA(x+i,y+j);
		}
	
	loadColor(0);
}
/*not optimized enough v*/
void drawImageScaled(Texture tex,int x,int y,int x_orig,int y_orig,int w,int h)
{
	int i,j;
	triangle2f T[2];
	triangle2i Ti[2],Ui[2];
	
	T[0].vertex[0].e[0]=0;
	T[0].vertex[0].e[1]=0;
	T[0].vertex[1].e[0]=w;
	T[0].vertex[1].e[1]=0;
	T[0].vertex[2].e[0]=w;
	T[0].vertex[2].e[1]=h;
	
	T[1].vertex[0].e[0]=w;
	T[1].vertex[0].e[1]=h;
	T[1].vertex[1].e[0]=0;
	T[1].vertex[1].e[1]=h;
	T[1].vertex[2].e[0]=0;
	T[1].vertex[2].e[1]=0;
	
	Ui[0].vertex[0].e[0]=0;
	Ui[0].vertex[0].e[1]=0;
	Ui[0].vertex[1].e[0]=tex.w;
	Ui[0].vertex[1].e[1]=0;
	Ui[0].vertex[2].e[0]=tex.w;
	Ui[0].vertex[2].e[1]=tex.h;
	
	Ui[1].vertex[0].e[0]=tex.w;
	Ui[1].vertex[0].e[1]=tex.h;
	Ui[1].vertex[1].e[0]=0;
	Ui[1].vertex[1].e[1]=tex.h;
	Ui[1].vertex[2].e[0]=0;
	Ui[1].vertex[2].e[1]=0;
	
	for(i=0; i<2; i++)
		for(j=0; j<3; j++)
		{
			
			T[i].vertex[j].e[0]-=x_orig;
			T[i].vertex[j].e[1]-=y_orig;
		
			T[i].vertex[j].e[0]+=x;
			T[i].vertex[j].e[1]+=y;
			
			Ti[i].vertex[j]=roundv2f(T[i].vertex[j]);
		}
	
	
	drawTriangleTextured(Ti[0],Ui[0],tex);
	drawTriangleTextured(Ti[1],Ui[1],tex);
}
void drawImageTransformed(Texture tex,int x,int y,int x_orig,int y_orig,int w,int h,float angle)
{
	int i,j;
	triangle2f T[2];
	triangle2i Ti[2],Ui[2];
	
	T[0].vertex[0].e[0]=0;
	T[0].vertex[0].e[1]=0;
	T[0].vertex[1].e[0]=w;
	T[0].vertex[1].e[1]=0;
	T[0].vertex[2].e[0]=w;
	T[0].vertex[2].e[1]=h;
	
	T[1].vertex[0].e[0]=w;
	T[1].vertex[0].e[1]=h;
	T[1].vertex[1].e[0]=0;
	T[1].vertex[1].e[1]=h;
	T[1].vertex[2].e[0]=0;
	T[1].vertex[2].e[1]=0;
	
	Ui[0].vertex[0].e[0]=0;
	Ui[0].vertex[0].e[1]=0;
	Ui[0].vertex[1].e[0]=tex.w;
	Ui[0].vertex[1].e[1]=0;
	Ui[0].vertex[2].e[0]=tex.w;
	Ui[0].vertex[2].e[1]=tex.h;
	
	Ui[1].vertex[0].e[0]=tex.w;
	Ui[1].vertex[0].e[1]=tex.h;
	Ui[1].vertex[1].e[0]=0;
	Ui[1].vertex[1].e[1]=tex.h;
	Ui[1].vertex[2].e[0]=0;
	Ui[1].vertex[2].e[1]=0;
	
	for(i=0; i<2; i++)
		for(j=0; j<3; j++)
		{
			
			T[i].vertex[j].e[0]-=x_orig;
			T[i].vertex[j].e[1]-=y_orig;
		 
			T[i].vertex[j]=rotatev2f(T[i].vertex[j],angle);
		
			T[i].vertex[j].e[0]+=x;
			T[i].vertex[j].e[1]+=y;
			
			Ti[i].vertex[j]=roundv2f(T[i].vertex[j]);
		}
	
	drawTriangleTextured(Ti[0],Ui[0],tex);
	drawTriangleTextured(Ti[1],Ui[1],tex);
}

void drawImagePart(Texture tex,int x,int y,int tx,int ty,int tw,int th)
{
	int i,j,is=0,js=0,ie=tw,je=th;
	
	if(x	<0) is=-x;
	if(y	<0) js=-y;
	if(x+tw	>current_buffer->w) ie=current_buffer->w-x;
	if(y+th	>current_buffer->h) je=current_buffer->h-y;
	
	for(j=js; j<je; j++)
		for(i=is; i<ie; i++)
		{
			getTexturePixelA(tex,tx+i,ty+j);
			drawPixelA(x+i,y+j);
		}
}

/*yet to be optimized*/
void drawImagePartScaled(Texture tex,int x,int y,int tx,int ty,int tw,int th,int x_orig,int y_orig,int w,int h)
{
	int i,j;
	triangle2f T[2];
	triangle2i Ti[2],Ui[2];
	
	T[0].vertex[0].e[0]=0;
	T[0].vertex[0].e[1]=0;
	T[0].vertex[1].e[0]=tw;
	T[0].vertex[1].e[1]=0;
	T[0].vertex[2].e[0]=tw;
	T[0].vertex[2].e[1]=th;
	
	T[1].vertex[0].e[0]=tw;
	T[1].vertex[0].e[1]=th;
	T[1].vertex[1].e[0]=0;
	T[1].vertex[1].e[1]=th;
	T[1].vertex[2].e[0]=0;
	T[1].vertex[2].e[1]=0;
	
	Ui[0].vertex[0].e[0]=0;
	Ui[0].vertex[0].e[1]=0;
	Ui[0].vertex[1].e[0]=tw;
	Ui[0].vertex[1].e[1]=0;
	Ui[0].vertex[2].e[0]=tw;
	Ui[0].vertex[2].e[1]=th;
	
	Ui[1].vertex[0].e[0]=tw;
	Ui[1].vertex[0].e[1]=th;
	Ui[1].vertex[1].e[0]=0;
	Ui[1].vertex[1].e[1]=th;
	Ui[1].vertex[2].e[0]=0;
	Ui[1].vertex[2].e[1]=0;
	
	for(i=0; i<2; i++)
		for(j=0; j<3; j++)
		{
			Ui[i].vertex[j].e[0]+=tx;
			Ui[i].vertex[j].e[1]+=ty;
			
			T[i].vertex[j].e[0]-=x_orig;
			T[i].vertex[j].e[1]-=y_orig;
			
			T[i].vertex[j].e[0]=T[i].vertex[j].e[0]/tw*w;
			T[i].vertex[j].e[1]=T[i].vertex[j].e[1]/th*h;
			
			T[i].vertex[j].e[0]+=x;
			T[i].vertex[j].e[1]+=y;
			
			Ti[i].vertex[j]=roundv2f(T[i].vertex[j]);
		}
	
	drawTriangleTextured(Ti[0],Ui[0],tex);
	drawTriangleTextured(Ti[1],Ui[1],tex);
}

void drawImagePartScaledColored(Texture tex,int x,int y,int tx,int ty,int tw,int th,int x_orig,int y_orig,int w,int h)
{
	int i,j;
	triangle2f T[2];
	triangle2i Ti[2],Ui[2];
	
	T[0].vertex[0].e[0]=0;
	T[0].vertex[0].e[1]=0;
	T[0].vertex[1].e[0]=tw;
	T[0].vertex[1].e[1]=0;
	T[0].vertex[2].e[0]=tw;
	T[0].vertex[2].e[1]=th;
	
	T[1].vertex[0].e[0]=tw;
	T[1].vertex[0].e[1]=th;
	T[1].vertex[1].e[0]=0;
	T[1].vertex[1].e[1]=th;
	T[1].vertex[2].e[0]=0;
	T[1].vertex[2].e[1]=0;
	
	Ui[0].vertex[0].e[0]=0;
	Ui[0].vertex[0].e[1]=0;
	Ui[0].vertex[1].e[0]=tw;
	Ui[0].vertex[1].e[1]=0;
	Ui[0].vertex[2].e[0]=tw;
	Ui[0].vertex[2].e[1]=th;
	
	Ui[1].vertex[0].e[0]=tw;
	Ui[1].vertex[0].e[1]=th;
	Ui[1].vertex[1].e[0]=0;
	Ui[1].vertex[1].e[1]=th;
	Ui[1].vertex[2].e[0]=0;
	Ui[1].vertex[2].e[1]=0;
	
	for(i=0; i<2; i++)
		for(j=0; j<3; j++)
		{
			Ui[i].vertex[j].e[0]+=tx;
			Ui[i].vertex[j].e[1]+=ty;
			
			T[i].vertex[j].e[0]-=x_orig;
			T[i].vertex[j].e[1]-=y_orig;
			
			T[i].vertex[j].e[0]=T[i].vertex[j].e[0]/tw*w;
			T[i].vertex[j].e[1]=T[i].vertex[j].e[1]/th*h;
			
			T[i].vertex[j].e[0]+=x;
			T[i].vertex[j].e[1]+=y;
			
			Ti[i].vertex[j]=roundv2f(T[i].vertex[j]);
		}
	
	
	drawTriangleTexturedColored(Ti[0],Ui[0],tex);
	drawTriangleTexturedColored(Ti[1],Ui[1],tex);
}

void drawImagePartTransformed(Texture tex,int x,int y,int tx,int ty,int tw,int th,int x_orig,int y_orig,int w,int h,float angle)
{
	int i,j;
	triangle2f T[2];
	triangle2i Ti[2],Ui[2];
	
	T[0].vertex[0].e[0]=0;
	T[0].vertex[0].e[1]=0;
	T[0].vertex[1].e[0]=tw;
	T[0].vertex[1].e[1]=0;
	T[0].vertex[2].e[0]=tw;
	T[0].vertex[2].e[1]=th;
	
	T[1].vertex[0].e[0]=tw;
	T[1].vertex[0].e[1]=th;
	T[1].vertex[1].e[0]=0;
	T[1].vertex[1].e[1]=th;
	T[1].vertex[2].e[0]=0;
	T[1].vertex[2].e[1]=0;
	
	Ui[0].vertex[0].e[0]=0;
	Ui[0].vertex[0].e[1]=0;
	Ui[0].vertex[1].e[0]=tw;
	Ui[0].vertex[1].e[1]=0;
	Ui[0].vertex[2].e[0]=tw;
	Ui[0].vertex[2].e[1]=th;
	
	Ui[1].vertex[0].e[0]=tw;
	Ui[1].vertex[0].e[1]=th;
	Ui[1].vertex[1].e[0]=0;
	Ui[1].vertex[1].e[1]=th;
	Ui[1].vertex[2].e[0]=0;
	Ui[1].vertex[2].e[1]=0;
	
	for(i=0; i<2; i++)
		for(j=0; j<3; j++)
		{
			Ui[i].vertex[j].e[0]+=tx;
			Ui[i].vertex[j].e[1]+=ty;
			
			T[i].vertex[j].e[0]-=x_orig;
			T[i].vertex[j].e[1]-=y_orig;
			
			T[i].vertex[j].e[0]=T[i].vertex[j].e[0]/tw*w;
			T[i].vertex[j].e[1]=T[i].vertex[j].e[1]/th*h;
			
			T[i].vertex[j]=rotatev2f(T[i].vertex[j],angle);
		
			T[i].vertex[j].e[0]+=x;
			T[i].vertex[j].e[1]+=y;
			
			Ti[i].vertex[j]=roundv2f(T[i].vertex[j]);
		}
	
	drawTriangleTextured(Ti[0],Ui[0],tex);
	drawTriangleTextured(Ti[1],Ui[1],tex);
}

void drawImagePartColored(Texture tex,int x,int y,int tx,int ty,int tw,int th)
{
	int i,j,is=0,js=0,ie=tw,je=th;
	
	saveColor(0);
		 
	if(x	<0) is=-x;
	if(y	<0) js=-y;
	if(x+tw	>current_buffer->w) ie=current_buffer->w-x;
	if(y+th	>current_buffer->h) je=current_buffer->h-y;

	for(j=js; j<je; j++)
		for(i=is; i<ie; i++)
		{
			getTexturePixelA(tex,tx+i,ty+j);
			scaleColor(colorRecord[0]);
			drawPixelA(x+i,y+j);
		}
	
	loadColor(0);
}
/*
void initDraw()
{
	fp[0]=&getNextLineX;
	fp[1]=&getNextLineX;
	fp[2]=&getNextLineX2;
}*/

typedef struct{

vector3f pos;
color col;

}voxel;

#define MAXIMUM_SORTED_INDICES 1000
int sorted_indices[MAXIMUM_SORTED_INDICES];


vector_array3f transformed_va={0,0,0};
int voxel_n;
void setTotalVoxelNumber(int n)
{
	voxel_n=n;
	addBufferva3f(&transformed_va,n);
	
	transformed_va.n=n;
}
void deleteVoxels()
{
	deleteva3f(&transformed_va);
}

float camera_dir=0,camera_dir2=0;
vector3f camera_pos={{0,0,0}};

float g_depth=0;
float *depthBuffer;
float max_depth;
int depthBufferN;
void setDepthBuffer(int w,int h,float depth)
{
	int i=0;
	max_depth=depth;
	depthBufferN=current_buffer->w*current_buffer->h;
	depthBuffer=malloc(depthBufferN*sizeof(float));
	for(i=0; i<depthBufferN; i++)
		depthBuffer[i]=max_depth;
}
void clearDepth()
{
	int i;
	for(i=0; i<depthBufferN; i++)
		depthBuffer[i]=max_depth;
}

void deleteDepthBuffer()
{
	free(depthBuffer);
}

float voxel_r=0.5f;
void drawVoxels(int w,int h,int d,vector3f* vertex_data,color *color_data,int n)
{
	uint32_t c,c2;
	
	int i;
	vector2i projection;
	float projection_r,project;

	vector3f translate;
	matrix4f transform=unitm4f;

	for(i=0; i<n; i++)
	{
		transformed_va.v[i]=vertex_data[i];
	}
	
	transform=m4fxm4f(transform,rotationY_m4f(camera_dir2));
	transform=m4fxm4f(transform,rotationZ_m4f(camera_dir));
	translate=negv3f(camera_pos);
	transform=m4fxm4f(transform,translation_m4f(translate));
	
	transformva3f_n(&transformed_va,transform,n);
	
	for(i=0; i<n; i++)
	{
		c2=0;/*color_data[i].b*/;
		c=c2;
		c=c<<8;
		c2=color_data[i].r;
		c=c|c2;
		c=c<<8;
		c2=color_data[i].g;
		c=c|c2;
		c=c<<8;
		c2=color_data[i].b;
		c=c|c2;
		
		if(vertex_data[i].e[0]<0) continue;
		
		project=d/transformed_va.v[i].e[0];
		projection.e[0]=transformed_va.v[i].e[1]*project+w/2;
		projection.e[1]=transformed_va.v[i].e[2]*project+h/2;
		
		projection_r=voxel_r*project;
		
		g_depth=transformed_va.v[i].e[0];
		
		/*drawCircle2(projection,projection_r);*/
		{
			vector2i p=projection;
			float r=projection_r;
			{
				
				float q2,q3;
				int q,x,y,x1,x2;
				const float e=1.01;
				int perimeter=(((int)(2*pi*r))*e)/2+1,j;
				float slice=1.0f/r/e;

				if(p.e[0]-r<=0 || p.e[0]+r>=current_buffer->w) continue;
				if(p.e[1]-r<=0 || p.e[1]+r>=current_buffer->h) continue;
				
				{
					r*=0.99;
					for(j=0; j<perimeter; j++)
					{
						q3=slice*( j)+pi/2;
						q2=cos(q3);
						x1=p.e[0]+q2*r;
						x2=p.e[0]-q2*r;
						y =p.e[1]+sin(q3)*r;
						
						for(x=x1; x<x2; x++)
						{	
							q=(current_buffer->w*y+x);
							if(g_depth<depthBuffer[q])
							{
								depthBuffer[q]=g_depth;
								q*=4;
								*((uint32_t*)(current_buffer->pixels+q))=c;							
							}
						}
					}
				}
			}
		
		}
	}
}

#endif
