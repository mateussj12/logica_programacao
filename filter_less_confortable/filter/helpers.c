#include <math.h>

#include "helpers.h"

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for (int index_height = 0; index_height < height; index_height++)
    {
        for (int index_width = 0; index_width < width; index_width++)
        {
            RGBTRIPLE pixel = image[index_height][index_width];

            int avarage = round((pixel.rgbtBlue + pixel.rgbtGreen + pixel.rgbtRed) / 3.00);

            image[index_height][index_width].rgbtBlue = avarage;
            image[index_height][index_width].rgbtGreen = avarage;
            image[index_height][index_width].rgbtRed = avarage;
        }
    }
    return;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for (int index_height = 0; index_height < height; index_height++)
    {
        for (int index_width = 0; index_width < width; index_width++)
        {

            RGBTRIPLE pixel = image[index_height][index_width];

            int originalBlue = pixel.rgbtBlue;
            int originalGreen = pixel.rgbtGreen;
            int originalRed = pixel.rgbtRed;

            int sepiaRed = round(0.393 * originalRed + 0.769 * originalGreen + 0.189 * originalBlue);
            int sepiaGreen = round(0.349 * originalRed + 0.686 * originalGreen + 0.168 * originalBlue);
            int sepiaBlue = round(0.272 * originalRed + 0.534 * originalGreen + 0.131 * originalBlue);

            image[index_height][index_width].rgbtBlue = (sepiaBlue > 255) ? 255 : sepiaBlue;
            image[index_height][index_width].rgbtGreen = (sepiaGreen > 255) ? 255 : sepiaGreen;
            image[index_height][index_width].rgbtRed = (sepiaRed > 255) ? 255 : sepiaRed;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
    for (int index_height = 0; index_height < height; index_height++)
    {
        for (int index_width = 0; index_width < (width / 2); index_width++)
        {
            int blue = image[index_height][index_width].rgbtBlue;
            int green = image[index_height][index_width].rgbtGreen;
            int red = image[index_height][index_width].rgbtRed;

            image[index_height][index_width].rgbtBlue = image[index_height][width - index_width - 1].rgbtBlue;
            image[index_height][index_width].rgbtGreen = image[index_height][width - index_width - 1].rgbtGreen;
            image[index_height][index_width].rgbtRed = image[index_height][width - index_width - 1].rgbtRed;

            image[index_height][width - index_width - 1].rgbtBlue = blue;
            image[index_height][width - index_width - 1].rgbtGreen = green;
            image[index_height][width - index_width - 1].rgbtRed = red;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];

    for (int row = 0; row < height; row++)
    {
        for (int col = 0; col < width; col++)
        {
            int count = 0;
            int rowCoord[] = {row - 1, row, row + 1};
            int colCoord[] = {col - 1, col, col + 1};

            float totalRed = 0, totalGreen = 0, totalBlue = 0;

            for (int index_row = 0; index_row < 3; index_row++)
            {
                for (int index_col = 0; index_col < 3; index_col++)
                {
                    int curRow = rowCoord[index_row];
                    int curCol = colCoord[index_col];

                    if (curRow >= 0 && curRow < height && curCol >= 0 && curCol < width)
                    {
                        RGBTRIPLE pixel = image[curRow][curCol];

                        totalRed = totalRed + pixel.rgbtRed;
                        totalGreen = totalGreen + pixel.rgbtGreen;
                        totalBlue = totalBlue + pixel.rgbtBlue;
                        count++;
                    }
                }
            }
            temp[row][col].rgbtRed = round(totalRed / count);
            temp[row][col].rgbtGreen = round(totalGreen / count);
            temp[row][col].rgbtBlue = round(totalBlue / count);
        }
    }

    //Copy to image
    for (int index_height = 0; index_height < height; index_height++)
    {
        for (int index_width = 0; index_width < width; index_width++)
        {
            image[index_height][index_width] = temp[index_height][index_width];
        }
    }
    return;
}
