#include <stdio.h>
#include <string.h>
#define L 250

void print_newick(FILE *out, char *text, int count); /* the function that prints the nodes as mentioned order */

int main()
{
    char text[L]; /* char array for text */
    int count = 0; /* it counts dashes */
    
    FILE *inp; /* a pointer which represents the file */
    inp = fopen("input.txt", "r"); /* open for reading */
    
    fgets(text, L, inp); /* getting line */
    fclose(inp); /* closing file */

    FILE *out; /* a pointer which represents the file */
    out = fopen("output.txt", "w"); /* open for reading */

    print_newick(out, text, count); /* calling function */
    fclose(out); /* closing file */
    return 0;
}

void print_newick(FILE *out,char *text, int count)
{
    int i = 0;
    int j = count;
    int a = 0;
        
    for(i = 0;i < strlen(text);i++)
    {
        if(text[i] == 40) /* a situation that program encounters open paranthesis */
        {
            text[i] = ' '; /* if program encounters parenthesis, it puts space character */
            j++; /* increasing count of dashes */
            print_newick(out, text, j); /* recursion part */
        }    
        
        else if(text[i] == 41) /* a situation that program encunters close paranthesis */
        {
            text[i] = ' '; /* if program encounters parenthesis, it puts space character */
            j--; /* decreasing count of dashes */
        }
        else if(text[i] == 44 || text[i] == 32) /* a situation that program encounters comma and space */
            continue;
        
        else
        {
            for(a = 0;a < j;a++) /* printing part */
            {
                fprintf(out, "-");
            }
            fprintf(out, "%c\n", text[i]);
            text[i] = ' '; /* after the character is printed, it is replaced with a space character*/
        }
    }
}