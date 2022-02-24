#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
typedef struct cat{
	char id[16],name[101];
	double price;
	int stocks;
	char description[210];
}catalog;
typedef struct catf{
	catalog * line;
	int nL;
	int avg;
}catff;

int cmpLine(const void* p1, const void* p2)
{
	const catalog n1=* (catalog*)p1;
	const catalog n2=*(catalog*)p2;
	return strcmp(n1.name,n2.name);
}

catff read( FILE* f)
{
	int nL=0;
	catalog * linie=malloc(sizeof(catalog));
	catalog curent;
	int m=0;
	if(!linie)
	{
		printf("Eroare!");
	}
	while((fscanf(f,"%s %s %lf %d",curent.name, curent.id,&curent.price,&curent.stocks))==4)
	{
		int c=getc(f);
		fgets(curent.description,209,f);	
		catalog * aux=realloc(linie,(nL+1)*sizeof(catalog));
		m+=strlen(curent.description);
		//printf("%d\n",m);
		if(!aux)
		{
			printf("Eroare!");
			free(linie);
			return(catff){NULL,0,0};
		}
		linie=aux;
		linie[nL++]=curent;
	}
	int avg=m/nL;
	return (catff){linie,nL,avg};
}


int main(int argc, char * argv[])
{
	if(argc!=2)
	{
		printf("Error!");
		return -1;
	}
	FILE *f=fopen(argv[1],"r");
	if(!f)
	{
		printf("Error");
		return -1;
	}
	catff lines=read(f);
	for(int i=0;i<lines.nL;i++)
	{
		if(strlen(lines.line[i].description)>lines.avg)
		{
			strcpy(lines.line[i].description+lines.avg,"...");
		}
		
		if((lines.line[i].price) <= 1)
			printf("%s %s %lf %d %s", lines.line[i].name,lines.line[i].id,lines.line[i].price,lines.line[i].stocks,lines.line[i].description);
			
	}

	qsort(lines.line,lines.nL,sizeof(*lines.line),cmpLine);
	for(int i=0;i<lines.nL;i++)
	{
                        printf("%s %s %lf %d %s\n", lines.line[i].name,lines.line[i].id,lines.line[i].price,lines.line[i].stocks,lines.line[i].description);
	}
	return 0;
}
