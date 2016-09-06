#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


int main (int argc, string argv[])
{
    if (argc != 2)
    {
        printf("Usage: ./caesar <key integer>\n");
        return 1;
    }
    
    int key = atoi(argv[1]); //converts key from string to int
    
    string message = GetString(); //prompts user for string to encrypt
    
    for (int i = 0, n = strlen(message); i < n; i++)
    {
        if (isalpha(message[i])) //checks if character i is alphabetical
        {
            if(isupper(message[i])) //checks if character is uppercase
            {
                int alpha = message[i] - 65; //converts ASCII value to 0-indexed number
                int c = (alpha + key) % 26; //moves number by key value
                int ascii = c + 65; //converts new value back to ASCII
                printf("%c", ascii);
            }
            else //runs if letter is lowercase (or "not" uppercase from previous check)
            {
                int alpha = message[i] - 97; //converts ASCII value to 0-indexed number
                int c = (alpha + key) % 26; //moves number by key value
                int ascii = c + 97; //converts new value back to ASCII
                printf("%c", ascii);
            }
            
        }
        else
        {
            printf("%c", message[i]);
        }
        
    }    
    
    printf("\n");
    return 0;
}