#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    int biWidth = atoi(argv[1]);
    signed int biHeight = atoi(argv[2]);
    
    int padding_out =  (4 - (biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    
    int biSizeImage = (biWidth * abs(biHeight)) * sizeof(RGBTRIPLE) + abs(biHeight) * padding_out;
    
    printf("%i %i\n", padding_out, biSizeImage);
    
    return 0;
}