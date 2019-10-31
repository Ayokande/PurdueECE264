#include <math.h>
#include "fourier.h"
#define M_PI 3.141592653589793115997963468544185161590576171875L

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
               (4 * intg_arg.func_to_be_integrated((upper_limit + lower_limit) / 2)) +
               intg_arg.func_to_be_integrated(upper_limit));
   lower_limit =intg_arg.lower_limit+(delta_x * (i+1));
   upper_limit = intg_arg.lower_limit+(delta_x *(i+2));
}
   integral = integral;
   return integral;
}


double simpson_numerical_integration_for_fourier(Integrand intg_arg, int n, 
                                                 double (*cos_sin)(double)) 
{
   double integral = 0.0;
   double lower_limit = intg_arg.lower_limit;
   int n_intervals = intg_arg.n_intervals;
   double delta_x = ((intg_arg.upper_limit - intg_arg.lower_limit) / n_intervals);
   double upper_limit = lower_limit + delta_x;
   double L = ((intg_arg.upper_limit - intg_arg.lower_limit) / 2);
   
   for (int i = 0; i < n_intervals; i++)
   {
      integral += ((delta_x) / 6) *
                  (((intg_arg.func_to_be_integrated(lower_limit)) * cos_sin((n * M_PI * lower_limit) / L)) +
                  ((4 * (intg_arg.func_to_be_integrated((upper_limit + lower_limit) / 2))) * cos_sin((n * M_PI * ((upper_limit + lower_limit) / 2)) / L)) +
                  ((intg_arg.func_to_be_integrated(upper_limit)) * cos_sin((n * M_PI * upper_limit) / L)));
      lower_limit =intg_arg.lower_limit+(delta_x * (i+1));
      upper_limit = intg_arg.lower_limit+(delta_x *(i+2));
   }
  integral =  integral;  
   return integral;
}

void fourier_coefficients(Fourier fourier_arg) 
{
   double L = ((fourier_arg.intg.upper_limit - fourier_arg.intg.lower_limit) / 2);
   fourier_arg.a_i[0] = simpson_numerical_integration(fourier_arg.intg) / L;

   for (int i = 1; i < fourier_arg.n_terms; i++) 
   {
      fourier_arg.a_i[i] =  simpson_numerical_integration_for_fourier(fourier_arg.intg, i, cos) / L;
      fourier_arg.b_i[i] =  simpson_numerical_integration_for_fourier(fourier_arg.intg, i, sin) / L;
   }
}
 
