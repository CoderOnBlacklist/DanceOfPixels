function drawRectangleFrame(p1,p2)
{
	model_stack();
	addv2(new vec2f(p1.e[0]+0.5,p1.e[1]+0.5));
	addv2(new vec2f(p2.e[0]-0.5,p1.e[1]+0.5));
	addv2(new vec2f(p2.e[0]-0.5,p2.e[1]-0.5));
	addv2(new vec2f(p1.e[0]+0.5,p2.e[1]-0.5));
	addv2(new vec2f(p1.e[0]+0.5,p1.e[1]+0.5));
	draw_stack(LINE_STRIP_MODE);
}

function drawImage(p1,p2,tex)
{
	gl.uniform1i(uniTexturing,1);
	gl.bindTexture(gl.TEXTURE_2D, tex);
	
	model_stack();
	addv2(new vec2f(p1.e[0],p1.e[1]));
	addv2(new vec2f(p1.e[0],p2.e[1]));
	addv2(new vec2f(p2.e[0],p2.e[1]));
	addv2(new vec2f(p2.e[0],p2.e[1]));
	addv2(new vec2f(p2.e[0],p1.e[1]));
	addv2(new vec2f(p1.e[0],p1.e[1]));
	
	addt2(new vec2f(0,0));
	addt2(new vec2f(0,1));
	addt2(new vec2f(1,1));
	addt2(new vec2f(1,1));
	addt2(new vec2f(1,0));
	addt2(new vec2f(0,0));
	draw_stack(TRIANGLE_MODE);
}

function loadImage(p1,p2,tex)
{	
	model_stack();
	addv2(new vec2f(p1.e[0],p1.e[1]));
	addv2(new vec2f(p1.e[0],p2.e[1]));
	addv2(new vec2f(p2.e[0],p2.e[1]));
	addv2(new vec2f(p2.e[0],p2.e[1]));
	addv2(new vec2f(p2.e[0],p1.e[1]));
	addv2(new vec2f(p1.e[0],p1.e[1]));
	
	addt2(new vec2f(0,0));
	addt2(new vec2f(0,1));
	addt2(new vec2f(1,1));
	addt2(new vec2f(1,1));
	addt2(new vec2f(1,0));
	addt2(new vec2f(0,0));
	return load_stack();
}