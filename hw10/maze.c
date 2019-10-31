#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include "maze.h"


Maze* malloc_maze(int num_rows,int num_cols)
{
	Maze* maze = malloc(sizeof(Maze));
	maze->cells = malloc(sizeof(*(maze->cells)) * num_rows);
	maze->num_rows = num_rows;
	maze->num_cols = num_cols;
	if(maze->cells == NULL)
	{
		return NULL;
	}
	for (int i = 0; i < num_rows; i++ )
	{
		maze->cells[i] = malloc(sizeof(*(maze->cells[i])) * num_cols);
		
		if(maze->cells[i] == NULL)
        	{
			for(int k = 0; k < i; k++)
			{
				free(maze->cells[k]);
			}
			free(maze->cells);
			free(maze);
                	return NULL;
        	}

	}
	return maze;
}


void free_maze(Maze* maze)
{
	for (int i = 0; i < (maze->num_rows); i++)
	{
		free(maze->cells[i]);
	}
	free(maze->cells);
	free(maze);
}


Maze* read_maze(FILE* fp)
{
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
	fseek(fp, 0L, SEEK_SET);
	Maze* maze = malloc_maze(rows,columns);
	char ch = 0;        
	for(int r = 0; r < rows; r++)
	{
		for(int c = 0; c <= columns; c++)
                {
			ch = fgetc(fp);
			if (ch != '\n' && ch != EOF)
			{
                        	maze->cells[r][c] = ch;
			}
                }
	}
	return maze;
}

bool write_maze(const char* filename,const Maze* maze)
{
	int rows = maze->num_rows;
	int columns = maze-> num_cols;
	FILE *fp = fopen(filename, "w");
	if (fp == NULL)
	{
		return false;
	}
	for(int r = 0; r < rows; r++)
	{
		for(int c = 0; c < columns; c++)
		{
			fputc(maze->cells[r][c],fp);
		}
		fputc('\n',fp);
	}
	fclose(fp);
	return true;
}

Maze* make_taller(const Maze* orig)
{
	int rows = (orig->num_rows * 2) - 1;
	int columns = orig->num_cols;	
	Maze* maze = malloc_maze(rows,columns);

	for(int r = 0; r < rows; r++)
                {
                        for(int c = 0; c < columns; c++)
                        {
				if(r < orig->num_rows)
				{
                                	maze->cells[r][c] = orig->cells[r][c];
				}
				
				else
				{
                                	maze->cells[r][c] = orig->cells[r - (orig->num_rows - 1)][c];
				}
                        }
                }

	return maze;
}

Maze* make_wider(const Maze* orig)
{
	int rows = orig->num_rows;
        int columns = (orig->num_cols * 2) - 1;
        Maze* maze = malloc_maze(rows,columns);

	int mid_row = rows / 2;
        int mid_column = columns / 2;
	
	for(int r = 0; r < (orig->num_rows); r++)
                {
                        for(int c = 0; c < columns; c++)
                        {       
                                if(c < orig->num_cols)
                                {       
                                        maze->cells[r][c] = orig->cells[r][c];
                                }
                                
                                else
                                {
                                        maze->cells[r][c] = orig->cells[r][(columns-1) - c];
                                }
                        }
                }
        maze->cells[mid_row][mid_column] = PATH;

	while(maze->cells[mid_row][mid_column - 1] == WALL && maze->cells[mid_row - 1][mid_column] == WALL && maze->cells[mid_row + 1][mid_column] == WALL)
	{
		maze->cells[mid_row][mid_column - 1] = PATH;
		mid_column--;
	}

	mid_column = columns / 2;
	while(maze->cells[mid_row][mid_column + 1] == WALL && maze->cells[mid_row - 1][mid_column] == WALL && maze->cells[mid_row + 1][mid_column] == WALL)
        {
                maze->cells[mid_row][mid_column + 1] = PATH;
        	mid_column++;
	}

        return maze;
}

