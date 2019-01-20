void drawTriangle2(triangle2i T)/*reconsider*/
{
	int
	ordered_indices[3],i,
	x[3],y[3],
	dy;
	
	sort3(getv2iY(T.vertex[0]),getv2iY(T.vertex[1]),getv2iY(T.vertex[2]),ordered_indices);
	
	x[0]=getv2iX(T.vertex[ordered_indices[0]]);
	y[0]=getv2iY(T.vertex[ordered_indices[0]]);
	x[1]=getv2iX(T.vertex[ordered_indices[1]]);
	y[1]=getv2iY(T.vertex[ordered_indices[1]]);
	x[2]=getv2iX(T.vertex[ordered_indices[2]]);
	y[2]=getv2iY(T.vertex[ordered_indices[2]]);
	
	dy=y[2]-y[1];
	for(i=0; i<dy; i++)
	{
		int x1,x2,yscan;
		yscan=y[1]+i;
		x1=getLineX(vec2i(x[2],y[2]),vec2i(x[1],y[1]),yscan);
		x2=getLineX(vec2i(x[2],y[2]),vec2i(x[0],y[0]),yscan);
		
		if(x1<x2)
		drawLineHorizontal(x1,x2,yscan);
		else
		drawLineHorizontal(x2,x1,yscan);
	}
	
	dy=y[1]-y[0];
	for(i=0; i<dy; i++)
	{
		int x1,x2,yscan;
		yscan=y[0]+i;
		x1=getLineX(vec2i(x[1],y[1]),vec2i(x[0],y[0]),yscan);
		x2=getLineX(vec2i(x[2],y[2]),vec2i(x[0],y[0]),yscan);
		
		if(x1<x2)
		drawLineHorizontal(x1,x2,yscan);
		else
		drawLineHorizontal(x2,x1,yscan);
	}	
}
