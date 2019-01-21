/*
Copyright (C) <2018-2019> <Tankut Zeytinoğlu>
You can find the text of zlib license in the root folder.
*/

function vec2f(x,y)
{
	this.e=new Array(2);
	
	if(arguments.length==2)
	{
		this.e[0]=x;
		this.e[1]=y;
	}
}

function dotv2f(v1,v2)
{
	return v1.e[0]*v2.e[0] + v1.e[1]*v2.e[1];
}

function subv2f(v1,v2)
{
	return new vec2f(
		v1.e[0]-v2.e[0],
		v1.e[1]-v2.e[1]
	);
}

function addv2f(v1,v2)
{
	return new vec2f(
		v1.e[0]+v2.e[0],
		v1.e[1]+v2.e[1]
	);
}

function negv2f(v)
{
	return	new vec2f(-v.e[0],-v.e[1]);
}

function scalev2f(v,s)
{
	return	new vec2f(s*v.e[0],s*v.e[1]);
}

function lengthv2f(v)
{
	return Math.sqrt(v.e[0]*v.e[0]+v.e[1]*v.e[1]);
}

function normalizev2f(v)
{
	return scalev2f(v,1/lengthv2f(v));
}

function rotatev2f(v,a)
{
	return new vec2f(
		v.e[0]*cos(a)-v.e[1]*sin(a),
		v.e[0]*sin(a)+v.e[1]*cos(a)
	);
}

function vec3f(x,y,z)
{
	this.e=new Array(3);
	
	if(arguments.length==3)
	{
		this.e[0]=x;
		this.e[1]=y;
		this.e[2]=z;
	}
}

function printv3f(v)
{
	console.log(v.e[0]+"\n");
	console.log(v.e[1]+"\n");
	console.log(v.e[2]+"\n");
}

function dotv3f(v1,v2)
{
	return new vec3f(
		v1.e[0]*v2.e[0]+
		v1.e[1]*v2.e[1]+
		v1.e[2]*v2.e[2]
	);
}

function subv3f(v1,v2)
{
	return new vec3f(
		v1.e[0]-v2.e[0],
		v1.e[1]-v2.e[1],
		v1.e[2]-v2.e[2]
	);
}

function addv3f(v1,v2)
{
	return new vec3f(
		v1.e[0]+v2.e[0],
		v1.e[1]+v2.e[1],
		v1.e[2]+v2.e[2]
	);
}

function negv3f(v)
{
	return	new vec3f(-v.e[0],-v.e[1],-v.e[2]);
}

function scalev3f(v,s)
{
	return new vec3f(s*v.e[0],s*v.e[1],s*v.e[2]);
}

function lengthv3f(v)
{
	return Math.sqrt(v.e[0]*v.e[0]+v.e[1]*v.e[1]+v.e[2]*v.e[2]);
}

function normalizev3f(v)
{
	return scalev3f(v,1/lengthv3f(v));
}

function rotateZv3f(v,a)
{
	return new vec3f(
		v.e[0]*Math.cos(a)-v.e[1]*Math.sin(a),
		v.e[0]*Math.sin(a)+v.e[1]*Math.cos(a),
		v.e[2]
	);
}

function rotateYv3f(v,a)
{
	return new vec3f(
		v.e[0]*Math.cos(a)-v.e[2]*Math.sin(a),
		v.e[1],
		v.e[0]*Math.sin(a)+v.e[2]*Math.cos(a)
	);
}

function rotateXv3f(v,a)
{
	return new vec3f(
		v.e[0],
		v.e[1]*Math.cos(a)-v.e[2]*Math.sin(a),
		v.e[1]*Math.sin(a)+v.e[2]*Math.cos(a)
	);
}

function crossf(v1,v2)
{
	return new vec3f(
		v1.e[1]*v2.e[2]-v1.e[2]*v2.e[1],
		v1.e[2]*v2.e[0]-v1.e[0]*v2.e[2],
		v1.e[0]*v2.e[1]-v1.e[1]*v2.e[0]
	)
	;
}

function vec4f(x,y,z,w)
{
	this.e=new Array(4);
	
	if(arguments.length==4)
	{
		this.e[0]=x;
		this.e[1]=y;
		this.e[2]=z;
		this.e[3]=w;
	}
}

function printv4f(v)
{
	console.log(v.e[0]+"\n");
	console.log(v.e[1]+"\n");
	console.log(v.e[2]+"\n");
	console.log(v.e[3]+"\n");
}

function dotv4f(v1,v2)
{
	return new vec4f(
		v1.e[0]*v2.e[0]+
		v1.e[1]*v2.e[1]+
		v1.e[2]*v2.e[2]+
		v1.e[3]*v2.e[3]
	);
}

function vec3f_to_vec4f(v)
{
	return new vec4f(v.e[0],v.e[1],v.e[2],1);
}

function vec4f_to_vec3f(v)
{
	return new vec3f(v.e[0],v.e[1],v.e[2]);
}

function mat3f(
r0c0,r0c1,r0c2,
r1c0,r1c1,r1c2,
r2c0,r2c1,r2c2
)
{
	this.col=new Array(3);
	this.col[0]=new vec4f();
	this.col[1]=new vec4f();
	this.col[2]=new vec4f();
	if(arguments.length==9)
	{
		this.col[0].e[0]=r0c0;
		this.col[0].e[1]=r1c0;
		this.col[0].e[2]=r2c0;
	
		this.col[1].e[0]=r0c1;
		this.col[1].e[1]=r1c1;
		this.col[1].e[2]=r2c1;
	
		this.col[2].e[0]=r0c2;
		this.col[2].e[1]=r1c2;
		this.col[2].e[2]=r2c2;
	}
}

function mat3fv(col0,col1,col2)
{
	var mat=new mat3f();
	
	mat.col[0]=col0;
	mat.col[1]=col1;
	mat.col[2]=col2;
	
	return mat;
}

function printm3f(m)
{
	var E=
	[
		m.col[0].e[0],m.col[1].e[0],m.col[2].e[0],
		m.col[0].e[1],m.col[1].e[1],m.col[2].e[1],
		m.col[0].e[2],m.col[1].e[2],m.col[2].e[2]
	];
	console.log("\n"+
		 E [0]+" "+E [1]+" "+E [2]+"\n"
		+E [3]+" "+E [4]+" "+E [5]+"\n"
		+E [6]+" "+E [7]+" "+E [8]+"\n"
	);
}

function detm3f(m)
{
	return (
	+m.col[0].e[0]*m.col[1].e[1]*m.col[2].e[2]
	+m.col[0].e[1]*m.col[1].e[2]*m.col[2].e[0]
	+m.col[0].e[2]*m.col[1].e[0]*m.col[2].e[1]
	-m.col[2].e[0]*m.col[1].e[1]*m.col[0].e[2]
	-m.col[2].e[1]*m.col[1].e[2]*m.col[0].e[0]
	-m.col[2].e[2]*m.col[1].e[0]*m.col[0].e[1]
	);
}



function mat4f(
r0c0,r0c1,r0c2,r0c3,
r1c0,r1c1,r1c2,r1c3,
r2c0,r2c1,r2c2,r2c3,
r3c0,r3c1,r3c2,r3c3
)
{
	this.col=new Array(4);
	this.col[0]=new vec4f();
	this.col[1]=new vec4f();
	this.col[2]=new vec4f();
	this.col[3]=new vec4f();
	if(arguments.length==16)
	{
		this.col[0].e[0]=r0c0;
		this.col[0].e[1]=r1c0;
		this.col[0].e[2]=r2c0;
		this.col[0].e[3]=r3c0;
	
		this.col[1].e[0]=r0c1;
		this.col[1].e[1]=r1c1;
		this.col[1].e[2]=r2c1;
		this.col[1].e[3]=r3c1;
	
		this.col[2].e[0]=r0c2;
		this.col[2].e[1]=r1c2;
		this.col[2].e[2]=r2c2;
		this.col[2].e[3]=r3c2;
	
		this.col[3].e[0]=r0c3;
		this.col[3].e[1]=r1c3;
		this.col[3].e[2]=r2c3;
		this.col[3].e[3]=r3c3;
	}
}

function mat4fv(col0,col1,col2,col3)
{
	var mat=new mat4f();
	
	mat.col[0]=col0;
	mat.col[1]=col1;
	mat.col[2]=col2;
	mat.col[3]=col3;
	
	return mat;
}

function printm4f(m)
{
	var E=
	[
		m.col[0].e[0],m.col[1].e[0],m.col[2].e[0],m.col[3].e[0],
		m.col[0].e[1],m.col[1].e[1],m.col[2].e[1],m.col[3].e[1],
		m.col[0].e[2],m.col[1].e[2],m.col[2].e[2],m.col[3].e[2],
		m.col[0].e[3],m.col[1].e[3],m.col[2].e[3],m.col[3].e[3]
	];
	console.log("\n"+
		 E [0]+" "+E [1]+" "+E [2]+" "+E [3]+"\n"
		+E [4]+" "+E [5]+" "+E [6]+" "+E [7]+"\n"
		+E [8]+" "+E [9]+" "+E[10]+" "+E[11]+"\n"
		+E[12]+" "+E[13]+" "+E[14]+" "+E[15]+"\n"
	);
}

function rowm4f(m,i)
{
	var result=new vec4f();
	
	result.e[0]=m.col[0].e[i];
	result.e[1]=m.col[1].e[i];
	result.e[2]=m.col[2].e[i];
	result.e[3]=m.col[3].e[i];
	
	return result;
}

function m4fxm4f(m1,m2)
{
	var result=mat4f();
	
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

function m4fxv4f(m,v)
{
	var result=new vec4f();
	
	result.e[0] = dotv4f( rowm4f(m,0) , v );
	result.e[1] = dotv4f( rowm4f(m,1) , v );
	result.e[2] = dotv4f( rowm4f(m,2) , v );
	result.e[3] = dotv4f( rowm4f(m,3) , v );
	
	return result;
}

function transposem4f(m)
{	
	var result=mat4f();
	
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

function translation_m4f(v)
{
	return new mat4f(
	1,0,0,v.e[0],
	0,1,0,v.e[1],
	0,0,1,v.e[2],
	0,0,0,1
	);
}

function scaling_m4f(v)
{
	return new mat4f(
	v.e[0]	,0		,0		,0,
	0		,v.e[1]	,0		,0,
	0		,0		,v.e[2] ,0,
	0		,0		,0		,1
	);
}

function rotationZ_m4f(a)
{
	return new mat4f(
	 Math.cos(a)	,-Math.sin(a), 0		, 0,
	 Math.sin(a)	, Math.cos(a), 0		, 0,
	 0		, 0		, 1		, 0,
	 0		, 0		, 0		, 1
	);
}
function rotationY_m4f(a)
{
	return new mat4f(
	 Math.cos(a)	, 0		,-Math.sin(a), 0,
	 0		, 1		, 0		, 0,
	 Math.sin(a)	, 0		, Math.cos(a), 0,
	 0		, 0		, 0		, 1
	);
}

function rotationX_m4f(a)
{
	return new mat4f(
	 1		, 0		, 0		, 0,
	 0		, Math.cos(a),-Math.sin(a), 0,
	 0		, Math.sin(a), Math.cos(a), 0,
	 0		, 0		, 0		, 1
	);
}

function perspective_m4f(near,far,ws,hs)
{
	return new mat4f(
	 near*ws, 0		 				,0			  			,0,
	 0		, near*hs				,0			  			,0,
	 0		, 0						,(far+near)/(far-near)  ,2*far*near/(near-far),
	 0		, 0						,1						,0
	);
}

function unitm4f()
{
	var result=new mat4f(
	1,0,0,0,
	0,1,0,0,
	0,0,1,0,
	0,0,0,1
	);
	
	return result;
}

var result_m4f=unitm4f();

function reset_m4f()
{
	result_m4f=unitm4f();
}

function mul_m4f(m)
{
	result_m4f=m4fxm4f(m,result_m4f);
}

function view_m4f(pos,dir)
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

function detm4f(m)
{
	return (
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
	)
	);
}

function invertm4f(m)
{	
	var
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
	
	return new mat4f(
	a1 /det,a2 /det,a3 /det,a4 /det,
	a5 /det,a6 /det,a7 /det,a8 /det,
	a9 /det,a10/det,a11/det,a12/det,
	a13/det,a14/det,a15/det,a16/det);
}

var
ModelMatrix			=unitm4f(),
ViewMatrix			=unitm4f(),
PerspectiveMatrix	=perspective_m4f(1.73,10000,1,1);

function getPVM()
{
	reset_m4f();
	mul_m4f(ModelMatrix);
	mul_m4f(ViewMatrix);
	mul_m4f(PerspectiveMatrix);
	
	return result_m4f;
}

function sendPVM()
{
	reset_m4f();
	mul_m4f(ModelMatrix);
	mul_m4f(ViewMatrix);
	mul_m4f(PerspectiveMatrix);
	transform(result_m4f);
}
