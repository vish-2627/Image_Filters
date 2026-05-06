#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    int avg, i, j;
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            avg = round((image[i][j].rgbtRed + image[i][j].rgbtBlue + image[i][j].rgbtGreen) / 3.0);
            image[i][j].rgbtRed = avg;
            image[i][j].rgbtBlue = avg;
            image[i][j].rgbtGreen = avg;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    int i, j;
    RGBTRIPLE copy[height][width];
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
    }

    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            image[i][j] = copy[i][width - 1 - j];
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int i, j;
    RGBTRIPLE copy[height][width];
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            copy[i][j].rgbtRed = image[i][j].rgbtRed;
            copy[i][j].rgbtBlue = image[i][j].rgbtBlue;
            copy[i][j].rgbtGreen = image[i][j].rgbtGreen;
        }
    }

    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            if (i == 0)
            {
                if (j == 0)
                {
                    image[i][j].rgbtRed =
                        round((copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed +
                               copy[i + 1][j].rgbtRed + copy[i + 1][j + 1].rgbtRed) /
                              4.0);
                    image[i][j].rgbtBlue =
                        round((copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue +
                               copy[i + 1][j].rgbtBlue + copy[i + 1][j + 1].rgbtBlue) /
                              4.0);
                    image[i][j].rgbtGreen =
                        round((copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen +
                               copy[i + 1][j].rgbtGreen + copy[i + 1][j + 1].rgbtGreen) /
                              4.0);
                }
                else if (j == width - 1)
                {
                    image[i][j].rgbtRed =
                        round((copy[i][j - 1].rgbtRed + copy[i][j].rgbtRed +
                               copy[i + 1][j - 1].rgbtRed + copy[i + 1][j].rgbtRed) /
                              4.0);
                    image[i][j].rgbtBlue =
                        round((copy[i][j - 1].rgbtBlue + copy[i][j].rgbtBlue +
                               copy[i + 1][j - 1].rgbtBlue + copy[i + 1][j].rgbtBlue) /
                              4.0);
                    image[i][j].rgbtGreen =
                        round((copy[i][j - 1].rgbtGreen + copy[i][j].rgbtGreen +
                               copy[i + 1][j - 1].rgbtGreen + copy[i + 1][j].rgbtGreen) /
                              4.0);
                }
                else
                {
                    image[i][j].rgbtRed =
                        round((copy[i][j - 1].rgbtRed + copy[i][j].rgbtRed +
                               copy[i][j + 1].rgbtRed + copy[i + 1][j - 1].rgbtRed +
                               copy[i + 1][j].rgbtRed + copy[i + 1][j + 1].rgbtRed) /
                              6.0);
                    image[i][j].rgbtBlue =
                        round((copy[i][j - 1].rgbtBlue + copy[i][j].rgbtBlue +
                               copy[i][j + 1].rgbtBlue + copy[i + 1][j - 1].rgbtBlue +
                               copy[i + 1][j].rgbtBlue + copy[i + 1][j + 1].rgbtBlue) /
                              6.0);
                    image[i][j].rgbtGreen =
                        round((copy[i][j - 1].rgbtGreen + copy[i][j].rgbtGreen +
                               copy[i][j + 1].rgbtGreen + copy[i + 1][j - 1].rgbtGreen +
                               copy[i + 1][j].rgbtGreen + copy[i + 1][j + 1].rgbtGreen) /
                              6.0);
                }
            }
            else if (i == height - 1)
            {
                if (j == 0)
                {
                    image[i][j].rgbtRed =
                        round((copy[i - 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed +
                               copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed) /
                              4.0);
                    image[i][j].rgbtBlue =
                        round((copy[i - 1][j].rgbtBlue + copy[i - 1][j + 1].rgbtBlue +
                               copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue) /
                              4.0);
                    image[i][j].rgbtGreen =
                        round((copy[i - 1][j].rgbtGreen + copy[i - 1][j + 1].rgbtGreen +
                               copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen) /
                              4.0);
                }
                else if (j == width - 1)
                {
                    image[i][j].rgbtRed =
                        round((copy[i - 1][j - 1].rgbtRed + copy[i - 1][j].rgbtRed +
                               copy[i][j - 1].rgbtRed + copy[i][j].rgbtRed) /
                              4.0);
                    image[i][j].rgbtBlue =
                        round((copy[i - 1][j - 1].rgbtBlue + copy[i - 1][j].rgbtBlue +
                               copy[i][j - 1].rgbtBlue + copy[i][j].rgbtBlue) /
                              4.0);
                    image[i][j].rgbtGreen =
                        round((copy[i - 1][j - 1].rgbtGreen + copy[i - 1][j].rgbtGreen +
                               copy[i][j - 1].rgbtGreen + copy[i][j].rgbtGreen) /
                              4.0);
                }
                else
                {
                    image[i][j].rgbtRed =
                        round((copy[i - 1][j - 1].rgbtRed + copy[i - 1][j].rgbtRed +
                               copy[i - 1][j + 1].rgbtRed + copy[i][j - 1].rgbtRed +
                               copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed) /
                              6.0);
                    image[i][j].rgbtBlue =
                        round((copy[i - 1][j - 1].rgbtBlue + copy[i - 1][j].rgbtBlue +
                               copy[i - 1][j + 1].rgbtBlue + copy[i][j - 1].rgbtBlue +
                               copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue) /
                              6.0);
                    image[i][j].rgbtGreen =
                        round((copy[i - 1][j - 1].rgbtGreen + copy[i - 1][j].rgbtGreen +
                               copy[i - 1][j + 1].rgbtGreen + copy[i][j - 1].rgbtGreen +
                               copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen) /
                              6.0);
                }
            }
            else if (j == 0)
            {
                image[i][j].rgbtRed =
                    round((copy[i - 1][j].rgbtRed + copy[i - 1][j + 1].rgbtRed +
                           copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed + copy[i + 1][j].rgbtRed +
                           copy[i + 1][j + 1].rgbtRed) /
                          6.0);
                image[i][j].rgbtBlue =
                    round((copy[i - 1][j].rgbtBlue + copy[i - 1][j + 1].rgbtBlue +
                           copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue +
                           copy[i + 1][j].rgbtBlue + copy[i + 1][j + 1].rgbtBlue) /
                          6.0);
                image[i][j].rgbtGreen =
                    round((copy[i - 1][j].rgbtGreen + copy[i - 1][j + 1].rgbtGreen +
                           copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen +
                           copy[i + 1][j].rgbtGreen + copy[i + 1][j + 1].rgbtGreen) /
                          6.0);
            }
            else if (j == width - 1)
            {
                image[i][j].rgbtRed =
                    round((copy[i - 1][j - 1].rgbtRed + copy[i - 1][j].rgbtRed +
                           copy[i][j - 1].rgbtRed + copy[i][j].rgbtRed +
                           copy[i + 1][j - 1].rgbtRed + copy[i + 1][j].rgbtRed) /
                          6.0);
                image[i][j].rgbtBlue =
                    round((copy[i - 1][j - 1].rgbtBlue + copy[i - 1][j].rgbtBlue +
                           copy[i][j - 1].rgbtBlue + copy[i][j].rgbtBlue +
                           copy[i + 1][j - 1].rgbtBlue + copy[i + 1][j].rgbtBlue) /
                          6.0);
                image[i][j].rgbtGreen =
                    round((copy[i - 1][j - 1].rgbtGreen + copy[i - 1][j].rgbtGreen +
                           copy[i][j - 1].rgbtGreen + copy[i][j].rgbtGreen +
                           copy[i + 1][j - 1].rgbtGreen + copy[i + 1][j].rgbtGreen) /
                          6.0);
            }
            else
            {
                image[i][j].rgbtRed = round((copy[i - 1][j - 1].rgbtRed + copy[i - 1][j].rgbtRed +
                                             copy[i - 1][j + 1].rgbtRed + copy[i][j - 1].rgbtRed +
                                             copy[i][j].rgbtRed + copy[i][j + 1].rgbtRed +
                                             copy[i + 1][j - 1].rgbtRed + copy[i + 1][j].rgbtRed +
                                             copy[i + 1][j + 1].rgbtRed) /
                                            9.0);
                image[i][j].rgbtBlue =
                    round((copy[i - 1][j - 1].rgbtBlue + copy[i - 1][j].rgbtBlue +
                           copy[i - 1][j + 1].rgbtBlue + copy[i][j - 1].rgbtBlue +
                           copy[i][j].rgbtBlue + copy[i][j + 1].rgbtBlue +
                           copy[i + 1][j - 1].rgbtBlue + copy[i + 1][j].rgbtBlue +
                           copy[i + 1][j + 1].rgbtBlue) /
                          9.0);
                image[i][j].rgbtGreen =
                    round((copy[i - 1][j - 1].rgbtGreen + copy[i - 1][j].rgbtGreen +
                           copy[i - 1][j + 1].rgbtGreen + copy[i][j - 1].rgbtGreen +
                           copy[i][j].rgbtGreen + copy[i][j + 1].rgbtGreen +
                           copy[i + 1][j - 1].rgbtGreen + copy[i + 1][j].rgbtGreen +
                           copy[i + 1][j + 1].rgbtGreen) /
                          9.0);
            }
        }
    }
    return;
}

#include <math.h>
// //Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE copy[height][width];
    int i, j,di,dj, kx = -1, ky = -1;
    int GxR, GxG, GxB, GyR,GyB, GyG,GR,GB,GG ;

    //making a copy of the original image
     for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            copy[i][j].rgbtRed = image[i][j].rgbtRed;
            copy[i][j].rgbtBlue = image[i][j].rgbtBlue;
            copy[i][j].rgbtGreen = image[i][j].rgbtGreen;
        }}

    int Gx[3][3] = {{-1,0,1},
                {-2,0,2},
                {-1,0,1}};

    int Gy[3][3] = {{-1,-2,-1},
                {0,0,0},
                {1,2,1}};


    //computing new value for each pixel and loading it to it
    for (i = 0; i < height; i++)
    {
        for (j = 0; j < width; j++)
        {
            GxR = 0;
            GxB = 0;
            GxG = 0;

            GyR = 0;
            GyB = 0;
            GyG = 0;

            for(di = -1; di<=1; di++)
            {

                for(dj = -1;dj<=1;dj++)
                {
                    int ni = i+di;
                    int nj = j+dj;

                    if (ni < 0 || ni >= height || nj < 0 || nj >= width)
                    {
                        continue;
                    }

                    kx = Gx[di+1][dj+1];
                    ky = Gy[di+1][dj+1];

                    GxR += kx*(int)copy[ni][nj].rgbtRed;
                    GxB += kx*(int)copy[ni][nj].rgbtBlue;
                    GxG += kx*(int)copy[ni][nj].rgbtGreen;

                    GyR += ky*(int)copy[ni][nj].rgbtRed;
                    GyB += ky*(int)copy[ni][nj].rgbtBlue;
                    GyG += ky*(int)copy[ni][nj].rgbtGreen;

                }
            }


            GR = round(sqrt((GxR * GxR) + (GyR * GyR)));
            GB = round(sqrt((GxB * GxB) + (GyB * GyB)));
            GG = round(sqrt((GxG * GxG) + (GyG * GyG)));

            image[i][j].rgbtRed = (GR> 255) ? 255 : GR;
            image[i][j].rgbtBlue = (GB> 255) ? 255 : GB;
            image[i][j].rgbtGreen = (GG> 255) ? 255 : GG;


        }
    }

    return;
}







// void edges(int height, int width, RGBTRIPLE image[height][width])
// {
//     RGBTRIPLE copy[height+2][width+2], Gx, Gy, G;
//     int i, j,di,dj, index = -1;

//     //making a copy of the original image
//      for (i = 0; i <= height+1; i++)
//     {
//         for (j = 0; j <= width+1; j++)
//         {
//             if (i <= 0 || i > height || j <= 0 || j > width)
//             {
//                 copy[i][j].rgbtRed = 0;
//                 copy[i][j].rgbtBlue = 0;
//                 copy[i][j].rgbtGreen = 0;
//             }
//             copy[i+1][j+1].rgbtRed = image[i][j].rgbtRed;
//             copy[i+1][j+1].rgbtBlue = image[i][j].rgbtBlue;
//             copy[i+1][j+1].rgbtGreen = image[i][j].rgbtGreen;
//         }
//     }

//     //computing new value for each pixel and loading it to it
//     for (i = 1; i < height+1; i++)
//     {
//         for (j = 1; j < width+1; j++)
//         {
//             Gx.rgbtRed = 0;
//             Gx.rgbtBlue = 0;
//             Gx.rgbtGreen = 0;

//             Gy.rgbtRed = 0;
//             Gy.rgbtBlue = 0;
//             Gy.rgbtGreen = 0;

//             for(di = -1; di<=1; di++)
//             {
//                 if(di == -1 || di == 1)
//                     index = -1;
//                 if(di == 0)
//                     index = -2;

//                 for(dj = -1;dj<=1;dj++)
//                 {

//                     Gx.rgbtRed += index*copy[i+di][j+dj].rgbtRed;
//                     Gx.rgbtBlue += index*copy[i+di][j+dj].rgbtBlue;
//                     Gx.rgbtGreen += index*copy[i+di][j+dj].rgbtGreen;

//                     Gy.rgbtRed += index*copy[j+dj][i+di].rgbtRed;
//                     Gy.rgbtBlue += index*copy[j+dj][i+di].rgbtBlue;
//                     Gy.rgbtGreen += index*copy[j+dj][i+di].rgbtGreen;


//                     if(di == -1 || di == 1)
//                         index++;
//                     if(di == 0)
//                         index+= 2;

//                 }

//             }
//             image[i-1][j-1].rgbtRed = round(sqrt((Gx.rgbtRed * Gx.rgbtRed) + (Gy.rgbtRed * Gy.rgbtRed)));
//             image[i-1][j-1].rgbtBlue = round(sqrt((Gx.rgbtBlue * Gx.rgbtBlue) + (Gy.rgbtBlue * Gy.rgbtBlue)));
//             image[i-1][j-1].rgbtGreen = round(sqrt((Gx.rgbtGreen * Gx.rgbtGreen) + (Gy.rgbtGreen * Gy.rgbtGreen)));

//             image[i-1][j-1].rgbtRed = (image[i-1][j-1].rgbtRed > 255)?255 : image[i-1][j-1].rgbtRed;
//             image[i-1][j-1].rgbtBlue = (image[i-1][j-1].rgbtBlue > 255)?255 : image[i-1][j-1].rgbtBlue;
//             image[i-1][j-1].rgbtGreen = (image[i-1][j-1].rgbtGreen > 255)?255 : image[i-1][j-1].rgbtGreen;
//         }
//     }

//     return;
// }

