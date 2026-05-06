#include <getopt.h>
#include <stdio.h>
#include <stdlib.h>


#include "helpers.h"

int main(int argc, char *argv[])
{
    // Define allowable filters
    char *filters = "begr";

    // Get filter flag and check validity
    char filter = getopt(argc, argv, filters);
    if (filter == '?')
    {
        printf("Invalid filter.\n");
        return 1;
    }

    // Ensure only one filter
    if (getopt(argc, argv, filters) != -1)
    {
        printf("Only one filter allowed.\n");
        return 2;
    }

    // Ensure proper usage
    if (argc != optind + 2)
    {
        printf("Usage: ./filter [flag] infile outfile\n");
        return 3;
    }

    // Remember filenames
    char *infile = argv[optind];
    char *outfile = argv[optind + 1];

    // Open input file
    FILE *inptr = fopen(infile, "r");
    if (inptr == NULL)
    {
        printf("Could not open %s.\n", infile);
        return 4;
    }

    // Open output file
    FILE *outptr = fopen(outfile, "w");
    if (outptr == NULL)
    {
        fclose(inptr);
        printf("Could not create %s.\n", outfile);
        return 5;
    }

    // Read infile's BITMAPFILEHEADER
    BITMAPFILEHEADER bf;
    fread(&bf, sizeof(BITMAPFILEHEADER), 1, inptr);

    // Read infile's BITMAPINFOHEADER
    BITMAPINFOHEADER bi;
    fread(&bi, sizeof(BITMAPINFOHEADER), 1, inptr);

    // Ensure infile is (likely) a 24-bit uncompressed BMP 4.0
    if (bf.bfType != 0x4d42 || bf.bfOffBits != 54 || bi.biSize != 40 ||
        bi.biBitCount != 24 || bi.biCompression != 0)
    {
        fclose(outptr);
        fclose(inptr);
        printf("Unsupported file format.\n");
        return 6;
    }

    // Get image's dimensions
    int height = abs(bi.biHeight);
    int width = bi.biWidth;

    // Allocate memory for image
    RGBTRIPLE(*image)[width] = calloc(height, width * sizeof(RGBTRIPLE));
    if (image == NULL)
    {
        printf("Not enough memory to store image.\n");
        fclose(outptr);
        fclose(inptr);
        return 7;
    }

    // Determine padding for scanlines
    int padding = (4 - (width * sizeof(RGBTRIPLE)) % 4) % 4;

    // Iterate over infile's scanlines
    for (int i = 0; i < height; i++)
    {
        // Read row into pixel array
        fread(image[i], sizeof(RGBTRIPLE), width, inptr);

        // Skip over padding
        fseek(inptr, padding, SEEK_CUR);
    }

    // Filter image
    switch (filter)
    {
        // Blur
        case 'b':
            blur(height, width, image);
            break;

        // Edges
        case 'e':
            edges(height, width, image);
            break;

        // Grayscale
        case 'g':
            grayscale(height, width, image);
            break;

        // Reflect
        case 'r':
            reflect(height, width, image);
            break;

    }

    // Write outfile's BITMAPFILEHEADER
    fwrite(&bf, sizeof(BITMAPFILEHEADER), 1, outptr);

    // Write outfile's BITMAPINFOHEADER
    fwrite(&bi, sizeof(BITMAPINFOHEADER), 1, outptr);

    // Write new pixels to outfile
    for (int i = 0; i < height; i++)
    {
        // Write row to outfile
        fwrite(image[i], sizeof(RGBTRIPLE), width, outptr);

        // Write padding at end of row
        for (int k = 0; k < padding; k++)
        {
            fputc(0x00, outptr);
        }
    }

    // Free memory for image
    free(image);

    // Close files
    fclose(inptr);
    fclose(outptr);
    return 0;
}





// #include <math.h>
// // Detect edges
// void edges(int height, int width, RGBTRIPLE image[height][width])
// {
//     RGBTRIPLE copy[height][width];
//     int i, j,di,dj, index = -1;
//     int GxR, GxG, GxB, GyR,GyB, GyG;

//     //making a copy of the original image
//      for (i = 0; i < height; i++)
//     {
//         for (j = 0; j < width; j++)
//         {
//             copy[i][j].rgbtRed = image[i][j].rgbtRed;
//             copy[i][j].rgbtBlue = image[i][j].rgbtBlue;
//             copy[i][j].rgbtGreen = image[i][j].rgbtGreen;
//         }
//     }

//     //computing new value for each pixel and loading it to it
//     for (i = 0; i < height; i++)
//     {
//         for (j = 0; j < width; j++)
//         {
//             GxR = 0;
//             GxB = 0;
//             GxG = 0;

//             GyR = 0;
//             GyB = 0;
//             GyG = 0;

//             for(di = -1; di<=1; di++)
//             {
//                 if(di == -1 || di == 1)
//                     index = -1;
//                 if(di == 0)
//                     index = -2;

//                 for(dj = -1;dj<=1;dj++)
//                 {
//                     int ni = i+di;
//                     int nj = j+dj;

//                     if (ni < 0 || ni >= height || nj < 0 || nj >= width)
//                     {
//                         if(di == -1 || di == 1)
//                             index++;
//                         if(di == 0)
//                             index+= 2;
//                         continue;
//                     }


//                     GxR += index*copy[ni][nj].rgbtRed;
//                     GxB += index*copy[ni][nj].rgbtBlue;
//                     GxG += index*copy[ni][nj].rgbtGreen;


//                     if(di == -1 || di == 1)
//                         index++;
//                     if(di == 0)
//                         index+= 2;

//                 }

//                 if(di == -1 || di == 1)
//                     index = -1;
//                 if(di == 0)
//                     index = -2;

//                 for(dj = -1;dj<=1;dj++)
//                 {
//                     int ni = i+di;
//                     int nj = j+dj;

//                     if (nj < 0 || nj >= height || ni < 0 || ni >= width)
//                     {
//                         if(di == -1 || di == 1)
//                             index++;
//                         if(di == 0)
//                             index+= 2;
//                         continue;
//                     }
//                     GyR += index*copy[nj][ni].rgbtRed;
//                     GyB += index*copy[nj][ni].rgbtBlue;
//                     GyG += index*copy[nj][ni].rgbtGreen;

//                     if(di == -1 || di == 1)
//                         index++;
//                     if(di == 0)
//                         index+= 2;

//                 }

//             }
//             image[i][j].rgbtRed = round(sqrt((GxR * GxR) + (GyR * GyR)));
//             image[i][j].rgbtBlue = round(sqrt((GxB * GxB) + (GyB * GyB)));
//             image[i][j].rgbtGreen = round(sqrt((GxG * GxG) + (GyG * GyG)));

//             image[i][j].rgbtRed = (image[i][j].rgbtRed > 255)?255 : image[i][j].rgbtRed;
//             image[i][j].rgbtBlue = (image[i][j].rgbtBlue > 255)?255 : image[i][j].rgbtBlue;
//             image[i][j].rgbtGreen = (image[i][j].rgbtGreen > 255)?255 : image[i][j].rgbtGreen;
//         }
//     }

//     return;
// }
