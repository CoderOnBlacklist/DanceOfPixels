#ifndef ANIMATION_H
#define ANIMATION_H

typedef struct
{
	Texture tex;
	TextureHW texHW;
	int SW_or_HW;
}
Image;

Image createImageHW(TextureHW texHW)
{
	Image image;
	
	image.texHW=texHW;
	image.SW_or_HW=1;
	
	return image;
}

typedef struct
{
	Image image;
	int mode;
}
Sprite;

Sprite SpriteC(Image image,int mode)
{
	Sprite sprite;
	
	sprite.image=image;
	sprite.mode=mode;
	
	return sprite;
}

void SpriteD(Sprite *sprite)
{
	if(sprite->image.SW_or_HW==0)
	{
		if(sprite->image.tex.pixels)
		deleteTexturePixels(&sprite->image.tex);
	}
	else
	{
		if(sprite->image.tex.id)
		deleteTextureHW(&sprite->image.texHW);
	}
}

typedef struct
{
	int x1,y1,x2,y2;
}ImagePart;

typedef struct
{
	double x1,y1,x2,y2;
}ImagePartN;

ImagePart ImagePartC(int x1,int y1,int x2,int y2)
{
	ImagePart image_part;
	
	image_part.x1=x1;
	image_part.y1=y1;
	image_part.x2=x2;
	image_part.y2=y2;
	
	return image_part;
}

ImagePartN ImagePartNC(double x1,double y1,double x2,double y2)
{
	ImagePartN image_part;
	
	image_part.x1=x1;
	image_part.y1=y1;
	image_part.x2=x2;
	image_part.y2=y2;
	
	return image_part;
}

ImagePartN ImagePart_to_ImagePartN(ImagePart in,vector2i image_size)
{
	ImagePartN out;
	
	out.x1=in.x1/(double)image_size.e[0];
	out.y1=in.y1/(double)image_size.e[1];
	out.x2=in.x1/(double)image_size.e[0];
	out.y2=in.y1/(double)image_size.e[1];
	
	return out;
}

ImagePart ImagePartN_to_ImagePart(ImagePartN in,vector2i image_size)
{
	ImagePart out;
	
	out.x1=in.x1*image_size.e[0];
	out.y1=in.y1*image_size.e[1];
	out.x2=in.x1*image_size.e[0];
	out.y2=in.y1*image_size.e[1];
	
	return out;
}


typedef struct SpriteGrid SpriteGrid;
typedef struct SpriteGrid
{
	int x1,y1,x2,y2,i1,i2;
	int (*division_mode_x)(int i,int x1,int x2);
	int (*division_mode_y)(int i,int y1,int y2);
	int (*index_mode_x)(int i,int i1,int i2);
	int (*index_mode_y)(int i,int i1,int i2);
}SpriteGrid;

/*how to initialize a function pointer*/

/*bro tip : function pointers and c++ style OO code, future homework to myself*/

/*the possibility of adding a function pointer inside a function*/

/*warning : multiple uses of malloc for small variables*/

typedef struct{
	int step_size;	
}quantitative_divisonE;

int quantitative_division(int i,int x1,int x2,void* extra_parameters)
{
1	int result_x;
	
	result_x=x1+i*extra_parameters->step_size;
	
	return result_x;
}

typedef struct{
	int part_count;
}proportional_divisonE;

int proportional_division(int i,int x1,int x2,void* extra_parameters)
{
	int result_x,part_w;
	
	part_w=(x2-x1)/extra_parameters->part_count;
	result_x=x1+part_w*i;
	
	return result_x;
}

/*
ImagePartN (*getIndex)[2]();
*/

/*index mode enum*/



int linearly_changing_index(int i,int xstart,int xend,unsigned int step)
{
	int j,x,xn,delta,remainder;
	delta=xend-xstart;
	
	xn=abs(delta);
	remainder=((i*step)%xn);
	
	x=xstart+remainder*(xn/delta);
	
	return x;
}

int exponentially_changing_index(int i,int xstart,int xend,unsigned int step,int exponent)
{
	int j,x,delta,xn,remainder;
	delta=xend-xstart;
	
	xn=abs(delta);
	remainder=power(i*step,exponent)%xn;
	
	x=xstart+remainder*(xn/delta);
	
	return x;
}


/*
vector2i calculateSpriteIndex(SpriteGrid grid,sprite_index_mode_type mode,int index)
{
	vector2i result;
	
	switch(mode)
	{
		case latin:
		{
			int xn,yn;
			xn=(grid.x2-grid.x1)/grid.x;
			yn=(grid.y2-grid.y1)/grid.y;
			result.e[0]=i%xn;
			result.e[1]=i/xn;
		}
		break;
		case japanese:
		{
			
		}
		break;
	}
}*/


/*
ImagePartN calculateImagePart(SpriteGrid grid,vector2i size,int index)
{
	switch(index_mode)
	{
		case 0;
		switch(grid.division_mode)
		{
			case 0;
			{
				ImagePartN part;
				int xn,yn,xi,yi,w,h;
				w=(grid.x2-grid.x1);
				h=(grid.y2-grid.y1);
				xn=w/grid.x;
				yn=h/grid.y;
				xi=i%xn;
				yi=i/xn;
				part.x1=(x1+xi*grid.x)/(double)size.e[0];
				part.y1=(y1+yi*grid.y)/(double)size.e[1];
				part.x2=(x1+(xi+1)*grid.x)/(double)size.e[0];
				part.y2=(y1+(yi+1)*grid.y)/(double)size.e[1];
				
				return part;
			}
			break;
			
		}
		break;
	}
}
*/

/*void drawIndex(float x,float y,int index)
{
	
}*/

#endif