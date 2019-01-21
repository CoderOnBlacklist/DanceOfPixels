/*
Copyright (C) <2018-2019> <Tankut Zeytinoğlu>
You can find the text of zlib license in the root folder.
*/

function SWmapToHWMap(v){
	v.e[0]=2*(v.e[0])/canvas.width-1;
	v.e[1]=1-2*(v.e[1])/canvas.height;
}

function HWmapToSWMap(v){
	v.e[0]=(v.e[0]+1)/2*canvas.width;
	v.e[1]=(1-v.e[1])/2*canvas.height;
}

var verticesxd;
var texcoordsxd;
var normalsxd;

var vertex_n;
var texcoord_n;
var normal_n;

var vertex_is;
var texcoord_is;
var normal_is;

var vb,tb,nb;

function init_draw()
{
	verticesxd=new Float32Array(30000);
	texcoordsxd=new Float32Array(30000);
	normalsxd=new Float32Array(30000);
	
	vb = gl.createBuffer();
    gl.bindBuffer(gl.ARRAY_BUFFER, vb);
    gl.bufferData(gl.ARRAY_BUFFER, verticesxd.byteLength, gl.STREAM_DRAW);

	tb = gl.createBuffer();
    gl.bindBuffer(gl.ARRAY_BUFFER, tb);
    gl.bufferData(gl.ARRAY_BUFFER, texcoordsxd.byteLength, gl.STREAM_DRAW);
}

function model_stack()
{
	  vertex_is=0;
	texcoord_is=0;
	  normal_is=0;
	
	  vertex_n=0;
	texcoord_n=0;
	  normal_n=0;
}

function addv2(v)
{
	SWmapToHWMap(v);
	vertex_is=2;
	verticesxd[(vertex_n)*2  ]=v.e[0];
	verticesxd[(vertex_n)*2+1]=v.e[1];
	vertex_n++;
}

function addv3(v)
{
	vertex_is=3;
	verticesxd[(vertex_n)*3  ]=v.e[0];
	verticesxd[(vertex_n)*3+1]=v.e[1];
	verticesxd[(vertex_n)*3+2]=v.e[2];
	vertex_n++;
}

function addt2(t)
{
	texcoord_is=2;
	texcoordsxd[(texcoord_n)*2  ]=t.e[0];
	texcoordsxd[(texcoord_n)*2+1]=t.e[1];
	texcoord_n++;
}

function addt3(t)
{
	texcoord_is=3;
	texcoordsxd[(texcoord_n)*3  ]=t.e[0];
	texcoordsxd[(texcoord_n)*3+1]=t.e[1];
	texcoordsxd[(texcoord_n)*3+2]=t.e[2];
	texcoord_n++;
}

function addn2(n)
{
	normal_is=2;
	normalsxd[(normal_n)*2  ]=n.e[0];
	normalsxd[(normal_n)*2+1]=n.e[1];
	normal_n++;
}

function addn3(n)
{
	normal_is=3;
	normalsxd[(normal_n)*3  ]=n.e[0];
	normalsxd[(normal_n)*3+1]=n.e[1];
	normalsxd[(normal_n)*3+2]=n.e[2];
	normal_n++;
}

function draw_stack(mode)
{	
	gl.bindBuffer(gl.ARRAY_BUFFER, vb);
    gl.bufferSubData(gl.ARRAY_BUFFER, 0,verticesxd);

	gl.bindBuffer(gl.ARRAY_BUFFER, tb);
    gl.bufferSubData(gl.ARRAY_BUFFER, 0,texcoordsxd);

	gl.bindBuffer(gl.ARRAY_BUFFER, vb);
	gl.vertexAttribPointer(attPosition,vertex_is,gl.FLOAT,gl.FALSE,0,0);
	gl.enableVertexAttribArray(attPosition);
	
	if(texcoord_is)
	{
		gl.bindBuffer(gl.ARRAY_BUFFER, tb);
		gl.vertexAttribPointer(attTexCoord,texcoord_is,gl.FLOAT,gl.FALSE,0,0);
		gl.enableVertexAttribArray(attTexCoord);
	}
	else
		gl.disableVertexAttribArray(attTexCoord);
	
	gl.drawArrays(mode,0,vertex_n);
}

function model(vb,tb,nb,vs,ts,ns,n)
{
	this.vs=vs;
	this.ts=ts;
	this.ns=ns;
	
	this.vb=vb;
	this.tb=tb;
	this.nb=nb;
	
	this.n=n;
}

function load_stack()
{
	var vertices,texcoords,normals;
	var vb,tb,nb;
	
	vertices=new Float32Array(vertex_n*vertex_is);
	texcoords=new Float32Array(texcoord_n*texcoord_is);
	normals=new Float32Array(normal_n*normal_is);
	
	var i,n;
	n=vertex_n*vertex_is;
	for(i=0; i<n; i++)
		vertices[i]=verticesxd[i];
	
	n=texcoord_n*texcoord_is;
	for(i=0; i<n; i++)
		texcoords[i]=texcoordsxd[i]
	
	n=normal_n*normal_is;
	for(i=0; i<n; i++)
		normals[i]=normalsxd[i]
	
	if(vertex_is)
	{
		vb = gl.createBuffer();
		gl.bindBuffer(gl.ARRAY_BUFFER, vb);
		gl.bufferData(gl.ARRAY_BUFFER, vertices.byteLength, gl.STREAM_DRAW);
		gl.bufferSubData(gl.ARRAY_BUFFER, 0,vertices);
	}
	
	if(texcoord_is)
	{
		tb = gl.createBuffer();
		gl.bindBuffer(gl.ARRAY_BUFFER, tb);
		gl.bufferData(gl.ARRAY_BUFFER, texcoords.byteLength, gl.STREAM_DRAW);
		gl.bufferSubData(gl.ARRAY_BUFFER, 0,texcoords);
	}
	
	if(normal_is)
	{
		nb = gl.createBuffer();
		gl.bindBuffer(gl.ARRAY_BUFFER, nb);
		gl.bufferData(gl.ARRAY_BUFFER, normals.byteLength, gl.STREAM_DRAW);
		gl.bufferSubData(gl.ARRAY_BUFFER, 0,normals);
	}
	
	return new model(vb,tb,nb,vertex_is,texcoord_is,normal_is,vertex_n);
}


function draw_model(m,mode)
{
	gl.bindBuffer(gl.ARRAY_BUFFER,m.vb);
	gl.vertexAttribPointer(attPosition,m.vertex_is,gl.FLOAT,gl.FALSE,0,0);
	gl.enableVertexAttribArray(attPosition);
	
	if(m.texcoord_is)
	{
		gl.bindBuffer(gl.ARRAY_BUFFER,m.tb);
		gl.vertexAttribPointer(attTexCoord,m.texcoord_is,gl.FLOAT,gl.FALSE,0,0);
		gl.enableVertexAttribArray(attTexCoord);
	}
	else
		gl.disableVertexAttribArray(attTexCoord);
	
	if(m.normal_is)
	{
		gl.bindBuffer(gl.ARRAY_BUFFER,m.nb);
		gl.vertexAttribPointer(attNormal,m.normal_is,gl.FLOAT,gl.FALSE,0,0);
		gl.enableVertexAttribArray(attNormal);
	}
	else
		gl.disableVertexAttribArray(attNormal);
	
	gl.drawArrays(mode,0,m.vertex_n);
}
