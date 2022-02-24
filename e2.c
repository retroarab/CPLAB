#include <stdio.h>
#include <stdlib.h>
#include <string.h>
typedef struct values{
	char key[51];
	char * value;
}v;

typedef struct values_all{
	v * lines;
	int nL;
}v_all;

char* readline(FILE* f) {

    char buffer;
    char *command = NULL;
    char *tmp = NULL;
    size_t size = 0;
    int last = 0;

    while ( 1 ){ //listen indefinitely for characters

	//the size of buffer required to hold the command( grows dynamically )
	size = size + sizeof( char );

	//allocate space for the new character
	tmp = realloc( command, size );

	if( tmp == NULL  ){//realloc failed
	    free( command );
	    return NULL;
	}
	else{ //get and store the character
	    command = tmp;
	    if( ( buffer = getc(f) ) != '\n' && buffer != "}" )
		command[ last++ ] = buffer;
	    else break; //break if carriage return is entered
	}
    }

    //a string is always null terminated
    command[ last -1 ] = '\0';

    return command;
}

v_all readf(FILE * f)
{
	v * linie=malloc(sizeof(v));
	v curent;
	int nL=0;
	while((fscanf(f,"{%s : ",curent.key))==1)
	{
		curent.value=readline(f);
		v * aux= realloc(linie,(nL+1)*sizeof(v));
		if(!aux)
		{
			return (v_all){NULL,0};
		}
		linie=aux;
		linie[nL++]=curent;

	}
	return(v_all){linie,nL};
}

int cmpLines(const void* l1, const void* l2)
{
	const v p1= *(v*) l1;
	const v p2= *(v*) l2;
	if(strlen(p1.key)==strlen(p2.key))
	{
		return strcmp(p1.key,p2.key);
	}
	else
		return strlen(p1.key)>strlen(p2.key);
}

int main(int argc, char* argv[])
{
	if(argc!=2)
	{
		printf("Error!");
		return 0;
	}
	FILE *  f=fopen(argv[1],"r");
	if(!f)
	{
		return 0;
	}
	v_all r=readf(f);
	qsort(r.lines,r.nL,sizeof(*r.lines),cmpLines);
	for(int i=0;i<r.nL;i++)
	{
		printf("%s : %s\n",r.lines[i].key,r.lines[i].value);
	}
	return 0;

}
