#include <stdio.h>
#include "maze.h"
int main(){
  FILE * fp = fopen("sample.2.7x9", "r");

  int  num_rows = 0;
  int  num_cols= 0;

  find_maze_dimensions( fp,  &num_rows, &num_cols);
  int openLoc = find_opening_location( fp);
  int location = count_path_locations( fp);
  char type = get_location_type( fp,2 ,2);
  int sizeNew = represent_maze_in_one_line( "newsample.2.7x9",  fp);

  printf(" Rows = %d\n Columns = %d\n Opening location = %d\nLocation = %d\nType = %c\nNew Size = %d\n", num_rows, num_cols,openLoc, location, type, sizeNew);

  fclose(fp);
return 0;

}

