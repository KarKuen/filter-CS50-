#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            float averagevalue = (image[x][y].rgbtBlue + image[x][y].rgbtGreen + image[x][y].rgbtRed) / 3.0;
            averagevalue = round(averagevalue);
            image[x][y].rgbtBlue = averagevalue;
            image[x][y].rgbtGreen = averagevalue;
            image[x][y].rgbtRed = averagevalue;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int x = 0; x < height; x ++)
    {
        for (int y = 0; y < width / 2; y++)
        {
            int tempR = image[x][y].rgbtRed;
            image[x][y].rgbtRed = image[x][width - 1 - y].rgbtRed;
            image[x][width - 1 - y].rgbtRed = tempR;

            int tempG = image[x][y].rgbtGreen;
            image[x][y].rgbtGreen = image[x][width - 1 - y].rgbtGreen;
            image[x][width - 1 - y].rgbtGreen = tempG;

            int tempB = image[x][y].rgbtBlue;
            image[x][y].rgbtBlue = image[x][width - 1 - y].rgbtBlue;
            image[x][width - 1 - y].rgbtBlue = tempB;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    int arrayR[height * width];
    int arrayG[height * width];
    int arrayB[height * width];
    int counter = 0;

    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            int sumR = 0;
            int sumG = 0;
            int sumB = 0;
            float count = 0;
            int averageR = 0;
            int averageG = 0;
            int averageB = 0;

            // for grid of size 3
            for (int i = -1; i < 2; i++)
            {
                for (int j = -1; j < 2; j++)
                {
                    // if theres a row above/below AND if it isnt more than the left and right extremems
                    if ((((x + i) >= 0) && ((x + i) <= (height - 1))) && ((y + j) >= 0) && ((y + j) <= (width - 1)))
                    {
                        sumR = sumR + image[x + i][y + j].rgbtRed;
                        sumG = sumG + image[x + i][y + j].rgbtGreen;
                        sumB = sumB + image[x + i][y + j].rgbtBlue;
                        count++;
                    }
                }
            }

            averageR = round(sumR / count);
            averageG = round(sumG / count);
            averageB = round(sumB / count);

            // Stores average in an 3 different arrays
            arrayR[counter] = averageR;
            arrayG[counter] = averageG;
            arrayB[counter] = averageB;

            counter++;
            // ITS CHANGING THE VALUE HENCE, THE SUBSEQUENT VALUE USES THE NEWLY CHANGED VALUE

        }
    }

    int counting = 0;

    for (int a = 0; a < height; a++)
    {
        for (int b = 0; b < width; b++)
        {
            image[a][b].rgbtRed = arrayR[counting];
            image[a][b].rgbtGreen = arrayG[counting];
            image[a][b].rgbtBlue = arrayB[counting];
            counting++;
        }
    }

    return;
}

// Detect edges
void edges(int height, int width, RGBTRIPLE image[height][width])
{
    int Gx[] = {-1, 0, 1, -2, 0, 2, -1, 0, 1};
    int Gy[] = {-1, -2, -1, 0, 0, 0, 1, 2, 1};

    int arrayR[height * width];
    int arrayG[height * width];
    int arrayB[height * width];

    int count = 0;

    for (int x = 0; x < height; x++)
    {
        for (int y = 0; y < width; y++)
        {
            int counter = 0;

            int Rtotalx = 0;
            int Gtotalx = 0;
            int Btotalx = 0;

            int Rtotaly = 0;
            int Gtotaly = 0;
            int Btotaly = 0;

            int GxGyRed = 0;
            int GxGyGreen = 0;
            int GxGyBlue = 0;

            // for a grid of size 3
            for (int i = -1; i < 2; i++)
            {
                for (int j = -1; j < 2; j++)
                {
                    // if theres a row above/below AND if it isnt more than the left and right extremems
                    if ((((x + i) >= 0) && ((x + i) <= (height - 1))) && ((y + j) >= 0) && ((y + j) <= (width - 1)))
                    {
                        Rtotalx = Rtotalx + (image[x + i][y + j].rgbtRed * Gx[counter]);
                        Gtotalx = Gtotalx + (image[x + i][y + j].rgbtGreen * Gx[counter]);
                        Btotalx = Btotalx + (image[x + i][y + j].rgbtBlue * Gx[counter]);

                        Rtotaly = Rtotaly + (image[x + i][y + j].rgbtRed * Gy[counter]);
                        Gtotaly = Gtotaly + (image[x + i][y + j].rgbtGreen * Gy[counter]);
                        Btotaly = Btotaly + (image[x + i][y + j].rgbtBlue * Gy[counter]);

                    }
                    counter++;
                }
            }
            // greater than 255
            GxGyRed = round(sqrt((Rtotalx * Rtotalx) + (Rtotaly * Rtotaly)));
            GxGyGreen = round(sqrt((Gtotalx * Gtotalx) + (Gtotaly * Gtotaly)));
            GxGyBlue = round(sqrt((Btotalx * Btotalx) + (Btotaly * Btotaly)));
            // red
            if (GxGyRed > 255)
            {
                arrayR[count] = 255;
            }
            else
            {
                arrayR[count] = GxGyRed;
            }
            // green
            if (GxGyGreen > 255)
            {
                arrayG[count] = 255;
            }
            else
            {
                arrayG[count] = GxGyGreen;
            }
            // blue
            if (GxGyBlue > 255)
            {
                arrayB[count] = 255;
            }
            else
            {
                arrayB[count] = GxGyBlue;
            }

            count++;

        }
    }

    int counting = 0;
    for (int a = 0; a < height; a++)
    {
        for (int b = 0; b < width; b++)
        {
            image[a][b].rgbtRed = arrayR[counting];
            image[a][b].rgbtGreen = arrayG[counting];
            image[a][b].rgbtBlue = arrayB[counting];
            counting++;
        }
    }
    return;
}
