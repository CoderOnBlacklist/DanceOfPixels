#ifndef PIXEL_MANIPULATION_HW
#define PIXEL_MANIPULATION_HW

typedef struct
{
	GLuint id;
	int w,h;
}
TextureHW;

#define NEAREST GL_NEAREST
#define LINEAR GL_LINEAR

GLint texFilter=LINEAR;
#define setTextureFiterHW(tex) {texFilter=tex;}

TextureHW loadTextureHW(char *file_path)
{
	TextureHW texHW;
	int w,h;
	Texture tex;
	tex.pixels=loadPixels(file_path,&w,&h);
	tex.w=w;
	tex.h=h;
	
	texHW.w=w;
	texHW.h=h;
	
	glPixelStorei(GL_UNPACK_ALIGNMENT,1);
	
	glGenTextures(1,&texHW.id);
	glBindTexture(GL_TEXTURE_2D,texHW.id);
	glTexImage2D(GL_TEXTURE_2D,0,GL_RGBA,w,h,0,GL_RGBA,GL_UNSIGNED_BYTE,tex.pixels);
	
	deleteTexturePixels(&tex);
	
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,texFilter);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,texFilter);
	
	return texHW;
}

void deleteTextureHW(TextureHW *tex)
{
	glDeleteTextures(1,&tex->id);
	tex->id=0;
}

void setColorHW(color c)
{
	g_color.r=c.r;
	g_color.g=c.g;
	g_color.b=c.b;
	g_color.a=255;
	
	glUniform4f(uniColor,c.r/255.0f,c.g/255.0f,c.b/255.0f,1);
}

void setColorAHW(colorA c)
{
	g_color=c;
	
	glUniform4f(uniColor,c.r/255.0f,c.g/255.0f,c.b/255.0f,c.a/255.0f);
}

void setColor2HW(u8 r,u8 g,u8 b)
{
	g_color.r=r;
	g_color.g=g;
	g_color.b=b;
	g_color.a=255;
	
	glUniform4f(uniColor,r/255.0f,g/255.0f,b/255.0f,1);
}

void setColorA2HW(u8 r,u8 g,u8 b,u8 a)
{
	g_color.r=r;
	g_color.g=g;
	g_color.b=b;
	g_color.a=a;
	
	glUniform4f(uniColor,r/255.0f,g/255.0f,b/255.0f,a/255.0f);
}

void invertColorHW()
{
	g_color.r=255-g_color.r;
	g_color.g=255-g_color.g;
	g_color.b=255-g_color.b;
	
	glUniform4f(uniColor,g_color.r/255.0f,g_color.g/255.0f,g_color.b/255.0f,g_color.a/255.0f);
}

void texturing(GLint state)
{
	glUniform1i(uniTexturing,state);
}

void clearHW()
{
	glClearColor(g_color.r/255.0f,g_color.g/255.0f,g_color.b/255.0f,1);
	glClear(GL_COLOR_BUFFER_BIT|GL_DEPTH_BUFFER_BIT);
}

void depthTest(bool t)
{
	if(t)
	glEnable(GL_DEPTH_TEST);
	else
	glDisable(GL_DEPTH_TEST);
}

int borderHW[4];
void drawingBorder(int x,int y,int w,int h)
{
	borderHW[0]=x;
	borderHW[1]=y;
	borderHW[2]=w;
	borderHW[3]=h;
	glUniform4i(uniBorder,x,H-(y+h),w,h);
}

void borderless()
{
	borderHW[0]=0;
	borderHW[1]=0;
	borderHW[2]=W;
	borderHW[3]=H;
	glUniform4i(uniBorder,0,0,W,H);
}

#endif