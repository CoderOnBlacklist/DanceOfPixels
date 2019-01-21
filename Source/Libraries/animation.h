/*
Copyright (C) <2018-2019> <Tankut Zeytinoğlu>
You can find the text of zlib license in the root folder.
*/

#ifndef ANIMATION_H
#define ANIMATION_H

/*Homework : seperate as HW and SW*/

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

typedef struct
{
	Texture tex;
	TextureHW texHW;
	int SW_or_HW;
}
Image;

vector2i getImageSize(Image image)
{
	vector2i size;
	
	if(image.SW_or_HW)
	{
		size.e[0]=image.tex.w;
		size.e[1]=image.tex.h;
	}
	else
	{
		size.e[0]=image.texHW.w;
		size.e[1]=image.texHW.h;
	}
	
	return size;
}

Image createImageHW(TextureHW texHW)
{
	Image image;
	
	image.texHW=texHW;
	image.SW_or_HW=1;
	
	return image;
}

void deleteImage(Image *image)
{	
	if(image->SW_or_HW==0)
	{
		if(image->tex.pixels)
		deleteTexturePixels(&(image->tex));
	}
	else
	{
		if(image->texHW.id)
		deleteTextureHW(&(image->texHW));
	}
}

typedef struct
{
	Image image;
	ImagePart image_part;
	vector2i frame_size;
	int index_offset;
}
Sprite;

Sprite SpriteC(Image image,ImagePart image_part,vector2i frame_size,int index_offset)
{
	Sprite sprite;
	
	sprite.image=image;
	sprite.image_part=image_part;
	sprite.frame_size=frame_size;
	sprite.index_offset=index_offset;

	return sprite;
}

void SpriteD(Sprite *sprite)
{
	deleteImage(&(sprite->image));
}



ImagePart calculateImagePart(Sprite sprite,int index)
{
	ImagePart part;
	int xn,yn,xi,yi,w,h;
	w=(sprite.image_part.x2-sprite.image_part.x1);
	h=(sprite.image_part.y2-sprite.image_part.y1);
	xn=((double)w)/sprite.frame_size.e[0];
	yn=((double)h)/sprite.frame_size.e[1];
	xi=(sprite.index_offset+index)%xn;
	yi=(sprite.index_offset+index)/xn;
	part.x1=(sprite.image_part.x1+(xi  )*sprite.frame_size.e[0]);
	part.y1=(sprite.image_part.y1+(yi  )*sprite.frame_size.e[1]);
	part.x2=(sprite.image_part.x1+(xi+1)*sprite.frame_size.e[0]);
	part.y2=(sprite.image_part.y1+(yi+1)*sprite.frame_size.e[1]);
	return part;
}

ImagePartN calculateImagePartN(Sprite sprite,int index)
{
	ImagePartN part;
	int xn,yn,xi,yi,w,h;
	vector2i image_size;
	image_size=getImageSize(sprite.image);
	w=(sprite.image_part.x2-sprite.image_part.x1);
	h=(sprite.image_part.y2-sprite.image_part.y1);
	xn=((double)w)/sprite.frame_size.e[0];
	yn=((double)h)/sprite.frame_size.e[1];
	xi=(sprite.index_offset+index)%xn;
	yi=(sprite.index_offset+index)/xn;
	part.x1=(sprite.image_part.x1+(xi  )*sprite.frame_size.e[0])/(double)image_size.e[0];
	part.y1=(sprite.image_part.y1+(yi  )*sprite.frame_size.e[1])/(double)image_size.e[1];
	part.x2=(sprite.image_part.x1+(xi+1)*sprite.frame_size.e[0])/(double)image_size.e[0];
	part.y2=(sprite.image_part.y1+(yi+1)*sprite.frame_size.e[1])/(double)image_size.e[1];
	return part;
}

void drawSpriteIndex(Sprite sprite,float x,float y,int index)/*invisible*/
{
	ImagePart image_part;
	
	image_part=calculateImagePart(sprite,index);
	
	if(sprite.image.SW_or_HW)
	drawImagePartHW/*(TextureHW tex,int x,int y,int tx,int ty,int tw,int th,int x_orig,int y_orig,int w,int h)
*/	(
		sprite.image.texHW,x,y,
		image_part.x1,
		image_part.y1,
		image_part.x2-image_part.x1,
		image_part.y2-image_part.y1
	);
	
}

#endif
