/**
 * recover.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Recovers JPEGs from a forensic image.
 */

#include <stdio.h>
#include <stdint.h>

typedef uint8_t BYTE;

int main(int argc, char* argv[])
{
    FILE* card = fopen("card.raw", "r");

    // check if file is NULL
    if (card == NULL)
    {
        printf("Could not open ""card.raw"".\n");
        return 1;
    }
    
    // initialize buffer
    BYTE buffer[512];
    
    // initialize output
    FILE* outptr = NULL;
    char title[8];
    int fcount = 0;
    

    while(fread(buffer, sizeof(buffer), 1, card) == 1)
    {
        // read 512 BYTES into card
        //fread(buffer, sizeof(buffer), 1, card);
        
        // check if buffer starts with signature
        if (buffer[0] == 0xff && buffer[1] == 0xd8 && buffer[2] == 0xff && (buffer[3] > 223 || buffer[3] < 240))
        {
            if (outptr == NULL)
            {
                // name initial file
                sprintf(title, "%03i.jpg", fcount);
                
                // open initial file
                outptr = fopen(title, "w");
                
                fcount++;
            }
            else
            {
                // close previous file
                fclose(outptr);
                
                // name new file
                sprintf(title, "%03i.jpg", fcount);
                
                // open new file
                outptr = fopen(title, "w");
                
                fcount++;
            }
        } 
        
        if (outptr != NULL)
        {
            fwrite(buffer, sizeof(buffer), 1, outptr);
        }
        
    }
    
    // TODO free memory
    
    return 0;
}
