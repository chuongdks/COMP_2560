#include <stdio.h>

int main (void)
{
	FILE *in, *out;

	struct pirate {
		char name[100]; /* real name */
		unsigned long pounds; /* in pounds sterling */
		unsigned int beard_len; /* in inches */
	} p, blackbeard = { "Edward Teach", 950, 48 };
	
	struct strange{
		int i;
		float j;
	} test;
	
	out = fopen ("pirate.data", "w");
	
	if (!out) {
		perror ("fopen");
		return 1;
	}
	//not casting for the first argument of fwrite....
	if (!fwrite (&blackbeard, sizeof (struct pirate), 1, out)) {
		perror ("fwrite");
		return 1;
	}
	

	if (fclose (out)) {
		perror ("fclose");
		return 1;
	}
	
	in = fopen ("pirate.data", "r");
	if (!in) {
		perror ("fopen");
		return 1;
	}
	if (!fread (&p, sizeof (struct pirate), 1, in)) {
		perror ("fread");
		return 1;
	}

	printf ("name=\"%s\" booty=%lu beard_len=%u\n",
			p.name, p.pounds, p.beard_len);
	//line 48-55 was inspired by a student question in winter 2023
	rewind(in); 
	
	int rt=fread(&test, sizeof(struct strange), 1, in);
	
	//printf("\nrt=%d\n", rt);

	printf ("test.i=%d, test.j=%f\n",test.i, test.j);
	
	if (fclose (in)) {
		perror ("fclose");
		return 1;
	}
	
	return 0;
}
