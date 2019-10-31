#include <stdio.h>
#include <stdlib.h>
#include "maze.h"

void find_maze_dimensions(FILE * fp, int * a_num_rows, int * a_num_cols)
{
    *a_num_rows = *a_num_cols = 0;
    int rows = 0;
    int columns = 0;
  
    fseek(fp, 0L, SEEK_SET);
    while(!feof(fp)) 
    {
      	if(fgetc(fp) == '\n')
        {
        	rows++;  
        }  
    }  
    
    fseek(fp, 0L, SEEK_SET);  
    while(fgetc(fp) != '\n') 
    {
    	columns++;  	 
    }  
  
	*a_num_rows = rows;
        *a_num_cols = columns;    
}

int find_opening_location(FILE * fp)
{
  	int location = 0;
    fseek(fp, 0L, SEEK_SET);
  
    while(fgetc(fp) == WALL) 
    {
    	location++;  	 
    }  
	return location;
}

int count_path_locations(FILE * fp)
{	
  	int path = 0;
    fseek(fp, 0L, SEEK_SET);
   while (!feof(fp))
   {  
     	if(fgetc(fp) == PATH) 
    	{
    		path++;  	 
    	} 	
   }
  
	return path;
}

char get_location_type(FILE * fp, int row, int col)
{
    int columns = 0;
  
    fseek(fp, 0L, SEEK_SET);  
    while(fgetc(fp) != '\n') 
    {
    	columns++;  	 
    }  
  
    int location = (columns * row)+ col;
    fseek(fp, location, SEEK_SET);
    
    if(fgetc(fp) == PATH)
    {
      	return PATH;
    }
	return WALL;
}

int represent_maze_in_one_line(char * filename, FILE * fp)
{
    FILE *fpout = fopen(filename, "w");
    int index = 0;
    fseek(fp, 0L, SEEK_SET);
    while ((index = fgetc(fp)) != EOF) 
    {
        if(index != '\n')
        {
          fputc(index,fpout);
        }
    }  
  
    fseek(fpout, 0L, SEEK_END);
    int size = ftell(fpout);
	return size;
}

