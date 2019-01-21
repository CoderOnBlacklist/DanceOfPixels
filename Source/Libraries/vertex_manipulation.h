/*
Copyright (C) <2018-2019> <Tankut Zeytinoğlu>
You can find the text of zlib license in the root folder.
*/

#ifndef VERTEX_MANIPULATION_H
#define VERTEX_MANIPULATION_H

#define SWmapToHWMap(v){\
v.e[0]=2*(v.e[0])/W-1;\
v.e[1]=1-2*(v.e[1])/H;\
}

#define HWmapToSWMap(v){\
v.e[0]=(v.e[0]+1)/2*W;\
v.e[1]=(1-v.e[1])/2*H;\
}

bool is_po_blank(char ch)
{
	return ch==' ' || ch=='\n' || ch=='\t';
}

bool is_po_float(char ch)
{
	return (ch>='0' && ch<='9') || ch=='-' || ch=='+' || ch=='.';
}


float verticesxd [30000];
float texcoordsxd[30000];
float normalsxd  [30000];

int vertex_n;
int texcoord_n;
int normal_n;

int vertex_is;
int texcoord_is;
int normal_is;

void model_stack()
{
	  vertex_is=0;
	texcoord_is=0;
	  normal_is=0;
	
	  vertex_n=0;
	texcoord_n=0;
	  normal_n=0;
}

float point_z;
#define setZ(z) {point_z=z;}
void addv2(vector2f v)
{
	SWmapToHWMap(v);
	vertex_is=3;
	verticesxd[(vertex_n)*3  ]=v.e[0];
	verticesxd[(vertex_n)*3+1]=v.e[1];
	verticesxd[(vertex_n)*3+2]=point_z;
	vertex_n++;
}

void addv3(vector3f v)
{
	vertex_is=3;
	verticesxd[(vertex_n)*3  ]=v.e[0];
	verticesxd[(vertex_n)*3+1]=v.e[1];
	verticesxd[(vertex_n)*3+2]=v.e[2];
	vertex_n++;
}

void addt2(vector2f t)
{
	texcoord_is=2;
	texcoordsxd[(texcoord_n)*2  ]=t.e[0];
	texcoordsxd[(texcoord_n)*2+1]=t.e[1];
	texcoord_n++;
}

void addt3(vector3f t)
{
	texcoord_is=3;
	texcoordsxd[(texcoord_n)*3  ]=t.e[0];
	texcoordsxd[(texcoord_n)*3+1]=t.e[1];
	texcoordsxd[(texcoord_n)*3+2]=t.e[2];
	texcoord_n++;
}

void addn2(vector2f n)
{
	normal_is=2;
	normalsxd[(normal_n)*2  ]=n.e[0];
	normalsxd[(normal_n)*2+1]=n.e[1];
	normal_n++;
}

void addn3(vector3f n)
{
	normal_is=3;
	normalsxd[(normal_n)*3  ]=n.e[0];
	normalsxd[(normal_n)*3+1]=n.e[1];
	normalsxd[(normal_n)*3+2]=n.e[2];
	normal_n++;
}

#define TRIANGLE_MODE GL_TRIANGLES
#define LINE_MODE GL_LINES

void load_stack(GLenum mode)
{
	
}

#endif
