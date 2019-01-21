/*
Copyright (C) <2018-2019> <Tankut Zeytinoğlu>
You can find the text of zlib license in the root folder.
*/

#ifndef PIXEL_MANIPULATION_H
#define PIXEL_MANIPULATION_H

/*
Texture struct definition is in io_basic_libraries.h
*/

Texture loadTexture(char *file_path)
{
	int w,h;
	Texture tex;
	tex.pixels=loadPixels(file_path,&w,&h);
	tex.w=w;
	tex.h=h;
	return tex;
}

Texture createTexture(int w, int h)
{
	Texture tex;
	tex.pixels=malloc(w*h*4*sizeof(u8));
	tex.w=w;
	tex.h=h;
	return tex;
}

void deleteTexturePixels(Texture *Tex)
{
	free(Tex->pixels);
	Tex->pixels=0;
}


typedef struct
{
	u8 r,g,b;
}color;

typedef struct
{
	u8 r,g,b,a;
}colorA;

color col(u8 r,u8 g,u8 b)
{
	color temp;
	
	temp.r=r;
	temp.g=g;
	temp.b=b;
	
	return temp;
}

colorA colA(u8 r,u8 g,u8 b,u8 a)
{
	colorA temp;
	
	temp.r=r;
	temp.g=g;
	temp.b=b;
	temp.a=a;
	
	return temp;
}

color to_col(colorA c)
{
	color temp;
	
	temp.r=c.r;
	temp.g=c.g;
	temp.b=c.b;
	
	return temp;
}

colorA to_colA(color c)
{
	colorA temp;
	
	temp.r=c.r;
	temp.g=c.g;
	temp.b=c.b;
	temp.a=255;
	
	return temp;
}

colorA g_color;

u8 key_r,key_g,key_b;
void setColorKey(int r,int g,int b)
{
	key_r=r;
	key_g=g;
	key_b=b;
}

void getTexturePixel(Texture Tex,int x,int y)
{	
	if(x<0 || x>=Tex.w || y<0 || y>=Tex.h) return;
	
	g_color.r=Tex.pixels[(Tex.w*y+x)*4  ];
	g_color.g=Tex.pixels[(Tex.w*y+x)*4+1];
	g_color.b=Tex.pixels[(Tex.w*y+x)*4+2];
}
void getTexturePixelA(Texture Tex,int x,int y)
{
	if(x<0 || x>=Tex.w || y<0 || y>=Tex.h) return;
	
	g_color.r=Tex.pixels[(Tex.w*y+x)*4  ];
	g_color.g=Tex.pixels[(Tex.w*y+x)*4+1];
	g_color.b=Tex.pixels[(Tex.w*y+x)*4+2];
	g_color.a=Tex.pixels[(Tex.w*y+x)*4+3];
}

void getTexturePixel2(Texture Tex,int x,int y,color *c)
{
	if(x<0 || x>=Tex.w || y<0 || y>=Tex.h) return;
		
	c->r=Tex.pixels[(Tex.w*y+x)*4  ];
	c->g=Tex.pixels[(Tex.w*y+x)*4+1];
	c->b=Tex.pixels[(Tex.w*y+x)*4+2];
}

void getTexturePixelA2(Texture Tex,int x,int y,colorA *c)
{	
	if(x<0 || x>=Tex.w || y<0 || y>=Tex.h) return;
	
	c->r=Tex.pixels[(Tex.w*y+x)*4  ];
	c->g=Tex.pixels[(Tex.w*y+x)*4+1];
	c->b=Tex.pixels[(Tex.w*y+x)*4+2];
	c->a=Tex.pixels[(Tex.w*y+x)*4+3];
}

void setColor(color c)
{
	g_color.r=c.r;
	g_color.g=c.g;
	g_color.b=c.b;
	g_color.a=255;
}

void setColor2(u8 r,u8 g,u8 b)
{
	g_color.r=r;
	g_color.g=g;
	g_color.b=b;
	g_color.a=255;
}

void setColorA(colorA c)
{
	g_color.r=c.r;
	g_color.g=c.g;
	g_color.b=c.b;
	g_color.a=c.a;
}
void setColorA2(u8 r,u8 g,u8 b,u8 a)
{
	g_color.r=r;
	g_color.g=g;
	g_color.b=b;
	g_color.a=a;
}

void scaleColor(color c)
{
	float xs,ys,zs;
	xs=c.r/255.0f;
	ys=c.g/255.0f;
	zs=c.b/255.0f;
	g_color.r=g_color.r*xs;
	g_color.g=g_color.g*ys;
	g_color.b=g_color.b*zs;
}

void scaleColor2(u8 r,u8 g,u8 b)
{
	float xs,ys,zs;
	xs=r/255.0f;
	ys=g/255.0f;
	zs=b/255.0f;
	g_color.r=g_color.r*xs;
	g_color.g=g_color.g*ys;
	g_color.b=g_color.b*zs;
}

void invertColor()
{
	g_color.r=255-g_color.r;
	g_color.g=255-g_color.g;
	g_color.b=255-g_color.b;
}

#define MAX_NUMBER_OF_COLOR_RECORDS 10
color  colorRecord [MAX_NUMBER_OF_COLOR_RECORDS];
colorA colorRecordA[MAX_NUMBER_OF_COLOR_RECORDS];

#define saveColor(i) {\
	colorRecord[i].r=g_color.r;\
	colorRecord[i].g=g_color.g;\
	colorRecord[i].b=g_color.b;\
}
#define loadColor(i) {\
	g_color.r=colorRecord[i].r;\
	g_color.g=colorRecord[i].g;\
	g_color.b=colorRecord[i].b;\
}

#define saveColorA(i) {colorRecordA[i]=g_color;}
#define loadColorA(i) {g_color=colorRecordA[i];}

#define convertRecordToColA(i) {\
	colorRecordA[i].r=colorRecord[i].r;\
	colorRecordA[i].g=colorRecord[i].g;\
	colorRecordA[i].b=colorRecord[i].b;\
}

#define convertRecordToCol(i) {\
	colorRecord[i].r=colorRecordA[i].r;\
	colorRecord[i].g=colorRecordA[i].g;\
	colorRecord[i].b=colorRecordA[i].b;\
}

void drawPixel(int x,int y)/*unoptimized*/
{
	current_buffer->pixels[(current_buffer->w*y+x)*4  ]=g_color.b;
	current_buffer->pixels[(current_buffer->w*y+x)*4+1]=g_color.g;
	current_buffer->pixels[(current_buffer->w*y+x)*4+2]=g_color.r;
}
void drawPixelCK(int x,int y)
{
	if(g_color.r==key_r && g_color.g==key_g && g_color.b==key_b) return;
	current_buffer->pixels[(current_buffer->w*y+x)*4  ]=g_color.b;
	current_buffer->pixels[(current_buffer->w*y+x)*4+1]=g_color.g;
	current_buffer->pixels[(current_buffer->w*y+x)*4+2]=g_color.r;
}
void drawPixelA(int x,int y)
{
	if(!g_color.a) return;
	current_buffer->pixels[(current_buffer->w*y+x)*4  ]=g_color.b;
	current_buffer->pixels[(current_buffer->w*y+x)*4+1]=g_color.g;
	current_buffer->pixels[(current_buffer->w*y+x)*4+2]=g_color.r;
}
void drawPixel2(int x,int y,color c)
{
	current_buffer->pixels[(current_buffer->w*y+x)*4  ]=c.b;
	current_buffer->pixels[(current_buffer->w*y+x)*4+1]=c.g;
	current_buffer->pixels[(current_buffer->w*y+x)*4+2]=c.r;
}
void drawPixel2A(int x,int y,colorA c)
{
	if(!c.a) return;
	current_buffer->pixels[(current_buffer->w*y+x)*4  ]=c.b;
	current_buffer->pixels[(current_buffer->w*y+x)*4+1]=c.g;
	current_buffer->pixels[(current_buffer->w*y+x)*4+2]=c.r;
}
void drawPixelSafe(int x,int y)/*two seperate names will be assigned later on*/
{
	if(x<0 || y<0 || x>=W || y>=H) return;
	current_buffer->pixels[(current_buffer->w*y+x)*4  ]=g_color.b;
	current_buffer->pixels[(current_buffer->w*y+x)*4+1]=g_color.g;
	current_buffer->pixels[(current_buffer->w*y+x)*4+2]=g_color.r;
}
void drawPixel2Safe(int x,int y,color c)
{
	if(x<0 || y<0 || x>=W || y>=H) return;
	current_buffer->pixels[(current_buffer->w*y+x)*4  ]=c.b;
	current_buffer->pixels[(current_buffer->w*y+x)*4+1]=c.g;
	current_buffer->pixels[(current_buffer->w*y+x)*4+2]=c.r;
}
void fetchPixel(int x,int y)
{
	g_color.b=current_buffer->pixels[(current_buffer->w*y+x)*4  ];
	g_color.g=current_buffer->pixels[(current_buffer->w*y+x)*4+1];
	g_color.r=current_buffer->pixels[(current_buffer->w*y+x)*4+2];
}
void fetchPixel2(int x,int y,color *c)
{
	c->b=current_buffer->pixels[(current_buffer->w*y+x)*4  ];
	c->g=current_buffer->pixels[(current_buffer->w*y+x)*4+1];
	c->r=current_buffer->pixels[(current_buffer->w*y+x)*4+2];
}

void clear()
{
	int i;
	for(i=0; i<N; i++)
	{
		current_buffer->pixels[i*4  ]=g_color.b;
		current_buffer->pixels[i*4+1]=g_color.g;
		current_buffer->pixels[i*4+2]=g_color.r;
		current_buffer->pixels[i*4+3]=255;
	}
}

#endif
