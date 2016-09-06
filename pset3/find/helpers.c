/**
 * helpers.c
 *
 * Computer Science 50
 * Problem Set 3
 *
 * Helper functions for Problem Set 3.
 */
       
#include <cs50.h>

#include "helpers.h"

int binarySearch(int key, int array[], int min, int max);

/**
 * Returns true if value is in array of n values, else false.
 */
bool search(int value, int values[], int n)
{
    int min = 0; //sets minimum index to 0
    int max = n - 1; //sets max index to length of array -1
    
    int result = binarySearch(value, values, min, max); //binary search for value
    
    if (result == value)
    {
        return true;
    }
    else
    {
        return false;
    }
}

/**
 * Sorts array of n values.
 */
void sort(int values[], int n)
{
    for (int pass = 1, flag = 0; pass < n; pass++, flag = 0) //sets list passes
     {
         int temp;
         
         for (int i = 0; i < n - pass; i++)
         {
             if (values[i] > values[i + 1])
             {
                 temp = values[i];
                 values[i] = values[i + 1];
                 values[i + 1] = temp;
                 flag++;
             }
         }
         
         if (flag == 0) //checks if swaps were made
         {
             return;
         }
     }
    
    return;
}

int binarySearch(int key, int array[], int min, int max)
{
    int mid = (min + max) / 2;
    
    if (max < min) //checks if min and max have crossed
        return -1;
    
    //recursive binary search
    
    if (array[mid] > key)
        return binarySearch(key, array, min, (mid - 1));
    else if (array[mid] < key)
        return binarySearch(key, array, (mid + 1), max);
    else
        return array[mid];
}

