//*****************

#include<stdio.h>
#include<ctype.h>

#define MAXTOK 256


//figure out what this prog does

static char inbuff[MAXTOK + 1];

char* getwords(FILE *inf)
{

	int c, count = 0;

	do
	{
	   c = getc(inf);
	} while (isspace(c));

	if (c == EOF)
		return(NULL);

	if (!isalnum(c))
		inbuff[count++] = c;
	else 
	{
		do{
		   if(count< MAXTOK)
			inbuff[count++] = c;
		   c = getc(inf);
		} while (isalnum(c));
		ungetc(c, inf);    //push back one character
	}


	inbuff[count] = '\0';
	
	//printf("%s\n", inbuff);
	return (inbuff);
}

int main() {
	FILE *fp=fopen("ungetc-demo.txt", "r");
	while(getwords(fp))
		printf("%s\n", inbuff);
}

