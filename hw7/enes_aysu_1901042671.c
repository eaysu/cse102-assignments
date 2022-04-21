#include <stdio.h>
#define ROW 512 /* max row */
#define COLUMN 512 /* max column */

void fill_array(FILE *inp, int terrain[ROW][COLUMN], int i, int j, int water_level); /* function declaretions */
void enumerate_island(int terrain[ROW][COLUMN], int i, int j, int number);
void rec_func(int terrain[ROW][COLUMN], int i, int j, int number);
void print_coordinates(FILE *out, int terrain[ROW][COLUMN], int i, int j, int number);

void fill_array(FILE *inp, int terrain[ROW][COLUMN], int i, int j, int water_level)
{
    for(i = 0;i < ROW;i++) /* fill the array with terrain values from input.txt */
    {
        for(j = 0;j < COLUMN;j++)
        {
            fscanf(inp, "%d", &terrain[i][j]);
        }
    }

    for(i = 0;i < ROW;i++) /* if the terrain level is under the water level the array stores 0 */
    {
        for(j = 0;j < COLUMN;j++)
        {
            if(terrain[i][j] > water_level)
            {
                terrain[i][j] = -1; /* if the terrain level is above the water level the array changes the value with -1 */   
            }
            else
            {
                terrain[i][j] = 0; /* if the terrain level is under the water level the array changes the value with 0 */
            }   
        }
    }
}

void enumerate_island(int terrain[ROW][COLUMN], int i, int j, int number)
{
    for(i = 0;i < ROW;i++)
    {
        for(j = 0;j < COLUMN;j++)
        {
            if(terrain[i][j] == -1) /* if the value is -1, it can be island */
            {
               rec_func(terrain, i, j, number); /* the function that enumerates the islands respectively */
               
               if(terrain[i][j] == -1) /* if the value is still -1 after recursion function, it is single-point island */
               {
                   terrain[i][j] = number;
               }
               number++; 
            }    
        }
    }
}

void rec_func(int terrain[ROW][COLUMN], int i, int j, int number) /* recursion function */
{
        if(i != ROW - 1 && terrain[i + 1][j] == -1) /* if statements notice that the process remains inside the matrix during the numbering process */
        {
            terrain[i + 1][j] = number;
            rec_func(terrain, i + 1, j, number);
        }   
        if(i != 0 && terrain[i - 1][j] == -1)
        {
            terrain[i - 1][j] = number;
            rec_func(terrain, i - 1, j, number);
        }
        if(j != COLUMN - 1 && terrain[i][j + 1] == -1)
        {
            terrain[i][j + 1] = number;
            rec_func(terrain, i, j + 1, number);
        }
        if(j != 0 && terrain[i][j - 1] == -1)
        {
            terrain[i][j - 1] = number;
            rec_func(terrain, i, j - 1, number);
        }  
}

void print_coordinates(FILE *out, int terrain[ROW][COLUMN], int i, int j, int number)
{
    for(i = 0;i < ROW;i++)
    {
        for(j = 0;j < COLUMN;j++)
        {
            if(terrain[i][j] == number) /* prints a coordinate from each island to output.txt*/
            {
                fprintf(out, "%d_coordinate%d %d_coordinate%d\n", i, number, j, number);
                number++;
            }
        }
    }
}

int main()
{
    int i, j;
    int number = 1;
    int water_level = 0;
    int terrain[ROW][COLUMN];   
    
    FILE *inp; /* file pointer for input.txt */
    inp = fopen("input.txt", "r");
    
    fscanf(inp, "%d", &water_level);
    fill_array(inp, terrain, i, j, water_level);
    fclose(inp); /* close the file */
    
    enumerate_island(terrain, i, j, number);

    FILE *out; /* file pointer for output.txt */
    out = fopen("output.txt", "w");

    print_coordinates(out, terrain, i, j, number);
    fclose(out); /* close the file */

    return 0;
}    
