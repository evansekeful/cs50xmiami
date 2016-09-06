#include <cs50.h>
#include <math.h>
#include <stdio.h>

int main(void)
{
   float change;
   do
   {
       printf("How much change is owed?\n"); //prompts user for change owed
       change = GetFloat();
   }
    while (change < 0);
    
    change = change*100; //moves float two decimals places
    change = round(change); //rounds change to nearest integer value
    
    int coins = 0; // sets coin count to 0
    
    while (change > 0)
    {
        
        coins = change/25; //divides change into quarters
        change = (int)change % 25; //reduces change value by quarters

        
        coins = coins + change/10; //divides remaining change into dimes
        change = (int)change % 10; //reduces change by dimes used

        
        coins = coins + change/5; //divides remaining change into nickels
        change = (int)change % 5; //reduces change by nickels

        coins = coins + (int)change; //adds remaining pennies to coin count
        change = 0; //reduces change to 0
        
    }
    
    printf("%i\n", coins); //prints # coins used for change
}