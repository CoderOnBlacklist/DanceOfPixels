#include<stdio.h>

void foo0()
{
	printf("0\n");
}
void foo1()
{
	printf("1\n");
}
void foo2()
{
	printf("2\n");
}

void (*f[3])();

int isLetter(char ch)
{
	return ((ch>='a' && ch<='z') || (ch>='A' && ch<='Z'));
}

char lowercase(char ch)
{
	return ((ch<='Z'))?(ch+32):ch;
}

int main()
{/*
	f[0]=&foo0;
	f[1]=&foo1;
	f[2]=&foo2;
	
	(*f[2])();
	
	*/
	char str[]="This is a public mirror site of Wikipedia.";
	int i;
	for(i=0; str[i]!='\0'; i++)
	{
		if(isLetter(str[i]))
		str[i]=lowercase(str[i]);
		
		if(isLetter(str[i]))
		printf("%i",str[i]-'a');
		else
		putchar('0');
		
		putchar('-');
	}
	4 9 7 3 4 1 5 9
	7 5 7 6 4 3 7 5
	7 8 3 4 9 4 8 7
	1 0 7 8 6 4 3 7
	
	4 9 7 3 4 1 5 9
	1 5 7 2 0 1 6 1
	0 3 5 7 5 1 1 2
	3 0 0 2 2 1 5 2
	0 4 7 3 3
	
	4 -1- 9 -0- 7 -- 3 -- 4 -- 1 -- 5 -- 9
	1 1 2 1 1 1 2 1
	1 0 1 0 1 0 0 1
	1 0 1 2 0 1 0 1
	
	return 0;
}


