#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include "maze.h"

Maze* _malloc_maze(int num_rows,int num_cols);
void _free_maze(Maze* maze);
Maze* _read_maze(FILE* fp);
bool _write_maze(const char* filename,const Maze* maze);

static bool is_path(Maze *maze, int row, int col)
{
	if ((row >= 0) && (row < maze->n_row))
	{
		if ((col >= 0) && (col < maze->n_col)) 
		{
			return maze->maze_array[row][col] == PATH;
     		}
   	}
	return false;
}

/* given a maze, current row (curr),                                     */
/* current column (curc), destination row (drow), destination col (dcol) */
/* current distance from source, determine the where to explore from the */
/* current location                                                      */
/* a recursive function: from the current location, try 'N', 'S', 'E',   */
/* 'W' locations one at a time if the attempt is successful, write the   */
/* direction in the file                                                 */

static int _pathfinder_helper(Maze *maze, int curr, int curc, int endr, int endc,
                            int count, FILE *dfptr)
{
   // you may uncomment this and use the output here to trace the function
   // with sample5.pdf
   // printf("(%d, %d), %d\n", curr, curc, count);
	maze->maze_array[curr][curc] = VISITED;
	if ((curr == endr) && (curc == endc)) 
	{ // reach the destination 
		int i;
		for (i = 0; i < count; i++) 
		{ // create enough space in file
			fputc(VISITED, dfptr);
		}
		return count;
	}

    int foundN = -1;
    int foundE = -1;
    int foundW = -1;
    int foundS = -1;
	if (is_path(maze, curr-1, curc)) 
	{
		foundN = _pathfinder_helper(maze, curr-1, curc, endr, endc, count+1, dfptr);
	}
	if (is_path(maze, curr+1, curc)) 
	{
		foundS = _pathfinder_helper(maze, curr+1, curc, endr, endc, count+1, dfptr);
	}
	if (is_path(maze, curr, curc+1)) 
	{
		foundE = _pathfinder_helper(maze, curr, curc+1, endr, endc, count+1, dfptr);

	}
	if (is_path(maze, curr, curc-1)) 
	{
		foundW = _pathfinder_helper(maze, curr, curc-1, endr, endc, count+1, dfptr);
	}

//REPEAT
    int dir[4] = {foundN, foundS, foundE, foundW};
    int random = INT_MAX;
    
    for(int i = 0; i < 4; i++)
    {
       if(dir[i] < random)
       {
           random = dir[i];
       }
    }
    maze->maze_array[curr][curc] = PATH;
    if (is_path(maze, curr-1, curc))
    {
        foundN = _pathfinder_helper(maze, curr-1, curc, endr, endc, count+1, dfptr);
        		if (foundN != -1)
        		{
        			fseek(dfptr, -1, SEEK_CUR); // go back one position
        			fputc('N', dfptr);
        			fseek(dfptr, -1, SEEK_CUR); // go back one position
        return foundN;
        	}
    }
    if (is_path(maze, curr+1, curc))
    {
        foundS = _pathfinder_helper(maze, curr+1, curc, endr, endc, count+1, dfptr);
        		if (foundS != -1)
            	{
        			fseek(dfptr, -1, SEEK_CUR); // go back one position
        			fputc('S', dfptr);
        			fseek(dfptr, -1, SEEK_CUR); // go back one position
        return foundS;
        		}
    }
    if (is_path(maze, curr, curc+1))
    {
        foundE = _pathfinder_helper(maze, curr, curc+1, endr, endc, count+1, dfptr);
        		if (foundE != -1)
        		{
        			fseek(dfptr, -1, SEEK_CUR); // go back one position
                  fputc('E', dfptr);
        			fseek(dfptr, -1, SEEK_CUR); // go back one position
        return foundE;
        		}
    }
    if (is_path(maze, curr, curc-1))
    {
        foundW = _pathfinder_helper(maze, curr, curc-1, endr, endc, count+1, dfptr);
        		if (foundW != -1)
        		{
        			fseek(dfptr, -1, SEEK_CUR); // go back one position
        			fputc('W', dfptr);
                    fseek(dfptr, -1, SEEK_CUR); // go back one position
        return foundW;
        		}
    }

    


		return -1;
}

/* this is a function implemented by the instructor to illustrate           */
/* how to use a recursive function to go from the left-most top entrance to */
/* the right-most bottom exit of a maze.  The function will print the       */
/* directions taken to reach the bottom exit, without visiting a location   */
/* twice.  Note that the recursion may visit a location a few times         */
/* Given three filenames, first one is a given maze, the second one is to   */
/* be written with the directions, the third is the explored maze           */
/* If the maze file does not exist, the function immediately return -1 and  */
/* do nothing else                                                          */
/* the directions are in the form of a series of characters                 */
/* 'N', 'S', 'E', 'W', without spacing (and without the quotes).            */
/* There should be just a single line, without a terminating newline        */
/* character. In other words, to the vi editor, it is an incomplete file    */
/* you are to assume that you start from the top-most, left-most entry      */
/* of the maze.  Therefore, the first direction is always 'S'               */
/* similarly, the last direction is always 'S'                              */
/* the returned value should be the number of steps taken to reach          */
/* the right-most bottom exit.  It is typically not the shortest distance   */
/* Note that the maze can be generated by amaze, or some combinations of    */
/* the maze expansion functions that you have written in PE08               */
/* you may assume that the maze file, if it exists, is in the correct format*/

int find_path_from_top_entrance_to_bottom_exit(char *maze_file, char *directions_file, char *visited_file)
{
	FILE *mfptr = fopen(maze_file, "r");
	if (mfptr == NULL) 
	{
		return -1;
	}
   
   /* read the maze from mfptr */

	Maze *maze = _read_maze(mfptr);
	fclose(mfptr);
	if (maze == NULL) 
	{
		return -1;
	}
   
   /* find the starting location, the top-most, left-most opening */
	int startr, startc;
	startr = 0;
	for (startc = 0; startc < maze->n_col; startc++) 
	{
		if (maze->maze_array[startr][startc] == PATH) 
		{
			break;
		}
	}

   /* find the ending location, the bottom-most, right most opening */
	int endr, endc;
	endr = maze->n_row-1;
	for (endc = maze->n_col-1; endc >= 0; endc--) 
	{
		if (maze->maze_array[endr][endc] == PATH) 
		{
			break;
		}
	} 

   // no starting location, deallocate and return 
	if (startc == maze->n_col) 
	{
		_free_maze(maze);
		return -1;
	}
   // no ending location, deallocate and return 
	if (endc == -1) 
	{
		_free_maze(maze);
		return -1;
	}

	FILE *dfptr = fopen(directions_file, "w");
	if (dfptr == NULL) 
	{
		_free_maze(maze);
		return -1;
	}
	int steps = _pathfinder_helper(maze, startr, startc, endr, endc, 0, dfptr);
	_write_maze(visited_file, maze);
	fclose(dfptr);
	_free_maze(maze);
	return steps;
}

   //HELPER FUNCTIONS COMING THROUGH

Maze* _malloc_maze(int num_rows,int num_cols)
{       
        Maze* maze = malloc(sizeof(Maze));
        maze->maze_array = malloc(sizeof(*(maze->maze_array)) * num_rows);
        maze->n_row = num_rows;
        maze->n_col = num_cols;
        if(maze->maze_array == NULL)
        {       
                return NULL;
        }
        for (int i = 0; i < num_rows; i++ )
        {       
                maze->maze_array[i] = malloc(sizeof(*(maze->maze_array[i])) * num_cols);
                
                if(maze->maze_array[i] == NULL)
                {       
                        for(int k = 0; k < i; k++)
                        {       
                                free(maze->maze_array[k]);
                        }
                        free(maze->maze_array);
                        free(maze);
                        return NULL;
                }
        
        }
        return maze;
}


void _free_maze(Maze* maze)
{       
        for (int i = 0; i < (maze->n_row); i++)
        {       
                free(maze->maze_array[i]);
        }
        free(maze->maze_array);
        free(maze);
}

Maze* _read_maze(FILE* fp)
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
        Maze* maze = _malloc_maze(rows,columns);
        char ch = 0;
        for(int r = 0; r < rows; r++)
        {
                for(int c = 0; c <= columns; c++)
                {
                        ch = fgetc(fp);
                        if (ch != '\n' && ch != EOF)
                        {
                                maze->maze_array[r][c] = ch;
                        }
                }
        }
        return maze;
}

bool _write_maze(const char* filename,const Maze* maze)
{
        int rows = maze->n_row;
        int columns = maze-> n_col;
        FILE *fp = fopen(filename, "w");
        if (fp == NULL)
        {
                return false;
        }
        for(int r = 0; r < rows; r++)
        {
                for(int c = 0; c < columns; c++)
                {
                        fputc(maze->maze_array[r][c],fp);
                }
                fputc('\n',fp);
        }
        fclose(fp);
        return true;
}


int dfs_shortest_path_directions(char *maze_file, char *directions_file,
                        Coord source, Coord destination)
{
    
	return -1;
}

int simulate_movement(char *maze_file, char *directions_file, char *visited_file,
                      Coord source, Coord destination)
{
    FILE* mazefile = fopen(maze_file, "r");
    Maze* maze = _read_maze(mazefile);
    FILE* directionsfile = fopen(directions_file, "r");
    
    if (mazefile == NULL)
    {
        return -1;
    }
    
    if (maze == NULL)
    {
        return -1;
    }
    
    if (directionsfile == NULL)
    {
        return -1;
    }

    int startrow = source.row;
    int startcol = source.col;
    
    int direction = 0;
    int moves = 1;
    
    maze->maze_array[startrow][startcol] = VISITED;

    while((direction = fgetc(directionsfile)) != EOF)
    {
        if(direction == 'N')
        {
            maze->maze_array[startrow - 1][startcol] = VISITED;
            startrow--;
        }
    
        if(direction == 'E')
        {
            maze->maze_array[startrow][startcol + 1] = VISITED;
            startcol++;
        }

        if(direction == 'W')
        {
            maze->maze_array[startrow][startcol - 1] = VISITED;
            startcol--;
        }

        if(direction == 'S')
        {
            maze->maze_array[startrow + 1][startcol] = VISITED;
            startrow++;
        }
    }
    bool writemaze = _write_maze(visited_file,maze);
    if (writemaze == false)
    {
        return -1;
    }
    _free_maze(maze);
    fclose(mazefile);
    fclose(directionsfile);
    
	return moves;
}

