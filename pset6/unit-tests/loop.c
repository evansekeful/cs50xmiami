/**
 * loop.c
 *
 * Computer Science 50
 * Problem Set 6
 *
 * Tests functionality of loop in lookup.c
 * */

#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main(int argc, char* argv[])
 {
    //copies argv1 to path for test
    char path[strlen(argv[1])];
    for (int t = 0, n = strlen(argv[1]); t < n; t++)
    {
        path[t] = argv[1][t]; 
    }
    
    int i = 0;
    while (isalpha(path[i]))
    {
        printf("%c\n", path[i]);
        i++;
    }
    
    printf("break\n");
}