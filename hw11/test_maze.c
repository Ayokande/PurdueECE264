#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "maze.h"

int find_path_from_top_entrance_to_bottom_exit(char *maze_file, char *directions_file, char *visited_file);

int main(int argc, char* argv[]) 
{
	if (argc < 2) 
	{
		return EXIT_FAILURE;
	}
  
	if ((strcmp("-s", argv[1]) != 0) && (strcmp("-m", argv[1]) != 0))
	{
        return EXIT_FAILURE;
    }
    
	if(strcmp("-s", argv[1]) == 0)
	{
        if(argc != 9)
        {
            return EXIT_FAILURE;
        }
        Coord source;
        Coord destination;
        char* error;
        source.row = strtol(argv[5], &error, 10);
        
        if (*error != '\0')
        {
            fprintf(stderr, "All shouls be integer figures!");
            return EXIT_SUCCESS;
        }
        
        source.col = strtol(argv[6], &error, 10);
        if (*error != '\0')
        {
            fprintf(stderr, "All shouls be integer figures!");
            return EXIT_SUCCESS;
        }
        
        destination.row = strtol(argv[7], &error, 10);
        if(*error != '\0')
        {
            fprintf(stderr, "All shouls be integer figures!");
            return EXIT_SUCCESS;
        }
        destination.col = strtol(argv[8], &error, 10);
        
        if(*error != '\0')
        {
            fprintf(stderr, "All should be integer figures!");
            return EXIT_SUCCESS;
        }
        
        int total_number_directions = simulate_movement(argv[2], argv[3], argv[4], source, destination);
        printf("total_number: %d\n", total_number_directions);
    }
    
    if(strcmp("-m", argv[1]) == 0)
    {
        if(argc != 8)
        {
            return EXIT_FAILURE;
        }
        Coord source;
        Coord destination;
        char* error;
        source.row = strtol(argv[4], &error, 10);
        if(*error != '\0')
        {
            fprintf(stderr, "All should be integer figures!");
            return EXIT_SUCCESS;
        }
        
        source.col = strtol(argv[5], &error, 10);
        if(*error != '\0')
        {
            fprintf(stderr, "All should be integer figures!");
            return EXIT_SUCCESS;
        }
        destination.row = strtol(argv[6], &error, 10);
        
        if(*error != '\0')
        {
            fprintf(stderr, "All should be integer figures!");
            return EXIT_SUCCESS;
        }
        destination.col = strtol(argv[7], &error, 10);
        
        if(*error != '\0')
        {
            fprintf(stderr, "All should be integer figures!");
            return EXIT_SUCCESS;
        }
        
        int shortest_path = dfs_shortest_path_directions(argv[2], argv[3], source, destination);
        printf("shortest_path: %d\n", shortest_path);
    }
    return EXIT_SUCCESS;
}
