#include <stdio.h>
#include <stdlib.h>
#include "aux.h"
// do not change this part, if you do, your code may not compile
//
/* test for structure defined by student */
#ifndef NTEST_STRUCT 
#include "numint.h"
#else
#include "numint_key.h"
#endif /* NTEST_STRUCT */
//
// do not change above this line, if you do, your code may not compile

      
int main(int argc, char * * argv)
{

if (argc != 5)
{
   return EXIT_FAILURE;
}

   Integrand intg_arg; 
   
   intg_arg.upper_limit = atof(argv[2]);
   intg_arg.lower_limit = atof(argv[3]);
   intg_arg.n_intervals = atoi(argv[4]);

if (intg_arg.n_intervals < 1)
{
   intg_arg.n_intervals = 1;
}

if(argv[1][0] == '1' && argv[1][1] == '\0')
{
   intg_arg.func_to_be_integrated = unknown_function_1;
}

else if(argv[1][0] == '2' && argv[1][1] == '\0')
{
   intg_arg.func_to_be_integrated = unknown_function_2;
}

else if(argv[1][0] == '3' && argv[1][1] == '\0') 
{
   intg_arg.func_to_be_integrated = unknown_function_3;
}

else
{
  return EXIT_FAILURE;
}


   double integral = simpson_numerical_integration(intg_arg);

   printf("%.10e\n", integral);
   return EXIT_SUCCESS;
}
