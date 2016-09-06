/**
 * copy.c
 *
 * Computer Science 50
 * Problem Set 4
 *
 * Resizes a BMP by a factor of n, just because.
 */
       
#include <stdio.h>
#include <stdlib.h>

#include "bmp.h"

int main(int argc, char* argv[])
{
    // ensure proper usage
    if (argc != 4)
    {
        printf("Usage: ./resize n infile outfile.\n");
        return 1;
    }
    
    // store multiplier
    int n = atoi(argv[1]);
    
    // ensure n is between 1 and 100
    if (n < 1 || n > 100)
    {
        printf("Multiplier n must be between 1 and 100\n");
        return 2;
    }
    
    // remember filenames
    char* infile = argv[2];
    char* outfile = argv[3];
    

    // open input file 
    FILE* inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 3;
    }

    // open output file
    FILE* outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        fprintf(stderr, "Could not create %s.\n", outfile);
        return 4;
    }

    // read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 || 
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        fprintf(stderr, "Unsupported file format.\n");
        return 5;
    }
    
    // declare outfile headers; initialize at infile values
    BITMAPFILEHEADER bf_out = bf;
    BITMAPINFOHEADER bi_out = bi;
    
    // determine padding for scanlines
    int padding =  (4 - (bi.biWidth * sizeof(RGBTRIPLE)) % 4) % 4;
    int padding_out =  (4 - ((bi.biWidth * n) * sizeof(RGBTRIPLE)) % 4) % 4;
    
    // resize image in BITMAPINFOHEADER
    bi_out.biWidth = bi.biWidth * n;
    bi_out.biHeight = bi.biHeight * n;
    bi_out.biSizeImage = (bi_out.biWidth * abs(bi_out.biHeight)) * sizeof(RGBTRIPLE) + abs(bi_out.biHeight) * padding_out;
    
    // resize image in BITMAPFILEHEADER
    bf_out.bfSize = bi_out.biSizeImage + 54;
    
    // write outfile's BITMAPFILEHEADER
    fwrite(&bf_out, sizeof(BITMAPFILEHEADER), 1, outptr);

    // write outfile's BITMAPINFOHEADER
    fwrite(&bi_out, sizeof(BITMAPINFOHEADER), 1, outptr);

    // iterate over infile's scanlines
    for (int i = 0, biHeight = abs(bi.biHeight); i < biHeight; i++)
    {
        
        // iterate writing of scanline n times (vertical resize)
        for (int v = 0; v < n; v++)
        {
            // iterate over pixels in scanline
            for (int j = 0; j < bi.biWidth; j++)
            {
                // temporary storage
                RGBTRIPLE triple;
    
                // read RGB triple from infile
                fread(&triple, sizeof(RGBTRIPLE), 1, inptr);
    
                // iterate writing of triple n times (horizontal resize)
                for (int h = 0; h < n; h++)
                {
                    // write RGB triple to outfile
                    fwrite(&triple, sizeof(RGBTRIPLE), 1, outptr);
                }
            }
    
            // reset location at start of scanline
            fseek(inptr, -(bi.biWidth * sizeof(RGBTRIPLE)), SEEK_CUR);
    
            // then add any necessary padding to outfile
            for (int k = 0; k < padding_out; k++)
            {
                fputc(0x00, outptr);
            }
        }
        
        // move down scanline in infile
        fseek(inptr, (bi.biWidth * sizeof(RGBTRIPLE)) + padding, SEEK_CUR);
    }
    

    // close infile
    fclose(inptr);

    // close outfile
    fclose(outptr);

    // that's all folks
    return 0;
}
