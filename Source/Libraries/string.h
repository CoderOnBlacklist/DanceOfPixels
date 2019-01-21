/*
Copyright (C) <2018-2019> <Tankut Zeytinoğlu>
You can find the text of zlib license in the root folder.
*/

#ifndef STRING_H
#define STRING_H

typedef struct
{
	char* str;
	int length;
}text;

/*why pointer does not work?*/
const char empty_string[1]="";

#define emptyText {empty_string,0}

text empty_text={empty_string,0};

int strLength(char *str)
{
	int i;
	for(i=0; str[i]!='\0'; i++);
	return i;
}

void deleteText(text *txt)
{
	if(txt->length==0) {txt->str=empty_string; return;}
	free(txt->str);
	txt->str=empty_string;
	txt->length=0;
}

void setText(text *txt,char *str)
{
	int i;
	deleteText(txt);
	txt->length=strLength(str);
	txt->str=malloc(sizeof(char)*(txt->length+1));
	for(i=0; i<txt->length; i++)
		txt->str[i]=str[i];
	txt->str[i]='\0';
}
void setText2(text *txt,char *str,int n)
{
	int i;
	deleteText(txt);
	txt->length=n;
	
	if(strLength(str)<n) return;
	
	txt->str=malloc(sizeof(char)*(txt->length+1));
	for(i=0; i<txt->length; i++)
		txt->str[i]=str[i];
	txt->str[i]='\0';
}

void appendText(text *txt,text ext)
{
	int i,new_length;
	char *new_str;
	new_length=txt->length+ext.length;
	
	new_str=malloc(sizeof(char)*(new_length+1));
	for(i=0; i<txt->length; i++)
		new_str[i]=txt->str[i];
	for(i=0; i<ext.length; i++)
		new_str[i+txt->length]=ext.str[i];
	new_str[i+txt->length]='\0';
	
	if(txt->length)	free(txt->str);
	
	txt->str=new_str;
	txt->length=new_length;
}
void appendCharacter(text* txt,char ch)
{
	int i,new_length;
	char *new_str;
	new_length=txt->length+1;
	
	new_str=malloc(sizeof(char)*(new_length+1));
	for(i=0; i<txt->length; i++)
		new_str[i]=txt->str[i];
		
	new_str[i]=ch;
	new_str[i+1]='\0';
	
	if(txt->length)	free(txt->str);
	txt->str=new_str;
	txt->length=new_length;
}
void appendString(text* txt,char* str)
{
	int i,new_length,str_length;
	char *new_str;
	str_length=strLength(str);
	new_length=txt->length+str_length;
	
	new_str=malloc(sizeof(char)*(new_length+1));
	for(i=0; i<txt->length; i++)
		new_str[i]=txt->str[i];
	for(i=0; i<str_length; i++)
		new_str[i+txt->length]=str[i];
	new_str[i+txt->length]='\0';
	
	if(txt->length)	free(txt->str);
	txt->str=new_str;
	txt->length=new_length;
}

int numOfDigits(int x);
text IntToText(int x);

void appendInteger(text* txt,int x)
{
	text number=emptyText;
	
	number=IntToText(x);
	appendText(txt,number);
	deleteText(&number);
}

text subText(text* txt,int from,int to);

void appendInteger2(text* txt,int x,int min_num_of_digits)
{
	int n=numOfDigits(x);
	const char *zeros="0000000000";
	text temp=emptyText;
	text number=emptyText;
	
	if(n<min_num_of_digits)
	{
		setText2(&temp,zeros,min_num_of_digits-n);
		appendText(txt,temp);
	}
	
	number=IntToText(x);
	appendText(txt,number);
	
	deleteText(&number);
	deleteText(&temp);
}

text FloatToText(float x,int after_comma);

void appendFloat(text* txt,float x,int after_comma)
{
	text number=emptyText;
	
	number=FloatToText(x,after_comma);
	appendText(txt,number);
	deleteText(&number);
}

text subText(text* txt,int from,int to)
{
	int i;
	text result;
	result.length=to-from+1;
	result.str=malloc(sizeof(char)*(result.length+1));
	for(i=0; i<result.length; i++)
		result.str[i]=txt->str[from+i];
	result.str[i]='\0';
	
	return result;
}

void deleteSubText(text *txt,int from,int to)
{
	text E=emptyText,result=emptyText;
	E=subText(txt,0,from-1);
	appendText(&result,E);
	deleteText(&E);
	E=subText(txt,to+1,txt->length-1);
	appendText(&result,E);
	deleteText(&E);
	deleteText(txt);
	*txt=result;
}

void insertText(text* txt,text ext,int from)
{
	text E=emptyText,result=emptyText;
	E=subText(txt,0,from-1);
	appendText(&result,E);
	deleteText(&E);
	appendText(&result,ext);
	E=subText(txt,from,txt->length-1);
	appendText(&result,E);
	deleteText(&E);
	deleteText(txt);
	*txt=result;
}

void insertString(text* txt,char* str,int from)
{
	text E=emptyText,result=emptyText;
	E=subText(txt,0,from-1);
	appendText(&result,E);
	deleteText(&E);
	appendString(&result,str);
	E=subText(txt,from,txt->length-1);
	appendText(&result,E);
	deleteText(&E);
	deleteText(txt);
	*txt=result;
}

void insertCharacter(text* txt,char ch,int from)
{
	text E=emptyText,result=emptyText;
	E=subText(txt,0,from-1);
	appendText(&result,E);
	deleteText(&E);
	appendCharacter(&result,ch);
	E=subText(txt,from,txt->length-1);
	appendText(&result,E);
	deleteText(&E);
	deleteText(txt);
	*txt=result;
}

void shiftTextLeft(text *txt,int from,int to,int shift)
{
	int i,n;
	n=to-from+1-shift;
	
	for(i=0; i<n; i++)
		txt->str[from+i]=txt->str[from+i+shift];

}
void shiftTextRight(text *txt,int from,int to,int shift)
{
	int i,n;
	n=to-from+1-shift;
	
	for(i=0; i<n; i++)
		txt->str[to-i]=txt->str[to-i-shift];

}

text IntToText(int x)
{
	text txt;
	int i,sgn,add;
	sgn=sign(x);
	add=(1-sgn)/2;
	x*=sgn;
	txt.length=numOfDigits(x)+add;
	txt.str=malloc(sizeof(char)*(txt.length+1));
	txt.str[0]='-';
	txt.str[txt.length]='\0';
	for(i=txt.length-1; i>=add; i--)
	{
		txt.str[i]='0'+x%10;
		x/=10;
	}
	return txt;
}

text FloatToText(float x,int after_comma)
{
	int digits,sign=1;
	text result=emptyText;
	
	sign-=(x<0)*2;
	x*=sign*power(10,after_comma);
	digits=(int)x;
	appendInteger(&result,digits);
	insertString(&result,".",result.length-after_comma);
	if((result.length-1)==after_comma)
	insertString(&result,"0",0);
	if(sign<0)
	insertString(&result,"-",0);
	
	return result;
}


int TextToInt(text txt)
{
	int i,result=0;
	for(i=0; i<txt.length; i++)
	{
		result*=10;
		result+=txt.str[i]-'0';
	}
	return result;
}

float TextToFloat(text txt)
{
	int sign=1,after_comma,i;
	float result;
	if(txt.str[0]=='-')	{deleteSubText(&txt,0,0);	sign=-1;}
	
	for(i=0; txt.str[txt.length-1-i]!='.'; i++);
	
	deleteSubText(&txt,txt.length-1-i,txt.length-1-i);
	
	result=TextToInt(txt)*sign;
	result/=power(10,i);
	
	return result;
}

#endif
