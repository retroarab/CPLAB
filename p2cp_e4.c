#include <stdio.h>
#include <stdlib.h>

typedef struct header{
	int n;
	char s[101];
}h;

typedef struct header_all{
	h  * lines;
	int nL;
}h_all;

int cmpLines(const void* p1, const void*  p2)
{
	const h l1=*(h*)p1;
	const h l2=*(h*)p2;
	return(l1.n>l2.n);
}

h_all readFile(FILE * f)
{
	int nL=0;
	h* pass=malloc(sizeof(h_all));
	if(!pass)
	{
		return (h_all){NULL,0};
	}
	h curent;
	while(fscanf(f," <h%d> %[^<] %*s ",&curent.n,curent.s)==2)
	{
		h * aux= realloc(pass,(nL+1)*sizeof(h));
		if(!aux)
		{
			free(pass);
			return (h_all){NULL,0};
		}
		pass=aux;
		pass[nL++]=curent;
	}
	return(h_all){pass,nL};
}



int main(int argc, char* argv[])
{
	if(argc!=2)
	{
		return 0;
	}
	FILE * f= fopen(argv[1],"r");
	if(!f)
	{
		return 0;
	}
	h_all r=readFile(f);
	qsort(r.lines,r.nL,sizeof(*r.lines),cmpLines);
	for(int i=0;i<r.nL;i++)
	{
		printf("%s \n",r.lines[i].s);
	}
}

