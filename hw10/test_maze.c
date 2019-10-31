#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include "maze.h"

int main (int argc, char** argv)
{
	FILE* fp = fopen("sample.2.7x9", "r");	
	Maze* maze = read_maze(fp);
	
	 for(int r = 0; r < (maze->num_rows); r++)
        {
                for(int c = 0; c < (maze->num_cols); c++)
                {
			printf("%c ",maze->cells[r][c]);
                }
		printf("\n");
        }
	Maze* tmaze = make_taller(maze);
	for(int r = 0; r < (tmaze->num_rows); r++)
        {
                for(int c = 0; c < (tmaze->num_cols); c++)
                {
                        printf("%c ",tmaze->cells[r][c]);
                }
                printf("\n");
        }
	Maze* wmaze = make_wider(maze);
        for(int r = 0; r < (wmaze->num_rows); r++)
        {
                for(int c = 0; c < (wmaze->num_cols); c++)
                {
                        printf("%c ",wmaze->cells[r][c]);
                }
                printf("\n");
        }

	write_maze("newsample.2.7x9",maze);	
	fclose(fp);
	free_maze(maze);
	free_maze(tmaze);
	free_maze(wmaze);

	Maze* test = malloc_maze(4,2);
	printf("%d\n", test->num_rows);
	printf("%d", test->num_cols);
	free_maze(test);
	return EXIT_SUCCESS;
}
