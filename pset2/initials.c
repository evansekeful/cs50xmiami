#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>

int main(void)
{
    string name = GetString();
    
    for (int i = 0, n = strlen(name); i < n; i++)
    {
        if (i == 0)
        {
            printf("%c", toupper(name[i])); //prints first initial in uppercase
        }
        else
        {
            if (name[i-1] == 32) //checks if a character is preceded by a space
            {
                printf("%c", toupper(name[i])); //prints character preceded by space in uppercase
            }
        }
    }
    
    printf("\n"); //prints new line
    
}