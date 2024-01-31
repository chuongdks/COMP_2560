#include <stdio.h> 

//this program helps you understand char, signed/unsigned char, and int

int main(void)
{
  int i = -1;
  signed char sc = 0xff;
  unsigned char usc = 0xff;
    
  printf ("Comparing %x with %x\n", i, sc);
  if (i == sc)    puts("i == sc");
  else            puts("i != sc");

  putchar ('\n');
  printf ("Comparing %x with %x\n", i, usc);

  if (i == usc)   puts("i == usc");
  else            puts("i != usc");

  return 0;
}
