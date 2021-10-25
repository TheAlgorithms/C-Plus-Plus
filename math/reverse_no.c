#include <stdio.h>
main()
{
	int i,no,x,y;
	x=0;
	y=0;
		printf("enter no ==");
		scanf("%d",&no);
	while (no > 0)
	{
		x=no %10;
		y=y*10 + x;
		no=no/10;
	}
		printf("\n reverse no is this == %d",y);
	}
		
	
		
		
