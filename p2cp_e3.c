#include <stdio.h>
#include <string.h>
int fill( float * f, size_t k,char * s)
{
	double value;
	int i=0;
	char * p = strpbrk(s,",");
	while((sscanf(s,"%lf",&value))==1)
	{
		if(p==NULL)
		{
			if(sscanf(s,"%lf",&value)==1)
			{

				if(i<k)
				{

					f[i++]=value;
				}
			}
			else
				break;
			break;
		}
		s=p+1;
		p=strpbrk(s,",");
		if(i<k)
		{
			f[i++]=value;
		}
		else
			break;

	}
	return i;
}

int main()
{
	float f[20]={0};
	char a[]="5.234,9.193,94.23";
	unsigned k=fill(f,sizeof(f)/sizeof(f[0]),a);
	for(int i=0;i<k;i++)
	{
		printf("%lf",f[i]);
	}
	printf("\n");
}
