#ifndef FONT_H
#define FONT_H

typedef struct
{
	TextureHW TexHW;
	Texture Tex;
	int grid_w,grid_h,xn,yn,offset;
} font;

font createFont(Texture Tex,int grid_w,int grid_h,int xn,int yn,int offset)
{
	font f;
	f.Tex=Tex;
	f.grid_w=grid_w;
	f.grid_h=grid_h;
	f.offset=offset;
	f.xn=xn;
	f.yn=yn;
	return f;
}

font createFontHW(TextureHW TexHW,int grid_w,int grid_h,int xn,int yn,int offset)
{
	font f;
	f.TexHW=TexHW;
	f.grid_w=grid_w;
	f.grid_h=grid_h;
	f.offset=offset;
	f.xn=xn;
	f.yn=yn;
	return f;
}

void deleteFontTexture(font *f)
{
	deleteTexturePixels(&f->Tex);
}

void deleteFontTextureHW(font f)
{
	glDeleteTextures(1,&f.TexHW);
}

font cfont;

typedef struct
{
	color c;
	float scaler;
	int default_w,default_h;
}style;

style styleC(color c,float scaler,int default_w,int default_h)
{
	style s;
	
	s.c=c;
	s.scaler=scaler;
	s.default_w=default_w;
	s.default_h=default_h;
	
	return s;
}

style cstyle={{255,255,255},1,9,18};

void useStyle(style s)
{
	cstyle=s;
}

void drawLetter(char ch,int x,int y)
{
	int i,j,ind;
	
	ind=ch-' ';
	
	if(ind<0 || ind>97) return;
	
	i=ind%cfont.xn;
	j=ind/cfont.xn;
	
	drawImagePart(cfont.Tex,x,y,cfont.grid_w*i,cfont.grid_h*j,cfont.grid_w,cfont.grid_h);
}

void drawLetterColored(char ch,int x,int y)
{
	int i,j,ind;
	
	ind=ch-' ';
	
	if(ind<0 || ind>97) return;
	
	i=ind%cfont.xn;
	j=ind/cfont.xn;
	
	drawImagePartColored(cfont.Tex,x,y,cfont.grid_w*i,cfont.grid_h*j,cfont.grid_w,cfont.grid_h);
}

void drawLetterColoredScaled(char ch,int x,int y)
{
	int i,j,ind;
	
	ind=ch-' ';
	
	if(ind<0 || ind>97) return;
	
	i=ind%cfont.xn;
	j=ind/cfont.xn;
	
	drawImagePartScaledColored(cfont.Tex,x,y,cfont.grid_w*i,cfont.grid_h*j,cfont.grid_w,cfont.grid_h,0,0,cstyle.scaler*cstyle.default_w,cstyle.scaler*cstyle.default_h);
}

void drawLetterScaledHW(char ch,int x,int y)
{
	int i,j,ind;
	
	if(
	(x>borderHW[0]+borderHW[2]) ||
	(x+cstyle.scaler*cstyle.default_w<borderHW[0]) ||
	(y>borderHW[1]+borderHW[3]) ||
	(y+cstyle.scaler*cstyle.default_h<borderHW[1])
	)
	return;
	
	ind=ch-' ';

	if(ind<0 || ind>97) return;
	
	i=ind%cfont.xn;
	j=ind/cfont.xn;
	
	drawImagePartScaledHW(cfont.TexHW,x,y,cfont.grid_w*i,cfont.grid_h*j,cfont.grid_w,cfont.grid_h,0,0,cstyle.scaler*cstyle.default_w,cstyle.scaler*cstyle.default_h);
}

int tab_space=4;

void drawStringHW(char *str,int x,int y)
{
	int i,row=0,col=0;
	
	setColorHW(cstyle.c);

	texturing(1);
	for(i=0; str[i]!='\0'; i++)
	{
		if(str[i]=='\n')
		{
			row++;
			col=0;
			continue;
		}
		if(str[i]=='\t')
		{
			if((col%tab_space)==0)
			col+=tab_space;
			else
			col+=tab_space-(col%tab_space);
			
			continue;
		}
		
		drawLetterScaledHW(str[i],x+cstyle.scaler*cstyle.default_w*col,y+cstyle.scaler*cstyle.default_h*row);
		
		col++;
	}
}

void drawCursorHW(char *str,int x,int y,int cursor_i)
{
	int i,row=0,col=0;
	
	setColorHW(cstyle.c);
	
	texturing(0);
	if(cursor_i==-1)
	{
		drawLinefHW
		(
		 vec2f(x+0.5f,y+0.5f),
		 vec2f(x+0.5f,y+cstyle.scaler*cstyle.default_h+0.5f)
		);
	}
	
	for(i=0; str[i]!='\0'; i++)
	{
		if(str[i]=='\n')
		{
			row++;
			col=0;
			if(i==cursor_i)
			{
				drawLinefHW
				(
				 vec2f(x+cstyle.scaler*cstyle.default_w*col+0.5f,y+cstyle.scaler*cstyle.default_h*row+0.5f),
				 vec2f(x+cstyle.scaler*cstyle.default_w*col+0.5f,y+cstyle.scaler*cstyle.default_h*row+cstyle.scaler*cstyle.default_h+0.5f)
				);
				break;
			}
			continue;
		}
		if(str[i]=='\t')
		{
			if((col%tab_space)==0)
			col+=tab_space;
			else
			col+=tab_space-(col%tab_space);

			if(i==cursor_i)
			{
				drawLinefHW
				(
				 vec2f(x+cstyle.scaler*cstyle.default_w*col+0.5f,y+cstyle.scaler*cstyle.default_h*row+0.5f),
				 vec2f(x+cstyle.scaler*cstyle.default_w*col+0.5f,y+cstyle.scaler*cstyle.default_h*row+cstyle.scaler*cstyle.default_h+0.5f)
				);
				break;
			}
			
			continue;
		}
		if(i==cursor_i)
		{
			drawLinefHW
			(
			 vec2f(x+cstyle.scaler*cstyle.default_w*(col+1)+0.5f,y+cstyle.scaler*cstyle.default_h*row+0.5f),
			 vec2f(x+cstyle.scaler*cstyle.default_w*(col+1)+0.5f,y+cstyle.scaler*cstyle.default_h*row+cstyle.scaler*cstyle.default_h+0.5f)
			);
			break;
		}
		
		col++;
	}
}

/*int getCursorX(char *str,int x,int y,int cursor_i)
{
	int i,row=0,col=0;
	
	setColorHW(cstyle.c);
	
	texturing(0);
	if(cursor_i==-1)
	{
		return x+0.5f;
	}
	
	for(i=0; str[i]!='\0'; i++)
	{
		if(str[i]=='\n')
		{
			row++;
			col=0;
			if(i==cursor_i)
			{
				return x+cstyle.scaler*cstyle.default_w*col+0.5f;
			}
			continue;
		}
		if(str[i]=='\t')
		{
			if((col%tab_space)==0)
			col+=tab_space;
			else
			col+=tab_space-(col%tab_space);

			if(i==cursor_i)
			{
				return x+cstyle.scaler*cstyle.default_w*col+0.5f;
			}
			
			continue;
		}
		if(i==cursor_i)
		{
			return x+cstyle.scaler*cstyle.default_w*(col+1)+0.5f;
		}
		
		col++;
	}
}

int getCursorY(char *str,int x,int y,int cursor_i)
{
	int i,row=0,col=0;
	
	setColorHW(cstyle.c);
	
	texturing(0);
	if(cursor_i==-1)
	{
		return y+0.5f;
	}
	
	for(i=0; str[i]!='\0'; i++)
	{
		if(str[i]=='\n')
		{
			row++;
			col=0;
			if(i==cursor_i)
			{
				return y+cstyle.scaler*cstyle.default_h*row+0.5f);
			}
			continue;
		}
		if(str[i]=='\t')
		{
			if((col%tab_space)==0)
			col+=tab_space;
			else
			col+=tab_space-(col%tab_space);

			if(i==cursor_i)
			{
				return y+cstyle.scaler*cstyle.default_h*row+0.5f);
			}
			
			continue;
		}
		if(i==cursor_i)
		{
			return y+cstyle.scaler*cstyle.default_h*row+0.5f);
		}
		
		col++;
	}
}
*/
void drawStringSelectedHW(char *str,int x,int y,int i1,int i2)
{
	int i,row=0,col=0;
	
	setColor(cstyle.c);
	
	saveColor(1);
	invertColor();
	saveColor(2);
	
	for(i=0; str[i]!='\0'; i++)
	{
		if(str[i]=='\n')
		{
			row++;
			col=0;
			continue;
		}
		if(str[i]=='\t')
		{
			if((col%tab_space)==0)
			col+=tab_space;
			else
			col+=tab_space-(col%tab_space);
			
			continue;
		}
		if((i>=i1) && (i<=i2))
		{
			texturing(0);
			
			setColorHW(colorRecord[1]);
			drawRectanglefHW(vec2f(x+cstyle.scaler*cstyle.default_w*col,y+cstyle.scaler*cstyle.default_h*row),vec2f(x+cstyle.scaler*cstyle.default_w*(col+1),y+cstyle.scaler*cstyle.default_h*(row+1)));

			texturing(1);
			
			setColorHW(colorRecord[2]);
			drawLetterScaledHW(str[i],x+cstyle.scaler*cstyle.default_w*col,y+cstyle.scaler*cstyle.default_h*row);
		}
		else
		{
			texturing(1);
			
			setColorHW(colorRecord[1]);
			drawLetterScaledHW(str[i],x+cstyle.scaler*cstyle.default_w*col,y+cstyle.scaler*cstyle.default_h*row);
		}
		
		col++;
	}
	
	loadColor(1);
}


void drawString(char *str,int x,int y)/*will be extented*/
{
	int i,row=0,col=0;
	
	setColor(cstyle.c);
	
	for(i=0; str[i]!='\0'; i++)
	{
		if(str[i]=='\n')
		{
			row++;
			col=0;
			continue;
		}
		if(str[i]=='\t')
		{
			if((col%tab_space)==0)
			col+=tab_space;
			else
			col+=tab_space-(col%tab_space);
			
			continue;
		}
		
		drawLetterColored(str[i],x+cstyle.scaler*cstyle.default_w*col,y+cstyle.scaler*cstyle.default_h*row);
		col++;
	}
}

void drawStringSelected(char *str,int x,int y,int i1,int i2)
{
	int i,row=0,col=0;
	
	setColor(cstyle.c);
	
	saveColor(1);
	invertColor();
	saveColor(2);
	
	for(i=0; str[i]!='\0'; i++)
	{
		if(str[i]=='\n')
		{
			row++;
			col=0;
			continue;
		}
		if(str[i]=='\t')
		{
			if((col%tab_space)==0)
			col+=tab_space;
			else
			col+=tab_space-(col%tab_space);
			
			continue;
		}
		
		if((i>=i1) && (i<=i2))
		{
			setColor(colorRecord[1]);
			drawRectangle(x+cstyle.scaler*cstyle.default_w*col,y+cstyle.scaler*cstyle.default_h*row,cstyle.scaler*cstyle.default_w,cstyle.scaler*cstyle.default_h);

			setColor(colorRecord[2]);
			drawLetterColored(str[i],x+cstyle.scaler*cstyle.default_w*col,y+cstyle.scaler*cstyle.default_h*row);
		}
		else
		{
			setColor(colorRecord[1]);
			drawLetterColored(str[i],x+cstyle.scaler*cstyle.default_w*col,y+cstyle.scaler*cstyle.default_h*row);
		}
		
		col++;
	}
	
	loadColor(1);
}

void drawCursor(char *str,int x,int y,int cursor_i)
{
	int i,row=0,col=0;
	
	setColor(cstyle.c);
	
	if(cursor_i==-1)
	{
		drawLine
		(
		 vec2i(x,y),
		 vec2i(x,y+cstyle.scaler*cstyle.default_h)
		);
	}
	
	for(i=0; str[i]!='\0'; i++)
	{
		if(str[i]=='\n')
		{
			row++;
			col=0;
			if(i==cursor_i)
			{
				drawLine
				(
				 vec2i(x+cstyle.scaler*cstyle.default_w*col,y+cstyle.scaler*cstyle.default_h*row),
				 vec2i(x+cstyle.scaler*cstyle.default_w*col,y+cstyle.scaler*cstyle.default_h*row+cstyle.scaler*cstyle.default_h)
				);
				break;
			}
			continue;
		}
		if(str[i]=='\t')
		{
			if((col%tab_space)==0)
			col+=tab_space;
			else
			col+=tab_space-(col%tab_space);
		
			if(i==cursor_i)
			{
				drawLine
				(
				 vec2i(x+cstyle.scaler*cstyle.default_w*col,y+cstyle.scaler*cstyle.default_h*row),
				 vec2i(x+cstyle.scaler*cstyle.default_w*col,y+cstyle.scaler*cstyle.default_h*row+cstyle.scaler*cstyle.default_h)
				);
				break;
			}
			
			continue;
		}
		if(i==cursor_i)
		{	
			drawLine
			(
			 vec2i(x+cstyle.scaler*cstyle.default_w*(col+1),y+cstyle.scaler*cstyle.default_h*row),
			 vec2i(x+cstyle.scaler*cstyle.default_w*(col+1),y+cstyle.scaler*cstyle.default_h*row+cstyle.scaler*cstyle.default_h)
			);
			break;
		}
		
		col++;
	}
}

int getStringWidth(char *str)
{
	int i,col=0,max_col=0;
	
	for(i=0; str[i]!='\0'; i++)
	{
		if(str[i]=='\n')
		{
			if(col>max_col) max_col=col;
			
			col=0;
			continue;
		}
		if(str[i]=='\t')
		{
			if((col%tab_space)==0)
			col+=tab_space;
			else
			col+=tab_space-(col%tab_space);
			
			continue;
		}
		col++;
	}
	
	if(col>max_col) max_col=col;
	
	return cstyle.scaler*cstyle.default_w*max_col;
}

int getStringHeight(char *str)
{
	int i,row=0;
	
	for(i=0; str[i]!='\0'; i++)
	{
		if(str[i]=='\n')
		{
			row++;
			continue;
		}
	}
	row++;
	
	return cstyle.scaler*cstyle.default_h*row;
}

int getCursorIndexFromMouseCoordinates(char *str,int x,int y,int mouse_x,int mouse_y)
{
	int i,row,col,col_p,target_row,col_overflow;
	
	target_row=(mouse_y-y)/cfont.grid_h;
	
	if(target_row<0) target_row=0;
	
	row=0;
	for(i=0; str[i]!='\0'; i++)
	{
		if(row==target_row)
		break;
		
		if(str[i]=='\n')
			row++;
	}
	
	col_overflow=1;
	col=0;
	
	
	if(mouse_x<x) return i;
	for(; str[i]!='\n' && str[i]!='\0'; i++)
	{
		if(str[i]=='\t')
		{
			col_p=col;
			
			if((col%tab_space)==0)
			col+=tab_space;
			else
			col+=tab_space-(col%tab_space);
			
			continue;
		}
		
		
		if(x+cfont.grid_w*col>mouse_x)
		{
			col_overflow=0;

			return i-1+!((mouse_x-x-cfont.grid_w*col_p)<(x+cfont.grid_w*col-mouse_x));
		}
		
		col_p=col;
		
		col++;
	}
	
	if(col_overflow)
	{
		return i;
	}
}

int getMaxRowNumber(char *str)
{
	int i,row=0,col=0;
	
	for(i=0; str[i]!='\0'; i++)
	{
		if(str[i]=='\n')
		{
			row++;
			col=0;
			continue;
		}
		if(str[i]=='\t')
		{
			if((col%tab_space)==0)
			col+=tab_space;
			else
			col+=tab_space-(col%tab_space);
			
			continue;
		}
		col++;
	}
	
	return row+1;
}

int getMaxColumnAtRow(char *str,int test_row)
{
	int i,j,c,row=0,col=0;
	
	for(i=0; str[i]!='\0'; i++)
	{
		if(str[i]=='\n')
		{
			row++;
			col=0;
			
			if(row==test_row)
			{
				for(j=i+1,c=0; str[j]!='\n' && str[j]!='\0'; j++)
				{
					if(str[j]=='\t')
					{
						if((c%tab_space)==0)
						c+=tab_space;
						else
						c+=tab_space-(c%tab_space);
						
						continue;
					}
					c++;
				}
				
				return c;
			}
			
			continue;
		}
		if(str[i]=='\t')
		{
			if((col%tab_space)==0)
			col+=tab_space;
			else
			col+=tab_space-(col%tab_space);
			
			if(row==test_row)
			{
				for(j=i+1,c=0; str[j]!='\n' && str[j]!='\0'; j++)
				{
					if(str[j]=='\t')
					{
						if(((col+c)%tab_space)==0)
						c+=tab_space;
						else
						c+=tab_space-((col+c)%tab_space);
						
						continue;
					}
					c++;
				}
				
				return col+c;
			}
			
			continue;
		}
		
		col++;
		
		if(row==test_row)
		{
			for(j=i+1,c=0; str[j]!='\n' && str[j]!='\0'; j++)
			{
				if(str[j]=='\t')
				{
					if(((col+c)%tab_space)==0)
					c+=tab_space;
					else
					c+=tab_space-((col+c)%tab_space);
						
					continue;
				}
				c++;
			}
			
			return col+c;
		}
	}
}


int getMaxWidthAtRow(char *str,int test_row)
{
	return getMaxColumnAtRow(str,test_row)*cstyle.scaler*cstyle.default_w;
}

int getColumnAtIndex(char *str,int index)
{
	int i,row=0,col=0;
	
	for(i=0; str[i]!='\0'; i++)
	{	
		if(str[i]=='\n')
		{
			row++;
			col=0;
			
			if(i==index)
			{
				return col;
			}
			
			continue;
		}
		if(str[i]=='\t')
		{
			if((col%tab_space)==0)
			col+=tab_space;
			else
			col+=tab_space-(col%tab_space);
			
			if(i==index)
			{
				return col;
			}
			
			continue;
		}
		col++;
		
		if(i==index)
		{
			return col;
		}
	}
}

int getRowAtIndex(char *str,int index)
{
	int i,row=0,col=0;
	
	for(i=0; str[i]!='\0'; i++)
	{	
		if(str[i]=='\n')
		{
			row++;
			col=0;
			
			if(i==index)
			{
				return row;
			}
			
			continue;
		}
		if(str[i]=='\t')
		{
			if((col%tab_space)==0)
			col+=tab_space;
			else
			col+=tab_space-(col%tab_space);
			
			if(i==index)
			{
				return row;
			}
			
			continue;
		}
		col++;
		
		if(i==index)
		{
			return row;
		}
	}
}


int getCursorX(char *str,int index)
{
	return getColumnAtIndex(str,index)*cstyle.scaler*cstyle.default_w;
}

int getCursorY(char *str,int index)
{
	return getRowAtIndex(str,index)*cstyle.scaler*cstyle.default_h;
}

/*
void drawStringSelected(char *str,int x,int y)
{
	int i,row=0,col=0;
	
	for(i=0; str[i]!='\0'; i++)
	{
		if(str[i]=='\n')
		{
			row++;
			col=0;
			continue;
		}
		if(str[i]=='\t')
		{
			if((col%tab_space)==0)
			col+=tab_space;
			else
			col+=tab_space-(col%tab_space);
			
			continue;
		}
		drawLetter(str[i],x+cfont.grid_w*col,y+cfont.grid_h*row);
		col++;
	}
}
*/
/*
typedef struct
{
	
} style;
*/

font default_font;

void initFont()
{
	if(file_exists("Fonts/font.png"))
	default_font=createFont(loadTexture("Fonts/font.png")					,9,18,14,7,0);
	else if(file_exists("../../Source/Fonts/font.png"))
	default_font=createFont(loadTexture("../../Source/Fonts/font.png")	,9,18,14,7,0);

	cfont=default_font;
}

void quitFont()
{
	deleteFontTexture(&default_font);
}

void initFontHW()
{
	if(file_exists("Fonts/font.png"))
	default_font=createFontHW(loadTextureHW("Fonts/font.png")					,9,18,14,7,0);
	else if(file_exists("../../Source/Fonts/font.png"))
	default_font=createFontHW(loadTextureHW("../../Source/Fonts/font.png")	,9,18,14,7,0);
	else if(file_exists("../../DanceOfPixels/Source/Fonts/font.png"))
	default_font=createFontHW(loadTextureHW("../../DanceOfPixels/Source/Fonts/font.png")	,9,18,14,7,0);
	
	cfont=default_font;
}

void quitFontHW()
{
	deleteFontTextureHW(default_font);
}



#endif

/*

			===		x
				qqqqx
			qqqqqqqqx
		qqqqqqqqqqqqx
	qqqqqqqqqqqqqqqqx
qqqqqqqqqqqqqqqqqqqqx




*/
