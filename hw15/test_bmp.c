#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bmp.h"

int main(int argc, char** argv)
{
    //Read File function call
    FILE* infptr = fopen("car.bmp","r");
    if(infptr == NULL)
    {
        return EXIT_SUCCESS;
    }
    char* error = NULL;
    BMPImage* picture = read_bmp(infptr,&error);
    fclose(infptr);
    if(picture == NULL)
    {
        if(error != NULL)
        {
            fprintf(stdout,"%s",error);
        }
        free(error);
        return EXIT_SUCCESS;
    }
    
    
    //Write File function call
    FILE* outfptr = fopen("o2.bmp","w");
    BMPImage* crop  = crop_bmp(picture,100,100,100,100,&error);
    bool success = write_bmp(outfptr,crop,&error);
    fclose(outfptr);
    if(crop == NULL)
    {
        if(error != NULL)
        {
            fprintf(stdout,"%s",error);
        }
        free(error);
        
        return EXIT_SUCCESS;
    }
    
    free_bmp(crop);
    free_bmp(picture);
    if(success == false)
    {
        free(error);
        return EXIT_SUCCESS;
    }
    
    
    return EXIT_SUCCESS;
}

