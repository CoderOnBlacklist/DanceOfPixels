var canvas;
var gl;

function createShader(source,type)
{
	var shader;
	var compiled;
	
	shader=gl.createShader(type);
	
	if(!shader) return 0;
	
	gl.shaderSource(shader,source);
	gl.compileShader(shader);
	compiled=gl.getShaderParameter(shader,gl.COMPILE_STATUS);
	
	if(!compiled)
	{	
		console.log(gl.getShaderInfoLog(shader));
		console.log("unable to load shader\n");
		
		gl.deleteShader(shader);
		
		return 0;
	}
	
	console.log("shader compiled successfully\n");
	return shader;
}

function createProgram(vertex_shader_str,fragment_shader_str)
{
	var vertex_shader,fragment_shader,program;
	
	vertex_shader = createShader(vertex_shader_str,gl.VERTEX_SHADER);
	fragment_shader = createShader(fragment_shader_str,gl.FRAGMENT_SHADER);
	
    program = gl.createProgram();
    gl.attachShader(program, vertex_shader);
    gl.attachShader(program, fragment_shader);
	
	{
		var linked;
		
		gl.linkProgram(program);
		
		linked=gl.getProgramParameter(program,gl.LINK_STATUS);
		
		if(linked)
			console.log("program was linked successfully\n");
	}
	
	gl.useProgram(program);
	
	return program;
}

var GLprogram;
var uniColor;
var uniSampler;
var uniTexturing;
var uniTransform;

var attPosition;
var attTexCoord;
var attNormal;

var transformMatrix=
[
	1,0,0,0,
	0,1,0,0,
	0,0,1,0,
	0,0,0,1
];

function transform(m)
{
	transformMatrix[ 0]=m.col[0].e[0]; transformMatrix[ 4]=m.col[1].e[0]; transformMatrix[ 8]=m.col[2].e[0]; transformMatrix[12]=m.col[3].e[0];
	transformMatrix[ 1]=m.col[0].e[1]; transformMatrix[ 5]=m.col[1].e[1]; transformMatrix[ 9]=m.col[2].e[1]; transformMatrix[13]=m.col[3].e[1];
	transformMatrix[ 2]=m.col[0].e[2]; transformMatrix[ 6]=m.col[1].e[2]; transformMatrix[10]=m.col[2].e[2]; transformMatrix[14]=m.col[3].e[2];
	transformMatrix[ 3]=m.col[0].e[3]; transformMatrix[ 7]=m.col[1].e[3]; transformMatrix[11]=m.col[2].e[3]; transformMatrix[15]=m.col[3].e[3];
	
	gl.uniformMatrix4fv(uniTransform,GL_FALSE,transformMatrix);
}

function color(r,g,b,a)
{
	gl.uniform4f(uniColor,r,g,b,a);
}

var TRIANGLE_MODE;
var LINE_MODE;
var LINE_STRIP_MODE;

function object(x,y)
{
	this.x=x;
	this.y=y;
}

var player=new object(10,10);
var tex;
var model;

function main()
{
	canvas=document.getElementById("example");
	if(!canvas)
	{
		console.log("Failed to retrieve the <canvas> element");
		return false;
	}
	
	gl=canvas.getContext('webgl');
	
	if(!gl)
	{
		console.log('Failed to get rendering context for WebGL');
		return;
	}
	
	TRIANGLE_MODE=gl.TRIANGLES;
	LINE_MODE=gl.LINES;
	LINE_STRIP_MODE=gl.LINE_STRIP;
	
	var vertex_shader_text =
	"attribute vec3 normal;\n"+
	"attribute vec2 texcoord;\n"+
	"attribute vec3 position;\n"+
	"uniform mat4 transform;\n"+
	"varying vec2 interpolated_texcoord;\n"+
	"void main()\n"+
	"{\n"+
	"	 interpolated_texcoord=texcoord;\n"+
	"    gl_Position =transform*vec4(position, 1.0);\n"+
	"}\n";
	var fragment_shader_text =
	"precision mediump float;\n"+
	"uniform vec4 color;\n"+
	"varying vec2 interpolated_texcoord;\n"+
	"uniform sampler2D tex;\n"+
	"uniform int texturing;\n"+
	"void main()\n"+
	"{\n"+
	"	vec4 result;\n"+
	"	if(texturing==1)\n"+
	"	result =(texture2D(tex,interpolated_texcoord))*color;\n"+
	"	else\n"+
	"	result =color;\n"+
	"	if(result.a>-0.001 && result.a<0.001) discard;\n"+
	"	gl_FragColor=result;\n"+
	"}\n";
	
	GLprogram=createProgram(vertex_shader_text,fragment_shader_text);
	
	attPosition=gl.getAttribLocation(GLprogram,"position");
	attTexCoord=gl.getAttribLocation(GLprogram,"texcoord");
	attNormal=gl.getAttribLocation(GLprogram,"normal");
	
	uniColor=gl.getUniformLocation(GLprogram,"color");
	uniSampler=gl.getUniformLocation(GLprogram,"tex");
	uniTexturing=gl.getUniformLocation(GLprogram,"texturing");
	uniTransform=gl.getUniformLocation(GLprogram,"transform");
	/*
	printf("(%i,%i,%i,%i,%i)",GLprogram,uniColor,uniSampler,uniTexturing,uniTransform);
	*/
	gl.uniformMatrix4fv(uniTransform,gl.FALSE,transformMatrix);
	
	gl.uniform1i(uniTexturing,0);
	
	gl.enable(gl.TEXTURE_2D);
	gl.activeTexture(gl.TEXTURE0);
	gl.bindTexture(gl.TEXTURE_2D,null);
	gl.uniform1i(uniSampler,0);
	
	gl.enable(gl.DEPTH_TEST);
	
	gl.enable(gl.BLEND);
	gl.blendFunc(gl.SRC_ALPHA,gl.ONE_MINUS_SRC_ALPHA);
	
	gl.viewport(0,0,canvas.width,canvas.height);
	
	init_draw();
	
	tex=loadTexture("apple.png");
	
	model_stack();
	addv2(new vec2f(0,0));
	addv2(new vec2f(32,32));
	model=load_stack();
	
	setInterval(mainLoop,33);
}



function mainLoop()
{
	player.x+=(key_right-key_left)*4;
	
	gl.clearColor(0.0,0.0,0.0,1.0);
	gl.clear(gl.COLOR_BUFFER_BIT|gl.DEPTH_BUFFER_BIT);
	
	color(1,1,1,1);
	
	gl.uniform1i(uniTexturing,0);
	gl.bindTexture(gl.TEXTURE_2D, tex);
	
	draw_model(model,LINE_MODE);
}
