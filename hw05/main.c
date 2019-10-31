#include <stdio.h>
#include <stdlib.h>
#include "aux.h"
#include "util.h"
#include "fourier.h"

int main(int argc, char ** argv) 
{

   if (argc != 6)
   {
      return EXIT_FAILURE;
   }

   Integrand integrand =
   {
      .upper_limit = atof(argv[3]),  // TODO: change to the real value
      .lower_limit = atof(argv[2]), // TODO: change to the real value
      .n_intervals = atoi(argv[4]),    // TODO: change to the real value

   };


   if(argv[1][0] == '1' && argv[1][1] == '\0')
   {  
      integrand.func_to_be_integrated = unknown_function_1;
   }

   else if(argv[1][0] == '2' && argv[1][1] == '\0')
   {
      integrand.func_to_be_integrated = unknown_function_2;
   }

   else if(argv[1][0] == '3' && argv[1][1] == '\0')
   {
      integrand.func_to_be_integrated = unknown_function_3;
   }
   else
   {
      return EXIT_FAILURE;
   }

   int n_terms = atoi(argv[5]);         // TODO: change to the real value
   if (n_terms < 1)
    {
    n_terms = 1; 
    }

   Fourier fourier = 
   {
	   .intg      = integrand,
	   .n_terms   = n_terms,
	   .a_i       = malloc(sizeof(*fourier.a_i) * n_terms),
	   .b_i       = malloc(sizeof(*fourier.b_i) * n_terms)
   };

   // If allocation of fourier.a_i and/or fourier.b_i failed, then free the
   // one that didn't fail and then exit with EXIT_FAILURE.
   if (fourier.a_i == NULL || fourier.b_i == NULL) 
   {
      free(fourier.a_i);  // free(..) has not effect if its argument is NULL
      free(fourier.b_i);
      return EXIT_FAILURE;
   }

   fourier_coefficients(fourier);

   print_fourier_coefficients(fourier.a_i, fourier.b_i, 
                              fourier.n_terms);

   free(fourier.a_i);
   free(fourier.b_i);

   return EXIT_SUCCESS;
} 
