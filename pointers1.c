example 1:-
#include<stdio.h>

void ptrfunc(int *ptr)
{
	*ptr=8;
}

int main()
{
	int x=5;

	printf("x=%d\n",x );
	printf(&x);
	printf("x=%d",x );
	return 0;
}

example 2:-
  #include<stdio.h>


int main()
{	
	printf("Pointer Basics\n");
	int a =76;
	int *ptra=&a
	int *ptr2= NULL;

	printf("The Address of pointer is %p\n", &ptra );
	printf("The Address of a is %p\n," &a);
	printf("The Address of a is %p\n",ptra );
	printf("The Address of some garbage is %p\n",ptr2);
	printf("The Value of a is %d\n", *ptra );
	printf("The Value of a is %d\n", *a );
	return 0;
}
