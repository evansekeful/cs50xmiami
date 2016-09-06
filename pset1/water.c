#include <stdio.h>
#include <cs50.h>

int main(void)
{
    printf("minutes: ");
    int minutes = GetInt(); //prompts user for shower minutes
    int bottles = minutes*12; //multiples minutes by number of bottles per minute
    printf("bottles: %i \n", bottles); //returns number of bottles used to shower
}
