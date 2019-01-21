/*
Copyright (C) <2018-2019> <Tankut Zeytinoğlu>
You can find the text of zlib license in the root folder.
*/

#ifndef	MATH_H
#define MATH_H

#include <math.h>

const float pi =3.14159265;
const float pi2=6.28318531;

#define clamp(a,x1,x2) {if(a<x1) a=x1; else if(a>x2) a=x2;}
#define clampf(a,x1,x2) {if(a<x1) a=x1+0.0001; else if(a>x2) a=x2-0.0001;}

float Rclampf(float a,float x1,float x2) 
{
	if(a<=x1)
		return (x1+0.0001);
	else if(a>=x2)
		return (x2-0.0001);
	else
		return a;
}

int close(float x,float y)
{
	const float epsilon=0.0001;
	
	return (x>(y-epsilon) && x<(y+epsilon));
}

int between(float x,float x1,float x2)
{
	return (x>x1) && (x<x2);
}

int betweenI(float x,float x1,float x2)
{
	const float epsilon=0.0001;
	
	return (x>x1-epsilon) && (x<x2+epsilon);
}

#define powersOf10fN 10
int powersOf10f[powersOf10fN];

void setPowersOf10fTable()
{
	powersOf10f[0]=1.0f;
	powersOf10f[1]=10.0f;
	powersOf10f[2]=100.0f;
	powersOf10f[3]=1000.0f;
	powersOf10f[4]=10000.0f;
	powersOf10f[5]=100000.0f;
	powersOf10f[6]=1000000.0f;
	powersOf10f[7]=10000000.0f;
	powersOf10f[8]=100000000.0f;
	powersOf10f[9]=1000000000.0f;
}

#define prime_numberN 1229
int prime_number[prime_numberN];

void setPrimeNumberTable()/*will be optimized*/
{
	int i,j,count=0;
	for(i=2; i<10000; i++)
	{
		int prime=1;
		for(j=2; j<i; j++)
		{
			if(i%j==0)
			prime=0;
		}
		if(!prime) continue;
		prime_number[count]=i;
		count++;
	}
}

int signf(float x);
int float_to_int(float x)
{
	int i,j,sgn,n,result=0;
	float i_f;
	sgn=signf(x);
	x*=sgn;

	if(close(x,1.0f)) return 1;
	if(betweenI(x,0.0f,1.0f)) return 0;

	for(i=1; i<=4; i++)
	{
		if(x<powersOf10f[i])
		break;
	}
	
	n=i;
	x/=powersOf10f[n-1];
	
	for(j=0; j<n; j++)
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

	return result/10*sgn;
}

int numOfDigits(int x)/*not optimized*/
{
	int i,add;
	add=!x;
	for(i=0; x>0; i++)
	{
		x/=10;
	}
	i+=add;
	return i;
}

int iroundf(float x)
{
	int sgn=1;
	sgn-=(x<0)*2;
	x*=sgn;
	return ((int)(x+0.5f))*sgn;
}

int ifloorf(float x)
{
	int sgn=1;
	sgn-=(x<0)*2;
	return ((int)(x*sgn+(1-sgn)/2))*sgn;
}

int sign(int x)
{
	return (x>0)-(x<0);
}

int signf(float x)
{
	return (x>0)-(x<0);
}


int abs(int x)
{
	x*=1-(x<0)*2;
	return x;
}

float absf(float x)
{
	x*=1.0f-(x<0.0f)*2.0f;
	return x;
}

int snap(float x,float grid_width,float within,float offset,int *result)
{
	int sgn_x=signf(x);
	float xp,i;
	
	xp=fmodf((x-offset)*sgn_x,grid_width);
	i=(x-offset)*sgn_x-xp;
	
	/*printf("error\n");*/
	
	if(xp>0.0f				&& xp<+within)
	{*result=iroundf(i*sgn_x+offset)			; return 1;}
	if(xp>grid_width-within && xp<grid_width)
	{*result=iroundf(i*sgn_x+grid_width+offset)	; return 1;}
	
	return 0;
}

#define g_epsilon 0.0001
/*int close(float )
{
	
}
*/
int maxn(int *x,int n)
{
	int i,max_index=0;
	for(i=1; i<n; i++)
		if(x[i]>x[i-1]) max_index=i;
	return x[max_index];
}

int min(x1,x2)
{
	return (x1<x2)?x1:x2;
}

int max(x1,x2)
{
	return (x1>x2)?x1:x2;
}

int power(int x,int y)
{
	int i,result=1;
	for(i=0; i<y; i++)
	{
		result*=x;
	}
	return result;
}
float powerf(float x,int y)
{
	int i;
	float result=1.0f;
	for(i=0; i<y; i++)
	{
		result*=x;
	}
	return result;
}


typedef struct
{
	int nominator,denominator;
}fraction;

fraction set_fraction(int nominator,int denominator)
{
	fraction result;
	
	result.nominator=nominator;
	result.denominator=denominator;
	
	return result;
}

fraction simplify(fraction x)
{
	int i;
	for(i=0; i<prime_numberN; i++)
	{
		if(prime_number[i]>x.denominator) break;
		while(x.nominator%prime_number[i]==0 && x.denominator%prime_number[i]==0)
		{
			x.nominator/=prime_number[i];
			x.denominator/=prime_number[i];
		}
	}
	
	return x;
}

float fraction_to_float(fraction x)
{
	return x.nominator/((float)(x.denominator));
}

#define decimal_precision 4

int numOfDigits(int x);
int signf(float x);
fraction float_to_fraction(float x)
{
	fraction result;
	int wholePart,decimalPart,sgn;
	
	sgn=signf(x);
	x*=sgn;
	wholePart=(int)x;
	decimalPart=(int)((x-wholePart)*power(10,decimal_precision));
	
	result.denominator=power(10,numOfDigits(decimalPart));
	result.nominator=decimalPart;
	
	result=simplify(result);
	
	result.nominator+=result.denominator*wholePart;
	result.nominator*=sgn;
	
	return result;
}

fraction addf(fraction x,fraction y)
{
	fraction result;
	
	x=simplify(x);
	y=simplify(y);
	
	result.nominator=x.nominator*y.denominator+x.denominator*y.nominator;
	result.denominator=x.denominator*y.denominator;
	
	result=simplify(result);
	
	return result;
}

fraction addfOpt(fraction x,fraction y)/*use as long as the denominators are same*/
{
	fraction result;
	
	result.nominator=x.nominator+y.nominator;
	
	return result;
}

fraction scalef(fraction x,int s)
{
	x=simplify(x);
	x.nominator*=s;
	x=simplify(x);
	
	return x;
}

fraction scalefOpt(fraction x,int y)/*use as long as the denominators are same*/
{
	fraction result;
	
	result.nominator=x.nominator*y;
	
	return result;
}
/*linear algebra*/

/**vector integer**/
typedef struct
{
	int e[2];
} vector2i;

vector2i vec2i(int x,int y)
{
	vector2i vec;
	vec.e[0]=x;
	vec.e[1]=y;
	return vec;
}

vector2i v2iX(vector2i v)
{
	return vec2i(v.e[0],0);
}
vector2i v2iY(vector2i v)
{
	return vec2i(0,v.e[1]);
}

vector2i subv2i(vector2i v1,vector2i v2)
{
	return 
	vec2i
	(
		v1.e[0]-v2.e[0],
		v1.e[1]-v2.e[1]
	);
}

vector2i addv2i(vector2i v1,vector2i v2)
{
	return 
	vec2i
	(
		v1.e[0]+v2.e[0],
		v1.e[1]+v2.e[1]
	);
}

vector2i negv2i(vector2i v)
{
	return	vec2i(-v.e[0],-v.e[1]);
}

vector2i scalev2i(vector2i v,int s)
{
	return	vec2i(s*v.e[0],s*v.e[1]);
}

typedef struct
{
	int e[3];
} vector3i;

vector3i vec3i(int x,int y,int z)
{
	vector3i vec;
	vec.e[0]=x;
	vec.e[1]=y;
	vec.e[2]=z;
	return vec;
}

vector3i v3iX(vector3i v)
{
	return vec3i(v.e[0],0,0);
}
vector3i v3iY(vector3i v)
{
	return vec3i(0,v.e[1],0);
}
vector3i v3iZ(vector3i v)
{
	return vec3i(0,0,v.e[2]);
}

vector3i subv3i(vector3i v1,vector3i v2)
{
	return 
	vec3i
	(
		v1.e[0]-v2.e[0],
		v1.e[1]-v2.e[1],
		v1.e[2]-v2.e[2]
	);
}

vector3i addv3i(vector3i v1,vector3i v2)
{
	return 
	vec3i
	(
		v1.e[0]+v2.e[0],
		v1.e[1]+v2.e[1],
		v1.e[2]+v2.e[2]
	);
}

vector3i negv3i(vector3i v)
{
	return	vec3i(-v.e[0],-v.e[1],-v.e[2]);
}

vector3i vec2i_to_vec3i(vector2i v)
{
	return vec3i(v.e[0],v.e[1],0);
}

vector2i vec3i_to_vec2i(vector3i v)
{
	return vec2i(v.e[0],v.e[1]);
}

vector3i crossi(vector3i v1,vector3i v2)
{
	return
	vec3i
	(
		v1.e[1]*v2.e[2]-v1.e[2]*v2.e[1],
		v1.e[2]*v2.e[0]-v1.e[0]*v2.e[2],
		v1.e[0]*v2.e[1]-v1.e[1]*v2.e[0]
	)
	;
}

/**vector float**/

typedef struct
{
	float e[2];
} vector2f;

vector2f vec2f(float x,float y)
{
	vector2f vec;
	vec.e[0]=x;
	vec.e[1]=y;
	return vec;
}

vector2f v2fX(vector2f v)
{
	return vec2f(v.e[0],0);
}
vector2f v2fY(vector2f v)
{
	return vec2f(0,v.e[1]);
}

float dotv2f(vector2f v1,vector2f v2)
{
	return v1.e[0]*v2.e[0] + v1.e[1]*v2.e[1];
}

vector2f direct_product2f(vector2f v1,vector2f v2)
{
	return vec2f(v1.e[0]*v2.e[0],v1.e[1]*v2.e[1]);
}

vector2f subv2f(vector2f v1,vector2f v2)
{
	return 
	vec2f
	(
		v1.e[0]-v2.e[0],
		v1.e[1]-v2.e[1]
	);
}

vector2f addv2f(vector2f v1,vector2f v2)
{
	return 
	vec2f
	(
		v1.e[0]+v2.e[0],
		v1.e[1]+v2.e[1]
	);
}
/*for now*/
void translatev2f(vector2f *v,vector2f delta)
{
	v->e[0]+=delta.e[0];
	v->e[1]+=delta.e[1];
}
void translatev2fOpt(vector2f *v,vector2f *delta)
{
	v->e[0]+=delta->e[0];
	v->e[1]+=delta->e[1];
}

vector2f negv2f(vector2f v)
{
	return	vec2f(-v.e[0],-v.e[1]);
}

vector2f scalev2f(vector2f v,float s)
{
	return	vec2f(s*v.e[0],s*v.e[1]);
}

/*for now*/

void scalev2fOpt(vector2f *v,float s)
{
	v->e[0]*=s;
	v->e[1]*=s;
}

float lengthv2f(vector2f v)
{
	return sqrt(v.e[0]*v.e[0]+v.e[1]*v.e[1]);
}

vector2f normalizev2f(vector2f v)
{
	return scalev2f(v,1/lengthv2f(v));
}

vector2f rotatev2f(vector2f v,float a)
{
	return
	vec2f
	(
		v.e[0]*cos(a)-v.e[1]*sin(a),
		v.e[0]*sin(a)+v.e[1]*cos(a)
	);
}

vector2i roundv2f(vector2f v)
{
	vector2i result;
	result.e[0]=iroundf(v.e[0]);
	result.e[1]=iroundf(v.e[1]);
	return result;
}

typedef struct
{
	float e[3];
} vector3f;

vector3f vec3f(float x,float y,float z)
{
	vector3f vec;
	vec.e[0]=x;
	vec.e[1]=y;
	vec.e[2]=z;
	return vec;
}

vector3f v3fX(vector3f v)
{
	return vec3f(v.e[0],0,0);
}
vector3f v3fY(vector3f v)
{
	return vec3f(0,v.e[1],0);
}
vector3f v3fZ(vector3f v)
{
	return vec3f(0,0,v.e[2]);
}

float dotv3f(vector3f v1,vector3f v2)
{
	return v1.e[0]*v2.e[0] + v1.e[1]*v2.e[1] + v1.e[2]*v2.e[2];
}

vector3f direct_product3f(vector3f v1,vector3f v2)
{
	return vec3f(v1.e[0]*v2.e[0],v1.e[1]*v2.e[1],v1.e[2]*v2.e[2]);
}

vector3f subv3f(vector3f v1,vector3f v2)
{
	return 
	vec3f
	(
		v1.e[0]-v2.e[0],
		v1.e[1]-v2.e[1],
		v1.e[2]-v2.e[2]
	);
}

vector3f addv3f(vector3f v1,vector3f v2)
{
	return 
	vec3f
	(
		v1.e[0]+v2.e[0],
		v1.e[1]+v2.e[1],
		v1.e[2]+v2.e[2]
	);
}
/*
void translatev3f(vector3f *v,vector3f delta)
{
	v->e[0]+=delta.e[0];
	v->e[1]+=delta.e[1];
	v->e[2]+=delta.e[2];
}
*/
vector3f negv3f(vector3f v)
{
	return	vec3f(-v.e[0],-v.e[1],-v.e[2]);
}

vector3f scalev3f(vector3f v,float s)
{
	return vec3f(s*v.e[0],s*v.e[1],s*v.e[2]);
}

float lengthv3f(vector3f v)
{
	return sqrt(v.e[0]*v.e[0]+v.e[1]*v.e[1]+v.e[2]*v.e[2]);
}

vector3f normalizev3f(vector3f v)
{
	return scalev3f(v,1/lengthv3f(v));
}

vector3f rotateZv3f(vector3f v,float a)
{
	return
	vec3f
	(
		v.e[0]*cos(a)-v.e[1]*sin(a),
		v.e[0]*sin(a)+v.e[1]*cos(a),
		v.e[2]
	);
}

vector3f rotateYv3f(vector3f v,float a)
{
	return
	vec3f
	(
		v.e[0]*cos(a)-v.e[2]*sin(a),
		v.e[1],
		v.e[0]*sin(a)+v.e[2]*cos(a)
	);
}

vector3f rotateXv3f(vector3f v,float a)
{
	return
	vec3f
	(
		v.e[0],
		v.e[1]*cos(a)-v.e[2]*sin(a),
		v.e[1]*sin(a)+v.e[2]*cos(a)
	);
}

vector3i roundv3f(vector3f v)
{
	vector3i result;
	result.e[0]=roundf(v.e[0]);
	result.e[1]=roundf(v.e[1]);
	result.e[2]=roundf(v.e[2]);
	return result;
}

typedef struct
{
	float e[4];
} vector4f;

vector4f vec4f(float x,float y,float z,float w)
{
	vector4f vec;
	vec.e[0]=x;
	vec.e[1]=y;
	vec.e[2]=z;
	vec.e[3]=w;
	return vec;
}

vector4f v4fX(vector4f v)
{
	return vec4f(v.e[0],0,0,0);
}
vector4f v4fY(vector4f v)
{
	return vec4f(0,v.e[1],0,0);
}
vector4f v4fZ(vector4f v)
{
	return vec4f(0,0,v.e[2],0);
}
vector4f v4fW(vector4f v)
{
	return vec4f(0,0,0,v.e[2]);
}

float dotv4f(vector4f v1,vector4f v2)
{
	return v1.e[0]*v2.e[0] + v1.e[1]*v2.e[1] + v1.e[2]*v2.e[2] + v1.e[3]*v2.e[3];
}

vector4f direct_product4f(vector4f v1,vector4f v2)
{
	return vec4f(v1.e[0]*v2.e[0],v1.e[1]*v2.e[1],v1.e[2]*v2.e[2],v1.e[3]*v2.e[3]);
}

vector4f subv4f(vector4f v1,vector4f v2)
{
	return 
	vec4f
	(
		v1.e[0]-v2.e[0],
		v1.e[1]-v2.e[1],
		v1.e[2]-v2.e[2],
		v1.e[3]-v2.e[3]
	);
}

vector4f addv4f(vector4f v1,vector4f v2)
{
	return 
	vec4f
	(
		v1.e[0]+v2.e[0],
		v1.e[1]+v2.e[1],
		v1.e[2]+v2.e[2],
		v1.e[3]+v2.e[3]
	);
}

vector4f negv4f(vector3f v)
{
	return	vec4f(-v.e[0],-v.e[1],-v.e[2],-v.e[3]);
}

vector4f scalev4f(vector4f v,float s)
{
	return vec4f(s*v.e[0],s*v.e[1],s*v.e[2],s*v.e[3]);
}

float lengthv4f(vector4f v)
{
	return sqrt(v.e[0]*v.e[0]+v.e[1]*v.e[1]+v.e[2]*v.e[2]+v.e[3]*v.e[3]);
}

vector4f normalizev4f(vector4f v)
{
	return scalev4f(v,1/lengthv4f(v));
}

vector4f rotatev4fZ(vector4f v,float a)
{
	return
	vec4f
	(
		v.e[0]*cos(a)-v.e[1]*sin(a),
		v.e[0]*sin(a)+v.e[1]*cos(a),
		v.e[2],
		v.e[3]
	);
}

vector4f rotatev4fY(vector4f v,float a)
{
	return
	vec4f
	(
		v.e[0]*cos(a)-v.e[2]*sin(a),
		v.e[1],
		v.e[0]*sin(a)+v.e[2]*cos(a),
		v.e[3]
	);
}

vector4f rotatev4fX(vector4f v,float a)
{
	return
	vec4f
	(
		v.e[0],
		v.e[1]*cos(a)-v.e[2]*sin(a),
		v.e[1]*sin(a)+v.e[2]*cos(a),
		v.e[3]
	);
}

vector2i vec2f_to_vec2i(vector2f v)
{
	return vec2i(v.e[0],v.e[1]);
}
vector2f vec2i_to_vec2f(vector2i v)
{
	return vec2f(v.e[0],v.e[1]);
}

vector3i vec3f_to_vec3i(vector3f v)
{
	return vec3i(v.e[0],v.e[1],v.e[2]);
}
vector3f vec3i_to_vec3f(vector3i v)
{
	return vec3f(v.e[0],v.e[1],v.e[2]);
}

vector3f vec2f_to_vec3f(vector2f v)
{
	return vec3f(v.e[0],v.e[1],0);
}

vector2f vec3f_to_vec2f(vector3f v)
{
	return vec2f(v.e[0],v.e[1]);
}

vector4f vec2f_to_vec4f(vector2f v)
{
	return vec4f(v.e[0],v.e[1],0,0);
}

vector2f vec4f_to_vec2f(vector4f v)
{
	return vec2f(v.e[0],v.e[1]);
}

vector4f vec3f_to_vec4f(vector3f v)
{
	return vec4f(v.e[0],v.e[1],v.e[2],1);
}

vector3f vec4f_to_vec3f(vector4f v)
{
	return vec3f(v.e[0],v.e[1],v.e[2]);
}

vector3f crossf(vector3f v1,vector3f v2)
{
	return
	vec3f
	(
		v1.e[1]*v2.e[2]-v1.e[2]*v2.e[1],
		v1.e[2]*v2.e[0]-v1.e[0]*v2.e[2],
		v1.e[0]*v2.e[1]-v1.e[1]*v2.e[0]
	)
	;
}

/*arrows*/

typedef struct{
	vector2i from,to;
} arrow2i;

arrow2i arr2iv(vector2i v1,vector2i v2)
{
	arrow2i arr;
	arr.from=v1;
	arr.to	=v2;
	return arr;
}
arrow2i arr2i(int x1,int y1,int x2,int y2)
{
	arrow2i arr;
	arr.from=vec2i(x1,y1);
	arr.to	=vec2i(x2,y2);
	return arr;
}

vector2i delta2i(arrow2i arr)
{
	return subv2i(arr.to,arr.from);
}

arrow2i arr2ishift(arrow2i arr,vector2i delta)
{
	return arr2iv(addv2i(arr.from,delta),addv2i(arr.to,delta));
}

/*****************************/
typedef struct{
	vector2f from,to;
} arrow2f;

arrow2f arr2fv(vector2f v1,vector2f v2)
{
	arrow2f arr;
	arr.from=v1;
	arr.to	=v2;
	return arr;
}
arrow2f arr2f(float x1,float y1,float x2,float y2)
{
	arrow2f arr;
	arr.from=vec2f(x1,y1);
	arr.to	=vec2f(x2,y2);
	return arr;
}

vector2f delta2f(arrow2f arr)
{
	return subv2f(arr.to,arr.from);
}

arrow2f arr2fshift(arrow2f arr,vector2f delta)
{
	return arr2fv(addv2f(arr.from,delta),addv2f(arr.to,delta));
}

arrow2i arr2f_to_arr2i(arrow2f arr)
{
	return arr2iv(vec2f_to_vec2i(arr.from),vec2f_to_vec2i(arr.to));
}
arrow2f arr2i_to_arr2f(arrow2i arr)
{
	return arr2fv(vec2i_to_vec2f(arr.from),vec2i_to_vec2f(arr.to));
}

/***/
typedef struct{
	vector3f from,to;
} arrow3f;

arrow3f arr3fv(vector3f v1,vector3f v2)
{
	arrow3f arr;
	arr.from=v1;
	arr.to	=v2;
	return arr;
}
arrow3f arr3f(float x1,float y1,float z1,float x2,float y2,float z2)
{
	arrow3f arr;
	arr.from=vec3f(x1,y1,z1);
	arr.to	=vec3f(x2,y2,z2);
	return arr;
}

vector3f delta3f(arrow3f arr)
{
	return subv3f(arr.to,arr.from);
}

arrow3f arr3fshift(arrow3f arr,vector3f delta)
{
	return arr3fv(addv3f(arr.from,delta),addv3f(arr.to,delta));
}

arrow2f arr3f_to_arr2f(arrow3f arr)
{
	return arr2fv(vec3f_to_vec2f(arr.from),vec3f_to_vec2f(arr.to));
}
arrow3f arr2f_to_arr3f(arrow2f arr)
{
	return arr3fv(vec2f_to_vec3f(arr.from),vec2f_to_vec3f(arr.to));
}
/***/

typedef struct{
	vector2i vertex[3];
} triangle2i;

triangle2i tri2iv(vector2i v1,vector2i v2,vector2i v3)
{
	triangle2i tri;
	tri.vertex[0]=v1;
	tri.vertex[1]=v2;
	tri.vertex[2]=v3;
	return tri;
}

triangle2i tri2i(int x1,int y1,int x2,int y2,int x3,int y3)
{
	triangle2i tri;
	tri.vertex[0]=vec2i(x1,y1);
	tri.vertex[1]=vec2i(x2,y2);
	tri.vertex[2]=vec2i(x3,y3);
	return tri;
}

typedef struct{
	vector2f vertex[3];
} triangle2f;

triangle2f tri2fv(vector2f v1,vector2f v2,vector2f v3)
{
	triangle2f tri;
	tri.vertex[0]=v1;
	tri.vertex[1]=v2;
	tri.vertex[2]=v3;
	return tri;
}

triangle2f tri2f(float x1,float y1,float x2,float y2,float x3,float y3)
{
	triangle2f tri;
	tri.vertex[0]=vec2f(x1,y1);
	tri.vertex[1]=vec2f(x2,y2);
	tri.vertex[2]=vec2f(x3,y3);
	return tri;
}

triangle2i tri2f_to_tri2i(triangle2f T)
{
	triangle2i TR;
	TR.vertex[0]=vec2f_to_vec2i(T.vertex[0]);
	TR.vertex[1]=vec2f_to_vec2i(T.vertex[1]);
	TR.vertex[2]=vec2f_to_vec2i(T.vertex[2]);
	return TR;
}

triangle2f tri2i_to_tri2f(triangle2i T)
{
	triangle2f TR;
	TR.vertex[0]=vec2i_to_vec2f(T.vertex[0]);
	TR.vertex[1]=vec2i_to_vec2f(T.vertex[1]);
	TR.vertex[2]=vec2i_to_vec2f(T.vertex[2]);
	return TR;
}
/**number array**/
/***int***/

typedef struct{
	int *v;
	int n,buffer_n;
} number_arrayi;

int lastni(number_arrayi *number_array)
{
	return number_array->v[number_array->n-1];
}

number_arrayi emptynai()
{
	number_arrayi result;
	result.v=0;
	result.n=0;
	result.buffer_n=0;
	return result;
}

int in_number_array(number_arrayi *number_array,int x)
{
	int i;
	for(i=0; i<number_array->n; i++)
		if(number_array->v[i]==x)
			{return 1;}

	return 0;
}

void deletenai(number_arrayi *number_array)
{
	  if(number_array->n)
	free(number_array->v);
	
	number_array->v=0;
	number_array->n=0;
	number_array->buffer_n=0;
}

void pushnai(number_arrayi *number_array,int v)
{	
	if((number_array->buffer_n)>(number_array->n))
		number_array->v[number_array->n++]=v;
	else
	{
		int i;
		int *vnew;
		
		vnew=malloc((number_array->n+1)*sizeof(int));
		
		for(i=0; i<number_array->n; i++)
			vnew[i]=number_array->v[i];
		
		vnew[i]=v;
		
		if	(number_array->n)
		free(number_array->v);
			 number_array->v=vnew;
			 number_array->n++;
			 number_array->buffer_n++;
	}
}

void pushnaiLargerExpansion(number_arrayi *number_array,int v,int add_buffer_n)
{	
	if((number_array->buffer_n)>(number_array->n))
		number_array->v[number_array->n++]=v;
	else
	{
		int i;
		int *vnew;
		
		vnew=malloc((number_array->n+add_buffer_n)*sizeof(int));
		
		for(i=0; i<number_array->n; i++)
			vnew[i]=number_array->v[i];
		
		vnew[i]=v;
		
		if	(number_array->n)
		free(number_array->v);
			 number_array->v=vnew;
			 number_array->n++;
			 number_array->buffer_n+=add_buffer_n;
	}
}

void addBuffernai(number_arrayi *number_array,int extra_buffer)
{
	int i;
	int *vnew;
		
	vnew=malloc((number_array->n+extra_buffer)*sizeof(int));
		
	for(i=0; i<number_array->n; i++)
		vnew[i]=number_array->v[i];
		
	if(number_array->n)
	free(number_array->v);
		
		 number_array->v=vnew;
		 number_array->buffer_n+=extra_buffer;
}

int popnai(number_arrayi *number_array,int deletion_threshold)
{
	if(!number_array->n)	return 0;
	
	number_array->n--;
	if((number_array->buffer_n)>=(number_array->n+deletion_threshold))
	{
		int i;
		int *vnew;
		
		vnew=malloc((number_array->n)*sizeof(int));
		
		for(i=0; i<number_array->n; i++)
			vnew[i]=number_array->v[i];
		
		free(number_array->v);
		
		number_array->v=vnew;
		number_array->buffer_n=number_array->n;
	}	
	
	return 1;
}

int deletefromnai(number_arrayi *number_array,int x,int deletion_threshold)/*new*//*other versions will be created*/
{
	int i;
	
	if(!number_array->n)	return 0;
	
	number_array->n--;
	if((number_array->buffer_n)>=(number_array->n+deletion_threshold))
	{
		int *vnew;
		
		vnew=malloc((number_array->n)*sizeof(int));
		
		for(i=0; i<x; i++)
			vnew[i]=number_array->v[i];
			
		for(i=x; i<number_array->n; i++)
			vnew[i]=number_array->v[i+1];
		
		free(number_array->v);
		
		number_array->v=vnew;
		number_array->buffer_n=number_array->n;
		
		return 1;
	}	
	
	for(i=x; i<number_array->n; i++)
		number_array->v[i]=number_array->v[i+1];
}

number_arrayi icopynai(number_arrayi *number_array)
{
	int i;
	number_arrayi new_number_array;
	
	new_number_array.v=malloc((number_array->n)*sizeof(int));
		
	for(i=0; i<number_array->n; i++)
		new_number_array.v[i]=number_array->v[i];
		
	new_number_array.n=new_number_array.buffer_n=number_array->n;
	
	return new_number_array;
}

/**vector array**/

/***int***/

typedef struct{
	vector2i *v;
	int n,buffer_n;
} vector_array2i;

vector2i lastv2i(vector_array2i *vector_array)
{
	return vector_array->v[vector_array->n-1];
}

vector_array2i emptyva2i()
{
	vector_array2i result;
	result.v=0;
	result.n=0;
	result.buffer_n=0;
	return result;
}

void deleteva2i(vector_array2i *vector_array)
{
	  if(vector_array->n)
	free(vector_array->v);
	
	vector_array->v=0;
	vector_array->n=0;
	vector_array->buffer_n=0;
}

void pushva2i(vector_array2i *vector_array,vector2i v)
{	
	if((vector_array->buffer_n)>(vector_array->n))
		vector_array->v[vector_array->n++]=v;
	else
	{
		int i;
		vector2i *vnew;
		
		vnew=malloc((vector_array->n+1)*sizeof(vector2f));
		
		for(i=0; i<vector_array->n; i++)
			vnew[i]=vector_array->v[i];
		
		vnew[i]=v;
		
		if	(vector_array->n)
		free(vector_array->v);
			 vector_array->v=vnew;
			 vector_array->n++;
			 vector_array->buffer_n++;
	}
}

void pushva2iLargerExpansion(vector_array2i *vector_array,vector2i v,int add_buffer_n)
{	
	if((vector_array->buffer_n)>(vector_array->n))
		vector_array->v[vector_array->n++]=v;
	else
	{
		int i;
		vector2i *vnew;
		
		vnew=malloc((vector_array->n+add_buffer_n)*sizeof(vector2f));
		
		for(i=0; i<vector_array->n; i++)
			vnew[i]=vector_array->v[i];
		
		vnew[i]=v;
		
		if	(vector_array->n)
		free(vector_array->v);
			 vector_array->v=vnew;
			 vector_array->n++;
			 vector_array->buffer_n+=add_buffer_n;
	}
}

void addBufferva2i(vector_array2i *vector_array,int extra_buffer)
{
	int i;
	vector2i *vnew;
		
	vnew=malloc((vector_array->n+extra_buffer)*sizeof(vector2i));
		
	for(i=0; i<vector_array->n; i++)
		vnew[i]=vector_array->v[i];
		
	if(vector_array->n)
	free(vector_array->v);
		
		 vector_array->v=vnew;
		 vector_array->buffer_n+=extra_buffer;
}

int popva2i(vector_array2i *vector_array,int deletion_threshold)
{
	if(!vector_array->n)	return 0;
	
	vector_array->n--;
	if((vector_array->buffer_n)>=(vector_array->n+deletion_threshold))
	{
		int i;
		vector2i *vnew;
		
		vnew=malloc((vector_array->n)*sizeof(vector2i));
		
		for(i=0; i<vector_array->n; i++)
			vnew[i]=vector_array->v[i];
		
		free(vector_array->v);
		
		vector_array->v=vnew;
		vector_array->buffer_n=vector_array->n;
	}	
	
	return 1;
}

int deletefromva2i(vector_array2i *vector_array,int x,int deletion_threshold)/*new*//*other versions will be created*/
{
	int i;
	
	if(!vector_array->n)	return 0;
	
	vector_array->n--;
	if((vector_array->buffer_n)>=(vector_array->n+deletion_threshold))
	{
		vector2i *vnew;
		
		vnew=malloc((vector_array->n)*sizeof(vector2i));
		
		for(i=0; i<x; i++)
			vnew[i]=vector_array->v[i];
			
		for(i=x; i<vector_array->n; i++)
			vnew[i]=vector_array->v[i+1];
		
		free(vector_array->v);
		
		vector_array->v=vnew;
		vector_array->buffer_n=vector_array->n;
		
		return 1;
	}	
	
	for(i=x; i<vector_array->n; i++)
		vector_array->v[i]=vector_array->v[i+1];
}

vector_array2i icopyva2i(vector_array2i *vector_array)
{
	int i;
	vector_array2i new_vector_array;
	
	new_vector_array.v=malloc((vector_array->n)*sizeof(vector2i));
		
	for(i=0; i<vector_array->n; i++)
		new_vector_array.v[i]=vector_array->v[i];
		
	new_vector_array.n=new_vector_array.buffer_n=vector_array->n;
	
	return new_vector_array;
}

void translateva2i(vector_array2i *vector_array,vector2i v)
{
	int i;
	for(i=0; i<vector_array->n; i++)
		vector_array->v[i]=addv2i(vector_array->v[i],v);
}

/***float***/

/*vector array start*/

typedef struct{
	vector2f *v;
	int n,buffer_n;
} vector_array2f;

vector2f lastv2f(vector_array2f *vector_array)
{
	return vector_array->v[vector_array->n-1];
}

vector_array2f emptyva2f()
{
	vector_array2f result;
	result.v=0;
	result.n=0;
	result.buffer_n=0;
	return result;
}

void deleteva2f(vector_array2f *vector_array)
{
	  if(vector_array->n)
	free(vector_array->v);
	
	vector_array->v=0;
	vector_array->n=0;
	vector_array->buffer_n=0;
}

void pushva2f(vector_array2f *vector_array,vector2f v)
{
	if((vector_array->buffer_n)>(vector_array->n))
		vector_array->v[vector_array->n++]=v;
	else
	{
		int i;
		vector2f *vnew;
		
		vnew=malloc((vector_array->n+1)*sizeof(vector2f));
		
		for(i=0; i<vector_array->n; i++)
			vnew[i]=vector_array->v[i];
		
		vnew[i]=v;
		
		if	(vector_array->n)
		free(vector_array->v);
			 vector_array->v=vnew;
			 vector_array->n++;
			 vector_array->buffer_n++;
	}
}

void addBufferva2f(vector_array2f *vector_array,int extra_buffer)
{
	int i;
	vector2f *vnew;
		
	vnew=malloc((vector_array->n+extra_buffer)*sizeof(vector2f));
		
	for(i=0; i<vector_array->n; i++)
		vnew[i]=vector_array->v[i];
		
	if(vector_array->n)
	free(vector_array->v);
		
		 vector_array->v=vnew;
		 vector_array->buffer_n+=extra_buffer;
}

int popva2f(vector_array2f *vector_array,int deletion_threshold)
{
	if(!vector_array->n)	return 0;
	
	vector_array->n--;
	if((vector_array->buffer_n)>=(vector_array->n+deletion_threshold))
	{
		int i;
		vector2f *vnew;
		
		vnew=malloc((vector_array->n)*sizeof(vector2f));
		
		for(i=0; i<vector_array->n; i++)
			vnew[i]=vector_array->v[i];
		
		free(vector_array->v);
		
		vector_array->v=vnew;
		vector_array->buffer_n=vector_array->n;
	}	
	
	return 1;
}

vector_array2f fcopyva2f(vector_array2f *vector_array)
{
	int i;
	vector_array2f new_vector_array;
	
	new_vector_array.v=malloc((vector_array->n)*sizeof(vector2f));
		
	for(i=0; i<vector_array->n; i++)
		new_vector_array.v[i]=vector_array->v[i];
		
	new_vector_array.n=new_vector_array.buffer_n=vector_array->n;
	
	return new_vector_array;
}

void translateva2f(vector_array2f *vector_array,vector2f v)
{
	int i;
	for(i=0; i<vector_array->n; i++)
		vector_array->v[i]=addv2f(vector_array->v[i],v);
}

void rotateva2f(vector_array2f *vector_array,float angle)
{
	int i;
	for(i=0; i<vector_array->n; i++)
		vector_array->v[i]=rotatev2f(vector_array->v[i],angle);
}

void scaleva2f(vector_array2f *vector_array,float scale)
{
	int i;
	for(i=0; i<vector_array->n; i++)
		vector_array->v[i]=scalev2f(vector_array->v[i],scale);
}

vector_array2i icopyva2f(vector_array2f *vector_array)
{
	int i;
	vector_array2i new_vector_array;
	
	new_vector_array.v=malloc((vector_array->n)*sizeof(vector2f));
		
	for(i=0; i<vector_array->n; i++)
		new_vector_array.v[i]=vec2f_to_vec2i(vector_array->v[i]);
		
	new_vector_array.n=new_vector_array.buffer_n=vector_array->n;
	
	return new_vector_array;
}

vector_array2f fcopyva2i(vector_array2i *vector_array)
{
	int i;
	vector_array2f new_vector_array;
	
	new_vector_array.v=malloc((vector_array->n)*sizeof(vector2i));
	
	for(i=0; i<vector_array->n; i++)
		new_vector_array.v[i]=vec2i_to_vec2f(vector_array->v[i]);
		
	new_vector_array.n=new_vector_array.buffer_n=vector_array->n;
	
	return new_vector_array;
}

typedef struct{
	vector3f *v;
	int n,buffer_n;
} vector_array3f;

vector3f lastv3f(vector_array3f *vector_array)
{
	return vector_array->v[vector_array->n-1];
}

vector_array3f emptyva3f()
{
	vector_array3f result;
	result.v=0;
	result.n=0;
	result.buffer_n=0;
	return result;
}

void deleteva3f(vector_array3f *vector_array)
{
	  if(vector_array->n)
	free(vector_array->v);
	
	vector_array->v=0;
	vector_array->n=0;
	vector_array->buffer_n=0;
}

void pushva3f(vector_array3f *vector_array,vector3f v)
{
	if((vector_array->buffer_n)>(vector_array->n))
		vector_array->v[vector_array->n++]=v;
	else
	{
		int i;
		vector3f *vnew;
		
		vnew=malloc((vector_array->n+1)*sizeof(vector3f));
		
		for(i=0; i<vector_array->n; i++)
			vnew[i]=vector_array->v[i];
		
		vnew[i]=v;
		
		if	(vector_array->n)
		free(vector_array->v);
			 vector_array->v=vnew;
			 vector_array->n++;
			 vector_array->buffer_n++;
	}
}

void pushva3fLargerExpansion(vector_array3f *vector_array,vector3f v,int add_buffer_n)
{
	if((vector_array->buffer_n)>(vector_array->n))
		vector_array->v[vector_array->n++]=v;
	else
	{
		int i;
		vector3f *vnew;
		
		vnew=malloc((vector_array->n+add_buffer_n)*sizeof(vector3f));
		
		for(i=0; i<vector_array->n; i++)
			vnew[i]=vector_array->v[i];
		
		vnew[i]=v;
		
		if	(vector_array->n)
		free(vector_array->v);
			 vector_array->v=vnew;
			 vector_array->n++;
			 vector_array->buffer_n+=add_buffer_n;
	}
}

void addBufferva3f(vector_array3f *vector_array,int extra_buffer)
{
	int i;
	vector3f *vnew;
		
	vnew=malloc((vector_array->n+extra_buffer)*sizeof(vector3f));
		
	for(i=0; i<vector_array->n; i++)
		vnew[i]=vector_array->v[i];
		
	if(vector_array->n)
	free(vector_array->v);
		
		 vector_array->v=vnew;
		 vector_array->buffer_n+=extra_buffer;
}

int popva3f(vector_array3f *vector_array,int deletion_threshold)
{
	if(!vector_array->n)	return 0;
	
	vector_array->n--;
	if((vector_array->buffer_n)>=(vector_array->n+deletion_threshold))
	{
		int i;
		vector3f *vnew;
		
		vnew=malloc((vector_array->n)*sizeof(vector2f));
		
		for(i=0; i<vector_array->n; i++)
			vnew[i]=vector_array->v[i];
		
		free(vector_array->v);
		
		vector_array->v=vnew;
		vector_array->buffer_n=vector_array->n;
	}	
	
	return 1;
}

vector_array3f fcopyva3f(vector_array3f *vector_array)
{
	int i;
	vector_array3f new_vector_array;
	
	new_vector_array.v=malloc((vector_array->n)*sizeof(vector3f));
		
	for(i=0; i<vector_array->n; i++)
		new_vector_array.v[i]=vector_array->v[i];
		
	new_vector_array.n=new_vector_array.buffer_n=vector_array->n;
	
	return new_vector_array;
}

void copyvacontent3f(vector_array3f *vector_array,vector_array3f *new_vector_array)
{
	int i;
	
	for(i=0; i<vector_array->n; i++)
		new_vector_array->v[i]=vector_array->v[i];
}

void translateva3f(vector_array3f *vector_array,vector3f v)
{
	int i;
	for(i=0; i<vector_array->n; i++)
		vector_array->v[i]=addv3f(vector_array->v[i],v);
}

void rotateva3fX(vector_array3f *vector_array,float angle)
{
	int i;
	for(i=0; i<vector_array->n; i++)
		vector_array->v[i]=rotateXv3f(vector_array->v[i],angle);
}
void rotateva3fY(vector_array3f *vector_array,float angle)
{
	int i;
	for(i=0; i<vector_array->n; i++)
		vector_array->v[i]=rotateYv3f(vector_array->v[i],angle);
}
void rotateva3fZ(vector_array3f *vector_array,float angle)
{
	int i;
	for(i=0; i<vector_array->n; i++)
		vector_array->v[i]=rotateZv3f(vector_array->v[i],angle);
}

void scaleva3f(vector_array3f *vector_array,float scale)
{
	int i;
	for(i=0; i<vector_array->n; i++)
		vector_array->v[i]=scalev3f(vector_array->v[i],scale);
}

vector_array3f fcopyva3i(vector_array3f *vector_array)
{
	int i;
	vector_array3f new_vector_array;
	
	new_vector_array.v=malloc((vector_array->n)*sizeof(vector2i));
	
	for(i=0; i<vector_array->n; i++)
		new_vector_array.v[i]=vector_array->v[i];
		
	new_vector_array.n=new_vector_array.buffer_n=vector_array->n;
	
	return new_vector_array;
}

/*vector array end*/

/**matrix float**/

typedef struct{
	vector2f col[2];
} matrix2f;

const matrix2f unitm2f=
{
	{{1,0},{0,1}}
};

matrix2f mat2f(float r0c0,float r0c1,float r1c0,float r1c1)
{
	matrix2f mat;
	
	mat.col[0].e[0]=r0c0;
	mat.col[0].e[1]=r1c0;
	mat.col[1].e[0]=r0c1;
	mat.col[1].e[1]=r1c1;
	
	return mat;
}

matrix2f matv2f(vector2f col0,vector2f col1)
{
	matrix2f mat;
	
	mat.col[0]=col0;
	mat.col[1]=col1;
	
	return mat;
}

vector2f rowm2f(matrix2f m,int i)
{
	vector2f result;
	
	result.e[0]=m.col[0].e[i];
	result.e[1]=m.col[1].e[i];
	
	return result;
}

matrix2f m2fxm2f(matrix2f m1,matrix2f m2)
{
	matrix2f result;
	
	result.col[0].e[0] = dotv2f( rowm2f(m1,0) , m2.col[0] );
	result.col[0].e[1] = dotv2f( rowm2f(m1,1) , m2.col[0] );
	result.col[1].e[0] = dotv2f( rowm2f(m1,0) , m2.col[1] );
	result.col[1].e[1] = dotv2f( rowm2f(m1,1) , m2.col[1] );
	
	return result;
}

vector2f m2fxv2f(matrix2f m,vector2f v)
{
	vector2f result;
	
	result.e[0] = dotv2f( rowm2f(m,0) , v );
	result.e[1] = dotv2f( rowm2f(m,1) , v );
	
	return result;
}

matrix2f transposem2f(matrix2f m)
{	
	matrix2f result;
	
	result.col[0].e[0] = m.col[0].e[0];
	result.col[0].e[1] = m.col[1].e[0];
	result.col[1].e[0] = m.col[0].e[1];
	result.col[1].e[1] = m.col[1].e[1];
	
	return result;
}

float detm2f(matrix2f m)
{
	return
	m.col[0].e[0]*m.col[1].e[1] - m.col[1].e[0]*m.col[0].e[1];
}

matrix2f invertm2f(matrix2f m)
{
	float
	det=m.col[0].e[0]*m.col[1].e[1] - m.col[1].e[0]*m.col[0].e[1];
	return
	mat2f(
	 m.col[1].e[1]/det,-m.col[1].e[0]/det,
	-m.col[0].e[1]/det, m.col[0].e[0]/det
	);
}

typedef struct{
	vector3f col[3];
} matrix3f;

const matrix3f unitm3f=
{
	{{1,0,0},{0,1,0},{0,0,1}}
};

matrix3f mat3f(float r0c0,float r0c1,float r0c2,float r1c0,float r1c1,float r1c2,float r2c0,float r2c1,float r2c2)
{
	matrix3f mat;
	
	mat.col[0].e[0]=r0c0;
	mat.col[0].e[1]=r1c0;
	mat.col[0].e[2]=r2c0;
	
	mat.col[1].e[0]=r0c1;
	mat.col[1].e[1]=r1c1;
	mat.col[1].e[2]=r2c1;
	
	mat.col[2].e[0]=r0c2;
	mat.col[2].e[1]=r1c2;
	mat.col[2].e[2]=r2c2;
	
	return mat;
}

matrix3f matv3f(vector3f col0,vector3f col1,vector3f col2)
{
	matrix3f mat;
	
	mat.col[0]=col0;
	mat.col[1]=col1;
	mat.col[2]=col2;
	
	return mat;
}

vector3f rowm3f(matrix3f m,int i)
{
	vector3f result;
	
	result.e[0]=m.col[0].e[i];
	result.e[1]=m.col[1].e[i];
	result.e[2]=m.col[2].e[i];
	
	return result;
}

matrix3f m3fxm3f(matrix3f m1,matrix3f m2)
{
	matrix3f result;
	
	result.col[0].e[0] = dotv3f( rowm3f(m1,0) , m2.col[0] );
	result.col[0].e[1] = dotv3f( rowm3f(m1,1) , m2.col[0] );
	result.col[0].e[2] = dotv3f( rowm3f(m1,2) , m2.col[0] );
	
	result.col[1].e[0] = dotv3f( rowm3f(m1,0) , m2.col[1] );
	result.col[1].e[1] = dotv3f( rowm3f(m1,1) , m2.col[1] );
	result.col[1].e[2] = dotv3f( rowm3f(m1,2) , m2.col[1] );

	result.col[1].e[0] = dotv3f( rowm3f(m1,0) , m2.col[2] );
	result.col[1].e[1] = dotv3f( rowm3f(m1,1) , m2.col[2] );
	result.col[1].e[2] = dotv3f( rowm3f(m1,2) , m2.col[2] );
	
	return result;
}

vector3f m3fxv3f(matrix3f m,vector3f v)
{
	vector3f result;
	
	result.e[0] = dotv3f( rowm3f(m,0) , v );
	result.e[1] = dotv3f( rowm3f(m,1) , v );
	result.e[2] = dotv3f( rowm3f(m,2) , v );
	
	return result;
}

matrix3f transposem3f(matrix3f m)
{	
	matrix3f result;
	
	result.col[0].e[0] = m.col[0].e[0];
	result.col[0].e[1] = m.col[1].e[0];
	result.col[0].e[2] = m.col[2].e[0];
	
	result.col[1].e[0] = m.col[0].e[1];
	result.col[1].e[1] = m.col[1].e[1];
	result.col[1].e[2] = m.col[2].e[1];
	
	result.col[2].e[0] = m.col[0].e[2];
	result.col[2].e[1] = m.col[1].e[2];
	result.col[2].e[2] = m.col[2].e[2];
	
	return result;
}

float detm3f(matrix3f m)
{
	return
	+m.col[0].e[0]*m.col[1].e[1]*m.col[2].e[2]
	+m.col[0].e[1]*m.col[1].e[2]*m.col[2].e[0]
	+m.col[0].e[2]*m.col[1].e[0]*m.col[2].e[1]
	-m.col[2].e[0]*m.col[1].e[1]*m.col[0].e[2]
	-m.col[2].e[1]*m.col[1].e[2]*m.col[0].e[0]
	-m.col[2].e[2]*m.col[1].e[0]*m.col[0].e[1]
	;
}



matrix3f translation_m3f(vector2f v)
{
	return mat3f(
	1,0,v.e[0],
	0,1,v.e[1],
	0,0,1
	);
}

matrix3f scaling_m3f(vector2f v)
{
	return mat3f(
	v.e[0]	,0		,0,
	0		,v.e[1]	,0,
	0		,0		,1
	);
}

matrix3f rotation_m3f(float a)
{
	return mat3f(
	 cos(a)	,-sin(a),0,
	 sin(a)	, cos(a),0,
	 0		, 0		,1
	);
}

typedef struct{
	vector4f col[4];
} matrix4f;

const matrix4f unitm4f=
{
	{{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}}
};

matrix4f mat4f(
float r0c0,float r0c1,float r0c2,float r0c3,
float r1c0,float r1c1,float r1c2,float r1c3,
float r2c0,float r2c1,float r2c2,float r2c3,
float r3c0,float r3c1,float r3c2,float r3c3
)
{
	matrix4f mat;
	
	mat.col[0].e[0]=r0c0;
	mat.col[0].e[1]=r1c0;
	mat.col[0].e[2]=r2c0;
	mat.col[0].e[3]=r3c0;
	
	mat.col[1].e[0]=r0c1;
	mat.col[1].e[1]=r1c1;
	mat.col[1].e[2]=r2c1;
	mat.col[1].e[3]=r3c1;
	
	mat.col[2].e[0]=r0c2;
	mat.col[2].e[1]=r1c2;
	mat.col[2].e[2]=r2c2;
	mat.col[2].e[3]=r3c2;
	
	mat.col[3].e[0]=r0c3;
	mat.col[3].e[1]=r1c3;
	mat.col[3].e[2]=r2c3;
	mat.col[3].e[3]=r3c3;
	
	return mat;
}

matrix4f mat4fv(vector4f col0,vector4f col1,vector4f col2,vector4f col3)
{
	matrix4f mat;
	
	mat.col[0]=col0;
	mat.col[1]=col1;
	mat.col[2]=col2;
	mat.col[3]=col3;
	
	return mat;
}

void printm4f(matrix4f m)
{
	printf("%f %f %f %f\n%f %f %f %f\n%f %f %f %f\n%f %f %f %f\n",
	m.col[0].e[0],m.col[1].e[0],m.col[2].e[0],m.col[3].e[0],
	m.col[0].e[1],m.col[1].e[1],m.col[2].e[1],m.col[3].e[1],
	m.col[0].e[2],m.col[1].e[2],m.col[2].e[2],m.col[3].e[2],
	m.col[0].e[3],m.col[1].e[3],m.col[2].e[3],m.col[3].e[3]
	);
}

vector4f rowm4f(matrix4f m,int i)
{
	vector4f result;
	
	result.e[0]=m.col[0].e[i];
	result.e[1]=m.col[1].e[i];
	result.e[2]=m.col[2].e[i];
	result.e[3]=m.col[3].e[i];
	
	return result;
}

matrix4f m4fxm4f(matrix4f m1,matrix4f m2)
{
	matrix4f result;
	
	result.col[0].e[0] = dotv4f( rowm4f(m1,0) , m2.col[0] );
	result.col[0].e[1] = dotv4f( rowm4f(m1,1) , m2.col[0] );
	result.col[0].e[2] = dotv4f( rowm4f(m1,2) , m2.col[0] );
	result.col[0].e[3] = dotv4f( rowm4f(m1,3) , m2.col[0] );
	
	result.col[1].e[0] = dotv4f( rowm4f(m1,0) , m2.col[1] );
	result.col[1].e[1] = dotv4f( rowm4f(m1,1) , m2.col[1] );
	result.col[1].e[2] = dotv4f( rowm4f(m1,2) , m2.col[1] );
	result.col[1].e[3] = dotv4f( rowm4f(m1,3) , m2.col[1] );
	
	result.col[2].e[0] = dotv4f( rowm4f(m1,0) , m2.col[2] );
	result.col[2].e[1] = dotv4f( rowm4f(m1,1) , m2.col[2] );
	result.col[2].e[2] = dotv4f( rowm4f(m1,2) , m2.col[2] );
	result.col[2].e[3] = dotv4f( rowm4f(m1,3) , m2.col[2] );
	
	result.col[3].e[0] = dotv4f( rowm4f(m1,0) , m2.col[3] );
	result.col[3].e[1] = dotv4f( rowm4f(m1,1) , m2.col[3] );
	result.col[3].e[2] = dotv4f( rowm4f(m1,2) , m2.col[3] );
	result.col[3].e[3] = dotv4f( rowm4f(m1,3) , m2.col[3] );
	
	return result;
}

matrix4f result_m4f={ {{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}} };
#define reset_m4f() { result_m4f=unitm4f; }
#define mul_m4f(m) {result_m4f=m4fxm4f(m,result_m4f);}


vector4f m4fxv4f(matrix4f m,vector4f v)
{
	vector4f result;
	
	result.e[0] = dotv4f( rowm4f(m,0) , v );
	result.e[1] = dotv4f( rowm4f(m,1) , v );
	result.e[2] = dotv4f( rowm4f(m,2) , v );
	result.e[3] = dotv4f( rowm4f(m,3) , v );
	
	return result;
}

matrix4f transposem4f(matrix4f m)
{	
	matrix4f result;
	
	result.col[0].e[0] = m.col[0].e[0];
	result.col[0].e[1] = m.col[1].e[0];
	result.col[0].e[2] = m.col[2].e[0];
	result.col[0].e[3] = m.col[3].e[0];
	
	result.col[1].e[0] = m.col[0].e[1];
	result.col[1].e[1] = m.col[1].e[1];
	result.col[1].e[2] = m.col[2].e[1];
	result.col[1].e[3] = m.col[3].e[1];
	
	result.col[2].e[0] = m.col[0].e[2];
	result.col[2].e[1] = m.col[1].e[2];
	result.col[2].e[2] = m.col[2].e[2];
	result.col[2].e[3] = m.col[3].e[2];
	
	result.col[3].e[0] = m.col[0].e[3];
	result.col[3].e[1] = m.col[1].e[3];
	result.col[3].e[2] = m.col[2].e[3];
	result.col[3].e[3] = m.col[3].e[3];
	
	return result;
}

matrix4f translation_m4f(vector3f v)
{
	return mat4f(
	1,0,0,v.e[0],
	0,1,0,v.e[1],
	0,0,1,v.e[2],
	0,0,0,1
	);
}

matrix4f scaling_m4f(vector3f v)
{
	return mat4f(
	v.e[0]	,0		,0		,0,
	0		,v.e[1]	,0		,0,
	0		,0		,v.e[2] ,0,
	0		,0		,0		,1
	);
}

matrix4f rotationZ_m4f(float a)
{
	return mat4f(
	 cos(a)	,-sin(a), 0		, 0,
	 sin(a)	, cos(a), 0		, 0,
	 0		, 0		, 1		, 0,
	 0		, 0		, 0		, 1
	);
}
matrix4f rotationY_m4f(float a)
{
	return mat4f(
	 cos(a)	, 0		,-sin(a), 0,
	 0		, 1		, 0		, 0,
	 sin(a)	, 0		, cos(a), 0,
	 0		, 0		, 0		, 1
	);
}

matrix4f rotationX_m4f(float a)
{
	return mat4f(
	 1		, 0		, 0		, 0,
	 0		, cos(a),-sin(a), 0,
	 0		, sin(a), cos(a), 0,
	 0		, 0		, 0		, 1
	);
}

matrix4f perspective_m4f(float near,float far,float ws,float hs)
{
	return mat4f(
	 near*ws, 0		 				,0			  			,0,
	 0		, near*hs				,0			  			,0,
	 0		, 0						,(far+near)/(far-near)  ,2*far*near/(near-far),
	 0		, 0						,1						,0
	);
}

matrix4f view_m4f(vector3f pos,vector3f dir)
{
	reset_m4f();
	mul_m4f(translation_m4f(negv3f(pos)));
	mul_m4f(rotationX_m4f(pi/2));
	mul_m4f(rotationY_m4f(pi/2));
	mul_m4f(rotationZ_m4f(pi));
	mul_m4f(rotationY_m4f(dir.e[0]));
	mul_m4f(rotationX_m4f(dir.e[1]));
	mul_m4f(rotationZ_m4f(dir.e[2]));
	
	return result_m4f;
}

matrix4f
ModelMatrix			={ {{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}} },
ViewMatrix			={ {{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}} },
PerspectiveMatrix	={ {{1,0,0,0},{0,1,0,0},{0,0,1,0},{0,0,0,1}} };

void transform(matrix4f m);

matrix4f getPVM()
{
	reset_m4f();
	mul_m4f(ModelMatrix);
	mul_m4f(ViewMatrix);
	mul_m4f(PerspectiveMatrix);
	
	return result_m4f;
}

void sendPVM()
{
	reset_m4f();
	mul_m4f(ModelMatrix);
	mul_m4f(ViewMatrix);
	mul_m4f(PerspectiveMatrix);
	transform(result_m4f);
}

float detm4f(matrix4f m)
{
	return 
	(m.col[0].e[0])*
	detm3f(mat3f(
		m.col[1].e[1],m.col[2].e[1],m.col[3].e[1],
		m.col[1].e[2],m.col[2].e[2],m.col[3].e[2],
		m.col[1].e[3],m.col[2].e[3],m.col[3].e[3])
	)+
	(m.col[1].e[0])*
	detm3f(mat3f(
		m.col[0].e[1],m.col[2].e[1],m.col[3].e[1],
		m.col[0].e[2],m.col[2].e[2],m.col[3].e[2],
		m.col[0].e[3],m.col[2].e[3],m.col[3].e[3])
	)+
	(m.col[2].e[0])*
	detm3f(mat3f(
		m.col[0].e[1],m.col[1].e[1],m.col[3].e[1],
		m.col[0].e[2],m.col[1].e[2],m.col[3].e[2],
		m.col[0].e[3],m.col[1].e[3],m.col[3].e[3])
	)+
	(m.col[3].e[0])*
	detm3f(mat3f(
		m.col[0].e[1],m.col[1].e[1],m.col[2].e[1],
		m.col[0].e[2],m.col[1].e[2],m.col[2].e[2],
		m.col[0].e[3],m.col[1].e[3],m.col[2].e[3])
	);	
}

matrix4f invertm4f(matrix4f m)
{	
	float
	a1,	a2,	a3,	a4,
	a5,	a6,	a7,	a8,
	a9,	a10,a11,a12,
	a13,a14,a15,a16,det;
	
	det=detm4f(m);

	a1=detm3f(
		mat3f(
			m.col[1].e[1],m.col[2].e[1],m.col[3].e[1],
			m.col[1].e[2],m.col[2].e[2],m.col[3].e[2],
			m.col[1].e[3],m.col[2].e[3],m.col[3].e[3]
		)
	);
	a2=-detm3f(
		mat3f(
			m.col[1].e[0],m.col[2].e[0],m.col[3].e[0],
			m.col[1].e[2],m.col[2].e[2],m.col[3].e[2],
			m.col[1].e[3],m.col[2].e[3],m.col[3].e[3]
		)
	);
	a3=detm3f(
		mat3f(
			m.col[1].e[0],m.col[2].e[0],m.col[3].e[0],
			m.col[1].e[1],m.col[2].e[1],m.col[3].e[1],
			m.col[1].e[3],m.col[2].e[3],m.col[3].e[3]
		)
	);
	a4=-detm3f(
		mat3f(
			m.col[1].e[0],m.col[2].e[0],m.col[3].e[0],
			m.col[1].e[1],m.col[2].e[1],m.col[3].e[1],
			m.col[1].e[2],m.col[2].e[2],m.col[3].e[2]
		)
	);
	a5=-detm3f(
		mat3f(
			m.col[0].e[1],m.col[2].e[1],m.col[3].e[1],
			m.col[0].e[2],m.col[2].e[2],m.col[3].e[2],
			m.col[0].e[3],m.col[2].e[3],m.col[3].e[3]
		)
	);
	a6=detm3f(
		mat3f(
			m.col[0].e[0],m.col[2].e[0],m.col[3].e[0],
			m.col[0].e[2],m.col[2].e[2],m.col[3].e[2],
			m.col[0].e[3],m.col[2].e[3],m.col[3].e[3]
		)
	);
	a7=-detm3f(
		mat3f(
			m.col[0].e[0],m.col[2].e[0],m.col[3].e[0],
			m.col[0].e[1],m.col[2].e[1],m.col[3].e[1],
			m.col[0].e[3],m.col[2].e[3],m.col[3].e[3]
		)
	);
	a8=detm3f(
		mat3f(
			m.col[0].e[0],m.col[2].e[0],m.col[3].e[0],
			m.col[0].e[1],m.col[2].e[1],m.col[3].e[1],
			m.col[0].e[2],m.col[2].e[2],m.col[3].e[2]
		)
	);
	a9=detm3f(
		mat3f(
			m.col[0].e[1],m.col[1].e[1],m.col[3].e[1],
			m.col[0].e[2],m.col[1].e[2],m.col[3].e[2],
			m.col[0].e[3],m.col[1].e[3],m.col[3].e[3]
		)
	);
	a10=-detm3f(
		mat3f(
			m.col[0].e[0],m.col[1].e[0],m.col[3].e[0],
			m.col[0].e[2],m.col[1].e[2],m.col[3].e[2],
			m.col[0].e[3],m.col[1].e[3],m.col[3].e[3]
		)
	);
	a11=detm3f(
		mat3f(
			m.col[0].e[0],m.col[1].e[0],m.col[3].e[0],
			m.col[0].e[1],m.col[1].e[1],m.col[3].e[1],
			m.col[0].e[3],m.col[1].e[3],m.col[3].e[3]
		)
	);
	a12=-detm3f(
		mat3f(
			m.col[0].e[0],m.col[1].e[0],m.col[3].e[0],
			m.col[0].e[1],m.col[1].e[1],m.col[3].e[1],
			m.col[0].e[2],m.col[1].e[2],m.col[3].e[2]
		)
	);
	a13=-detm3f(
		mat3f(
			m.col[0].e[1],m.col[1].e[1],m.col[2].e[1],
			m.col[0].e[2],m.col[1].e[2],m.col[2].e[2],
			m.col[0].e[3],m.col[1].e[3],m.col[2].e[3]
		)
	);
	a14=detm3f(
		mat3f(
			m.col[0].e[0],m.col[1].e[0],m.col[2].e[0],
			m.col[0].e[2],m.col[1].e[2],m.col[2].e[2],
			m.col[0].e[3],m.col[1].e[3],m.col[2].e[3]
		)
	);
	a15=-detm3f(
		mat3f(
			m.col[0].e[0],m.col[1].e[0],m.col[2].e[0],
			m.col[0].e[1],m.col[1].e[1],m.col[2].e[1],
			m.col[0].e[3],m.col[1].e[3],m.col[2].e[3]
		)
	);
	a16=detm3f(
		mat3f(
			m.col[0].e[0],m.col[1].e[0],m.col[2].e[0],
			m.col[0].e[1],m.col[1].e[1],m.col[2].e[1],
			m.col[0].e[2],m.col[1].e[2],m.col[2].e[2]
		)
	);
	
	return mat4f(
	a1 /det,a2 /det,a3 /det,a4 /det,
	a5 /det,a6 /det,a7 /det,a8 /det,
	a9 /det,a10/det,a11/det,a12/det,
	a13/det,a14/det,a15/det,a16/det);
}


void transformva2f(vector_array2f *vector_array,matrix3f transform_matrix)
{
	vector3f v3;
	int i;
	for(i=0; i<vector_array->n; i++)
	{
		v3.e[0]=vector_array->v[i].e[0];
		v3.e[1]=vector_array->v[i].e[1];
		v3.e[2]=1;
		
		v3=m3fxv3f(transform_matrix,v3);
		
		vector_array->v[i].e[0]=v3.e[0];
		vector_array->v[i].e[1]=v3.e[1];
	}
}

void transformva2f_n(vector_array2f *vector_array,matrix3f transform_matrix,int n)
{
	vector3f v3;
	int i;
	for(i=0; i<n; i++)
	{
		v3.e[0]=vector_array->v[i].e[0];
		v3.e[1]=vector_array->v[i].e[1];
		v3.e[2]=1;
		
		v3=m3fxv3f(transform_matrix,v3);
		
		vector_array->v[i].e[0]=v3.e[0];
		vector_array->v[i].e[1]=v3.e[1];
	}
}

void transformva3f(vector_array3f *vector_array,matrix4f transform_matrix)
{
	vector4f v4;
	int i;
	for(i=0; i<vector_array->n; i++)
	{
		v4.e[0]=vector_array->v[i].e[0];
		v4.e[1]=vector_array->v[i].e[1];
		v4.e[2]=vector_array->v[i].e[2];
		v4.e[3]=1;
		
		v4=m4fxv4f(transform_matrix,v4);
		
		vector_array->v[i].e[0]=v4.e[0];
		vector_array->v[i].e[1]=v4.e[1];
		vector_array->v[i].e[2]=v4.e[2];
	}
}

void transformva3f_n(vector_array3f *vector_array,matrix4f transform_matrix,int n)
{
	vector4f v4;
	int i;
	for(i=0; i<n; i++)
	{
		v4.e[0]=vector_array->v[i].e[0];
		v4.e[1]=vector_array->v[i].e[1];
		v4.e[2]=vector_array->v[i].e[2];
		v4.e[3]=1;
		
		v4=m4fxv4f(transform_matrix,v4);
		
		vector_array->v[i].e[0]=v4.e[0];
		vector_array->v[i].e[1]=v4.e[1];
		vector_array->v[i].e[2]=v4.e[2];
	}
}

/*geometric calculations*/
float mod2pi(float x)
{
	while(x>pi2)
	x-=pi2;
	
	while(x<0)
	x+=pi2;
	
	return x;
}

float getAnglev2f(vector2f v)
{
	v=normalizev2f(v);
	
	return
	
	mod2pi
	(
		acos(v.e[0])*(1-2*(v.e[1]<0))
	);
}

vector2f getTriangleMassPoint(triangle2f T)
{
	return vec2f
	(
		(T.vertex[0].e[0]+T.vertex[1].e[0]+T.vertex[2].e[0])/3,
		(T.vertex[0].e[1]+T.vertex[1].e[1]+T.vertex[2].e[1])/3
	);
}

float fgetLineXiv(vector2i p1,vector2i p2,float y)
{
	float m;
	if(p2.e[0]==p1.e[0]) return p1.e[0];
	m=((float)(p2.e[1]-p1.e[1]))/(p2.e[0]-p1.e[0]);
	return ( y- (p1.e[1]-m*p1.e[0]) ) / m;
}
float getLineXf(float x1,float y1,float x2,float y2,float y)
{
	float m=(y2-y1)/(x2-x1);
	return ( y- (y1-m*x1) ) / m;
}

int clockwise_i(vector2i v1,vector2i v2)
{
	vector3i v=crossi(vec2i_to_vec3i(v1),vec2i_to_vec3i(v2));
	return ( v.e[2]<0 );
}
int clockwise_f(vector2f v1,vector2f v2)
{
	vector3f v=crossf(vec2f_to_vec3f(v1),vec2f_to_vec3f(v2));
	return ( v.e[2]<0.0f );
}

int clockwiseTriangle2f(triangle2f tri)
{
	return clockwise_f
	(
		subv2f(tri.vertex[1],tri.vertex[0]),
		subv2f(tri.vertex[2],tri.vertex[1])
	);
}

int pointAtLeftOfArrow(vector2f p,arrow2f arr)
{
	return clockwise_f(subv2f(p,arr.from),delta2f(arr));
}

int pointAtRightOfArrow(vector2f p,arrow2f arr)
{
	return clockwise_f(delta2f(arr),subv2f(p,arr.from));
}

vector2f LineToLineIP(arrow2f L1,arrow2f L2)
{
	float t1,a,b,c,d,q,p,r,s;
	vector2f IP,slope1;
	
	q=L1.to.e[0]-L1.from.e[0];
	p=L2.to.e[0]-L2.from.e[0];
	r=L1.to.e[1]-L1.from.e[1];
	s=L2.to.e[1]-L2.from.e[1];
	a=L1.from.e[0];
	b=L2.from.e[0];
	c=L1.from.e[1];
	d=L2.from.e[1];
	
	{
		float denominator=q*s-r*p;
		if(!denominator) return vec2f(-1993,-1993);
		t1=(p*(c-d)+s*(b-a))/denominator;
	}
	slope1=scalev2f(subv2f(L1.to,L1.from),t1);
	IP=addv2f(L1.from,slope1);
	
	return IP;
}

vector2i LineToLineIPi(arrow2i L1,arrow2i L2)
{
	vec2f_to_vec2i( LineToLineIP(arr2i_to_arr2f(L1),arr2i_to_arr2f(L2)) );
}

int LineSegmentToLineSegment(arrow2f L1,arrow2f L2)
{
	float determinant;
	vector2f S[2],T,B;
	matrix2f A;
	S[0]=subv2f(L1.to,L1.from);
	S[1]=subv2f(L2.to,L2.from);
	determinant=S[0].e[1]*S[1].e[0]-S[0].e[0]*S[1].e[1];
	if(!determinant) return 0;
	
	B.e[0]=L2.from.e[0]-L1.from.e[0];
	B.e[1]=L2.from.e[1]-L1.from.e[1];
	
	A.col[0].e[0]=-S[1].e[1]; A.col[1].e[0]= S[1].e[0];
	A.col[0].e[1]=-S[0].e[1]; A.col[1].e[1]= S[0].e[0];
	
	B=scalev2f(B,1/determinant);
	T=m2fxv2f(A,B);
	
	return (0<T.e[0] && T.e[0]<1) && (0<T.e[1] && T.e[1]<1);
}

int LineSegmentToLineSegmenti(arrow2i L1,arrow2i L2)
{
	LineSegmentToLineSegment(arr2i_to_arr2f(L1),arr2i_to_arr2f(L2));
}

int LineToLineSegment(arrow2f L1,arrow2f L2) /*non-optimized*/
{
	float determinant;
	vector2f S[2],T,B;
	matrix2f A;
	S[0]=subv2f(L1.to,L1.from);
	S[1]=subv2f(L2.to,L2.from);
	determinant=S[0].e[1]*S[1].e[0]-S[0].e[0]*S[1].e[1];
	if(!determinant) return 0;
	
	B.e[0]=L2.from.e[0]-L1.from.e[0];
	B.e[1]=L2.from.e[1]-L1.from.e[1];
	
	A.col[0].e[0]=-S[1].e[1]; A.col[1].e[0]= S[1].e[0];
	A.col[0].e[1]=-S[0].e[1]; A.col[1].e[1]= S[0].e[0];
	
	B=scalev2f(B,1/determinant);
	T=m2fxv2f(A,B);
	
	return (0<T.e[1] && T.e[1]<1);
}

int LineToLineSegmenti(arrow2i L1,arrow2i L2)
{
	LineToLineSegment(arr2i_to_arr2f(L1),arr2i_to_arr2f(L2));
}

/*
int LineSegmentToCircle()
{
	
}*/


int LineToSphere(arrow3f line,vector3f sphere_pos,float sphere_r)
{
	float a,b,c,d,e,f,u1,u2,u3,k,l,m,s,t,u,k1,k2,k3,delta,A,B,C,r;
	u1=line.to.e[0]-line.from.e[0];
	u2=line.to.e[1]-line.from.e[1];
	u3=line.to.e[2]-line.from.e[2];
	a=u2;
	b=-u1;
	c=-line.from.e[0]*u2+line.from.e[1]*u1;
	d=u3;
	e=-u1;
	f=-line.from.e[0]*u3+line.from.e[2]*u1;
	k=sphere_pos.e[0];
	l=sphere_pos.e[1];
	m=sphere_pos.e[2];
	r=sphere_r;
	k1=1;
	k2=-a/b;
	k3=-d/e;
	s=-k;
	t=-c/b-l;
	u=-f/e-m;
	A=k1*k1+k2*k2+k3*k3;
	B=2*(k1*s+k2*t+k3*u);
	C=s*s+t*t+u*u-r*r;
	delta=B*B-4*A*C;
	
	return (delta>=0);
}

float point_distance(vector2f P1,vector2f P2)
{
	float dx,dy;
	dx=P1.e[0]-P2.e[0];
	dy=P1.e[1]-P2.e[1];
	return sqrt(dx*dx+dy*dy);
}

float point_distance_3d(vector3f P1,vector3f P2)
{
	float dx,dy,dz;
	dx=P1.e[0]-P2.e[0];
	dy=P1.e[1]-P2.e[1];
	dz=P1.e[2]-P2.e[2];
	return sqrt(dx*dx+dy*dy+dz*dz);
}

float arrowLength(arrow2f arr)
{
	return point_distance(arr.from,arr.to);
}

float line_to_point_distance(arrow2f L,vector2f p)/*non-optimized*/
{
	vector2f slope,p2,IP;
	slope=delta2f(L);
	slope=vec2f(slope.e[1],-slope.e[0]);
	p2=addv2f(p,slope);
	
	IP=LineToLineIP(L,arr2fv(p,p2));
	
	return point_distance(p,IP);
}

int PointToLine(vector2f p,arrow2f l,float d)
{
	vector2f normal,delta,P,c;
	delta=subv2f(l.to,l.from);
	normal=vec3f_to_vec2f(crossf(vec3f(delta.e[0],delta.e[1],0),vec3f(0,0,1)));
	P=addv2f(p,normal);
	c=LineToLineIP(arr2fv(p,P),l);
	
	return point_distance(p,c)<d;
}

int PointToLineSegmentLeft(vector2f p,arrow2f l,float d)
{
	vector2f middle,normal,delta;
	float d2;
	delta=subv2f(l.to,l.from);
	normal=vec3f_to_vec2f(crossf(vec3f(0,0,1),vec3f(delta.e[0],delta.e[1],0)));
	normal=normalizev2f(normal);
	middle=vec2f((l.to.e[0]+l.from.e[0])/2,(l.to.e[1]+l.from.e[1])/2);
	d2=point_distance(middle,l.from);
	l.from=addv2f(l.from,scalev2f(normal,d/2));
	l.to  =addv2f(l.to  ,scalev2f(normal,d/2));
	return (PointToLine(p,l,d/2) && PointToLine(p,arr2fv(middle,addv2f(middle,normal)),d2))
	;
}

int PointToLineSegmentRight(vector2f p,arrow2f l,float d)
{
	vector2f middle,normal,delta;
	float d2;
	delta=subv2f(l.to,l.from);
	normal=vec3f_to_vec2f(crossf(vec3f(delta.e[0],delta.e[1],0),vec3f(0,0,1)));
	normal=normalizev2f(normal);
	middle=vec2f((l.to.e[0]+l.from.e[0])/2,(l.to.e[1]+l.from.e[1])/2);
	d2=point_distance(middle,l.from);
	l.from=addv2f(l.from,scalev2f(normal,d/2));
	l.to  =addv2f(l.to  ,scalev2f(normal,d/2));
	return (PointToLine(p,l,d/2) && PointToLine(p,arr2fv(middle,addv2f(middle,normal)),d2))
	;
}

int PointToLineSegment(vector2f p,arrow2f l,float d)
{
	vector2f middle,normal,delta;
	float d2;
	delta=subv2f(l.to,l.from);
	normal=vec3f_to_vec2f(crossf(vec3f(delta.e[0],delta.e[1],0),vec3f(0,0,1)));
	middle=vec2f((l.to.e[0]+l.from.e[0])/2,(l.to.e[1]+l.from.e[1])/2);
	d2=point_distance(middle,l.from);
	return (PointToLine(p,l,d) && PointToLine(p,arr2fv(middle,addv2f(middle,normal)),d2))
	;
}

int PointInRectangle(vector2f P,vector2f Rp,vector2f Rs)
{
	return
	(Rp.e[0]<P.e[0]) && (P.e[0]<Rp.e[0]+Rs.e[0]) &&
	(Rp.e[1]<P.e[1]) && (P.e[1]<Rp.e[1]+Rs.e[1]);
}
int PointInRectanglei(vector2i P,vector2i Rp,vector2i Rs)
{
	return
	(Rp.e[0]<=P.e[0]) && (P.e[0]<Rp.e[0]+Rs.e[0]) &&
	(Rp.e[1]<=P.e[1]) && (P.e[1]<Rp.e[1]+Rs.e[1]);
}

int PointInTriangle(vector2f P,triangle2f T)
{	
	int cw=clockwiseTriangle2f(T),c1,c2,c3;
	c1=!pointAtLeftOfArrow(P,arr2fv(T.vertex[0],T.vertex[1]));
	c2=!pointAtLeftOfArrow(P,arr2fv(T.vertex[1],T.vertex[2]));
	c3=!pointAtLeftOfArrow(P,arr2fv(T.vertex[2],T.vertex[0]));
	
	if(!cw)
	{
		c1=!pointAtRightOfArrow(P,arr2fv(T.vertex[0],T.vertex[1]));
		c2=!pointAtRightOfArrow(P,arr2fv(T.vertex[1],T.vertex[2]));
		c3=!pointAtRightOfArrow(P,arr2fv(T.vertex[2],T.vertex[0]));
	}
	return
	(
		(c1) &&
		(c2) &&
		(c3)
	);
}

int PointInTrianglei(vector2i P,triangle2i T)
{
	PointInTriangle( addv2f(vec2i_to_vec2f(P),vec2f(0.5,0.5)),tri2i_to_tri2f(T));
}

int PointInTriangleCW(vector2f P,triangle2f T)
{	
	int c1,c2,c3;
	c1=!pointAtLeftOfArrow(P,arr2fv(T.vertex[0],T.vertex[1]));
	c2=!pointAtLeftOfArrow(P,arr2fv(T.vertex[1],T.vertex[2]));
	c3=!pointAtLeftOfArrow(P,arr2fv(T.vertex[2],T.vertex[0]));
	
	return
	(
		(c1) &&
		(c2) &&
		(c3)
	);
}

int PointInTriangleExtended(vector2f P,triangle2f T,float epsilon)/*uncompleted*/
{
	int cw=clockwiseTriangle2f(T),c1,c2,c3;
	arrow2f a1,a2,a3;
	vector2f shift;
	vector3f temp;

	a1=arr2fv(T.vertex[0],T.vertex[1]);
	a2=arr2fv(T.vertex[1],T.vertex[2]);
	a3=arr2fv(T.vertex[2],T.vertex[0]);
	
	temp=crossf(
	vec3f(0,0,1),
	vec2f_to_vec3f(delta2f(a1))
	);	
	temp=normalizev3f(temp);
	shift=vec3f_to_vec2f(temp);
	shift=scalev2f(shift,(1-(!cw)*2)*epsilon);
	a1=arr2fshift(a1,shift);

	temp=crossf(
	vec3f(0,0,1),
	vec2f_to_vec3f(delta2f(a2))
	);
	temp=normalizev3f(temp);
	shift=vec3f_to_vec2f(temp);
	shift=scalev2f(shift,(1-(!cw)*2)*epsilon);	
	a2=arr2fshift(a2,shift);
		
	temp=crossf(
	vec3f(0,0,1),
	vec2f_to_vec3f(delta2f(a3))
	);
	temp=normalizev3f(temp);
	shift=vec3f_to_vec2f(temp);
	shift=scalev2f(shift,(1-(!cw)*2)*epsilon);	
	a3=arr2fshift(a3,shift);

	c1=!pointAtLeftOfArrow(P,a1);
	c2=!pointAtLeftOfArrow(P,a2);
	c3=!pointAtLeftOfArrow(P,a3);
	
	return
	(
		(cw*c1+!cw*(!c1)) &&
		(cw*c2+!cw*(!c2)) &&
		(cw*c3+!cw*(!c3))
	);
}
void PointInTriangleWrtPointInTriangle(vector2f P1,triangle2f T1,vector2f *P2,triangle2f T2)
{
	float r1,r2;
	vector2f I;
	arrow2f p1,p2,q1,q2;
	
	p1.from	=T1.vertex[0];
	p1.to	=P1;
	
	q2.from	=T1.vertex[1];
	q2.to	=T1.vertex[2];
	
	I=LineToLineIP(p1,q2);
	
	p2.from	=T1.vertex[0];
	p2.to	=I;
	
	q1.from	=T1.vertex[1];
	q1.to	=I;
	
	r1=arrowLength(p1)/arrowLength(p2);
	r2=arrowLength(q1)/arrowLength(q2);
	
	/*if(clockwiseTriangle2f(T1))
	r2=-r2;*/
	/*if(pointAtLeftOfArrow(P1,arr2fv(T1.vertex[1],T1.vertex[0])))
	r2=-r2;*/
	
	I=
	addv2f
	(
		scalev2f(subv2f(T2.vertex[2],T2.vertex[1]),r2),
		T2.vertex[1]
	);
	
	*P2=
	addv2f
	(
		scalev2f(subv2f(I,T2.vertex[0]),r1),
		T2.vertex[0]
	);
}

int TriangleToTriangle(triangle2f T1,triangle2f T2)
{
	vector2f mass_point[2];
	int result;
	
	result=
	LineSegmentToLineSegment(arr2fv(T1.vertex[0],T1.vertex[1]),arr2fv(T2.vertex[0],T2.vertex[1])) ||
	LineSegmentToLineSegment(arr2fv(T1.vertex[0],T1.vertex[1]),arr2fv(T2.vertex[1],T2.vertex[2])) ||
	LineSegmentToLineSegment(arr2fv(T1.vertex[0],T1.vertex[1]),arr2fv(T2.vertex[2],T2.vertex[0])) ||
	
	LineSegmentToLineSegment(arr2fv(T1.vertex[1],T1.vertex[2]),arr2fv(T2.vertex[0],T2.vertex[1])) ||
	LineSegmentToLineSegment(arr2fv(T1.vertex[1],T1.vertex[2]),arr2fv(T2.vertex[1],T2.vertex[2])) ||
	LineSegmentToLineSegment(arr2fv(T1.vertex[1],T1.vertex[2]),arr2fv(T2.vertex[2],T2.vertex[0])) ||
	
	LineSegmentToLineSegment(arr2fv(T1.vertex[2],T1.vertex[0]),arr2fv(T2.vertex[0],T2.vertex[1])) ||
	LineSegmentToLineSegment(arr2fv(T1.vertex[2],T1.vertex[0]),arr2fv(T2.vertex[1],T2.vertex[2])) ||
	LineSegmentToLineSegment(arr2fv(T1.vertex[2],T1.vertex[0]),arr2fv(T2.vertex[2],T2.vertex[0])) ||
	
	PointInTriangle(T1.vertex[0],T2) ||
	PointInTriangle(T1.vertex[1],T2) ||
	PointInTriangle(T1.vertex[2],T2) ||
	
	PointInTriangle(T2.vertex[0],T1) ||
	PointInTriangle(T2.vertex[1],T1) ||
	PointInTriangle(T2.vertex[2],T1);
	
	if(result) return 1;
	
	mass_point[0].e[0]=(T1.vertex[0].e[0]+T1.vertex[1].e[0]+T1.vertex[2].e[0])/3;
	mass_point[0].e[1]=(T1.vertex[0].e[1]+T1.vertex[1].e[1]+T1.vertex[2].e[1])/3;
	
	mass_point[1].e[0]=(T2.vertex[0].e[0]+T2.vertex[1].e[0]+T2.vertex[2].e[0])/3;
	mass_point[1].e[1]=(T2.vertex[0].e[1]+T2.vertex[1].e[1]+T2.vertex[2].e[1])/3;
	
	result=
	PointInTriangle(mass_point[0],T2) ||
	PointInTriangle(mass_point[1],T1);
	
	return result;
}

int PointInCircle(vector2f pos1,vector2f pos2,float r)
{
	return point_distance(pos1,pos2)<r;
}

int CircleToCircle(vector2f pos1,float r1,vector2f pos2,float r2)
{
	return point_distance(pos1,pos2)<r1+r2;
}
int CircleToTriangle(vector2f pos1,float r,triangle2f tri)
{
	int check[3];
	
	if(!clockwiseTriangle2f(tri))
	{
		check[0]=
		PointToLineSegmentLeft(pos1,arr2fv(tri.vertex[1],tri.vertex[0]),r)||
		PointToLineSegmentLeft(pos1,arr2fv(tri.vertex[2],tri.vertex[1]),r)||
		PointToLineSegmentLeft(pos1,arr2fv(tri.vertex[0],tri.vertex[2]),r);
	}
	else
	{
		check[0]=
		PointToLineSegmentRight(pos1,arr2fv(tri.vertex[1],tri.vertex[0]),r)||
		PointToLineSegmentRight(pos1,arr2fv(tri.vertex[2],tri.vertex[1]),r)||
		PointToLineSegmentRight(pos1,arr2fv(tri.vertex[0],tri.vertex[2]),r);
	}
	
	check[1]=
	PointInCircle(pos1,tri.vertex[0],r)||
	PointInCircle(pos1,tri.vertex[1],r)||
	PointInCircle(pos1,tri.vertex[2],r);
	
	check[2]=PointInTriangle(pos1,tri);
	
	return check[0] || check[1] || check[2];
}

int CircleToRectangle(vector2f pos1,float r,vector2f pos2,vector2f size)
{
	return
	(PointInCircle(pos1,vec2f(pos2.e[0],pos2.e[1]),r) && PointInRectangle(pos1,vec2f(pos2.e[0]-r,pos2.e[1]-r),vec2f(r,r))) ||
	(PointInCircle(pos1,vec2f(pos2.e[0]+size.e[0],pos2.e[1]),r) && PointInRectangle(pos1,vec2f(pos2.e[0]+size.e[0],pos2.e[1]-r),vec2f(r,r))) ||
	(PointInCircle(pos1,vec2f(pos2.e[0]+size.e[0],pos2.e[1]+size.e[1]),r) && PointInRectangle(pos1,vec2f(pos2.e[0]+size.e[0],pos2.e[1]+size.e[1]),vec2f(r,r))) ||
	(PointInCircle(pos1,vec2f(pos2.e[0],pos2.e[1]+size.e[1]),r) && PointInRectangle(pos1,vec2f(pos2.e[0]-r,pos2.e[1]+size.e[1]),vec2f(r,r))) ||
	PointInRectangle(pos1,vec2f(pos2.e[0]-r,pos2.e[1]),vec2f(size.e[0]+2*r,size.e[1])) ||
	PointInRectangle(pos1,vec2f(pos2.e[0],pos2.e[1]-r),vec2f(size.e[0],size.e[1]+2*r));
}

int RectangleToRectangle(vector2f Rp1,vector2f Rs1,vector2f Rp2,vector2f Rs2)
{
	return
	(Rp1.e[0]<Rp2.e[0]+Rs2.e[0] && Rp1.e[0]+Rs1.e[0]>Rp2.e[0]) &&
	(Rp1.e[1]<Rp2.e[1]+Rs2.e[1] && Rp1.e[1]+Rs1.e[1]>Rp2.e[1]);
}

int LineSegmentToRectangle(arrow2f L,vector2f pos,vector2f size)
{
	return
	PointInRectangle(L.from,pos,size) ||
	PointInRectangle(L.to	,pos,size) ||
	LineSegmentToLineSegment(L,arr2f(pos.e[0],pos.e[1],pos.e[0]+size.e[0],pos.e[1])) ||
	LineSegmentToLineSegment(L,arr2f(pos.e[0]+size.e[0],pos.e[1],pos.e[0]+size.e[0],pos.e[1]+size.e[1])) ||
	LineSegmentToLineSegment(L,arr2f(pos.e[0]+size.e[0],pos.e[1]+size.e[1],pos.e[0],pos.e[1]+size.e[1])) ||
	LineSegmentToLineSegment(L,arr2f(pos.e[0],pos.e[1]+size.e[1],pos.e[0],pos.e[1]))
	;
}

int CircleToThickLineSegment(vector2f pos,float r,arrow2f L1,float d1)
{
	triangle2f L1triangle[2];
	vector2f normal;
	
	normal=vec3f_to_vec2f(crossf(vec2f_to_vec3f(subv2f(L1.to,L1.from)),vec3f(0,0,1)));
	normal=normalizev2f(normal);
	
	L1triangle[0].vertex[0]=addv2f(L1.from,scalev2f(normal, d1));
	L1triangle[0].vertex[1]=addv2f(L1.from,scalev2f(normal,-d1));
	L1triangle[0].vertex[2]=addv2f(L1.to,scalev2f(normal, d1));
	
	L1triangle[1].vertex[0]=addv2f(L1.to,scalev2f(normal, d1));
	L1triangle[1].vertex[1]=addv2f(L1.to,scalev2f(normal,-d1));
	L1triangle[1].vertex[2]=addv2f(L1.from,scalev2f(normal,-d1));

	return
	CircleToTriangle(pos,r,L1triangle[0])||
	CircleToTriangle(pos,r,L1triangle[1]);
}

int ThickLineSegmentToThickLineSegment(arrow2f L1,float d1,arrow2f L2,float d2)
{
	triangle2f L1triangle[2],L2triangle[2];
	vector2f normal;
	
	normal=vec3f_to_vec2f(crossf(vec2f_to_vec3f(subv2f(L1.to,L1.from)),vec3f(0,0,1)));
	normal=normalizev2f(normal);
	
	L1triangle[0].vertex[0]=addv2f(L1.from,scalev2f(normal, d1));
	L1triangle[0].vertex[1]=addv2f(L1.from,scalev2f(normal,-d1));
	L1triangle[0].vertex[2]=addv2f(L1.to,scalev2f(normal, d1));
	
	L1triangle[1].vertex[0]=addv2f(L1.to,scalev2f(normal, d1));
	L1triangle[1].vertex[1]=addv2f(L1.to,scalev2f(normal,-d1));
	L1triangle[1].vertex[2]=addv2f(L1.from,scalev2f(normal,-d1));
	
	normal=vec3f_to_vec2f(crossf(vec2f_to_vec3f(subv2f(L2.to,L2.from)),vec3f(0,0,1)));
	normal=normalizev2f(normal);
	
	L2triangle[0].vertex[0]=addv2f(L2.from,scalev2f(normal, d2));
	L2triangle[0].vertex[1]=addv2f(L2.from,scalev2f(normal,-d2));
	L2triangle[0].vertex[2]=addv2f(L2.to,scalev2f(normal, d2));
	
	L2triangle[1].vertex[0]=addv2f(L2.to,scalev2f(normal, d2));
	L2triangle[1].vertex[1]=addv2f(L2.to,scalev2f(normal,-d2));
	L2triangle[1].vertex[2]=addv2f(L2.from,scalev2f(normal,-d2));
	
	return
	TriangleToTriangle(L1triangle[0],L2triangle[0]) ||
	TriangleToTriangle(L1triangle[0],L2triangle[1]) ||
	TriangleToTriangle(L1triangle[1],L2triangle[0]) ||
	TriangleToTriangle(L1triangle[1],L2triangle[1]);
	
}

/*
void clipTriangleFromTriangle(triangle2f T1,triangle2f T2,triangle2f *newTriangles,int *n)
{
	int in_triangle1[3],in_triangle2[3],in2N=0,in1N,triangle1_to_line[3],triangle2_to_line[3];
	
	in_triangle2[0]=PointInTriangle(T1.vertex[0],T2);
	in_triangle2[1]=PointInTriangle(T1.vertex[1],T2);
	in_triangle2[2]=PointInTriangle(T1.vertex[2],T2);
	
	in2N=in_triangle2[0]+in_triangle2[1]+in_triangle2[2];
	
	switch(in2N)
	{
		case 0:
		in_triangle1[0]=PointInTriangle(T2.vertex[0],T1);
		in_triangle1[1]=PointInTriangle(T2.vertex[1],T1);
		in_triangle1[2]=PointInTriangle(T2.vertex[2],T1);
		
		in1N=in_triangle1[0]+in_triangle1[1]+in_triangle1[2];

		switch(in1N)
		{
			case 0:
			triangle1_to_line[]
			break;
		}
		
		break;
	}
}*/

/*algorithms*/



void swap(int *x1,int *x2)
{
	int temp;
	temp=*x1;
	*x1=*x2;
	*x2=temp;
}

/*x1 and x2 needs to be done in form of array, something to work on later*/
void sort2(int x1,int x2,int *ordered_indices)
{
	ordered_indices[0]=0;
	ordered_indices[1]=1;
	
	if(x1>x2)
	{
		ordered_indices[0]=1;
		ordered_indices[1]=0;
	}
}

void sort3(int x1,int x2,int x3,int *ordered_indices)
{
	/*from smallest to greatest*/
	ordered_indices[2]=2;
	ordered_indices[1]=0;
	ordered_indices[0]=1;
	if(x1<x2)
	{
		ordered_indices[0]=0;
		ordered_indices[1]=1;
	}
	if(x1>x2)
	{
		if(x1>x3)
		{
			ordered_indices[2]=0;
			ordered_indices[1]=1;
			ordered_indices[0]=2;
			if(x2<x3)
			{
				ordered_indices[0]=1;
				ordered_indices[1]=2;
			}
		}
	}
	else
	{
		if(x2>x3)
		{
			ordered_indices[2]=1;
			ordered_indices[1]=0;
			ordered_indices[0]=2;
			if(x1<x3)
			{
				ordered_indices[0]=0;
				ordered_indices[1]=2;
			}
		}
	}
}

int initMath()
{
	/*setPrimeNumberTable();*/
	setPowersOf10fTable();
}

#endif
