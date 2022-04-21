#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#define N 100 /* defining maximum array size */
#define L 1000 /* defining maximum line character */

int main()
{
    FILE *val; /* a pointer which represents the file */
    val = fopen("values.txt", "r"); /* open for reading */

    if(val == NULL) /* error message */
    {
        printf("*** no file here ***\n");
    }
    else /* successfull message */
    {
        printf("*** reading successfull (values.txt) ***\n");
    }

    double values[N]; /* to store values from the file */
    double num = 0;
    int count = 0; /* counts of numbers in the file */

    while(fscanf(val, "%lf", &num) != EOF) /* getting numbers from values.txt */
    {
        values[count] = num;
        count++;
    }

    fclose(val); /* close the file */

    FILE *poly; /* a pointer which represents the file */
    poly = fopen("polynomial.txt", "r"); /* open for reading */

    if(poly == NULL) /* error message */
    {
        printf("*** no file here ***\n");
    }
    else /* successfull message */
    {
        printf("*** reading successfull (polynomial.txt) ***\n");
    }

    int i = 0, j = 0, k = 0, m = 0, n = 0, index = 0; /* loop control letters */
    char line[L]; 
    fgets(line, L, poly); /* reads polynomial from the file */

    fclose(poly); /* close the file */
    
    int flag = 0;  /* for partial operations */
    double sign_arr[L];
    double power_arr[L];
    double coefficient_arr[L];
    char *temp_piece;
    char *temp2_piece;
    char *temp3_piece;
    char *monomial_piece;
    char *endptr;
    char temp_arr[L][L];
    char temp2_arr[L][L];
    char temp3_arr[L][L];
    char monomial_arr[L][L];
    int place = 0;

    for(i = 0;i < L;i++) /* initialize mentioned arrays to 1  */
    {
        sign_arr[i] = 1;
        power_arr[i] = 1;
        coefficient_arr[i] = 1;
    }
    
    i = 0;
    temp_piece = strtok(line, "+"); /* splitting polynomial from + */

    while(temp_piece != NULL)
    {
        strcpy(temp_arr[i], temp_piece);
        temp_piece = strtok(NULL, "+");
        i++;
    }

    for(j = 0;j < i;j++) /* splitting continues with - */
    {
        if(flag == 0) /* if program encounters -, puts -1 in sign_arr */
        {
            while(temp_arr[j][m] != NULL)
            {
                if(temp_arr[j][m] == '-')
                {
                    sign_arr[place] = -1;
                    place++;
                }
                m++;
            }
            flag = 1;
        }

        if(flag == 1)
        {
            while(temp_arr[j][m] != NULL)
            {
                if(temp_arr[j][m] == '-')
                {
                    sign_arr[place + j + 1] = -1;
                    place++;
                }
                m++;
            }
        }
        
        monomial_piece = strtok(temp_arr[j], "-"); /* we obtain monomials without signs */
        while(monomial_piece != NULL)
        {
            strcpy(monomial_arr[k], monomial_piece);
            monomial_piece = strtok(NULL, "-");
            k++;
        }
    }

    m = 0;
    
    for(j = 0;j < k;j++)
    {
        temp2_piece = strtok(monomial_arr[j], "^"); /* splitting monomials to its coefficients and powers */
        while(temp2_piece != NULL)
        {
            flag = 1;
            n = 0;
            strcpy(temp2_arr[m], temp2_piece);
            temp2_piece = strtok(NULL, "^");
            while(temp2_arr[m][n] != NULL)
            {
                if(temp2_arr[m][n] == 'x')
                {
                    if(n == 0)
                    {
                        index++;
                        m++;
                        continue;
                    }
                    
                    temp3_piece = strtok(temp2_arr[m], "x");
                    while(temp3_piece != NULL)
                    {
                        strcpy(temp3_arr[m], temp3_piece);
                        temp3_piece = strtok(NULL, "x");
                        coefficient_arr[index] = strtod(temp3_arr[m], &endptr); /* converting string to double */
                        index++;
                        flag = 0;
                    }
                } 
                n++;    
            }
            if(flag == 1)
            {
                power_arr[index - 1] = strtod(temp2_arr[m], &endptr); /* converting string to double */
            }
            m++;
        }
    }
    
    FILE *evl; /* a pointer which represents the file */
    evl = fopen("evaluations.txt", "w"); /* open for writing */

    double result = 0;

    for(i = 0;i < count;i++) /* writing results to the file */
    {
        for(j = 0;j < k;j++)
        {
            result = result + (sign_arr[j]*coefficient_arr[j]*pow(values[i],power_arr[j]));
        }
        fprintf(evl, "%.2lf\n", result);
        result = 0;
    }

    fclose(evl); /* close the file */

    return 0;
}