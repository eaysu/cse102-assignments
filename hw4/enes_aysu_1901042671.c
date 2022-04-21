#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define N 100 /* max length of a user input */
#define M 25 /* max number of parts */

double total_price(char *object); /* function declaretions */
void parsing_function(char *part, int *count, char name_of_parts[M][N], int *num_of_parts);

int main()
{
    char object[N]; /* input array */
    char *objptr;
    double result = 0;

    printf("Define the object:\n"); /* getting input from user */
    fgets(object, N, stdin);

    objptr = strtok(object, "\n"); /* avoiding '\n' character */
    while(objptr != NULL)
    {
        strcpy(object, objptr);
        objptr = strtok(NULL, "\n"); /* converting '\n' symbol to a space */
    }

    result = total_price(object); /* calling the function that calculates the price */

    printf("Total cost of %s is : %.1lf\n", object, result); /* printing the object's name and its price */
    return 0;
}

double total_price(char *object) 
{
    char part[N]; /* parts without '+' symbol */
    char *partptr;
    char name_of_parts[M][N]; /* for holding name of parts */
    char *r_ptr;
    int count[M] = {0}; /* for holding quantity of parts */
    int num_of_parts = 0; /* number of parts */
    int is_it_digit = 1; /* the number that checks to see if the sting is a number */
    double result = 0.0;
    double price = 0.0;
    
    printf("What is %s ?:\n", object);
    fgets(part, N, stdin);

    partptr = strtok(part, "\n"); /* avoiding '\n' character */
    while(partptr != NULL)
    {
        strcpy(part, partptr);
        partptr = strtok(NULL, "\n"); /* converting '\n' symbol to a space */
    }
    
    int i = 0;
    while(i < strlen(part) && is_it_digit == 1) /* the loop that to understand if the string is a number or not */
    {
        if(part[i] <= 57 && part[i] >= 48 || part[i] == 46) /* restriction to ascii values of numbers and dot */
            is_it_digit = 1; /* while the string is a number */
        
        else
            is_it_digit = 0; /* while the string is not a number */
        
        i++;
    }

    if(is_it_digit == 1) 
    {
        result = strtod(part, &r_ptr); /* converting string to double number */
        return result;
    }
        
    else if(is_it_digit == 0)
    {
        parsing_function(part, count, name_of_parts, &num_of_parts); /* calling the function that parses parts into proper type */
        
        for(i = 0;i < num_of_parts;i++)
        {
            price = total_price(name_of_parts[i]); /* recursive part */
            result = result + count[i] * price;
        }

        return result;
    }    
}

void parsing_function(char *part, int *count, char name_of_parts[M][N], int *num_of_parts)
{
    char temp1[M][N];
    char temp2[M][N];
    char *tempptr1;
    char *tempptr2;
    char *endptr;

    int i = 0;
    int j = 0;

    tempptr1 = strtok(part, "+"); /* avoiding '+' symbol */
    while(tempptr1 != NULL)
    {
        strcpy(temp1[i], tempptr1);
        tempptr1 = strtok(NULL, "+"); /* converting '+' symbol to a space */
        i++;
    }

    int m = 0;

    for(j = 0;j < i;j++)
    {
        tempptr2 = strtok(temp1[j], "*"); /* avoiding '*' symbol */
        while(tempptr2 != NULL)
        {
            strcpy(temp2[m], tempptr2);
            tempptr2 = strtok(NULL, "*"); /* converting '*' symbol to a space */
            
            if(m % 2 == 0)
                count[j] = strtod(temp2[m], &endptr); /* if m is even number, temp2 includes quantity of parts */
            
            else if(m % 2 == 1)
                strcpy(name_of_parts[j], temp2[m]); /* if m is odd number, temp2 includes name of parts */

            m++;    
        }
    }

    *num_of_parts = i; /* saving number of parts */
}