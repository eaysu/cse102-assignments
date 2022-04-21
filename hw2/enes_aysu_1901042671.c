#include <stdio.h>
#define N 100 /* defining maximum array size */

int main()
{
    FILE *in; /* a pointer which represents the file */
    FILE *out; /* a pointer which represents the file */
    in = fopen("input.txt", "r"); /* open for reading */

    if(in == NULL) /* error message */
    {
        printf("*** no file here ***\n");
    }

    else /* successfull message */
    {
        printf("*** reading successfull ***\n");
    }
    

    int numbers[N] = {0}; /* an array which includes repeated numbers from the file "input.txt" */
    int repetitions[N] = {0}; /* an array which includes counts of repetitions from the file "input.txt" */

    int i = 0, j = 0, k = 0; /* loop control letters */
    int arr_size = 0; /* to specify how many elements the array includes */
    int temp = 0; /* temporary value */
    int flag = 0; /* for if number is 0 condition */
    int count = 0; /* counts of numbers in the file */
    int number; /* for initializing numbers from text */

    while(fscanf(in, "%d", &number) != EOF)
    {
        count++; /* determining how many numbers are in the file */
    }

    fseek(in, 0, SEEK_SET); /* returning the cursor to the beggining of the file */

    for(i = 0;i < count;i++) /* picking numbers in order */
    {
        fscanf(in, "%d", &number); /* picking a number from the file */

        for(j = 0;j <= arr_size;j++) /* comparing numbers for repetition condition */
        {
            if(number == 0 && flag == 0) /* to calculate correctly if the number "0" is found in the file */
            {
                flag++;
                break;
            }
            
            if(number == numbers[j])
            {
                if(number == 0) /* to the zero contained in the file not to interfere with other existing zeros in the array */
                {
                   repetitions[j]++;
                   k = 1;
                   break; 
                }
                
                else /* inreasing repetition count */
                {
                    repetitions[j]++;
                    k = 1;
                }  
            }
        }
        
        if(k == 1) /* for only one of the repeated numbers to be include in the sequence */
        {
            k = 0;
            continue;
        }

        numbers[arr_size] = number; /* inserting number in the array */
        repetitions[arr_size]++; /* inreasing repetition count */ 
        arr_size++; /* for the next number to be insert in the next box in the array */
    }
    
    fclose(in); /* close the file */
    
    for(i = 0;i < arr_size;i++) /* sorting repetitions from small value to big value */
    {
        for(j = 0;j < (arr_size - (i + 1));j++)
        {
            if(repetitions[j] > repetitions[j + 1])
            {
                temp = repetitions[j]; 
                repetitions[j] = repetitions[j + 1];
                repetitions[j + 1] = temp;
                                                /* repetitions and numbers should change simultaneously */
                temp = numbers[j];
                numbers[j] = numbers[j + 1];
                numbers[j + 1] = temp;
            }
        }
    }

    for(i = 0;i < arr_size;i++) /* sorting numbers that have the same repetition from small value to big value */
    {
        for(j = 0;j < (arr_size - (i + 1));j++)
        {
            if(repetitions[j] == repetitions[j + 1] && numbers[j] > numbers[j + 1])
            {
                temp = numbers[j];
                numbers[j] = numbers[j + 1];
                numbers[j + 1] = temp;
            }
        }
    }
    
    out = fopen("output.txt", "w"); /* open for writing */

    for(i = 0;i < arr_size;i++) /* printing numbers and repetitions in the ascending order in the "output.txt" */
    {
        fprintf(out,"%d:%d\n", numbers[i], repetitions[i]);
    }
    
    fclose(out); /* close the file */
    
    return 0; 
}