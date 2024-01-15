#include "helpers.h"
#include <math.h>

void swap(RGBTRIPLE *x, RGBTRIPLE *y);





int limit (int RGB)
{
    if (RGB > 0xFF)
    {
        RGB = 0xFF;

    }
    return RGB;
}
// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{

    for (int i=0; i<height; i++)
    {
        for (int j=0; j<width; j++)
        {

            double average = (image[i][j].rgbtRed + image[i][j].rgbtGreen + image[i][j].rgbtBlue)/3.0;
            RGBTRIPLE gray;
            gray.rgbtRed = round(average);
            gray.rgbtGreen = round(average);
            gray.rgbtBlue = round(average);
            image[i][j].rgbtBlue = gray.rgbtBlue;
            image[i][j].rgbtRed = gray.rgbtRed;
            image[i][j].rgbtGreen = gray.rgbtGreen;


        }



    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{


    for (int i=0; i<height; i++)
    {
        for (int j=0; j<width; j++)
        {
        RGBTRIPLE sepia;

        float sepiaRed = (image[i][j].rgbtRed * .393) + (image[i][j].rgbtGreen * .769) + (image[i][j].rgbtBlue *.189);
        float sepiaGreen = (image[i][j].rgbtRed * .349) + (image[i][j].rgbtGreen * .686) + (image[i][j].rgbtBlue *.168);
        float sepiaBlue = (image[i][j].rgbtRed * .272) + (image[i][j].rgbtGreen * .534) + (image[i][j].rgbtBlue *.131);

        if (sepiaRed > 255)
        {
            sepiaRed = 255;
        }
        if (sepiaGreen > 255)
        {
            sepiaGreen = 255;
        }
        if (sepiaBlue > 255)
        {
            sepiaBlue = 255;
        }

        sepia.rgbtRed = round(sepiaRed);
        image[i][j].rgbtRed = sepia.rgbtRed;
        sepia.rgbtGreen = round(sepiaGreen);
        image[i][j].rgbtGreen = sepia.rgbtGreen;
        sepia.rgbtBlue = round(sepiaBlue);
        image[i][j].rgbtBlue = sepia.rgbtBlue;

        }


     }

    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int i=0; i<height; i++)
    {
        for (int j=0; j<width/2; j++)
        {
            swap(&image[i][j], &image[i][width-j-1]);
        }


    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{

     RGBTRIPLE copy[height][width];
     for (int i = 0; i < height; i++)
     {
        for (int j = 0; j < width; j++)
        {
            copy[i][j] = image[i][j];
        }
     }

     for (int i=0; i<height; i++)
    {
        for (int j=0; j<width; j++)
        {
        int Red = 0;
        int Blue = 0;
        int Green = 0;
        double count = 0;

             for (int col=i-1; col<=i+1; col++)
             {

                    for (int row=j-1; row<=j+1; row++)
                    {
                        if  (col < 0  || col > height-1)
                        {
                            continue;
                        }
                        if (row < 0  || row > width-1)
                        {
                            continue;
                        }
                            Red += copy[col][row].rgbtRed;
                            Blue += copy[col][row].rgbtBlue;
                            Green += copy[col][row].rgbtGreen;
                            count+=1;

                    }
              }

                image[i][j].rgbtRed = round(Red/count);
                image[i][j].rgbtBlue = round(Blue/count);
                image[i][j].rgbtGreen = round(Green/count);



             }
         }



    return;
}


void swap(RGBTRIPLE *x, RGBTRIPLE  *y)
{

RGBTRIPLE temp = *x;
*x = *y;
*y = temp;


}