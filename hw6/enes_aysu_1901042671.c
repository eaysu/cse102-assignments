/*
**
** the windows ubuntu terminal counts \n's one more than the linux ubuntu terminal 
**
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define L 10 /* max input size */
#define F 0 /* final value */
typedef struct line  
{ 
    char op_name[L];
    char op_result[L]; 
    char op_1[L]; 
    char op_2[L];
}line;

int read_line(FILE* fp, char *filename);
int count_inputs(FILE *fp);
void parse_INPUT(FILE *crc, FILE *inp, int *values, char **input, int set);
void parse_OPERATIONS(FILE *fp, char *filename, line **operations);
int evaluations(FILE *fp, line **operations, int *values, char **input, int j, int ff_value);

int read_line(FILE* fp, char *filename) /* to learn how many rows in the circuit.txt and input.txt */
{
    char ch;
    int count = 0;

    fp = fopen(filename, "r");

    while((ch = fgetc(fp)) != EOF)
    {
        if(ch == '\n') 
        {
            count++;
        }
    }

    fclose(fp); /* close circuit.txt or input.txt */
    return count;
}

int count_inputs(FILE *fp) /* to find how many inputs in the circuit.txt */
{
    char ch;
    int count = 0;

    fp = fopen("circuit.txt", "r");

    while((ch = fgetc(fp)) != '\n')
    {
        if(ch == ' ') /* every space means an input */
        {
            count++;
        }
    }
    fclose(fp); /* close circuit.txt */
    return count;
}

void parse_INPUT(FILE *crc, FILE *inp, int *values, char **input, int set) /* parsing input.txt and INPUT line */
{
    crc = fopen("circuit.txt", "r");
    inp = fopen("input.txt", "r");

    int num, i;
    int count = 0;

    fseek(inp, set, SEEK_SET);
    
    for(i = 0;i < count_inputs(crc);i++) /* parsing and storing one and zeroes */
    {
        fscanf(inp, "%d", &num);
        values[i] = num;
    }
    
    fseek(crc, 5, SEEK_SET);

    for(i = 0;i < count_inputs(crc);i++) /* parsing and storing input identifiers */
    {
        input[i] = malloc(sizeof(char) * L);
        fscanf(crc, "%s", input[i]);
    }

    fclose(inp); /* close input.txt */
    fclose(crc); /* close circuit.txt */
}

void parse_OPERATIONS(FILE *fp, char *filename, line **operations)
{
    int i;
    char ch;
 
    fp = fopen(filename, "r");

    while((ch = fgetc(fp)) != EOF)
    {
        if(ch == '\n')
        {
            break;
        }
    }

    fseek(fp, ftell(fp),SEEK_SET); /* for start parsing after INPUT line */

    for(i = 0;i <(read_line(fp, filename) - 1);i++)
    {
        operations[i] = malloc(sizeof(line)); /* parsing and storing operations into line string */
        
        fscanf(fp, "%s", operations[i] -> op_name);
        fscanf(fp, "%s", operations[i] -> op_result);
        fscanf(fp, "%s", operations[i] -> op_1);
        if(strcmp(operations[i] -> op_name, "AND") == 0 || strcmp(operations[i] -> op_name, "OR") == 0) /* to check unnecessary storing */
        {
            fscanf(fp, "%s", operations[i] -> op_2);
        }
    }
    fclose(fp); /* close circuit.txt */
}

int evaluations(FILE *fp, line **operations, int *values, char **input, int j, int ff_value)
{
    int i, temp1, temp2;
    
    if(strcmp(operations[j] -> op_name, "AND") == 0) /* AND operation */ 
    {
        for(i = 0;i < count_inputs(fp);i++)
        {
            if(strcmp(operations[j] -> op_1, input[i]) == 0)
                temp1 = i;
            else if(strcmp(operations[j] -> op_2, input[i]) == 0)
                temp2 = i;
        }
        values[temp1] = values[temp1] && values[temp2]; /* do and store operation */
        strcpy(input[temp1],operations[j] -> op_result);
    }

    else if(strcmp(operations[j] -> op_name, "OR") == 0) /* OR operation */ 
    {
        for(i = 0;i < count_inputs(fp);i++)
        {
            if(strcmp(operations[j] -> op_1, input[i]) == 0)
                temp1 = i;
            else if(strcmp(operations[j] -> op_2, input[i]) == 0)
                temp2 = i;
        }
        values[temp1] = values[temp1] || values[temp2]; /* do and store operation */
        strcpy(input[temp1],operations[j] -> op_result);
    }

    else if(strcmp(operations[j] -> op_name, "NOT") == 0) /* NOT operation */ 
    {
        for(i = 0;i < count_inputs(fp);i++)
        {
            if(strcmp(operations[j] -> op_1, input[i]) == 0)
                temp1 = i;
        }
        if(values[temp1] == 1)  /* do and store operation */
            values[temp1] = 0;
        else
            values[temp1] = 1;
        strcpy(input[temp1],operations[j] -> op_result);
    }

    else if(strcmp(operations[j] -> op_name, "FLIPFLOP") == 0) /* FLIPFLOP operation */ 
    {
        for(i = 0;i < count_inputs(fp);i++)
        {
            if(strcmp(operations[j] -> op_1, input[i]) == 0)
                temp1 = i;
        }
        if((ff_value == 1 && values[temp1] == 1) || (ff_value == 0 && values[temp1] == 0))
        {
            values[temp1] = 0; /* do and store operation */
            ff_value = 0;
            strcpy(input[temp1],operations[j] -> op_result);
        }
        else
        {
            values[temp1] = 1; /* do and store operation */
            ff_value = 1;
            strcpy(input[temp1],operations[j] -> op_result);
        }
    }
    return ff_value; /* returning the flipflop value to use it again */
}

int main()
{
    FILE *inp;
    FILE *crc;
    char circuit[] = "circuit.txt";
    char inputs[] = "input.txt";
    int i, j;
    int fseek_set = 0;
    int ff_value = 0; /* initial flipflop value */

    line **operations = (line**) malloc(sizeof(line*) * (read_line(crc, circuit) - 1)); /* memory allocations */
    int *values = (int*) malloc(sizeof(int) * count_inputs(crc));
    char **input = (char**) malloc(sizeof(char*) * count_inputs(crc));

    parse_OPERATIONS(crc, circuit, operations);

    for(i = 0;i < read_line(inp, inputs);i++) /* the number of rows in the input.txt will be processed as much as */
    {
        parse_INPUT(crc, inp, values, input, fseek_set);
        fseek_set = 2 * (i + 1) * count_inputs(crc); /* to switch to a lower line in the input.txt */
        
        for(j = 0;j < read_line(crc, circuit) - 1;j++) /* the number of rows in the circuit.txt file will be processed as much as except INPUT line */
        {
            ff_value = evaluations(crc, operations, values, input, j, ff_value);
        }
        printf("%d\n", values[F]); /* printing operation results */
    } 
    return 0;
}