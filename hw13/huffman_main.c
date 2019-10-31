#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define SIZE 256
#include "huffman.h"


int main(int argc, char* argv[]) 
{
    long int value[SIZE] = {0};
    
    FILE *input = fopen(argv[1],"r");
    
    FILE *output1 = fopen(argv[2],"w");
    read_from_file(input, value, output1);
    fclose(input);
    fclose(output1);
    
    
    
	return EXIT_SUCCESS;
}
