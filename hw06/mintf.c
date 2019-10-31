#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "mintf.h"

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
return;
}




void mintf(const char *format, ...)
{
   va_list arg;
   va_start(arg, format);

   int index;
   while(format[index] != '\0')
   {
      if(format[index] == '%' && format[index+1] == 'd')
      {
	   int value = va_arg(arg, int);
	   print_integer(value, 10, "");
	   index+=2;
      }
      	
      
      if(format[index] == '%' && format[index+1] == 'x')
      {
         
	   int value = va_arg(arg, int);
	   print_integer(value, 16, "0x");
	   index+=2;
      }

      if(format[index] == '%' && format[index+1] == 'b')
      {
	   int value = va_arg(arg, int);
	   print_integer(value, 2, "0b");
	   index+=2;

      }

      if(format[index] == '%' && format[index+1] == '$')
      {
	   int value = va_arg(arg, int);
	   print_integer(value, 10, "$");
	   index+=2;
      
      }

      if(format[index] == '%' && format[index+1] == 's')
      {
	   char* value = va_arg(arg, char*);
           int i =0;
	   while (value[i] != '\0')
           {
           fputc(value[i], stdout);
           i++;
           }
	   index+=2;

      }

      if(format[index] == '%' && format[index+1] == 'c')
      {
	   int value = va_arg(arg, int);
	   fputc(value, stdout);
	   index+=2;

      }

      if((format[index] == '%' && format[index+1] == '%') ||(format[index] == '%' && format[index+1] == ' ') )
      {
	   fputc('%', stdout);
	   
	   index+=2;

      }
   index++;	
   }	
return;
}
