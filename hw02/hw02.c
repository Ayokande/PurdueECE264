#include <stdio.h>
#include "hw02.h"

void print_integer(int n, int radix, char* prefix)
{
if(n < 0)
{
n = 0 - n;
fputc('-', stdout);
}


int idx_in_s = 0;
while(prefix[idx_in_s] != '\0')
{
   fputc(prefix[idx_in_s], stdout);
   idx_in_s += 1;
}

if (n == 0)
{
   fputc('0', stdout);
}

if (n == radix)
{
   fputc('1', stdout);
   fputc('0', stdout);
}

int val1 = n;
int power = 1;
int index =0;
while (power < val1)
{
   power *= radix;  
   index++;
}
   index--;

while(index > 0)
{
   power /= radix;
   int value = val1 / power;

   if (value > 9)
   {
      fputc('W' + value, stdout);
   }
   else if (value <= 9 && value != 0)
   {
      fputc('0' + value, stdout);
   }
 else if (value ==0  )
{
fputc('0',stdout);
}

   val1 -= (power * value);



index--;
}

if (val1 > 9)
{
   fputc('W' + val1, stdout);
}
 if (val1 < 10) 
{
   
fputc('0' + val1, stdout);
}

}

