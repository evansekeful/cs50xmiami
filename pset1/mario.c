#include <cs50.h>
#include <stdio.h>

int main(void)
{
    int height;
    do
    {
        printf("Height: ");
        height = GetInt();
    }
    while (height > 23 || height < 0); //checks if height is greater than 23 or negative
    
    
    for (int row = 0; row < height; row++) //adds rows
    {
        for (int space = height - 1 - row; space > 0; space--) //prints dynamic spaces based on row
        {
            printf(" ");
        } 
        
        for (int hash = 0; hash < row + 1; hash++) //prints dynamic hashes based on row
        {
            printf("#");
        }
        
        printf("#\n");
    }
}
