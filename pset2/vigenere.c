#include <stdio.h>
#include <cs50.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


int main (int argc, string argv[])
{
     if (argc != 2) //checks if one keyword is passed to main
    {
        printf("Usage: ./vigenere <key string>\n");
        return 1;
    }
    
    int keylen = strlen(argv[1]);
    int key[keylen];
    
    for (int i = 0; i < keylen; i++)
    {
        key[i] = argv[1][i]; //write argument character array to int array
        
        if (isalpha(key[i]))
        {
            key[i] = toupper(key[i]);//convert key to uppercase
            key[i] = key[i] - 65; //converts ASCII value to 0-indexed number
        }
        else
        {
          printf("Usage: ./vigenere <key string>\n");
          return 1;  
        }
    }
        
    string message = GetString();
    
    for (int i = 0, j = 0, n = strlen(message); i < n; i++)
    {
        if (isalpha(message[i])) //checks if character i is alphabetical
        {
            if(isupper(message[i])) //checks if character is uppercase
            {
                int alpha = message[i] - 65; //converts ASCII value to 0-indexed number
                int c = (alpha + key[j % keylen]) % 26; //moves number by key value
                int ascii = c + 65; //converts new value back to ASCII
                printf("%c", ascii);
            }
            else //runs if letter is lowercase (or "not" uppercase from previous check)
            {
                int alpha = message[i] - 97; //converts ASCII value to 0-indexed number
                int c = (alpha + key[j % keylen]) % 26; //moves number by key value
                int ascii = c + 97; //converts new value back to ASCII
                printf("%c", ascii);
            }
            
            j++;
            
        }
        else
        {
            printf("%c", message[i]);
        }
    }
    
    printf("\n");
}