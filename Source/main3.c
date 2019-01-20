#include<stdio.h>
#include<stdlib.h>
#include<string.h>

typedef struct
{
	int n;
	void *ptr;
}array;

#define array_type char

#define emptyArray {0,0}

#define pushElement(arr,x) {\
	array_type temp=x;\
	pushElement_f(arr,&temp,sizeof(array_type));\
}

void pushElement_f(array *a,void* x,size_t size)
{
	void *temp;

	temp=malloc(size*(a->n+1));

	memcpy(temp				,a->ptr	,size*(a->n));
	memcpy(temp+size*(a->n)	,x		,size);
		
	if((a->n)>0) free(a->ptr);
	a->ptr=temp;
	
	a->n++;
}


int main()
{
	int i;
	array a={0,0};

#undef	array_type
#define array_type int

	for(i=0; i<10; i++)
	{
		int j;
		j=i*i;
		pushElement(&a,j);
	}
	
	for(i=0; i<10; i++)
	printf("%i\n",*((int*)a.ptr+i));
	
	free(a.ptr);
	
	return 0;
}
