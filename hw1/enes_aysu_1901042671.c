/* 
    the code theoretically performs general file operations in the expected time. 
    it may also include more effective methods in a situation where all the numbers are the same or different. 
    comparison can also be performed by creating less complex loops.
*/

#include <stdio.h>

int digit_calculator(int number); /* function declaration */ 

int main()
{
    FILE *fp; /* A Pointer which represents the file.*/
    fp = fopen ("file.txt", "r+"); /*open for reading and writing, overwriting a file*/

    int i = 0, j = 0, k = 0; /* loop control letters */
    int count = 0; 
    int number; /* for initializing numbers from text */
    int check; /* for comparing whether the numbers are the same*/
    int position = 0; /* cursors position */

    while(fscanf(fp, "%d", &number) != EOF)
    {
        count++; /* determining how many numbers are in the file */
    }

    fseek(fp, 0, SEEK_SET); /* returning the cursor to the beggining of the file */

    for(i = 0;i < count;i++) /* picking numbers in order */
    {
        fscanf(fp, "%d", &number); /* picking a number from the file */
        position = ftell(fp); /* holding position for not forget */
  
        for(j = 0;j < count;j++)
        {
            fscanf(fp, "%d", &check); /* picking numbers from the file to compare other numbers */
            if(number == check) /* if numbers are the same one of them needs to be deleted */
            {
                fseek(fp, -digit_calculator(number), SEEK_CUR); /* returning the cursor for the beggining of the deleted number */ 
                for(k = 0;k < digit_calculator(number);k++) /* finding how many digits we need to delete */
                {
                    fputs(" ", fp); /* putting space instead of number */
                }
                count--; /* removing the deleted number from the loop */       
            }
        }
        fseek(fp, position, SEEK_SET); /* passing other number */
    }
    fclose(fp); /* close the file */
    
    return 0;
}

int digit_calculator(int number)
{
    int NumOfDigits = 0;

    if(number <= 0)
    {
        NumOfDigits++; /* if the number is 0 it has 1 digit. if the number is negative it has negative sign. we need to add this sign for calculating number of digit. */
    }

    while(number != 0)
    {
        number /= 10; /* finding how many digits the number has */
        NumOfDigits++;
    }

    return NumOfDigits; /* return value */
}
