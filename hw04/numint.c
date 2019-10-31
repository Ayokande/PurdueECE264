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
// This is the only file you have to include 

double simpson_numerical_integration(Integrand intg_arg)
{
   double integral = 0.0;
   double lower_limit = intg_arg.lower_limit; 
   int n_intervals = intg_arg.n_intervals;
   double delta_x = ((intg_arg.upper_limit - lower_limit) / n_intervals);
   double upper_limit = lower_limit + delta_x;

for (int i = 0; i < n_intervals; i++)
{
   integral += ((delta_x) / 6) * (intg_arg.func_to_be_integrated(lower_limit) +
		 (4 * intg_arg.func_to_be_integrated((upper_limit + lower_limit) / 2)) 		+ intg_arg.func_to_be_integrated(upper_limit));
   lower_limit =intg_arg.lower_limit+(delta_x * (i+1));
   upper_limit = intg_arg.lower_limit+(delta_x *(i+2));
}
   integral = -1 * integral;

   return integral;
}
