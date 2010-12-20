#include <stdio.h>
#include <time.h>
int main()
{
	clock_t start,end;
	start = clock();
	int x = 0;
	int y = 0;
	int z = 0;
	int k = 3;
	int i,j;

	for (i=0; i<2000000000; i++) {
		x++;
		z++;
		if (i<1499999999)
//		if (i<1999999999)
		{
			x++;
			z++;
		}
		else
		{
			y++;
			z--;
		}
		
		if (i > 200000000)
		{
			y++;
		}
		else
		{
		  k=1;
			x++;
		}
		switch(i%20)
		{
			case 1:
				x++;
				k = 3;
			case 2:
				y++;
			default:
				z=z+k;
				k=3;
				if (i<1499999999)
				{
					x=x+k;
					z++;
				}
				else
				{
					y++;
					z--;
				}
				
				if (i > 200000000)
				{
					y++;
				}
				else
				{
					x++;
				}
		}
		//printf("%d %d %d ",x,y,z);
	}
	printf("%d %d %d ",x,y,z);
	printf("\n");
	end = clock();
	printf("%ld\n", (end-start)*1000/CLOCKS_PER_SEC);
	
}
